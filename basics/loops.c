#include <stdio.h>

#define MAX_IDS 30

int main()
{
    int ids[MAX_IDS] = {0};

    for (int i = 0; i < MAX_IDS; i++)
    {
        ids[i] = i;
        printf("%d\n", ids[i]);
    }

    return 0;
}
