#include "satgrille.h"

void generer_sat_grille(Grille G,int dimension,int *compteur_clauses_grille) {
    generer_sat_grille_au_moins(dimension,compteur_clauses_grille);
    generer_sat_grille_au_plus(dimension,compteur_clauses_grille);
}

void generer_sat_grille_au_moins(int dimension,int *compteur_clauses_grille) {
    FILE * f = NULL;
    char variable[4];
    f = fopen("pbsat.cnf", "a");
    int i = 0, j = 0, k = 0;
    for (i = 0; i < dimension; i++) {
	for (j = 0; j < dimension; j++) {
	    for (k = 0; k < dimension; k++) {
		sprintf(variable, "%i%i%i ", i + 1, j + 1, k + 1);
		fputs(variable, f);
	    }
	    fputs("0 \n", f);
            (*compteur_clauses_grille)++;
	}
    }
    fclose(f);
}

void generer_sat_grille_au_plus(int dimension,int *compteur_clauses_grille) {
    int i = 0, j = 0, k = 0, l = k + 1;
    FILE * f = NULL;
    f = fopen("pbsat.cnf", "a");
    char variable1[5];
    char variable2[7];
    for (i = 0; i < dimension; i++) {
	for (j = 0; j < dimension; j++) {
	    for (k = 0; k < dimension; k++) {
		for (l = k + 1; l < dimension; l++) {
		    sprintf(variable1, "-%i%i%i ", i + 1, j + 1, k + 1);
		    fputs(variable1, f);
		    sprintf(variable2, "-%i%i%i 0\n", i + 1, j + 1, l + 1);
		    fputs(variable2, f);
                    (*compteur_clauses_grille)++;
		}
	    }
	}
    }
    fclose(f);
}

void generer_sat_saisies(Grille G, int dimension,int *compteur_clauses_saisies) {
    FILE * f = NULL;
    f = fopen("pbsat.cnf", "a");
    int i, j, k;
    char clause[6];

    for (i = 0; i < dimension; i++) {
	for (j = 0; j < dimension; j++) {
	    if (G[i][j] > 0 && G[i][j] <= dimension) {
		k = G[i][j];
		sprintf(clause, "%i%i%i 0\n", i+1, j+1, k);
		fputs(clause, f);
                (*compteur_clauses_saisies)++;
	    }
	}
    }
    fclose(f);
}




