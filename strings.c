#include <stdio.h>

#define MAX_IDS 32

int main()
{
    int ids[MAX_IDS] = {0,1,2};

    char mystr[] = {'h','e','l','l','o', 0}; // 0 is the null terminator
    char *myotherstr = "world"; // null terminator is automatically added

    printf("%s\n", mystr);

    //strcpy(destPtr, srcPtr);
    //strncpy(destPtr, srcPtr, n);
}
