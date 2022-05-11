#include <stdio.h>
#include <stdlib.h>

// Structura Spectacol poate memora datele despre un spectacol(nr spectacolului, ora de incepere si respectiv ora la care este eliberata sala de specatol)
typedef struct{
    int ID, start, stop;
}Spectacol;

//cu ajutorul functiei compara putem folosi functia qsort pentru a storta spectacolele in ordine crescatoare in functie de ora la care se termina fiecare dintre acestea
int compara(const void *p, const void *q){
    return ((Spectacol*)p)->stop - ((Spectacol*)q)->stop;
}


int main(){

    /*
    n - numarul de spectacole
    prog- nr maxim de spectacole programate

    S_date - spectacolele din fisireul date.in
    S_programate - spectacollele programate 
    */
    int n, prog, i;
    
    Spectacol S_date[100], S_programate[100];

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

    fscanf(citire, "%d", &n);

    for(i = 0; i < n; i++){   // Citirea datelor din fisier
        fscanf(citire, "%d %d %d", &S_date[i].ID, &S_date[i].start, &S_date[i].stop);
    }

    fclose(citire); // inchiderea fisierului date.in deoarece am terminat cu citirea datelor din fisier

    // Sortarea spectacolelor in functie de ora la care se termina cu ajutorul functiei qsort
    qsort(S_date, n, sizeof(Spectacol), compara);

    S_programate[0] = S_date[0]; // programam primul spectacol
    prog = 1; // cum am programat primul spectacol, variabila prog devine 1

    for(i = 1; i < n; i++) // pentru fiecare spectacol verificam daca incepe dupa ultimul spectacol programat, iar in caz afirmativ il vom adauga la spectacolele programate 
        if(S_date[i].start >= S_programate[prog - 1].stop)
            S_programate[prog++] = S_date[i];

    for( i = 0; i < prog; i++) // afisarea solutiei optim-determinate
        fprintf(afisare, "%d \n", S_programate[i].ID);

    fclose(afisare); // inchiderea fisierului deschis pentru scriere adica date.out
    return 0;

}