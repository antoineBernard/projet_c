#include <stdio.h>

//void affichage;

main() 
{
    //le compteur pour compter les tours : si c'est impaire c'est au blanc de jouer, sinon c'est au noir
    int choix, compteur,i;
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

    printf("Hello World! et bienvenue le jeu d'échec !\nTaper 1 pour commencer une partie : \n");
    scanf("%d", &choix);
    
    
    switch (choix)
    {
      case 1:
        printf("C'est parti !\n");
        
        //affichage -> dans le futur celui-ci sera une fonction
        printf("        A         B         C         D         E         F         G         H\n");
        printf("------------------------------------------------------------------------------------\n");
        
        for (i=0; i<=7; i++) 
          {
          /*on créé le tableau et le rempli avec la case du tableau t (au dessus)*/
          printf("%d  |    %c    |    %c    |    %c    |    %c    |    %c    |    %c    |    %c    |    %c    |\n", i+1, t[i][0], t[i][1], t[i][2], t[i][3], t[i][4], t[i][5], t[i][6], t[i][7]);
          printf("------------------------------------------------------------------------------------\n");
          }
      break;
    }
}    
  
/*void affichage
{
 
 futur fonction pour afficher le plateau à chaque modification
 
}
*/
