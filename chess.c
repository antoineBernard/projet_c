/*
modules :

affichage()
deplacementPiont()
deplacementFou()
deplacementCavalier()
deplacementRoi()
deplacementReine()
deplacementTour()
verifEchec
verifEchecMat

*/



#include <stdio.h>
#include <string.h>
#include <ctype.h>
// ---------------------------------------- Déclaration des fonctions ------------------

char centrage(int millieu);
void affichage();



// ---------------------------------------- Déclaration des variables globales ------------------
    //!rappel! les tableaux en C : j'indique le nombre de case
char t[8] [8]={
    't','c','f','q','k','f','c','t',
    'p','p','p','p','p','p','p','p',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    'P','P','P','P','P','P','P','P',
    'T','C','F','Q','K','F','C','T'
}; 
int partietermine=0;
char nomVainqueur(20);

// ---------------------------------------- Procédure principale ------------------

main() 
{
    //le compteur pour compter les tours : si c'est impaire c'est au blanc de jouer, sinon c'est au noir
    int choix, compteur,i, millieu;

   printf("Hello World! et bienvenue sur le jeu d'échec !\n\n");
   printf("-------------    MENU      ----------------\n");
   printf("     |   -1- Commencer une partie     |\n");
   printf("     |   -0- QUITTER                    |\n");
   printf("-------------------------------------------\n");
   printf("choix : ");
    scanf("%d", &choix);
    
    switch (choix)
    {
      case 1:
        printf("C'est parti !\n");
        affichage();
        
        while(partietermine=0)
        {
          
          
          
          
        }
        
        //printf("la partie est terminé, le vainqueur est : ", vainqueur)
      break;
      
      case 0:
        printf("Au revoir, et a bientot !\n");
      break;
    }
}    

// --------------------------------------------- Fonction centrage--------------------

  char centrage (int millieu)//fonction de centrage, pour rendre le programme plus joli
{
  int nbEspace;
  for(nbEspace=1 ; nbEspace <= (millieu) ; nbEspace++)
  printf(" ");
}
 
// --------------------------------------------- Fonction affichage du plateau--------------------
  
void affichage()
{
  int i;
  printf("        A         B         C         D         E         F         G         H\n");
  printf("-----------------------------------------------------------------------------------\n");
  
  for (i=0; i<=7; i++) 
    {
    /*on créé le tableau et le remplit avec la case du tableau t*/
    printf("%d  |    %c    |    %c    |    %c    |    %c    |    %c    |    %c    |    %c    |    %c    |\n", i+1, t[i][0], t[i][1], t[i][2], t[i][3], t[i][4], t[i][5], t[i][6], t[i][7]);
    printf("------------------------------------------------------------------------------------\n");
    }
}

