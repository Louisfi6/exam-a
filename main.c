#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE  9
#define LIST_SIZE  9
#define LIST_SIZE  9

int liste[LIST_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9};


//Fonction saisir() pour remplir la grille de sudoku en mettant i j et la valeur v tant que remplissage est inferieur a 81

int saisir(int grid[GRID_SIZE][GRID_SIZE]){
    //faire un boucle while pour remplir la grille de sudoku

    int i, j, v;
    int remplissage = 0;

    while(remplissage <= 81){
        printf("Saisissez les indices i et j et la valeur v a placer a l emplacement (i,j) dans la grille de sudoku : \n");
        scanf("\n%d\n %d\n %d", &i, &j, &v);
        if (i < 0 || i > 8 || j < 0 || j > 8 || v < 1 || v > 9){
            printf("Erreur de saisie");
            return 0;
        }
        if (grid[i][j] != 0){
            printf("La case deja occupee");
            return 0;
        }
        grid[i][j] = v;
        printf("Voici le sudoku que vous avez rempli : \n");
        for (i = 0; i < GRID_SIZE; i++) { // boucle for qui va afficher la grid
            if(i % 3 == 0)
                printf("+-------+-------+-------+\n");
            for (j = 0; j < GRID_SIZE; j++) {
                if(j % 3 == 0)
                    printf("| ");
                printf("%d ", grid[i][j]);
            }
            printf("| \n");
        }printf("+-------+-------+-------+\n");
        remplissage++;
    }
}


//Fonction qui va vérifier si la grid renvoie par la fonction saisir() est la meme que solvedGrid

bool verifier(int grid[GRID_SIZE][GRID_SIZE], int solvedGrid[GRID_SIZE][GRID_SIZE]){
    int i, j;
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] != solvedGrid[i][j]){
                return false;
            }
        }
    }
    return true;
}

void melangerListe(){
    int i, j, end;
    for (i = 0; i < LIST_SIZE - 1; i++) { //parcourir la liste des nombres à mélanger
        j = rand() % (LIST_SIZE - i) + i;
        //algo de fisher yates pour mélanger les nombres
        end = liste[i];
        liste[i] = liste[j];
        liste[j] = end;
    }
}

int main(){
    srand( time( NULL ) );
    melangerListe();


    int grid[GRID_SIZE][GRID_SIZE] = {0}; //création du tableau en 2D
    int i, j, k; //variables pour les itérations
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            k = (i * 3 + i / 3 + j) % LIST_SIZE; // Calcul de la position du prochain numéro à placer
            grid[i][j] = liste[k]; // Placement du numéro dans la grille
        }
    }

    int num_to_remove  = 1; //30 nombres doivent être supprimés

    while (num_to_remove > 0) {
        int row = rand() % 9; //choisir une ligne au hasard
        int col = rand() % 9; //choisir une colone au hasard
        if (grid[row][col] != 0) { //si la grille avec la colone + ligne choisies est différent de 0
            grid[row][col] = 0; // on met la case à 0
            num_to_remove--; //décrémentation pour arriver enfin à 30 nombres supprimés
        }
    }

    int solvedGrid[GRID_SIZE][GRID_SIZE]; //on copie la grid dans solvedGrid

    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            solvedGrid[i][j] = grid[i][j]; //on parcourt la grid puis on copie les éléments dans solvedGrid. Au final on
            //va venir compléter les cases = 0 par les chiffres manquants
        }
    }


    printf("Voici le sudoku a resoudre : \n");
    for (i = 0; i < GRID_SIZE; i++) { // boucle for qui va afficher la grid
        if(i % 3 == 0)
            printf("+-------+-------+-------+\n");
        for (j = 0; j < GRID_SIZE; j++) {
            if(j % 3 == 0)
                printf("| ");
            printf("%d ", grid[i][j]);
        }
        printf("| \n");
    }
    printf("+-------+-------+-------+\n");

    //Demander à l'utilisateur de remplir la grid avec la fonction saisir()


    saisir(grid);

    if(saisir(grid) == verifier(grid, solvedGrid)){
        printf("Bravo vous avez reussi a resoudre le sudoku");
    }
    else{
        printf("Dommage vous n'avez pas reussi a resoudre le sudoku");
    }




//    //system("pause");
    return 0;
}