#include <stdio.h>
#include <stdbool.h>

#define MAX_EMPLOYEES 1000

struct __attribute__((__packed__)) Employee_t
{
   int id;
   char firstname[64];
   char lastname[64];
   float income;
   bool isManager;
};

int main()
{
    struct Employee_t employees[MAX_EMPLOYEES];

    printf("Size of employee: %ld\n", sizeof(struct Employee_t));

    return 0;
}
