/*
Pb 9 / Dura Alexandru-Bogdan

Să  se  construiască  o  matrice  pătratică,  având  2^n  linii  și  2^ncoloane,  
cu  elemente  din mulțimea {0,1} urmând următorul procedeu:-se împarte tabloul în patru subtablouri 
de latură 2^(n-1)-se plasează valori 1 în subtabloul dreapta-sus și valori nule în celelalte subtablouri-se 
reia  procedeul  pentru  fiecare  dintre  celelalte  trei  subtablouri,  până  la  obținerea 
unor subtablouri de latură 1,care vor avea valori nule.

Date de intrare:fișierul date.in conține numărul n, cu semnificația din enunț.

Date de ieșire:fișierul date.out conține matricea construită.

Restricții și precizări:  n<10
*/

#include <stdio.h>
#include <stdlib.h>

int** m;  // am declarat global matricea pentru a o putea umple usor cu ajutorul functiei pune_unu

void pune_unu(int xi, int yi, int xj, int yj) { // functia odata apelata completeaza matricea m de la xi si yi pana la xj si respectiv yj cu "1".
    int i, j;
    for(i = xi; i < xj; i++)
        for(j = yi; j < yj; j++)
            m[i][j] = 1;
}

void matrice_div_imp(int xi, int yi, int xj, int yj){

    int mij_X, mij_Y;

    mij_X = (xi + xj) / 2; //calculez mijlocul pentru coorondata X
    mij_Y = (yi + yj) / 2; //calculez mijlocul pentru coordonata Y

    pune_unu(xi, mij_Y, mij_X, yj); // umplu cu valoarea "1" patratul din dreapta sus, care este dat de coordonatele xi--->mij_X si mij_Y--->yj

    if(xj - xi > 1){    // verific daca latura ramasa este mai mare ca 1 (nu avea rost sa verificam si pentru coordonata Y deoarece matricea este patrata)
        // tabloul se imparte in 4 subtablouri si il reapelez pe fiecare cu functia matrice_div_imp 

        matrice_div_imp(xi, yi, mij_X, mij_Y);    //stanga sus
        matrice_div_imp(xi, mij_Y, mij_X, yj);    //dreapta sus  
        matrice_div_imp(mij_X, yi, xj, mij_Y);    //stanga jos  
        matrice_div_imp(mij_X, mij_Y, xj, yj);    //dreapta jos
        
    }
}

int main()
{
    FILE *citire;
    FILE *afisare;

    citire = fopen("date.in", "r"); //deschid fisierul pentru citire
    afisare = fopen("date.out", "w"); //deschid fisierul pentru scriere

    if(citire == NULL){ 
        printf("Nu s-a putut deschide fisirerul date.in!");
        exit(1);
    }

    if(afisare == NULL){
        printf("Nu s-a putut deschide fisirerul date.out!");
        exit(1);
    }

    int n , i, j, latura;
    
    //fscanf(citire, "%d", &n);
    latura = 1 << n; // latura <- 2^n

    m = (int **)malloc(latura * sizeof(int *));   //aloc dinamic matricea pentru a nu o aloca static de fiecare data pentru latura de 1024(cea mai mare latura posibila , 2^10)
    for (i = 0; i < latura; i++)
         m[i] = (int *)malloc(latura * sizeof(int));
    
    for(i = 0; i < latura; i++) //umplu matricea cu zero
        for(j = 0; j < latura; j++)
            m[i][j] = 0;

    matrice_div_imp(0, 0, latura, latura); // apelarea initiala

    for(i = 0; i < latura; i++) {    // afisarea matricei create
        for(j = 0; j < latura; j++)
            fprintf(afisare, "%d ", m[i][j]);
        fprintf(afisare, "\n");
    }

    for (i = 0; i < latura; i++)  // eliberarea memoriei
        free(m[i]);
    free(m);
    fclose(citire);
    fclose(afisare);

    return 0;
}

