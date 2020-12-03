#include <stdbool.h>
#include <stdio.h>

int main()
{
    FILE* file = fopen("../test2/text.txt", "r");
    if (file == NULL) {
        printf("program couldn't open the file");
        return -1;
    }

    char bufferFirst = '0';
    char bufferSecond = '0';

    bool findMultilineComment = false;
    bool isComment = false;

    while (bufferSecond != EOF || bufferFirst != EOF) {
        bufferFirst = fgetc(file);
        if (bufferFirst == '\n') {
            isComment = false;
        }
        if (isComment && !findMultilineComment) {
            printf("%c", bufferFirst);
        }
        if (bufferFirst == '/' && bufferSecond == '/' && !findMultilineComment) {
            isComment = true;
            printf("//");
        }
        if (bufferFirst == '*' && bufferSecond == '/') {
            findMultilineComment = true;
        }
        if (bufferFirst == '/' && bufferSecond == '*' && findMultilineComment) {
            findMultilineComment = false;
        }
        if (bufferFirst != '\n') {
            bufferSecond = bufferFirst;
        }
        if (bufferFirst == '\n') {
            printf("\n");
            bufferSecond = '0';
        }
    }

    return 0;
}
