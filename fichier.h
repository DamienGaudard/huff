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


/**
 * Projet algorithmique
 */
 
#ifndef __Projet_Algo__fichier__
#define __Projet_Algo__fichier__

#include <stdio.h>
#include "arbres.h"

#define TAILLE_CARACTERE 8



/*Définition de la structure du buffer*/
struct buffer
{
	/*code binaire de l'élément présent dans le buffer (max 32 bits)*/
	unsigned int info;
	/*nombre de bits utilisés dans info*/
	unsigned int nbr_bits;
};

typedef struct buffer t_buffer, *tpb;

/*Prototypes*/

void initialisation_buffer();

int ouvrir_fichieri(char* nom_fichier_initial);

int ouvrir_fichierf(char* nom_fichier_final);

void fermer_fichieri();

void fermer_fichierf();

unsigned int recup_caractere();

void ecrire_caractere(int caractere);

unsigned int recup_cb_caractere();

tpb recup_cb_feuille(tpa a);

void ecrire_cb(tpb code_binaire);

tpa recup_feuille(tpa a);

void libere_buffer();

#endif 
