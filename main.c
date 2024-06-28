#include "includes.h"

int main()
{
    abonent* struct_init = create_array(sizeof(int)*10);
    menu(struct_init);
    return 0;
}


void menu(abonent* struct_init) {
    int user_input = 0;
    unsigned int pos = 0;
    char data;

    while (1) {
      printf("Список абонентов:\n");
      printf("1) Добавить абонента\n");
      printf("2) Удалить абонента\n");
      printf("3) Поиск абонента\n");
      printf("4) Вывод всех записей\n");
      printf("5) Выход\n");
      printf(">");
      scanf("%d", &user_input);
      getchar();

      switch(user_input) {
        case 1:
            printf("Введите информацию об абоненте:\n");
            scanf("%s", &data );
            input_user_data(struct_init, &data);
            break;
        case 2:
            printf("Введите номер абонента:\n");
            scanf("%d", &pos );
            delete_user_data(struct_init,pos);
            break; 
        case 3:
            printf("Введите номер:\n");
            scanf("%d", &pos );
            printf("struct_init[%d], %s\n",pos, (char*)find_user_data(struct_init, pos));
            menu(struct_init);  
            break;
        case 4:  
            output_user_data(struct_init);
            break;
        case 5:
            clear_array(struct_init);
            exit(0);
            break;
        default:
            printf("Введите запрос еще раз\n");
            menu(struct_init);
      }
    }
}