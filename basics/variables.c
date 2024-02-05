#include <stdio.h>

#define MAX_PERSONS 1024

// Global scope vars
int g_NumPersons = 0;

int main()
{
    // type name = initial value;
    int personID = 0;
    personID += 1;

    {
        int personID = 0;
        personID += 1;
    }

    #ifdef DEBUG
    printf("WE ARE IN DEBUG MODE: %s:%d", __FILE__, __LINE__);
    #endif
}
