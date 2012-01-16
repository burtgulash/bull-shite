#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))


typedef struct {
    FILE *file;
    char *name;
    int lines, words, chars;
} file_counter;


int dec_log(int x)
{
    int l = 0;

    while (x) {
        l++;
        x /= 10;
    }

    return (l);
}


int main(int argc, char **argv)
{
    file_counter **files;
    int exit_code;
    int i;                      /* file iterator */
    int j;
    int c;                      /* file char iterator */
    int useStdin;               /* no file provided -> use stdin */
    int inWord;                 /* is in word flag */
    int maxChars;
    int maxWords;
    int maxLines;
    int printChars;
    int printLines;
    int printWords;

    files = (file_counter **) malloc(sizeof(file_counter *) * (argc + 1));
    i = 0;
    useStdin = 1;
    maxChars = 0;
    maxWords = 0;
    maxLines = 0;
    exit_code = 0;
    printChars = 0;
    printLines = 0;
    printWords = 0;


    /* Parse flags and input files. */
    for (argv++, argc--; argc--; argv++) {
        if ((*argv)[0] == '-') {
            switch ((*argv)[1]) {
            case 'l':
                printLines = 1;
                break;
            case 'w':
                printWords = 1;
                break;
            case 'c':
                printChars = 1;
                break;
            }
        } else {
            files[i] = (file_counter *) malloc(sizeof(file_counter));
            files[i]->file = fopen(*argv, "rb");
            files[i]->name = *argv;
            files[i]->lines = 0;
            files[i]->words = 0;
            files[i]->chars = 0;

            if (files[i]->file == NULL) {
                perror("Can't open file.");
                return 1;
            }
            useStdin = 0;
            i++;
        }
    }

    /* Turn all printing on if none was specified */
    if (!printChars && !printWords && !printLines) {
        printChars = 1;
        printWords = 1;
        printLines = 1;
    }

    if (useStdin) {
        files[0] = (file_counter *) malloc(sizeof(file_counter));
        files[0]->file = stdin;
        files[0]->lines = 0;
        files[0]->words = 0;
        files[0]->chars = 0;

        i = 1;
    }

    for (j = 0; j < i; j++) {
        inWord = 0;
        while ((c = getc(files[j]->file)) != EOF) {
            files[j]->chars++;
            if (c == '\n')
                files[j]->lines++;
            if (isspace(c)) {
                if (inWord)
                    files[j]->words++;
                inWord = 0;
            } else
                inWord = 1;
        }
    }


    for (j = 0; j < i; j++) {
        maxChars = MAX(maxChars, files[j]->chars);
        maxLines = MAX(maxLines, files[j]->lines);
        maxWords = MAX(maxWords, files[j]->words);
    }

    maxChars = dec_log(maxChars);
    maxLines = dec_log(maxLines);
    maxWords = dec_log(maxWords);


    for (j = 0; j < i; j++) {
        if (printLines)
            printf("%*d ", maxLines, files[j]->lines);
        if (printWords)
            printf("%*d ", maxWords, files[j]->words);
        if (printChars)
            printf("%*d ", maxChars, files[j]->chars);
        if (i > 1)
            printf("%s", files[j]->name);
        printf("\n");

        fclose(files[j]->file);
        free(files[j]);
    }

    free(files);
    return (exit_code);
}
