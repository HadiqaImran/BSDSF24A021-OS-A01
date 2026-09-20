#include <stdio.h>
#include <stdlib.h>
#include "../include/mystrfunctions.h"
#include "../include/myfilefunctions.h"

int main() {
    printf("--- Testing String Functions ---\n");

    char str1[50] = "Hello";
    printf("mystrlen(\"%s\") = %d\n", str1, mystrlen(str1));

    char str2[50];
    mystrcpy(str2, str1);
    printf("mystrcpy result: %s\n", str2);

    char str3[10];
    mystrncpy(str3, "HelloWorld", 5);
    printf("mystrncpy (n=5): %s\n", str3);

    char str4[50] = "Hello, ";
    mystrcat(str4, "World!");
    printf("mystrcat result: %s\n", str4);

    printf("\n--- Testing File Functions ---\n");

    FILE* fp = fopen("test.txt", "r");
    if (fp == NULL) {
        printf("Could not open test.txt\n");
        return 1;
    }

    int lines, words, chars;
    wordCount(fp, &lines, &words, &chars);
    printf("Lines: %d, Words: %d, Chars: %d\n", lines, words, chars);

    rewind(fp);
    char** matches;
    int matchCount = mygrep(fp, "test", &matches);
    printf("Found %d matching lines containing 'test':\n", matchCount);
    for (int i = 0; i < matchCount; i++) {
        printf("  %s", matches[i]);
        free(matches[i]);
    }
    free(matches);

    fclose(fp);
    return 0;
}
