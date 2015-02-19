/*
a ajouter a l'affichage ? 

  "Voulez vous donnez un nom aux joueurs?  (O/N):"         //si choix non : "joueur1" et "joueur2" par défault (a afficher)
     "Joueur 1 (pieces blanche), quel est votre nom ? :"
     "joueur 2 (pieces noir)" quel est votre nom ?: "
  "Antoine joue les pièces blanches, Marion les noires" 
  
  "La partie commence !"
  
  affichage();
  "Les pieces blanche sont en MAJUSCULE, les noires en minuscule"
  
  "C'est a Antoine de jouer : 
     quelle piece voulez vous jouer ? (ex : B7) : "
     
  "Antoine choisi  de jouer le pion en B7,
    ou voulez vous la déplacer ? (ex: B4) : "
     
     Le fou a mangé le pion placé en C4 !
     Le fou est déplacé en B3 !
     Le roi noire est en echec !!
            ou
     Impossible... une de vos piece empêche ce mouvement en B2
            ou
     Impossible... votre roi est en echec, vous devez le protéger !


modules :

affichage();
deplacementPiece();  --> et dedant on imbrique la piece
   rechercheCase(); --> renvoi le type de piece, verifie que c'est la bonne couleur via la variable globale "joueurActif"
   deplacementPion();  --> il test lui même qu'il ne 'percute' pas un pion en avançant, il renvoit la la ligne et colonne de la piece percuté
   deplacementFou();  //penser a dire a l'utilisateur si il passe au dessus d'un pion : enemi(lui proposer de le bouffer ?) ou ami 
   deplacementCavalier(); 
   deplacementRoi();
   deplacementReine();
   deplacementTour();
testDiagonalHG(); --> ya t'il une piece dans la diagonal ? (renvoit la colonne et la ligne)    -- pour le FOU, Reine
testDiagonalHD(); --> ya t'il une piece dans la diagonal ? (renvoit la colonne et la ligne)
testDiagonalBG(); --> ya t'il une piece dans la diagonal ? (renvoit la colonne et la ligne)
testDiagonalBD(); --> ya t'il une piece dans la diagonal ? (renvoit la colonne et la ligne)
testLigne(); //pour tour et reine
testColonne();

verifEchecRoidujoueurQuiJoue(CouleurDuRoi);    ---> une piece met en danger le roi, il doit renvoyer un boolean, et si c'est une piece blanche ou une piece noire
      //exemple : celui ci balaye, et utilise que les pieces dans la chaine "tcfqkp" pour tester le "R"

verifEchecRoidujoueurAdverse(CouleurDuRoi);    ---> une piece met en danger le roi, il doit renvoyer un boolean, et si c'est une piece blanche ou une piece noire
      //exemple : celui ci balaye, et utilise que les pieces dans la chaine "TCFQKP" pour tester le "r"
  
  verifPion(couleurduRoi) --> recherche tout les pions et simule leur déplacement, est ce que je touche le roi ?, il renvoit VRAI ou FAUX
  verifFou(couleurduRoi)     //si tu tombe sur le roi de cette couleur,
  verifCavalier(couleurduRoi)
  verifReine(couleurduRoi)
  verifTour(couleurduRoi)
verifEchecMat();    ---> il faut tester tous les déplacements autour du roi
  verifDeplacementRoi()
    verifEchecRoiDujoueurQuiJoue()
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
// ---------------------------------------- Déclaration des fonctions ------------------

void centrage(int millieu);
void affichage();
void deplacementpiece();

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

char alphabet[10]= "ABCDEFGH";  //pour trouver l'emplacement dans le tableau dans la fonction rechercheCase().. A=0, B=1...

int partietermine=0;
char nomVainqueur[20];
char pieceBlanche[20] = "PTCFQK";  //pour qu'on vérifie si c'est une piece blanche
char pieceNoire[20] = "ptcfqk";  //pour qu'on vérifie si c'est une piece noir
char joueurActif[20];           //utilse pour savoir avec qui on joue actuellement. (pendant l'appelle des modules)
char joueurBlanc[20] = "Joueur1";
char joueurNoir[20] = "Joueur2";


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
       
        
        while(partietermine==0)
        {
          affichage();
          printf("-------au joueur BLANC de jouer : (P,T,C,F,Q,K)-------");
          //jouerActif = joueurBlanc;
          deplacementpiece();
          affichage();
          printf("-------au joueur NOIR de jouer : (p,t,c,f,q,k)-------");
          //joueurActif = joueurNoir;
        }
        //printf("la partie est terminé, le vainqueur est : ", nomVainqueur)
      break;
      case 0:
        printf("Au revoir, et a bientot (coquin) !\n");
      break;
    }
}    

// --------------------------------------------- Fonction centrage--------------------

  void centrage (int millieu)//fonction de centrage, pour rendre le programme plus joli
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

// --------------------------------------------- Fonction déplacement de piece--------------------
void deplacementpiece()
{
  printf("quelle piece voulez-vous déplacer ? ( colonne PUIS ligne ex: 3 2");
  
}
