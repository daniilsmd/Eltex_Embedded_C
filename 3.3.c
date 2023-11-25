#include <stdio.h>

int main() {      
  int array[10];
  for (int i = 0; i < 10; i++) {
    array[i] = i + 1;
  }

  int *ptr = array;
  for (int i = 0; i < 10; i++) {
    printf("*ptr=%d\n", *ptr);
    ptr++;
  }
}

