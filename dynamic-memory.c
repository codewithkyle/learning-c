#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_EMPLOYEES 1000

struct employee_t
{
    int id;
    int income;
    bool staff;
};

void initialize_employee(struct employee_t *e, int id)
{
    e->id = id;
    e->income = 0;
    e->staff = false;

    return;
}

int main()
{
    // number read from somewhere (disc?)
    int n = 4;

    // Allocates size of employee * number of employees into an employee pointer
    struct employee_t *employees = malloc(sizeof(struct employee_t)*n);

    // memory allocation can fail...
    if (employees == NULL)
    {
        printf("The allocator failed\n");
        return -1;
    }

    // We then pass in a reference to ??? into our initalize func
    // Q: how does it know it's an array?
    initialize_employee(&employees[0], 0);

    // Well, this worked so I guess when you malloc from 
    // n number of structs it lets you access the instance of the struct via its index
    initialize_employee(&employees[1], 1);

    printf("%d\n", employees[1].id);

    // Frees up allocated memory
    free(employees);

    // Prevents us from 'use after free' issues
    employees = NULL;
}
