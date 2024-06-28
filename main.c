#include "includes.h"

int main() {
    int user_input = 0;
    int operand1, operand2, output;
    while (1) {
        printf("\nВыберите операцию:\n");
        printf("1) Сложение\n");
        printf("2) Вычитание\n");
        printf("3) Умножение\n");
        printf("4) Деление\n");
        printf("5) Выход\n");
        scanf("%d", &user_input);
        
        switch(user_input) {
            case 1:
                printf("\nВведите первый операнд: ");
                scanf("%d", &operand1);
                printf("\nВведите второй операнд: ");                         
                scanf("%d", &operand2); 
                output = add(operand1, operand2);
                printf("\nРавно: %d\n", output);
                break;
            case 2:
                printf("\nВведите первый операнд: ");
                scanf("%d", &operand1);
                printf("\nВведите второй операнд: ");                         
                scanf("%d", &operand2);       
                output = sub(operand1, operand2); 
                printf("\nРавно: %d\n", output);
                break; 
            case 3:
                printf("\nВведите первый операнд: ");
                scanf("%d", &operand1);
                printf("\nВведите второй операнд: ");                         
                scanf("%d", &operand2);      
                output = mul(operand1, operand2);
                printf("\nРавно: %d\n", output);
                break;
            case 4:        
                printf("\nВведите первый операнд: ");
                scanf("%d", &operand1);
                printf("\nВведите второй операнд: ");                         
                scanf("%d", &operand2);       
                output = div(operand1, operand2);
                printf("\nРавно: %d\n", output);
                break; 
            case 5:
                return 0;
                break;
            default:
                printf("Введите запрос еще раз\n");
        }
    }
}