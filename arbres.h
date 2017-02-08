/**
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de Polytech Marseille. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

/**
 * @author GAUDARD Damien <damien.gaudard@etu.univ-amu.fr>
 * @author AIT SAID Anaïs <anais.ait-said@etu.univ-amu.fr>
 */

#ifndef __Projet_Algo__arbres__
#define __Projet_Algo__arbres__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define A 258

#define B 515

/*Définition de la structure arbre et d'un pointeur sur arbre*/

struct arbre{

	int feuille;
	unsigned int code_binaire;
	int poids;
	int ordre_gal;
	struct arbre *pere;
	struct arbre *fg;
	struct arbre *fd;
};

typedef struct arbre arbre, *tpa;

/*prototypes*/

void init_poids();

void init_ptr_ordre_gal();

void init_ptr_caractere();

tpa init_arbre();

int est_feuille(tpa a);

int poids(tpa a);

int ordre_gal(tpa a);

tpa pere(tpa a);

tpa fils_droit(tpa a);

tpa fils_gauche(tpa a);

unsigned int code_binaire(tpa a);

tpa ptr_feuille (int c);

tpa rechercher_caractere(unsigned int a);

tpa modif_arbre(unsigned int c, tpa a);

void my_free(tpa a);


#endif 

