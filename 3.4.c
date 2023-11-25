//Напишите программу, которая ищет введенной строке (с клавиатуры)
//введенную подстроку (с клавиатуры) и возвращает указатель на начало
//подстроки, если подстрока не найдена в указатель записывается NULL.

#include <stdio.h>

int main() {
  char string[128];
  char substring[128];
  char *p;

  printf("Enter string: ");
  fgets(string, sizeof string, stdin);
  printf("Enter substring: ");
  fgets(substring, sizeof substring, stdin);

  int lenstring = 0;
  int lensubstring = 0;
  for (int i = 1; string[i] != '\0'; i++) {   // подсчет символов в строке без учета терминального нуля.
    lenstring++;                            
  }
  for (int i = 1; substring[i] != '\0'; i++) {
    lensubstring++;
  }

  int pos = 0;
  int count = 0;
  while(pos < lenstring) {
    for (int i = pos; i < lenstring; i++) {
      if (substring[0] == string[i]) {
        pos = i;
        break;
      }
    }
    p = &string[pos];
    for (int i = 1; i < lenstring; i++) {
      if (substring[i] == string[pos + i]) {
        count++;
        if (count == (lensubstring - 1)) {
          printf("\nSubstring found");
          printf("\nSubstring address is: %p", p);
          printf("\nFirst character in substring is: %c\n", *p);
          return 0;
        }
      }
      else {
        pos++;
        break;
      }        
    }
  }
  printf("\nSubstring not found\n");
  p = NULL;
  return 0;
}

