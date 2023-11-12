#include <stdio.h> 

int main() { 
int N = 0;
printf("Введите размер: ");
scanf("%d", &N);
printf("\nМассив:\n");
int a[N][N];
for (int i = 0; i < N; i++) {
  for (int j = 0; j < N; j++) {
    a[i][j] = 0;
    if ((i + j + 1) >= N) {
      a[i][j] = 1;
    }
    printf("%3d", a[i][j]);
  }
  printf("\n");
}
printf("\n");
return 0;
}