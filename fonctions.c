#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<string.h>


int camp_jaune[2]={7,1};
int camp_bleu[2]={1,15};
int camp_vert[2]={7,1};
int camp_rouge[2]={7,1};

void deplacer(int x, int y){
	char chaine[40];
	
	sprintf(chaine,"\033[%d;%dH",x,y);
	if(write(1,chaine,strlen(chaine))==-1)
		{
			perror("write");
			exit(-1);
		}
}


char T[15][15];
int joueur=1;

struct cheval {
	int avancer;
	char pion;
	int x;
	int y;
};
typedef struct cheval cheval;

void partie_joueur2();
void partie_joueur1();
void affiche_plateau2(char T[15][15]);

void afficheregles(){
	printf("LES REGLES DU JEU\n");
	printf("Nombre de Joueurs 2 a  4\n");
	printf("BUT DU JEU\n");
	printf("Faire le tour du plateau avec ses quatre petits chevaux et les rentrer tous a l'ecurie.\n");
}

void camp_haut_gauche()
{
	int i=0,j=0;
	
	for(i=0; i<6; i++)
		 for(j=0; j<6; j++)
	      T[i][j] = ' ' ;
	T[0][0] = 'J' ; T[0][1] = 'J' ; T[1][0] = 'J' ; T[1][1] = 'J' ;	
}

void camp_haut_droite()
{
	int i=0, j=0 ;
	for(i=0; i<6; i++)
	   for(j=9; j<15; j++)
	      T[i][j] = ' ' ;
	T[0][13] = 'B' ; T[0][14] = 'B' ; T[1][13] = 'B' ; T[1][14] = 'B' ;	
}

camp_bas_gauche()
{
	int i=0, j=0 ;
	for(i=9; i<15; i++)
	   for(j=0; j<6; j++)
	      T[i][j] = ' ' ;
	T[13][0] = 'V' ; T[13][1] = 'V' ; T[14][0] = 'V' ; T[14][1] = 'V' ;	
}

void camp_bas_droite()
{
	int i=0, j=0 ;
	for(i=9; i<15; i++)
	   for(j=9; j<15; j++)
	      T[i][j] = ' ' ;
	T[13][13] = 'R' ; T[13][14] = 'R' ; T[14][13] = 'R' ; T[14][14] = 'R' ; 	
}

void chemin_podium(char T[15][15])
{
	T[7][7] = 'X' ;	// Milieu du plateau 
	T[0][7]='E';
	T[1][7]='1';
	T[2][7]='2';
	T[3][7]='3';
	T[4][7]='4';
	T[5][7]='5';
	T[6][7]='6';
	T[7][0]='E';
	T[7][1]='1';
	T[7][2]='2';
	T[7][3]='3';
	T[7][4]='4';
	T[7][5]='5';
	T[7][6]='6';
	T[14][7]='E';
	T[13][7]='1';
	T[12][7]='2';
	T[11][7]='3';
	T[10][7]='4';
	T[9][7]='5';
	T[8][7]='6';
	T[7][14]='E';
	T[7][13]='1';
	T[7][12]='2';
	T[7][11]='3';
	T[7][10]='4';
	T[7][9]='5';
	T[7][8]='6';	
}

void afficheplateau (char T[15][15])
{	
    int i=0, j=0 ;
    
	for(i=0; i<15; i++)
	   for(j=0; j<15; j++)
	      T[i][j] = 'o' ;		// Placement des caracteres o sur le chemin
	camp_haut_gauche();
	camp_haut_droite();
	camp_bas_gauche();
	camp_bas_droite();
	chemin_podium(T);	
	for(i=0; i<15; i++) {
	   for(j=0; j<15; j++)
	      printf("%c   ", T[i][j]) ;	// Affichage des caracteres
	   printf("\r\n") ;
	}
	deplacer(2,1);
	write(1,"*",1);
	
}

int de(int dernier_lancer){
	int i;
	srand(time(NULL));
	i=(rand()+dernier_lancer)%6;
 	return i+1;	//Il n'y a pas 0 sur le de
}

void tour_joueur(int joueur)
{
	int i=0,lancer,sortir;
	cheval camp[2][4];  
	do{
  		if (joueur==1){
  			joueur=2;
  			printf("\nLancement du de pour le joueur %d\n",joueur);
	  		lancer=de(i);
	  		printf("\nde  = %d \n",lancer);
			if(lancer==6){
				printf("Choisissez le cheval a sortir (entre 1 et 4) :");
				scanf("%d",&sortir);
				
				if(sortir!=1)	printf("Pas possible ! Choisissez un autre\n");
				T[7][1]='J';
				//affiche_plateau2(T);
			}
  		}
  		else{
  			joueur=1;
  			printf("\nLancement du de pour le joueur %d\n",joueur);
	  		lancer=de(i);
	  		printf("\nde  = %d \n",lancer);
			if(lancer==6){
				printf("Choisissez le cheval a sortir (entre 1 et 4) :");
				scanf("%d",&sortir);
				
				if(sortir!=1)	printf("Pas possible ! Choisissez un autre\n");
				T[7][15]='R';
				//affiche_plateau2(T);
			}		
		}
	}while(lancer!=6);
}

void choix_camp(int joueur)
{
	char choix;
	
	printf("Entrez votre choix d'ecurie (J,R) :");
	scanf("%s",&choix);
	
	switch(choix){
    	case 'J' : printf("Joueur 1 gere l'ecurie jaune et le joueur 2 gere l'ecurie rouge\n");
	  			 break;
    	case 'R' : printf("Vous gerez l'ecurie rouge et le joueur 2 gere l'ecurie jaune\n");
	  		 	 break;
    	default :  printf("Choix invalide.\n");	
    		   break;
	}	
}

void jeu(){
	int choix;
 
  do
  {
    
    printf ("\n===MENU Joueur===\n");
    printf ("0 - Abandonner.\n");
    printf ("1 - Lancer le de\n");
    printf ("2 - Passer votre tour.\n");
    
    printf ("\nQue voulez-vous faire ? : ");
    scanf ("%d", &choix);
    printf ("\n");
    
    switch (choix)
    {
      case 0 : 		printf ("Vous avez abandonne !\n"); break;
      case 1 : 		choix_camp(joueur);
	  				tour_joueur(joueur);	  			
	  				//partie_joueur1(joueur);
	  				break;
      case 2 : tour_joueur (joueur); break;
      default : printf ("Choix invalide\n");
   }
  }
  while (choix!=0);
}


void plateau_joueur2(char T[15][15])
{
	int i=0, j=0,lancer;
	    	
	for(i=0; i<15; i++)
		for(j=0; j<15; j++)
	      	T[i][j] = 'o' ;
	camp_haut_gauche();
	camp_bas_droite();
	for(i=9; i<15; i++)
	   	for(j=0; j<6; j++)
		T[i][j] = ' ' ;			// Escpace au camp bas gauche
	for(i=0; i<6; i++)
		for(j=9; j<15; j++)
			T[i][j] = ' ' ;		// Escpace au camp haut droite	
	chemin_podium(T);
	for(i=0; i<15; i++) {
		for(j=0; j<15; j++)
	   	printf("%c   ", T[i][j]) ;	// Affichage des caracteres
		printf("\r\n") ;
	}
	jeu();					// Appel de la fonction jeu pour comencer le jeu
}

void plateau_joueur3(char T[15][15])
{
	int i=0, j=0 ;
    
	for(i=0; i<15; i++)
	   for(j=0; j<15; j++)
	      T[i][j] = 'o' ;
	camp_haut_gauche();
	camp_bas_droite();
	camp_haut_droite();
	for(i=9; i<15; i++)
	   for(j=0; j<6; j++)
	      T[i][j] = ' ' ;
	chemin_podium(T);
	for(i=0; i<15; i++) {
	   for(j=0; j<15; j++)
	      printf("%c   ", T[i][j]) ;	// Affichage des caracteres
	   printf("\r\n") ;
	}
}

void plateau_joueur4(char T[15][15])
{
	int i=0, j=0 ;
    
	afficheplateau(T);
}

void jouer()
{
	int i=0,j=0,nbre_joueur=0;
	cheval camp[4][4];
	
	printf("Combien de joueurs ? :");
	scanf("%d",&nbre_joueur);
	
	switch(nbre_joueur){
      	case 0 : printf ("Pas possible ! Il faut au minimum 2 joueurs et au max 4 joueurs\n"); break;
      	case 1 : printf("Pas possible ! Il faut au minimum 2 joueurs et au max 4 joueurs");break;
      	case 2 : plateau_joueur2 (T); break;
      	case 3 : plateau_joueur3(T); break;
      	case 4 : plateau_joueur4(T); break;
      			default : printf ("Choix invalide.\n");
	}
}

void menu ()
{
	int choix;
 
	do
  	{
    
   		printf ("\n\n\n===DEBUT DU JEU===\n");
    		printf ("0 - Abandonner.\n");
    		printf ("1 - Regles du jeu.\n");
    		printf ("2 - Voir le plateau du jeu.\n");
    		printf ("3 - Jouer.\n");

    		printf ("\nEntrez votre choix : ");
    		scanf ("%d", &choix);
    		printf ("\n");

    		switch (choix)
    		{
      			case 0 : printf ("Vous avez abandonne ! Bye \n"); break;
      			case 1 : afficheregles (); break;
      			case 2 : afficheplateau (T); break;
      			case 3 : jouer (); break;
      			default : printf ("Choix invalide.\n");
    		}
  	}
  while (choix!=0);
}


int main()
{
	menu();

	return 0;
}
