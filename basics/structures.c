#include <stdio.h>
#include <stdbool.h>

#define MAX_IDS 32
#define MAX_EMPLOYEES 1000

struct Employee_t
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

    for (int i = 0; i < MAX_EMPLOYEES; i ++)
    {
        employees[i].id = i;
        employees[i].income = 10 * i;
        employees[i].isManager = false;
    }

    printf("%f\n", employees[10].income);

    return 0;
}
