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
#include <stdlib.h>
#include <assert.h>

static void MAJ(tpa a);
static tpa meme_poids(tpa a);
static void swap_ordre(tpa a, tpa b);
static void swap(tpa a, tpa b);
static tpa changer_fils_droit(tpa a, tpa b);
static tpa changer_fils_gauche(tpa a, tpa b);
static tpa changer_pere(tpa a, tpa b);
static tpa changer_ordre_gal(tpa a, int b);
static tpa changer_poids(tpa a, int b);
static tpa creer_noeud(tpa pere, tpa fg, tpa fd, int poids, int ordre_gal);
static tpa creer_feuille(tpa pere, unsigned int code_binaire, int poids, int ord_gal);

/*Le tableau poids contient les poids des noeuds et feuilles de l'arbre en construction*/
static int tab_poids[B];
/*Le tableau ptr_ordre_gal contient les pointeurs sur les noeuds et feuilles, afin de pouvoir faire l'échange lors de la mise à jour de l'arbre*/
static tpa ptr_ordre_gal[B];
/*Le tableau caractere contient des pointeurs vers les feuilles de l'arbre*/
static tpa ptr_caractere[A];

/*Initialisation de poids avec des 0*/
void init_poids(){
	int i;
	for(i=0;i<B;i++){
		tab_poids[i] = 0;
	}
}

/*Initialisation de ptr_ordre_gal avec des pointeurs NULL*/
void init_ptr_ordre_gal(){
	int i;
	for (i=0;i<B;i++){
		ptr_ordre_gal[i] = NULL;
	}
}

/*Initialisation de ptr_caractere avec des pointeurs NULL*/
void init_ptr_caractere(){
	int i;
	for (i=0;i<A;i++){
		ptr_caractere[i] = NULL;
	}
}

/*Initialisation de l'arbre de Huffman avec une feuille de caractère inconnu et un noeud*/
tpa init_arbre(){
	tpa CaractereInconnu;
	tpa Noeud;
	tpa Eof;
	
	CaractereInconnu = (tpa)malloc(sizeof(arbre));
	Noeud = (tpa)malloc(sizeof(arbre));
	Eof = (tpa)malloc(sizeof(arbre));

	init_poids();
	init_ptr_ordre_gal();
	init_ptr_caractere();
	
	Eof->feuille = 1;
	Eof->poids = 0;
	Eof->code_binaire = EOF; 
	Eof->pere = NULL;
	Eof->fd = NULL;
	Eof->fg = NULL;
	Eof->ordre_gal = 3;
	
	CaractereInconnu->feuille = 1;
	CaractereInconnu->poids = 0;
	CaractereInconnu->pere = NULL;
	CaractereInconnu->fd = NULL;
	CaractereInconnu->fg = NULL;
	CaractereInconnu->ordre_gal = 2;
	
	Noeud->feuille = 0;
	Noeud->poids = 0;
	Noeud->pere = NULL;
	Noeud->fd = Eof;
	Noeud->fg = CaractereInconnu;
	Noeud->ordre_gal = 1;
	
	CaractereInconnu->pere = Noeud;
	Eof->pere = Noeud;
	
	/*MaJ des tableaux*/
	ptr_ordre_gal[0] = Noeud;
	tab_poids[0] = 0;
	ptr_caractere[A-2] = CaractereInconnu;
	ptr_ordre_gal[1] = CaractereInconnu;
	tab_poids[1] = 0;
	ptr_caractere[A-1] = Eof;
	ptr_ordre_gal[2] = Eof;
	tab_poids[2] = 0;
	
	return Noeud;
}

/*
Cette fonction prend en paramètre un pointeur sur une structure arbre.
On renvoit le champs feuille de cette structure.
Ce champs contient 1 si a es une feuille, 0 si a est un noeud.
Cette fonction permet donc de savoir si l'élément passé en paramètre est une feuill ou non 

*/

int est_feuille(tpa a){
	return a->feuille;
}

/*Renvoi le poids d'un arbre donné en paramètre*/
int poids(tpa a){
	return a->poids;
}

/*Renvoi l'ordre de Gallager d'un arbre donné en paramètre*/
int ordre_gal(tpa a){
	return a->ordre_gal;
}

/*
Cette fonction prend en paramètre un pointeur sur un arbre.
Elle renvoit le champ pere de la structure.
Cette fonction permet donc d'obtenir le pointeur sur le pere de l'arbre en paramètre. 
*/
tpa pere(tpa a){
	return a->pere; 
}

/*
Cette fonction prend en paramètre un pointeur sur un arbre.
Elle renvoit le champ fd de la structure.
Cette fonction permet donc d'obtenir le pointeur sur le fils droit de l'arbre en paramètre.

*/
tpa fils_droit(tpa a){
	assert(!est_feuille(a));
	return a->fd;
}

/*
Cette fonction prend en paramètre un pointeur sur un arbre.
Elle renvoit le champ fg de la structure.
Cette fonction permet donc d'obtenir le pointeur sur le fils gauche de l'arbre en paramètre.
*/
tpa fils_gauche(tpa a){
	assert(!est_feuille(a));
	return a->fg;
}


/*
Cette fonction prend en paramètre un pointeur sur un arbre.
Elle renvoit le champ code_bianire de la structure.
Cette fonction permet donc d'obtenir le code binaire associé à la feuille en paramètre. 
*/
unsigned int code_binaire(tpa a){
	assert(est_feuille(a));
	return a->code_binaire;
}


/*
L'objectif de cette fonction est de créer une feuille
Cette fonction prend en paramètres un pointeur sur le pere de la feuille,
un entier correspondant au code binaire du caractère, un entier correspodnant au poids de la feuille,
et enfin un entier correspondant à son ordre de galager. 
On remplit un à un les champs de la nouvelle feuille.
On renvoit la nouvelle feuille créée.
*/
static tpa creer_feuille(tpa pere, unsigned int code_binaire, int poids, int ordre_gal){
	tpa feuille;  
	feuille = (tpa)malloc(sizeof(arbre)); 

	feuille->feuille=1;  //on crée une feuille le champ feuille doit donc être à 1
	feuille->code_binaire=code_binaire; //on remplit avec le champ code_binaire paramètre code_binaire
	feuille->poids=poids; //on remplit le champ poids avec le paramètre poids
	feuille->ordre_gal=ordre_gal; //on remplit le champ ordre_gal avec ordre_gal
	feuille->pere=pere; //on remplit le champ pere avec le paramètre père
	feuille->fg=NULL; //on crée une feuille donc elle n'a pas de fils gauche
	feuille->fd=NULL; //idem fils gauche

	return feuille;
}

/*
L'objectif de cette fonction est de créer un noeud.
Cette fonction prend en paramètres un pointeur sur le père du noeud,
un pointeur sur le fils gauche du noeud, un pointeur sur le fils droit du noeud,
un entier correspondant au poids du noeud et enfin un entier correspondant à l'odre de galager du noeud.
On remplit un à un les champs du nouveau noeud. 
On renvoit le nouveau noeud créé.
*/
static tpa creer_noeud(tpa pere, tpa fg, tpa fd, int poids, int ordre_gal){

	tpa noeud;
	noeud=(tpa)malloc(sizeof(arbre));

	noeud->feuille=0; //on crée un noeud le champ feuille doit donc être à zéro
	noeud->poids=poids; //on remplit le champ poids avec le parmètre poids
	noeud->ordre_gal=ordre_gal; //on remplit le champ ordre_gal avec le paramètre ordre_gal
	noeud->pere=pere; //on remplit le champ pere avec le paramètre pere
	noeud->fg=fg; //on remplit le champ fg avec le paramètre fg
	noeud->fd=fd; //on remplit le champ fd avec le paramètre fd
	
	return noeud;

}

/*
Cette fonction prend en paramètre un pointeur sur un arbre et un entier b qui correspond au nouveau poids.
On modifie le champ poids de l'arbre en paramètre.
On retourne le nouvel arbre avec le poids modifié 
*/
static tpa changer_poids(tpa a, int b){
	a->poids=b;
	return a;
}

/*
Cette fonction prend en paramètre un pointeur sur un arbre et un entier b qui correspond au nouvel ordre de galager.
On modifie le champ ordre_gal de l'arbre en paramètre.
On retourne le nouvel arbre avec l'ordre de galager modifié 
*/
static tpa changer_ordre_gal(tpa a, int b){
	a->ordre_gal=b;
	return a;
}


/*Renvoi un pointeur sur un arbre, après modification de son père.
 *La fonction va prendre un arbre en paramètre pour changer son père et
 *va renvoyer l'arbre avec la modification.
 *L'arbre b correspond au nouveau pere.
 */
static tpa changer_pere(tpa a, tpa b){
	assert(!est_feuille(b));
	a->pere = b;
	return a;
}
 
/*Renvoi un pointeur sur un arbre, après modification de son fils gauche.
 *La fonction va prendre un arbre en paramètre pour changer son fils gauche
 *et va renvoyer l'arbre avec la modification.
 *L'arbre b correspond au nouveau fils gauche.
 */
static tpa changer_fils_gauche(tpa a, tpa b){
	assert(!est_feuille(a));
	a->fg = b;
	return a;
}

/*Renvoi un pointeur sur un arbre, après modification de son fils droit.
 *La fonction va prendre un arbre en paramètre pour changer son fils droit
 *et va renvoyer l'arbre avec la modification.
 *L'arbre b correspond au nouveau fils droit.
 */
static tpa changer_fils_droit(tpa a, tpa b){
	assert(!est_feuille(a));
	a->fd = b;
	return a;
}

/*
Cette fonction prend en paramètres un entier c 
Cet entier correspond au code du caractère dont on cherche la feuille
En utilisant le tableau caractère on va récupérer le pointeur sur la feuille
contenant le caractère c.
Cette fonction permet donc de retrouver le pointeur sur un caractère à partir de son code. 
*/

tpa ptr_feuille (int c){
	return ptr_caractere[c];
}

/*
Cette fonction prend en paramètre un entier qui correcpond au code binaire du caractère. 
La fonction chercher si le caractère reccherché est présent dans le tableau caractère. 
S'il l'est on retourne le pointeur sur la bonne feuille, sinon on retourne un pointeur null.
*/
tpa rechercher_caractere(unsigned int a){
	if (ptr_caractere[a]==NULL){	
		return NULL;
	} else {
		return ptr_caractere[a];
	}
}

/*
Cette fonction prend en paramètre deux pointeurs sur arbres. 
La fonction permet d'échanger les positions des deux arbres.
*/
static void swap(tpa a, tpa b){
	assert((a!=NULL) && (b!=NULL));
	tpa tmpa, tmpb; //on déclare deux variables temporaires.

	//on les initialise avec les pères des deux arbres
	tmpa=pere(a);
	tmpb=pere(b);

	if (tmpa!=tmpb){
		if(fils_gauche(tmpa) == a) changer_fils_gauche(tmpa,b);
		else changer_fils_droit(tmpa, b);

		if(fils_gauche(tmpb) == b) changer_fils_gauche(tmpb,a);
		else changer_fils_droit(tmpb,a);

		changer_pere(a,tmpb);
		changer_pere(b,tmpa);

	} else {
		if(fils_gauche(tmpa)==a){
			changer_fils_gauche(tmpa,b);
			changer_fils_droit(tmpa,a);
		} else {
			changer_fils_gauche(tmpa, a);
			changer_fils_droit(tmpa, b);
		}
	}


}

/* Cette fonction prend en paramètres deux pointeurs sur arbres.
L'objectif de cette fonction est de modifier l'ordre de Gallager de deux arbres.
*/

static void swap_ordre(tpa a, tpa b){
	assert((a!=NULL) && (b!=NULL));

	int tmp;

	tmp=ordre_gal(a);
	
	changer_ordre_gal(a,ordre_gal(b));
	changer_ordre_gal(b,tmp);

	tab_poids[ordre_gal(a)-1]=poids(a);
	tab_poids[ordre_gal(b)-1]=poids(b);
	ptr_ordre_gal[ordre_gal(a)-1]=a;
	ptr_ordre_gal[ordre_gal(b)-1]=b;

}

/*Cette fonction prend en parametre un pointeur sur un arbre. Elle a pour objectif de rendre le premier sous-arbre de l'arbre qui possède le même poids que celui passé en paramètre */

static tpa meme_poids(tpa a){
	assert(a!=NULL);
	int p, ordre, i;

	//on récupère l'ordre et le poids du paramètre
	ordre=ordre_gal(a);
	p=poids(a);

	//on initialise i à l'indice du pointeur sur le paramètre
	i=ordre-2;

	//on recule dans le tableau tant que le poids est le même
	while(p==tab_poids[i]){
		i--;
	}
	
	//quand on sort de la boucle le poids n'est plus le même
	//donc on augmente l'indice pour tomber sur le premier élément apparaissant dans le tableau qui a le même poids que a
	i++;

	return ptr_ordre_gal[i];
}


/* Cette fonction prend en paramètre un pointeur sur un arbre. 
Cette fonction a pour objectif de mettre à jour l'arbre (augmenter le poids, modifier les noeuds, changer l'ordre de gallager, echanger les noeuds). Ceci permet à l'arbre de respecter toutes les propriétés qu'il doit respecter */

static void MAJ(tpa a){
	
	tpa tmp;

	if(a!= NULL){
	//On vérifie si le père de a n'est pas null. Si le père de a est null cela signifie qu'on a atteint la racine.
		while(pere(a)!=NULL){
	//on cherche le premier sous arbre qui a le même ordre que a
			tmp=meme_poids(a);
	//si ce sous-arbre ne correspond ni à a ni à son père
			if((tmp!=a) && (tmp!=pere(a))){
	//on échange les deux sous arbres
				swap(a,tmp);
	//on échange également leurs ordres
				swap_ordre(a,tmp);
			}
	//on augmente le poids de a
			changer_poids(a,poids(a)+1);
	//on met à jour le tableau des poids
			tab_poids[ordre_gal(a)-1]=poids(a);

	//on passe au père de a
			a=pere(a);
		}
	//une fois sortie de la boucle cela signifie qu'on a atteint la racine 
	//on augmente le poids de la racine
		changer_poids(a, poids(a)+1);
	//on met à jour le tableau des poids
		tab_poids[ordre_gal(a)-1]=poids(a);
	}
}

/* cette fonction prend en paramètre un entier non signé ainsi qu'un pointeur sur arbre. L'objectif de cette fonction est de modifier l'arbre de façon à insérer le nouveau caractère*/

tpa modif_arbre(unsigned int c, tpa a){
	tpa fg;
	tpa noeud; 
	tpa tmp;

	tpa feuille_c=rechercher_caractere(c);

	if(feuille_c!=NULL){
		MAJ(feuille_c);
	} else {
		/*on creer un pointeur sur la feuille de caractere inconnu*/
		tmp=pere(ptr_caractere[256]);
		
		noeud=creer_noeud(pere(tmp), NULL, tmp,1,ordre_gal(tmp));

		if(pere(tmp)!=NULL){
			changer_fils_droit(pere(tmp),noeud);
		}
		/*on creer une nouvelle feuille*/
		fg=creer_feuille(noeud,c,1,ordre_gal(tmp)+1);

		/*on modifie les ordres de gallager*/
		changer_ordre_gal(tmp,ordre_gal(tmp)+2);
		changer_ordre_gal(fils_gauche(tmp), ordre_gal(tmp) + 1);
		changer_ordre_gal(fils_droit(tmp), ordre_gal(tmp) + 2);
		changer_pere(tmp,noeud);
		changer_fils_gauche(noeud,fg);

		/*on met a jour les tableaux*/
		ptr_caractere[c]=fg;
		ptr_ordre_gal[ordre_gal(noeud)-1]=noeud;
		tab_poids[ordre_gal(noeud)-1]=poids(noeud);

		ptr_ordre_gal[ordre_gal(fg)-1]=fg;
		tab_poids[ordre_gal(fg)-1]=poids(fg);
		ptr_ordre_gal[ordre_gal(tmp)-1]=tmp;

		tab_poids[ordre_gal(tmp)-1]=poids(tmp);
		ptr_ordre_gal[ordre_gal(fils_gauche(tmp))-1]=fils_gauche(tmp);
		ptr_ordre_gal[ordre_gal(fils_droit(tmp))-1]=fils_droit(tmp);
	
		tab_poids[ordre_gal(fils_droit(tmp))-1]=poids(fils_droit(tmp));
		tab_poids[ordre_gal(fils_gauche(tmp))-1]=poids(fils_gauche(tmp));

		MAJ(pere(noeud));

		if(pere(a)!=NULL){
			a=noeud;
		}
	}
	
	return a;

}

/*Cette fonction prend en paramètre un pointeur sur un arbre. 
L'objectif de cette fonction est de libérer la mémoire allouer pour l'arbr*/

void my_free(tpa a){
	if(!est_feuille(a)){
		my_free(fils_gauche(a));
		free(fils_gauche(a));
		my_free(fils_droit(a));
		free(fils_droit(a));
	}
}











