#include <stdio.h>

// return_type name_of_func(list of args) { }

//int initialize_employee_structure(Employee *e)
//{
    // initialize a struct that
    // contains employee data
//}

int add(int x, int y)
{
    return x + y;
}

int main(int argc, char *argv[])
{
    int other_int = add(1, 2);
    printf("%d\n", other_int);

    return 0;
}
