#include <stdio.h>

#define MAX_IDS 32

int main()
{
    int ids[MAX_IDS] = {0,1,2};

    printf("%d\n", ids[0]);

    ids[3] = 0x41;

    printf("%d\n", ids[3]);
}
