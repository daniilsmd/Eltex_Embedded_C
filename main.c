#include "includes.h"

int main() {

    void *handle = dlopen("./HW_8.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    int user_input = 0;
    int operand1, operand2, output;
    int (*add)(int, int);
    int (*sub)(int, int);
    int (*mul)(int, int);
    int (*div)(int, int);
    add = dlsym(handle, "add");
    sub = dlsym(handle, "sub");
    mul = dlsym(handle, "mul");
    div = dlsym(handle, "div");

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
    dlclose(handle); 

    return 0;
}