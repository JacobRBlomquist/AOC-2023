#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const char *nums[] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
};
/**
 * Loop through each line.
 * Then loop through each character.
 * If it is a digit, greedily store in the `last` digit.
 * If we haven't set the first digit, set it.
 */
int solvePart1(const char *contents, int *result)
{
    int length = strlen(contents);
    char *contentsCopy = malloc(length);
    memcpy(contentsCopy, contents, length);

    int total = 0;

    char *line = strtok(contentsCopy, "\n");
    while (line != NULL)
    {
        //|49 - 57|
        char first = ' ', last;
        int lineLength = strlen(line);
        for (int i = 0; i < lineLength; i++)
        {
            char curChar = line[i];

            // either 1,2,3,4,5,6,7,8,9 in ascii
            if (((int)curChar) >= 49 && ((int)curChar) <= 57)
            {
                if (first == ' ')
                {
                    first = curChar;
                }
                last = curChar;
            }
        }
        int value = (((int)first) - 48) * 10 + (((int)last) - 48);
        total += value;
        line = strtok(NULL, "\n");
    }

    free(contentsCopy);
    *result = total;
    return 0;
}

int extractNumber(const char *string, int *result)
{
    int length = strlen(string);
    // digit i.e. 1,2,3,4,5,6,7,8,9
    if (((int)string[0]) >= 49 && ((int)string[0]) <= 57)
    {
        *result = ((int)string[0]) - 48;
        return 0;
    }

    // check for string
    for (int i = 0; i < 9; i++)
    {
        const char *curNumString = nums[i];
        int numLength = strlen(curNumString);
        if (length < numLength)
            continue;
        bool found = true;
        for (int j = 0; j < numLength; j++)
        {
            if (string[j] != curNumString[j])
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            *result = i + 1;
            return 0;
        }
    }

    return -1;
}

int solvePart2(const char *contents, int *result)
{
    int length = strlen(contents);
    char *contentsCopy = malloc(length);
    memcpy(contentsCopy, contents, length);

    int total = 0;

    char *line = strtok(contentsCopy, "\n");
    while (line != NULL)
    {
        //|49 - 57|
        char first = ' ', last;
        int lineLength = strlen(line);
        for (int i = 0; i < lineLength; i++)
        {

            int digit;
            if (extractNumber(line + i, &digit) == 0)
            {
                if (first == ' ')
                {
                    first = (char)(digit + 48);
                }
                last = (char)(digit + 48);
            }
        }
        int value = (((int)first) - 48) * 10 + (((int)last) - 48);
        total += value;
        line = strtok(NULL, "\n");
    }

    free(contentsCopy);
    *result = total;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s file-to-process\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open file.");
        return 1;
    }

    // get file size
    fseek(file, 0, SEEK_END);
    long fileLength = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *contents = malloc(fileLength);
    fread(contents, fileLength, 1, file);
    fclose(file);

    int result1, result2;
    solvePart1(contents, &result1);
    solvePart2(contents, &result2);
    printf("Part1: %d\n", result1);
    printf("Part2: %d\n", result2);

    free(contents);
}