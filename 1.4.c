#include <stdio.h> 

int main() 
{
    int a, b, c, d; 
    a = b = c = d = 0;
    printf("Введите число: ");
    scanf("%d", &a);
    printf("Введите число для замены: ");
    scanf("%d", &b);

    for (int i = 31; i >= 0; i--) 
    {
        printf("%d", (a >> i) & 1);
    }

    a = (a & 0xFFFF00FF);
    a = (a ^ (b << 8));

    printf("\n");
    for (int i = 31; i >= 0; i--)
    {
        printf("%d", (a >> i) & 1);
    }
}
