#include <stdio.h> 

int main() { 
  int N = 0;
  int c = 1;
  int limj1, limj2, limi1, limi2 = 0;
  int i, j = 0;
  printf("Введите размер: ");
  scanf("%d", &N);
  int a[N][N];
  limj2 = limi2 = N;
  
  while (c <= (N * N)) {
    for (j = limj1; j < limj2; j++) {
      a[limi1][j] = c++;
    }
    limi1++;

    for (i = limi1; i < limi2; i++) {
      a[i][limj2 - 1] = c++;
    }
    limj2--;

    for (j = limj2; j > limj1; j--) {
      a[limi2 - 1][j - 1] = c++;
    }
    limi2--;

    for (i = limi2; i > limi1; i--) {
      a[i - 1][limj1] = c++;
    }
    limj1++;
  }

  printf("\nМассив:\n");
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      printf("%3d", a[i][j]);
    }
    printf("\n");
  }
  return 0;
}