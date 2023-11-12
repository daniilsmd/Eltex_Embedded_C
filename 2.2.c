#include <stdio.h> 

int main() { 
  int N = 0;
  printf("Введите размер массива: ");
  scanf("%d", &N);
  printf("\nПервоначальный массив:\n");
  int a[N];
  for (int i = 0; i < N; i++) { //заполним массив
    a[i] = i;
    printf("%3d", a[i]);
  }
  printf("\nПеревернутый массив:\n");    
  int b[N];
  for (int i = 0; i < N; i++) {
    b[i] = a[N - i - 1];
    printf("%3d", b[i]);
  }
  printf("\n");
  return 0;
}