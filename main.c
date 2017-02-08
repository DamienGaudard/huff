#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbres.h"
#include "fichier.h"
#include "codage.h"

#define N 200
/*Cette fonction permet d'obtenir l'extension d'un fichier.*/
char * extension_fichier (char * fichier){
    int i,j, l;
    char * extension_f;
    l = strlen(fichier)-1;
    i=0;
    j=l-1;
    while(i==0 && j>0){
        if(fichier[j]=='.')i=j;
        j--;
    }
    extension_f=(char *)malloc(sizeof(char)*(l-j));
    j=j+2;
    l=l-j+1;
    for (i=0; i<=l;i++){
        extension_f[i] = fichier[j++];
    }
    return extension_f;
}
/*Cette fonction ajoute une extension au nom d'un fichier.*/
char * ajouter_extension(char * fichier, char * extension){
    char *tmp;
    int i=0;
    tmp=(char*)malloc(sizeof(char)*(strlen(fichier)+strlen(extension)+1));
    while(fichier[i]!='\0'){
        tmp[i]=fichier[i];
        i++;
    }
    tmp[i]='\0';
    tmp=strcat(tmp,extension);
    return tmp;
}

int main(int argc, char **argv){
    tpa a;
    int x, r;
    char * f_destination;
    char f_source[N];
        

	printf("===============================================================================\n");
        printf("|                                 BIENVENUE				      |\n");
        printf("|									      |\n");
        printf("|                  Ceci est un programme de compression et		      |\n");
        printf("|               décompression basé sur l'algorithme de Huffman. 	      |\n");
        printf("|									      |\n");
        printf("|		   Auteurs : Anaïs AIT SAID & Damien GAUDARD		      |\n");
        printf("===============================================================================\n\n");
    do {
        
        printf("\n");
        printf("Sélectionnez l'action que vous voulez effectuer\n");
        printf("1 : compresser\n");
        printf("2 : décompresser\n");
        printf("0 : quitter\n");
        scanf("%d", &x);
        
        
        switch(x)
        {
                
            case(1) : // Compression
                
                printf("\n");
                printf("Félicitation ! Vous avez choisit la COMPRESSION !\n");
                printf("Entrez le nom du fichier à compresser (y compris son extension) : ");
                scanf("%s",f_source);
                
                r = ouvrir_fichieri(f_source);
                if(!r){
		    printf("Raté ! Aucun fichier ne porte ce nom dans le dossier où nous nous trouvons !\n");
                    printf("Appuyez sur entrée pour continuer.\n");
		    getchar();
                    getchar();
                }
                else{
                    f_destination = ajouter_extension(f_source, ".huffman");
                    ouvrir_fichierf(f_destination);
                    a = init_arbre();
                    initialisation_buffer();
                    a = encoder(a);
                    libere_buffer();
                    my_free(a);
                    fermer_fichierf();
                    fermer_fichieri();
                    printf("C'est fait, %s a été créé ! \nAppuyez sur entrée pour continuer. \n", f_destination);
                    getchar();
                    getchar();
                }
                
                break ;
                
            case(2) : // Décompression
		
		printf("\n");
                printf("Félicitation ! Vous avez choisit la DECOMPRESSION !\n");
                printf("Entrez le nom du fichier à décompresser (y compris son extension) : ");
                scanf("%s",f_source);
                
                if(strcmp(extension_fichier(f_source),"huffman")){
		    printf("Raté ! On ne peut pas décompresser un fichier qui ne porte pas l'extension .huffman !\n");
                    printf("Appuyez sur entrée pour continuer.\n");
                    getchar();
		    getchar();
                }
                else{
                    r = ouvrir_fichieri(f_source);
                    if(!r){
		    	printf("Raté ! Aucun fichier ne porte ce nom dans le dossier où nous nous trouvons !\n");
                    	printf("Appuyez sur entrée pour continuer.\n");
			getchar();
                        getchar();
                    }
                    else{
                        f_destination = f_source;
                        f_destination[strlen(f_destination)-8] = '\0';
                        ouvrir_fichierf(f_destination);
                        a = init_arbre();
                        initialisation_buffer();
                        a = decoder(a);
                        my_free(a);
                        fermer_fichierf();
                    	fermer_fichieri();
                    	printf("C'est fait, %s a été restauré ! \nAppuyez sur entrée pour continuer. \n", f_destination);
                        getchar();
                        getchar();
                    }
                }
                break ;
                
        }
        
    } while(x!=0) ;   
    return 0;
}


