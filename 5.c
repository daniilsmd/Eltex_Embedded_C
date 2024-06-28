#include <stdio.h>
#include <string.h>

struct abonent {
   char name[10];
   char second_name[10];
   char tel[10];
};

void input_user_data(struct abonent abonent_list[], int i) {
  printf("Введите имя абонента: ");
  fgets(abonent_list[i].name, sizeof abonent_list[i].name, stdin);
  abonent_list[i].name[strlen(abonent_list[i].name) - 1] = '\0';
  printf("Введите фамилию абонента: ");
  fgets(abonent_list[i].second_name, sizeof abonent_list[i].second_name, stdin);
  abonent_list[i].second_name[strlen(abonent_list[i].second_name) - 1] = '\0';
  printf("Введите телефон абонента: ");
  fgets(abonent_list[i].tel, sizeof abonent_list[i].tel, stdin);
  abonent_list[i].tel[strlen(abonent_list[i].tel) - 1] = '\0';
}

void delete_user_data(struct abonent abonent_list[]) {
  printf("Введите номер кандидата на удаление: ");
  int pos = 0;
  scanf("%d", &pos);
  getchar();
  abonent_list[pos - 1].name[0] = abonent_list[pos - 1].second_name[0] = abonent_list[pos - 1].tel[0] = '\0';
}

void find_user_data(struct abonent abonent_list[]) {
  char search_prompt[10];
  int pos = 0;
  printf("Введите имя разыскиваемого абонента: ");
  fgets(search_prompt, sizeof search_prompt, stdin);
  search_prompt[strlen(search_prompt) - 1] = '\0';
  for (pos = 0; pos < 100; pos++) {
    if (strcmp(abonent_list[pos].name, search_prompt) == 0) {
      printf("Абонент найден, вот его данные:\n");
      printf("%3d %10s %10s %10s\n", pos + 1, abonent_list[pos].name, abonent_list[pos].second_name, abonent_list[pos].tel);
      return;
    }
    printf("Такого абонента нет\n");
  }
}

void output_user_data(struct abonent abonent_list[]) {
  for (int pos = 0; pos < 100; pos++) {
  printf("%3d %10s %10s %10s\n", pos + 1, abonent_list[pos].name, abonent_list[pos].second_name, abonent_list[pos].tel);
  }
}

int main() {
  struct abonent abonent_list[100] = {};
  int user_input = 0;
  int i = 0;
  while (1) {
    printf("Список абонентов:\n");
    printf("1) Добавить абонента\n");
    printf("2) Удалить абонента\n");
    printf("3) Поиск абонентов по имени\n");
    printf("4) Вывод всех записей\n");
    printf("5) Выход\n");
    printf(">");
    scanf("%d", &user_input);
    getchar();

    switch(user_input) {
      case 1:
        if (i > 100) {
          printf("Справочник переполнен!");
          break;
        }
        input_user_data(abonent_list, i);
        i++;
        break;
      case 2:
        delete_user_data(abonent_list);
        break;
      case 3:
        find_user_data(abonent_list);
        break;
      case 4:
        output_user_data(abonent_list);
        break;
      case 5:
        return 0;
      default:
        printf("Введите запрос еще раз");
    }
  }
}
