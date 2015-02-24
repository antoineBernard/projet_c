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
     Le roi noir est en echec !!
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
#define NONTROUVE -1 //en C, -1 est utilisé dans les booléens
// ---------------------------------------- Déclaration des fonctions ------------------

void retoursLigne(int nbLignes);
void affichage();
void deplacementpiece();
char rechercheCase(char charColonne, 
                   int *p_ligne,
                   int *p_intColonne,
                   char *p_pieceTrouve);

// ---------------------------------------- Déclaration des variables globales ------------------
    //!rappel! les tableaux en C : j'indique le nombre de case
    
    // t[0][0] = t     t[0][1] = c    t[6][6] = P
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
char nomVainqueur[20];
char piecesBlanches[10] = "PTCFQK";  //pour qu'on vérifie si c'est une piece blanche
char piecesNoires[10] = "ptcfqk";  //pour qu'on vérifie si c'est une piece noire
int joueurActif;           //utilse pour savoir avec qui on joue actuellement. 1 = blanc, 2 = noir
char joueurBlanc[20] = "Joueur1";
char joueurNoir[20] = "Joueur2";
int ECHEC;

// ---------------------------------------- Procédure principale ------------------
main() 
{
    //le compteur pour compter les tours : sera utile pour savoir si il y a égalité (lorsqu'un joueur n'a plus qu'un roi, s'il survit 50 coups ya égalité je crois)s
    int choix, compteur,i, millieu;

   printf("Hello World! et bienvenue sur le jeu d'échec !\n\n");
   printf("-------------    MENU      ----------------\n");
   printf("     |   -1- Commencer une partie       |\n");
   printf("     |   -0- QUITTER                    |\n");
   printf("-------------------------------------------\n");
   printf("choix : ");
   scanf("%d", &choix);
    
    switch (choix)
    {
      case 1:
        retoursLigne(2);
        printf("C'est parti !\n");
       
        
        while(partietermine == 0)
        {
          affichage();
          printf("-------au joueur BLANC de jouer : (P,T,C,F,Q,K)-------\n");
          joueurActif = 1;
          deplacementpiece();
          affichage();
          printf("-------au joueur NOIR de jouer : (p,t,c,f,q,k)-------\n");
          joueurActif = 2;
          deplacementpiece();
          partietermine == 1; //je fake la fin de la partie pour les tests logiciels
        }
        //printf("la partie est terminé, le vainqueur est : ", nomVainqueur)
      break;
      case 0:
        printf("Au revoir, et a bientot (coquin) !\n");
      break;
    }
}    

// --------------------------------------------- Fonction retours ligne--------------------

  void retoursLigne(int nbLignes) // Pourquoi ne pas mettre ça dans affichage()? Ce serait moins lourd et plus compréhensible pour quelqu'un de l'extérieur
{
  int i;
  for(i=1 ; i <= nbLignes ; i++)
  printf("\n");
}
 
// --------------------------------------------- Fonction affichage du plateau--------------------
void affichage()
{
  int i;
  retoursLigne(5);
  printf("        A         B         C         D         E         F         G         H\n");
  printf("-----------------------------------------------------------------------------------\n");
  
  for (i=0; i<=7; i++) 
    {
    /*on créé le tableau et le remplit avec la case du tableau t*/
    printf("%d  |    %c    |    %c    |    %c    |    %c    |    %c    |    %c    |    %c    |    %c    |\n", i+1, t[i][0], t[i][1], t[i][2], t[i][3], t[i][4], t[i][5], t[i][6], t[i][7]);
    printf("------------------------------------------------------------------------------------\n");
    }
  retoursLigne(5);
}

// --------------------------------------------- Fonction déplacement de piece--------------------
void deplacementpiece()
{
  char charColonneDepart, charColonneArrivee, bidon;
  char pieceTrouve = 'm', *p_pieceTrouve = &pieceTrouve; //la fonction recherchePiece renverra la vraie piece
  int intColonneDepart = -1 , *p_intColonneDepart = &intColonneDepart, ligneDepart, *p_ligneDepart = &ligneDepart; //*p_variable est un pointeur, &variable c'est ce qu'il pointe.
  int ligneArrivee;
  ECHEC = 1; //ECHEC est une variable globale
  while(ECHEC == 1)
  {
      ECHEC = 0;

      bidon = getchar(); // --> Vidage du buffer avant la saisie, parce que la première donnée lue est un char. De rien <3
      printf("quelle piece voulez-vous déplacer ? ( ex: B3) : ");  //GROS PROBLEME DE BUFFER LORQUE QU'ON REPOND 3 char par exemple.. grave ? ça peut mettre fin à la partie
      scanf("%c%d", &charColonneDepart, &ligneDepart);
      rechercheCase(charColonneDepart,
                    p_ligneDepart, 
                    p_intColonneDepart,
                    p_pieceTrouve);
                    
                    
                    
                    
                    
                // A PARTIR D'ICI ON A ACCES AU VARIABLE intColonneDepart, pieceTrouve, LigneDepart pour le reste des fonctions 
                
        
        
      retoursLigne(2);          
      //printf("intColonneDepart : %d  -- pieceTrouve : %c -- ligneDepart : %d\n", intColonneDepart, pieceTrouve, ligneDepart);
  }
  
  retoursLigne(2);
  printf("Où voulez-vous la déplacer? (ex : C9) : ");
  bidon = getchar();
  scanf("%c%d", &charColonneArrivee, &ligneArrivee);
    // test + test associé
}

// --------------------------------------------- Fonction recherche Piece ------------------------------------------------//
char rechercheCase(char charColonne, 
                   int *p_ligne,
                   int *p_intColonne,
                   char *p_pieceTrouve)
{
    char alphabet[10]= "ABCDEFGH";  //pour trouver l'emplacement dans le tableau dans la fonction rechercheCase().. A=0, B=1...
    char piecesDuJoueurActif[10];
    char bidon;
    int i = 0, j = 0;

    //-------pour trouver l'index de la LETTRE dans l'alphabet ----
    for(i ; i < strlen(alphabet) ; i++)
    {
      if(alphabet[i] == charColonne)
      {
          *p_intColonne = i;
      }
    }
//-------pour vérifier si la colonne et la ligne existe ----
    if((*p_intColonne < 0) || (*p_intColonne > 7) || (*p_ligne < 1) || (*p_ligne > 8))
    {
        printf("Mauvaise saisie ! A1 est la première case, H8 est la dernière, Veuillez recommencer \n");
        ECHEC = 1;
    }
    else
    {
      char bidon;
      *p_pieceTrouve = t[*p_ligne-1][*p_intColonne];
      // + Je suggère qu'on donne des noms à la colonne et à la ligne de la pièce, c'est utile pour la suite
      printf("la piece trouvée est : %c\n", *p_pieceTrouve); // Faut qu'on discute de cette pieceTrouve...
    
      //---------pour vérifier que c'est une piece de la bonne COULEUR (rien de raciste) -----
       if(joueurActif == 1)
           strcpy(piecesDuJoueurActif, piecesBlanches);//lorsque joueurActif = 1 (voir le main) alors les pieces de références à prendre sont TCFQKP en MAJuscule
       else
           strcpy(piecesDuJoueurActif, piecesNoires);
           
      ECHEC = 1; //je passe ECHEC à 1 avant le test de la COULEUR
      for(j ; j < strlen(piecesDuJoueurActif) ; j++)
      {
          if(piecesDuJoueurActif[j] == *p_pieceTrouve)
          {
            ECHEC = 0; //si il trouve la piece -> c'est bon :) je repasse à 0
          }
      }
      if(ECHEC == 1)
      {
        printf("Vous avez choisi une pièce de l'adversaire...Veuillez recommencer \n");
      }
    }
}

/*


//------------------------------------------------- Test de la diagonale haut/gauche ------------------------------------------------ // GO CHAMPIONNE !!
void testDiagonalHG(int intColonne,
                    int ligne,
                    int caseArrivee, // Variable à définir
                    int ECHEC) 
{
    int i, j, Nope;
    
    
    for(i = 0 ; i < strlen(piecesDuJoueurActif) ; i++)
    {
        if(piecesDuJoueurActif[i] == caseArrivee)
        {

            Nope = 1;
        }
    }
    
    for(i = intColonne, j = ligne-1 ; i> colArrivee , j> ligneArrivee  ; i--, j--)
    {
        if(t[i][j] != ' ')
        {
            Nope = 2;
        }
        
    }
    
    if(Nope == 1 && Nope == 2)
    {
        printf("Une de vos pièces est déjà sur la case *ex : B3*, et la pièce *nom pièce* y bloque l'accès\n");
        ECHEC = 1;
    }
    else if(Nope == 1)
    {
        printf("Une de vos pièces est déjà sur cette case !\n");
        ECHEC = 1;
    }
    else if(Nope == 2)
    {
        printf("La pièce *nom pièce* en *ex : B3* bloque le passage\n");
        ECHEC = 0;
    }
    else
    {
        caseArrivee = pieceTrouve;
        pieceTrouve = ' ';
        printf("Déplacement effectué !\n");
    }
    
    //Verif Echec au Roi/Pat
    
}

//..........................................Test de la diagonale haut/droit..........................................//
void testDiagonalHD(int intColonne,
                    int ligne,
                    int caseArrivee,
                    int ECHEC)
{
    int i, j, Nope;
    
        for(i = 0 ; i < strlen(piecesDuJoueurActif) ; i++)
    {
        if(piecesDuJoueurActif[i] == caseArrivee)
        {

            Nope = 1;
        }
    }
    
    for(i = intColonne, j = ligne-1 ; i< colArrivee , j> ligneArrivee  ; i++, j--)
    {
        if(t[i][j] != ' ')
        {
            Nope = 2;
        }
    }
    
    if(Nope == 1 && Nope == 2)
    {
        printf("Une de vos pièces est déjà sur la case *ex : B3*, et la pièce *nom pièce* y bloque l'accès\n");
        ECHEC = 1;
    }
    else if(Nope == 1)
    {
        printf("Une de vos pièces est déjà sur cette case !\n");
        ECHEC = 1;
    }
    else if(Nope == 2)
    {
        printf("La pièce *nom pièce* en *ex : B3* bloque le passage\n");
        ECHEC = 0;
    }
    else
    {
        caseArrivee = pieceTrouve;
        pieceTrouve = ' ';
        printf("Déplacement effectué !\n");
    }
    
    //Verif Echec au Roi/Pat    
}

//..........................................Test de la diagonale bas/droit..........................................//
void testDiagonalBD(int intColonne,
                    int ligne,
                    int caseArrivee,
                    int ECHEC)
{
        int i, j, Nope;
    
    for(i = 0 ; i < strlen(piecesDuJoueurActif) ; i++)
    {
        if(piecesDuJoueurActif[i] == caseArrivee)
        {
            Nope = 1;
        }
    }
    
    for(i = intColonne, j = ligne-1 ; i< colArrivee , j< ligneArrivee  ; i++, j++)
    {
        if(t[i][j] != ' ')
        {
            Nope = 2;
        }
    }
    
    if(Nope == 1 && Nope == 2)
    {
        printf("Une de vos pièces est déjà sur la case *ex : B3*, et la pièce *nom pièce* y bloque l'accès\n");
        ECHEC = 1;
    }
    else if(Nope == 1)
    {
        printf("Une de vos pièces est déjà sur cette case !\n");
        ECHEC = 1;
    }
    else if(Nope == 2)
    {
        printf("La pièce *nom pièce* en *ex : B3* bloque le passage\n");
        ECHEC = 0;
    }
    else
    {
        caseArrivee = pieceTrouve;
        pieceTrouve = ' ';
        printf("Déplacement effectué !\n");
    }
    
    //Verif Echec au Roi/Pat    
}

//..........................................Test de la diagonale bas/gauche..........................................//
void testDiagonalBG(int intColonne,
                    int ligne,
                    int caseArrivee,
                    int ECHEC)
{
        int i, j, Nope;
    
    for(i = 0 ; i < strlen(piecesDuJoueurActif) ; i++)
    {
        if(piecesDuJoueurActif[i] == caseArrivee)
        {
            Nope = 1;
        }
    }
    
    for(i = intColonne, j = ligne-1 ; i> colArrivee , j< ligneArrivee  ; i--, j++)
    {
        if(t[i][j] != ' ')
        {
            Nope = 2;
        }
    }
    
    if(Nope == 1 && Nope == 2)
    {
        printf("Une de vos pièces est déjà sur la case *ex : B3*, et la pièce *nom pièce* y bloque l'accès\n");
        ECHEC = 1;
    }
    else if(Nope == 1)
    {
        printf("Une de vos pièces est déjà sur cette case !\n");
        ECHEC = 1;
    }
    else if(Nope == 2)
    {
        printf("La pièce *nom pièce* en *ex : B3* bloque le passage\n");
        ECHEC = 0;
    }
    else
    {
        caseArrivee = pieceTrouve;
        pieceTrouve = ' ';
        printf("Déplacement effectué !\n");
    }
    
    //Verif Echec au Roi/Pat    
}


*/