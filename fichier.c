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

#include "fichier.h"
#include <stdio.h>
#include <stdlib.h>

/*On definit des macros pour recuperer les 8 premiers ou derniers bits d'un entier.*/
#define derniers_bits 255
#define premiers_bits 2147483648

static FILE * fichier_initial = NULL;
static FILE * fichier_final = NULL;
static tpb buffer = NULL;

/*Initialise le buffer. */
void initialisation_buffer()
{
	buffer = (tpb)malloc(sizeof(t_buffer));
	buffer->info = 0;
	buffer->nbr_bits = 0;
}

/*Ouvre le fichier initial.
 */
int ouvrir_fichieri(char* nom_fichier_initial)
{
	fichier_initial = fopen(nom_fichier_initial, "rb"); 	//"rb" signifie qu'on va ouvrir un
								//fichier binaire en lecture.
	if (fichier_initial == NULL) return 0;
	else return 1;
}

/*Ouvre le fichier final.
 */
int ouvrir_fichierf(char* nom_fichier_final)
{
	fichier_final = fopen(nom_fichier_final, "wb"); 	//"wb" signifie qu'on va ouvrir un
								//fichier binaire en ecriture.
	if (fichier_final == NULL) return 0;
	else return 1;
}

/*Ferme le fichier initial.
 */
void fermer_fichieri()
{
	fclose(fichier_initial);
}

/*Ferme le fichier final.
 */
void fermer_fichierf()
{
	fclose(fichier_final);
}

/*Recupere et renvoie le prochain caractere du fichier initial.
 */
unsigned int recup_caractere()
{
	assert(fichier_initial != NULL);
	return fgetc(fichier_initial);
}

/*Ecrit un caractere dans le fichier final.
 */
void ecrire_caractere(int caractere)
{
	assert(fichier_final != NULL);
	fprintf(fichier_final, "%c", caractere);
}

/*Recupere et renvoie le code binaire du caractere contenu dans le buffer
 */
unsigned int recup_cb_caractere()
{
	unsigned int a = 0;
	
	/*on recupere les bits du prochain caractere*/
	a = recup_caractere();
	
	/*on met les bits dans le buffer*/
	buffer->info = (buffer->info) << (TAILLE_CARACTERE);
	buffer->nbr_bits = buffer->nbr_bits + TAILLE_CARACTERE;
	buffer->info = (buffer->info) | a;

	/*on met les 8 premiers bits du buffer dans a*/
	a = (buffer->info) >> (buffer->nbr_bits - TAILLE_CARACTERE);
	a = (a & derniers_bits);
	
	/*on reajuste la taille du buffer*/
	buffer->nbr_bits = buffer->nbr_bits - TAILLE_CARACTERE;

	return a;
	
}

/*Recupere et renvoie le cobinaire d'une feuille de l'arbre de huffman
 */
tpb recup_cb_feuille(tpa a)
{
	tpb tmp = NULL;
	tmp = (tpb)malloc(sizeof(t_buffer));

	/*initialisation du temporaire*/
	tmp->info = tmp->info & 0;
	tmp->nbr_bits = 0;

	/*on parcourt tout l'arbre, donc tant qu'on est pas remonte jusqu'a la racine*/
	while(pere(a) != NULL)
	{
		if(fils_gauche(pere(a)) == a)
		{	
			tmp->info = tmp->info >> 1;
			(tmp->nbr_bits)++;
		}else{
			tmp->info = tmp->info >> 1;
			tmp->info = tmp->info | premiers_bits;
			(tmp->nbr_bits)++;
		}
		a = pere(a);
	}

	/*on decale le temporaire*/	
	tmp->info = tmp->info >> (32-(tmp->nbr_bits));
	return tmp;
}

/*Ecrit le code binaire d'un caractere dans le buffer. La fonction prend en paramètre
 *un pointeur sur un buffer contenant le code binaire a ecrire.
 */
void ecrire_cb(tpb code_binaire)
{
	tpb tmp = NULL;
	tmp = (tpb)malloc(sizeof(t_buffer));
	
	/*on met dans le buffer les bits de code_binaire*/
	buffer->info = (buffer->info) << (code_binaire->nbr_bits);
	buffer->info = (buffer->info) | (code_binaire->info);
	buffer->nbr_bits = (buffer->nbr_bits) + (code_binaire->nbr_bits);

	
	while(buffer->nbr_bits > TAILLE_CARACTERE)
	{
		/*on decale (a droite) vers les 8dernier bits du buffer*/
		tmp->info = (buffer->info) >> (buffer->nbr_bits - TAILLE_CARACTERE);
		ecrire_caractere(tmp->info);
		
		/*on remet le buffer a la taille sans le caractere ecrit*/
		buffer->nbr_bits = (buffer->nbr_bits) - TAILLE_CARACTERE;
	}

	free(tmp);
}

/*Recuper et renvoie une feuille de l'arbre de huffman en regardant le code binaire 
 *contenu dans le buffer.
 */
tpa recup_feuille(tpa a)
{
	unsigned int tmp = 0;

	while(!est_feuille(a))
	{
		if((buffer->nbr_bits) == 0)
		{
			tmp = recup_caractere();
			buffer->info = (buffer->info) << TAILLE_CARACTERE;
			buffer->nbr_bits = (buffer->nbr_bits) + TAILLE_CARACTERE;
			buffer->info = (buffer->info) | tmp;
		}
		/*on recupere le dernier bit du buffer*/
		tmp = (buffer->info) >> (buffer->nbr_bits - 1);
		tmp = tmp & (int)1;
		
		if(tmp == 1) a = fils_droit(a);
		else a = fils_gauche(a);
		
		(buffer->nbr_bits)--;
			
	}
	return a;
}

/*Ecrit le caractere contenu dans le buffer dans le fichier final afin de liberer le buffer*/
void libere_buffer()
{
	/*on ecrit le code binaire du caractère de fin de fichier*/	
	ecrire_cb(recup_cb_feuille(ptr_feuille(A-1)));
	
	buffer->info = buffer->info << (TAILLE_CARACTERE - buffer->nbr_bits);

	/*on ecrit les dernier bits du buffer*/
	ecrire_caractere(buffer->info);
}


