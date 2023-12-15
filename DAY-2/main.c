#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int readfile(char *filename, char **output)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return -1;

    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = malloc(sizeof(char) * length);
    if (buffer == NULL)
    {
        return -1;
        fclose(file);
    }

    fread(buffer, length, 1, file);
    fclose(file);
    *output = buffer;

    return 0;
}

char **splitOnChar(char *input, char *delimiter)
{
    size_t length = strlen(input);
    char *copy = malloc(sizeof(char) * (length + 1));
    memcpy(copy, input, length);
    copy[length] = '\0';

    // get number of tokens
    int numTokens = 1;
    for (size_t i = 0; copy[i] != '\0'; i++)
    {
        if (copy[i] == delimiter[0])
            numTokens++;
    }

    char **buffer = malloc(sizeof(char *) * (numTokens + 1));

    char *current = strtok(copy, delimiter);
    int index = 0;
    while (current != NULL)
    {
        buffer[index++] = current;
        current = strtok(NULL, delimiter);
    }
    buffer[numTokens] = NULL;
    return buffer;
}

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        printf("Usage: %s path-to-input-file", argv[0]);
        return -1;
    }

    char *contents;
    if (readfile(argv[1], &contents) != 0)
    {
        return -1;
    }

    char **tokens = splitOnChar(contents, "\n");

    int total = 0;
    int totalPower = 0;

    for (int i = 0; tokens[i] != NULL; i++)
    {
        int gameNumber = 0;
        int num = 0;
        sscanf(tokens[i], "Game %d: %n", &gameNumber, &num);
        printf("%s -> Game: %d\n", tokens[i], gameNumber);

        char **rounds = splitOnChar(tokens[i] + num, ";");
        int validGame = 1;
        int minRed = 0;
        int minGreen = 0;
        int minBlue = 0;

        for (int j = 0; rounds[j] != NULL; j++)
        {
            printf("\tRound: %s\n", rounds[j]);
            char **cubes = splitOnChar(rounds[j], ",");
            int validRound = 1;
            for (int k = 0; cubes[k] != NULL; k++)
            {

                // 12 red cubes, 13 green cubes, and 14 blue
                printf("\t\tCubes: %s", cubes[k]);
                int cubeVal = 0;
                sscanf(cubes[k], "%d", &cubeVal);

                char *red = strstr(cubes[k], "red");
                char *green = strstr(cubes[k], "green");
                char *blue = strstr(cubes[k], "blue");

                if (red != NULL)
                {
                    if (minRed < cubeVal)
                        minRed = cubeVal;
                    if (cubeVal > 12)
                        validRound = 0;
                    printf(" -- R");
                }
                if (green != NULL)
                {
                    if (minGreen < cubeVal)
                        minGreen = cubeVal;
                    if (cubeVal > 13)
                        validRound = 0;
                    printf(" -- G");
                }
                if (blue != NULL)
                {
                    if (minBlue < cubeVal)
                        minBlue = cubeVal;
                    if (cubeVal > 14)
                        validRound = 0;
                    printf(" -- B");
                }

                printf(" %d\n", cubeVal);
            }
            if (validRound == 0)
            {
                validGame = 0;
            }
            else
            {
                printf("\tVALID ROUND\n");
            }

            free(cubes);
        }
        if (validGame == 1)
            total += gameNumber;

        printf("Game %d Power: R%d|G%d|B%d %d\n", gameNumber, minRed, minGreen, minBlue, minRed * minGreen * minBlue);
        totalPower += minRed * minGreen * minBlue;

        free(rounds);
    }

    printf("RESULT %d\n", total);
    printf("Total Power %d\n", totalPower);

    free(tokens);
    free(contents);

    return 0;
}