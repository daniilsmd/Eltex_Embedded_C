#include <stdio.h>

int main () {
  int num1 = 34754554;
  char num2;
  char *ptr;
  printf("\nEnter number: ");
  scanf("%c", &num2);
  ptr = (char*) &num1;
  ptr = ptr + 2;
  *ptr = num2;
  printf("%d\n", num1);
}

