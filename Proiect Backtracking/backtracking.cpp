#include <cstdio>
#include <cstdlib>
#include <fstream>

FILE* afisare; // Am declarat global fisierul pentru afisare deoarece afisarea are loc in functia bkt

/* 
    Am declarat global vectorii pentru a ii putea  folosi vectorii atat in main cat si in functia de backtracking si in functia de verificare

    drum[102] - vectorul in care retin drumurile de la orasul A la orasul B
    v[102][102] - matricea care retine toate drumurile
    w[102] - vectorul care retine cate drumuri directe am din fiecare oras
*/

int drum[102];
int v[102][102]; 
int w[102];

int verificare(int oras, int k) { // Functia verificare returneaza 1 daca drumul retinut trece prin variabila oras si in caz contrar returneaza 0.
    int i;
    for(i = 0; i < k; i++)
        if(drum[i] == oras)
            return 1;
    return 0;
}

void bkt(int k, int B) {
    int i;

    if(drum[k - 1] == B) { // verific daca in capatul din dreapta am ajuns in orasul B si in caz afirmativ, afisez drumul din A in B
        for(i = 0; i < k; i++)
            fprintf(afisare, "%d ", drum[i]);

        fprintf(afisare, "\n");
    }
    else {
        for(i = 0; i < w[drum[k - 1]]; i++) {
            if(verificare(v[drum[k - 1]][i], k) == 0) {  
                drum[k] = v[drum[k - 1]][i];
                bkt(k + 1, B);
            }
        }
    }
}

using namespace std;

int main() {
    int N, A, B;

    ifstream citire("date.in"); // deschid fisierul pentru citire
    afisare = fopen("date.out", "w"); // deschid fisierul pentru scriere

    if(not citire) {
        printf("Nu s-a putut deschide fisirerul date.in!");
        exit(1);
    }

    if(afisare == NULL) {
        printf("Nu s-a putut deschide fisirerul date.out!");
        exit(1);
    }

    citire >> N;
    citire >> A >> B;

    int i, j, x, y;

    for(i = 1; i <= N; i++) // Initializez vectorul w cu 0
        w[i] = 0;

    while(citire >> x >> y) { // Memorarea drumurilor in matricea v
        v[x][w[x]] = y;
        w[x]++;

        v[y][w[y]] = x;
        w[y]++;
    }

    drum[0] = A; // orasul din care porneste drumul este A

    bkt(1, B); // apelarea functiei

    citire.close();
    fclose(afisare);
    return 0;
}