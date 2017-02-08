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
#include "arbres.h"
#include "codage.h"
#include "fichier.h"
#include <stdio.h>
#include <stdlib.h>


tpa encoder(tpa a)
{
	tpb c = NULL; 
	c = (tpb)malloc(sizeof(t_buffer));
	tpa feuille = NULL;
	tpb tmp = NULL;
	c->info = recup_caractere();
	c->nbr_bits = TAILLE_CARACTERE;

	while(c->info != EOF){
		feuille = rechercher_caractere((c->info));
		if(feuille != NULL){

			tmp = recup_cb_feuille(feuille);
			ecrire_cb(tmp);
			free(tmp);
		} else {
			tmp = recup_cb_feuille(ptr_feuille(A-2));
			ecrire_cb(tmp);
			free(tmp);
			ecrire_cb(c);
		}
		
		a = modif_arbre((c->info),a);
		c->info = recup_caractere();
	}
	
	return a;
}



tpa decoder(tpa a){
	tpa tmp = NULL;
	unsigned int c = 0;
	
	tmp = recup_feuille(a);

	while(tmp != ptr_feuille(A-1)){
		if(tmp == ptr_feuille(A-2)){
			c = recup_cb_caractere();
			ecrire_caractere(c);
			a = modif_arbre(c,a);

		} else {
			ecrire_caractere(code_binaire(tmp));
			a = modif_arbre(code_binaire(tmp),a);
		}
		tmp = recup_feuille(a);
	}
	return a;
}
	
