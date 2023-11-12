#include <stdio.h> 

int main() { 
  int N = 0;
  int c = 1;
  printf("Введите размер: ");
  scanf("%d", &N);
  printf("\nМассив:\n");
  int a[N][N];
  for (int i = 0; i < N; i++) { //заполним массив
    for (int j = 0; j < N; j++) {
      a[i][j] = c++;
      printf("%3d", a[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  return 0;
}
