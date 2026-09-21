# Programming Assignment 1 - Report

**Name:** Hadiqa Imran
**Roll Number:** BSDSF24A021
**Repository:** https://github.com/HadiqaImran/BSDSF24A021-OS-A01

This report documents my work building `libmyutils`, a C utility library, across multiple stages: a basic multi-file build, a static library, a dynamic library, and finally man pages with a system install target. Each section below answers the report questions for that feature.


## Feature 2: Multi-file Project using Make Utility

**Q1: Explain the linking rule `$(TARGET): $(OBJECTS)`. How does it differ from a rule that links against a library?**

This rule basically tells make that my executable depends on all the object files, so if any .o file changes, make knows it needs to relink everything into the target again. The recipe just throws all the object files at gcc and it links them into one binary - whatever code is in those .o files gets included, whether it's actually being used or not. This is different from linking against a library, which is what I'll do in Feature 3. When you link against a library instead of raw object files, the linker is smarter about it - it only pulls in the specific functions it actually needs to resolve, not the whole library blindly. So object files get dumped in completely, but libraries get picked from selectively.

**Q2: What is a git tag and why is it useful? Difference between simple and annotated tags?**

A git tag is just a name attached to one specific commit, and unlike a branch it doesn't move forward when you keep committing - it stays stuck on that one point forever. It's useful because it lets you mark a version of your project that actually matters, like "this is v1.0," so you can always go back to that exact state later without having to remember a commit hash. There are two kinds: a lightweight tag is just a pointer to a commit with nothing else attached, made with a plain `git tag name`. An annotated tag (`git tag -a`) is more like a mini commit itself - it stores who made it, when, and a message explaining it. GitHub Releases actually require an annotated tag, which is why I used `-a` for mine.

**Q3: What is the purpose of a GitHub Release? Why attach binaries?**

A GitHub Release takes one of your tags and turns it into something a normal user can actually download and use, instead of them having to clone your whole repo and build it themselves. It comes with a title, description, and you can attach files to it. Attaching the compiled binary (bin/client in my case) matters because it means someone without a C compiler or any of my Makefile setup can just download the file and run it directly - it's the difference between giving someone your source code versus giving them working software.

## Feature 3: Creating and using Static Library

**Q1: Compare the Makefile from Part 2 and Part 3. What are the key differences?**

In Part 2's Makefile, the target executable depended directly on all three object files and linked them together in one gcc command. In Part 3 I added a new rule that builds lib/libmyutils.a from just the two utility object files (mystrfunctions.o and myfilefunctions.o) using ar rcs, and I introduced an AR variable for that. The executable's rule changed too - now client_static only depends on main.o and the library itself, and instead of listing object files to link, it uses -L../lib to tell the linker where to find the library and -lmyutils to actually link against it. So instead of one flat linking step, there's now a separate library-building step in between.

**Q2: What is the purpose of the ar command? Why is ranlib often used immediately after it?**

ar is used to create and manage archive files, which in this context means bundling multiple .o files into a single static library (.a file). It basically packs the object files together into one archive. ranlib is used to generate or update the index inside that archive - the index maps which symbols (function names) live in which object file, so the linker can quickly find what it needs instead of scanning through every object file in the archive one at a time. I actually used the -s flag with ar (ar rcs) instead of running ranlib separately, since -s tells ar to generate that same index itself as part of the same command.

**Q3: When you run nm on client_static, are the symbols for functions like mystrlen present? What does this tell you?**

Yes - running nm bin/client_static | grep mystrlen shows mystrlen listed with a T symbol type, meaning it's defined and present in the executable's actual code section. This confirms that static linking physically copies the machine code of every function it needs straight from the library into the final executable at link time. That's different from dynamic linking, where the executable would only keep a reference to the function and look it up in a separate shared library file at runtime instead of containing the code itself.

## Feature 4: Creating and using Dynamic Library

**Q1: What is Position-Independent Code (-fPIC) and why is it a fundamental requirement for creating shared libraries?**

Position-Independent Code is machine code that doesn't assume it'll be loaded at one fixed memory address - it can run correctly no matter where in memory it actually ends up. This matters for shared libraries specifically because a .so file can get loaded into many different programs at once, and each of those programs might load it at a different memory address depending on what else is already using memory at that time. Without -fPIC, the code would have hardcoded assumptions about its own address that would break the moment it got loaded somewhere else. That's why I had to compile separate _pic.o versions of mystrfunctions.c and myfilefunctions.c specifically for the .so build, instead of reusing the regular object files from the static build.

**Q2: Explain the difference in file size between your static and dynamic clients. Why does this difference exist?**

In theory, a statically linked executable should be noticeably bigger than a dynamically linked one, because the static version physically copies all the library's code into the executable itself, while the dynamic version just keeps a reference to the shared library and loads its code at runtime instead. In my case the two ended up close in size since libmyutils is a really small library, so the overhead of the dynamic linking metadata roughly cancels out the space saved - but with a bigger library the difference would show up clearly, since every program using it statically would carry its own full copy of the code, while programs using it dynamically would all share the exact same one copy in memory.

**Q3: What is the LD_LIBRARY_PATH environment variable? Why was it necessary, and what does this tell you about the loader's responsibilities?**

LD_LIBRARY_PATH is an environment variable that tells the dynamic loader extra folders to search when looking for shared libraries at runtime, in addition to the default system locations like /lib and /usr/lib. I needed to set it because my custom libmyutils.so lives inside my own project folder, which isn't a location the loader checks by default - without it, client_dynamic failed immediately with a "cannot open shared object file" error, even though the program itself compiled and linked successfully. This shows that with dynamic linking, the linker's job at compile time is only to record that a dependency exists - it's the operating system's dynamic loader that's actually responsible for finding and loading the real library code at the moment the program runs, which is a completely separate step from linking.
