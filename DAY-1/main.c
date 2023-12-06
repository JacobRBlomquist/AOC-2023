#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const char *digits = "123456789";

/**
 * Loop through each line.
 * Then loop through each character.
 * If it is a digit, greedily store in the `last` digit.
 * If we haven't set the first digit, set it.
 */
int solvePart1(const char *contents, int *result)
{
    char *copy = malloc(strlen(contents));
    memcpy(copy, contents, strlen(contents));

    char *currentLine = strtok(copy, "\n");
    int accum = 0;
    while (currentLine != NULL)
    {
        int length = (int)strlen(currentLine);
        char twoDigit[2] = "\0\0";

        for (int i = 0; i < length; i++)
        {
            char cur = currentLine[i];

            for (int j = 0; j < 10; j++)
            {
                if (cur == digits[j])
                {
                    if (twoDigit[0] == 0)
                        twoDigit[0] = cur;
                    twoDigit[1] = cur;
                }
            }
        }
        // printf("%s -> %s -> %d\n", currentLine, twoDigit, atoi(twoDigit));
        accum += atoi(twoDigit);

        currentLine = strtok(NULL, "\n");
    }

    *result = accum;
    free(copy);
    return 0;
}

typedef struct node
{
    struct node *children[26];
    bool isTerminal;
    char character;
    int terminalValue;
} node;

node *initTrie()
{
    node *root = malloc(sizeof(node));
    for (int i = 0; i < 26; i++)
        root->children[i] = 0;

    root->isTerminal = false;
    root->terminalValue = -1;
    return root;
}

int insertStringTrie(node *root, const char *string, int val)
{
    int length = strlen(string);
    node *current = root;
    for (int i = 0; i < length; i++)
    {
        char currentChar = string[i];
        int index = currentChar - 97;
        if (current->children[index] == 0)
        {
            node *newNode = initTrie();
            newNode->character = currentChar;
            current->children[index] = newNode;
            current = newNode;
        }
        else
        {
            current = current->children[index];
        }
    }
    current->isTerminal = true;
    current->terminalValue = val;
    return 0;
}

int freeTrie(node *root)
{
    if (!root->isTerminal)
    {
        for (int i = 0; i < 26; i++)
        {
            if (root->children[i] != 0)
                freeTrie(root->children[i]);
        }
    }

    free(root);

    return 0;
}

int walkTrieSubstring(node *root, const char *string, int *output)
{
    int length = strlen(string);
    int index = 0;
    node *current = root;
    while (!current->isTerminal)
    {
        int curIndex = string[index] - 97;
        if (curIndex < 0 || curIndex > 26)
        {
            return -1;
        }
        if (current->children[curIndex] != 0)
        {
            current = current->children[curIndex];
            index++;
            if (index > length)
            {
                return -1;
            }
            continue;
        }
        else
        {
            return -1;
        }
    }
    *output = current->terminalValue;
    return 0;
}

int solvePart2(const char *contents, int *result)
{
    char *copy = malloc(strlen(contents));
    memcpy(copy, contents, strlen(contents));

    // Build Trie
    node *trie = initTrie();
    insertStringTrie(trie, "one", 1);
    insertStringTrie(trie, "two", 2);
    insertStringTrie(trie, "three", 3);
    insertStringTrie(trie, "four", 4);
    insertStringTrie(trie, "five", 5);
    insertStringTrie(trie, "six", 6);
    insertStringTrie(trie, "seven", 7);
    insertStringTrie(trie, "eight", 8);
    insertStringTrie(trie, "nine", 9);

    char *currentLine = strtok(copy, "\n");

    int accum = 0;
    while (currentLine != NULL)
    {
        int length = (int)strlen(currentLine);
        char twoDigit[2] = "\0\0";
        for (int i = 0; i < length; i++)
        {
            char cur = currentLine[i];
            // Check if number
            bool foundDigit = false;

            for (int j = 0; j < 10; j++)
            {
                if (cur == digits[j])
                {
                    if (twoDigit[0] == 0)
                        twoDigit[0] = cur;
                    twoDigit[1] = cur;
                    foundDigit = true;
                    break;
                }
            }
            if (foundDigit)
                continue;

            // Check for number as word
            // Walk the trie
            int foundNumber = -1;
            if (walkTrieSubstring(trie, &currentLine[i], &foundNumber) == 0)
            {
                if (twoDigit[0] == 0)
                    twoDigit[0] = (char)(foundNumber + 48);
                twoDigit[1] = (char)(foundNumber + 48);
            }
        }
        // printf("%s -> %s -> %d\n", currentLine, twoDigit, atoi(twoDigit));
        accum += atoi(twoDigit);

        currentLine = strtok(NULL, "\n");
    }

    *result = accum;
    freeTrie(trie);
    free(copy);
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