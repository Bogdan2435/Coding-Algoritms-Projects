#include <stdio.h>
#include <stdlib.h>

int main(){

    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);

    while(n > m){
        printf("Datele introduse nu sunt corecte.(m trebuie sa fie mai mare sau egal cu n)");
        scanf("%d", &n);
        scanf("%d", &m);
    }


    int v[1000][1000]; // Declararea matricei
    int i, j;

    for(i = 1; i <= n; i++)
        for(j = 1; j <= m; j++)
            v[i][j] = 0; // Initializarea tuturor elementelor cu 0

    v[1][1] = 1; // Primul element este egal cu 1

    for(i = 1; i <= n; i++)
        for(j = 1; j <= m; j++)
            v[i][j] = v[i-1][j] + v[i-1][j-1];

    printf("Numarul de trasee pe care poate trece PacMan este egal cu %d", v[n][m]);

    return 0;

}