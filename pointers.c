#include <stdio.h>
#include <stdbool.h>

struct employee_t
{
    int id;
    int income;
    bool staff;
};

void initialize_employee(struct employee_t *e)
{
    e->id = 0;
    e->income = 0;
    e->staff  =false;

    return;
}

int main()
{
    int x = 3;

    // Create a pointer to the address of x on the stack
    int *px = &x;

    // De-reference a pointer by using * again to get the value of x
    printf("%d\n", *px);

    // This prints the address
    printf("%p\n", px);

    struct employee_t Ralph;

    initialize_employee(&Ralph);

    printf("Ralph income: %d\n", Ralph.income);
}
