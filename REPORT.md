
## Feature 2: Multi-file Project using Make Utility

**Q1: Explain the linking rule `$(TARGET): $(OBJECTS)`. How does it differ from a rule that links against a library?**

This rule basically tells make that my executable depends on all the object files, so if any .o file changes, make knows it needs to relink everything into the target again. The recipe just throws all the object files at gcc and it links them into one binary - whatever code is in those .o files gets included, whether it's actually being used or not. This is different from linking against a library, which is what I'll do in Feature 3. When you link against a library instead of raw object files, the linker is smarter about it - it only pulls in the specific functions it actually needs to resolve, not the whole library blindly. So object files get dumped in completely, but libraries get picked from selectively.

**Q2: What is a git tag and why is it useful? Difference between simple and annotated tags?**

A git tag is just a name attached to one specific commit, and unlike a branch it doesn't move forward when you keep committing - it stays stuck on that one point forever. It's useful because it lets you mark a version of your project that actually matters, like "this is v1.0," so you can always go back to that exact state later without having to remember a commit hash. There are two kinds: a lightweight tag is just a pointer to a commit with nothing else attached, made with a plain `git tag name`. An annotated tag (`git tag -a`) is more like a mini commit itself - it stores who made it, when, and a message explaining it. GitHub Releases actually require an annotated tag, which is why I used `-a` for mine.

**Q3: What is the purpose of a GitHub Release? Why attach binaries?**

A GitHub Release takes one of your tags and turns it into something a normal user can actually download and use, instead of them having to clone your whole repo and build it themselves. It comes with a title, description, and you can attach files to it. Attaching the compiled binary (bin/client in my case) matters because it means someone without a C compiler or any of my Makefile setup can just download the file and run it directly - it's the difference between giving someone your source code versus giving them working software.
