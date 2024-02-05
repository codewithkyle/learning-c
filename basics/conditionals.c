#include <stdio.h>

int main()
{
    int temp;
    printf("Enter the temperature: ");
    scanf("%d", &temp);

    if (temp >= 70)
    {
        printf("dang bruther, its hot\n");
    }
    else if (temp >= 30)
    {
        printf("dang bruther, its mild\n");
    }
    else 
    {
        printf("dang bruther, its cold\n");
    }

    return 0;
}
