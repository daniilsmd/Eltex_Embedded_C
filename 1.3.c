#include <stdio.h> 

int main() 
{
    int a, b, c; 
    a = b = c = 0;
    printf("Введите число: ");
    scanf("%d", &a);
    for (int i = 31; i >= 0; i--) 
    {
        b = ((a >> i) & 1);
        printf("%d", b);
        if (b == 1)
            c++;
    }
    printf("\n");
    printf("Количество единиц: %d", c);
    printf("\n");
}
