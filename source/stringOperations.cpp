#include <stringOperations.h>

//Searches for a single or sequence of strings (and returns the position of the first char)
char strStr(const char *string, unsigned int substr)
{
    unsigned int length = strlen(string);
}

char getWord(const char *string, unsigned int word)
{

}

char getWords(const char *string, unsigned int word)
{

}

//Reverses a string sub-char wise
char subStrReverses(const char *string)
{
    unsigned int length = strlen(string);
    unsigned int index = 0;
    char newString;

    for (index = 0; index < length; index++)
    {
        newString + string[index];
    }
    return newString;
}

char *subStrReverse(const char *string)
{
    unsigned int length = strlen(string);
    unsigned int index = 0;
    char *newString;

    for (index = 0; index < length; index++)
    {
        newString[index] + string[index];
    }
    return newString;
}
