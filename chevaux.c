#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

char T[15][15];
char j1[4], j2[4],j3[4],j4[4];
int joueur=1;


int main()
{
	initialiser(T);
	menu();

	return 0;
}


/*
int sortir_pion(char T[15][15], int joueur,cheval camp[2][4])
{
	int i,sortir;
	
	printf("Choisissez le cheval a sortir (entre 1 et 4) :");
	scanf("%d",&sortir);
	//sortir--;
	if(camp[joueur][sortir].danslecamp == 1)	dedans=1;		// On verifie si le cheval est dans le camp	
	if(sortir > 3)	dedans=0;					
	
	for(i=0;i<3;i++){
		if(camp[joueur][i].avancer==0){
			dedans=0;
			printf("Le cheval ne peux pas sortir ! choisissez un autre\n");
		}
	}
	if(dedans==1){
		printf("Le cheval est sortis !\n");
		camp[joueur][sortir].danslecamp=0;
		camp[joueur][sortir].avancer=0;
		camp[joueur][sortir].coord[0]=camp[joueur][sortir].x;
		camp[joueur][sortir].coord[1]=camp[joueur][sortir].y;
		camp[joueur][sortir].passage= T[camp[joueur][sortir].x][camp[joueur][sortir].y];
		T[camp[joueur][sortir].x][camp[joueur][sortir].y]=(camp[joueur][sortir].pion);

	}
}
*/
