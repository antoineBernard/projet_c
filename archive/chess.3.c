/*

system("clear");

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
     
     
     ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     MODIFICATIONS EFFECTUEES : 25/02
     Marion :
     Ajout de deux modules : testRangeeDroite & testColonneBas (Rangee remplace ligne, terme d'échecs)
     Codage des modules : testRangeeDroite & testRangee Gauche + testColonneHaut & testColonneBas
     Test du programme : pas de problème de buffer de mon coté pour la lecture de la pièce à chercher
     Je laisse ma partie en commentaire tant qu'on aura pas décidé de comment on gère les variables, mais le reste devrait fonctionner.
     C'est plus qu'une question de syntaxe !
     
     PS : Quand tu as lu mets 'OK' à coté de "Marion : ", comme ça j'efface et je mets que ce qui a changé
     
     Antoine :
     
     //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


modules :

affichage();
deplacementPiece();  --> et dedant on imbrique la piece
   rechercheCase(); --> renvoi le type de piece, verifie que c'est la bonne couleur via la variable globale "joueurActif"
   deplacementPion();  --> il test lui même qu'il ne 'percute' pas un pion en avançant, il renvoit la la ligne et colonne de la piece percuté
   deplacementFou();  //penser a dire a l'utilisateur si il passe au dessus d'une piece : enemi(lui proposer de le bouffer ?) ou ami ==> NON : il ne peut pas passer par dessus (Art. 3.5 des règles).
   deplacementCavalier(); 
   deplacementRoi();
   deplacementReine();
   deplacementTour();
testDiagonalHG(); --> ya t'il une piece dans la diagonal ? (indique la colonne et la ligne)    -- pour le FOU, Reine
testDiagonalHD(); --> ya t'il une piece dans la diagonal ? (indique la colonne et la ligne)
testDiagonalBG(); --> ya t'il une piece dans la diagonal ? (indique la colonne et la ligne)
testDiagonalBD(); --> ya t'il une piece dans la diagonal ? (indique la colonne et la ligne)
testRangeeGauche(); //pour tour et reine
testRangeeDroite();
testColonneHaut();
testColonneBas();
        --> TOUT EST OK. RESTE A LES APPELER

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
#define NONTROUVE -1 
// ---------------------------------------- Déclaration des fonctions ------------------

void retoursLigne(int nbLignes);
void affichage();
void deplacementpiece();
char verifCaseChoisie(char charColonne, 
                   int ligne,
                   int intColonne);
void deplacementPion();
void verifDeplacementArrivee();
void deplacementCavalier();
// ---------------------------------------- Déclaration des types en global ------------------
  struct infoCase                              
              {
                char charColonne;
                int ligne;
                int colonne;
              };


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
struct infoCase caseDepart; 
struct infoCase caseArrivee;

// ---------------------------------------- Procédure principale ------------------
main() 
{
    //le compteur pour compter les tours : sera utile pour savoir si il y a égalité (lorsqu'un joueur n'a plus qu'un roi, s'il survit 50 coups ya égalité je crois)
    int choix, compteur,i, millieu;
    
printf("_______________________________________________________________________________________________________\n");
printf("_______________________________________________________________________________________________________\n");
printf("   .d8888b.  888    888 8888888888  .d8888b.   .d8888b.      8888888b. 8888888  .d8888b.   8888888888\n");
printf("  d88P  Y88b 888    888 888        d88P  Y88b d88P  Y88b     888   Y88b  888   d88P  Y88b  888       \n");
printf("  888    888 888    888 888        Y88b.      Y88b.          888    888  888   Y88b.       888       \n");
printf("  888        8888888888 8888888     Y888b.    Y888b.         888   d88P  888    Y888b.     8888888   \n");
printf("  888        888    888 888            Y88b.     Y88b.       8888888P    888       Y88b.   888       \n");
printf("  888    888 888    888 888              888       888       888         888         888   888       \n");
printf("  Y88b  d88P 888    888 888        Y88b  d88P Y88b  d88P     888         888   Y88b  d88P  888       \n");
printf("   Y8888P    888    888 8888888888   Y8888P     Y8888P       888       8888888  Y8888P     8888888888\n");
printf("_______________________________________________________________________________________________________\n");
printf("_______________________________________________________________________________________________________\n\n\n");


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
          //partietermine = 1; //je fake la fin de la partie pour les tests logiciels
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
  char alphabet[10]= "ABCDEFGH";  
  int j = 0;
  caseDepart.colonne = 0 ;
  char bidon;
  char pieceTrouve;
  int ligneArrivee;
  ECHEC = 1; //ECHEC est une variable globale
  while(ECHEC == 1)
  {
      ECHEC = 0;

      bidon = getchar();
      printf("quelle piece voulez-vous déplacer ? ( ex: B3) : ");  
      
      scanf("%c%d", &caseDepart.charColonne, &caseDepart.ligne);
      caseDepart.charColonne = toupper(caseDepart.charColonne);
      
      verifCaseChoisie(caseDepart.charColonne , caseDepart.ligne , caseDepart.colonne);
      caseDepart.ligne--;
      pieceTrouve = t[caseDepart.ligne][caseDepart.colonne] ;

       //rangeeDepart = ligneDepart ;
           
                // A PARTIR D'ICI ON A ACCES AUX VARIABLES caseDepart.colonne, pieceTrouve, caseDepart.ligne pour le reste des fonctions 
        
      retoursLigne(2);
  }
  
  retoursLigne(2);
  
  printf("caseDepart.colonne = %d   pieceTrouve = %c  caseDepart.ligne = %d \n", caseDepart.colonne, pieceTrouve ,caseDepart.ligne);
 
  if(pieceTrouve = 'p')
    {
        deplacementPion();
    }
  else if(pieceTrouve = 't')
    {printf("coucou");}//deplacementTour
  else if(pieceTrouve = 'c')
    {printf("coucou");}//deplacementCavalier
  else if(pieceTrouve = 'f')
    {printf("coucou");}//deplacementFou
  else if(pieceTrouve = 'q')
    {printf("coucou");}//deplacementReine
  else
    {printf("coucou");}//deplacementRoi
}

// --------------------------------------------- Fonction verifCaseChoisie ------------------------------------------------//
char verifCaseChoisie(char charColonne,
                   int ligne,
                   int intColonne)
{
    char alphabet[10]= "ABCDEFGH";  //pour trouver l'emplacement dans le tableau dans la fonction rechercheCase().. A=0, B=1...
    char piecesDuJoueurActif[10];
    char pieceTrouve, bidon;
    int i= 0,j = 0, flagEspace = 0;

    //-------pour trouver l'index de la LETTRE dans l'alphabet ----
    for(i ; i < strlen(alphabet) ; i++)
    {
      if(alphabet[i] == charColonne)
      {
          intColonne = i;
      }
    }
    //-------pour vérifier si la colonne et la ligne existe ----
    if((intColonne < 0) || (intColonne > 7) || (ligne < 1) || (ligne > 8))
    {
        printf("Mauvaise saisie ! A1 est la première case, H8 est la dernière, Veuillez recommencer \n");
        ECHEC = 1;
    }
    else
    {
      char bidon;
      pieceTrouve = t[ligne-1][intColonne];
      // + Je suggère qu'on donne des noms à la colonne et à la ligne de la pièce, c'est utile pour la suite
      printf("la piece trouvée est : %c\n", pieceTrouve);
    
      //---------pour vérifier que c'est une piece de la bonne COULEUR (rien de raciste) -----//
       if(joueurActif == 1)
           {strcpy(piecesDuJoueurActif, piecesBlanches);}
       else
           {strcpy(piecesDuJoueurActif, piecesNoires);}
           
      ECHEC = 1; //je passe ECHEC à 1 avant le test de la COULEUR
      for(j ; j < strlen(piecesDuJoueurActif) ; j++)
      {
          if(piecesDuJoueurActif[j] == pieceTrouve)
          {
            ECHEC = 0; //si il trouve la piece -> c'est bon :) je repasse à 0
          }
          else if(pieceTrouve == ' ')
            flagEspace = 1;
      }
      if(ECHEC == 1)
      {
        if(flagEspace == 1)
            printf("Vous avez choisi une case vide... Veuillez recommencer \n");
        else
            printf("Vous avez choisi une pièce de l'adversaire...Veuillez recommencer \n");
      }
    }
    caseDepart.colonne = intColonne;
}

//------------------------------------------------- procédure déplacement pion ------------------------------------------------ // module terminé
void deplacementPion()
{
    printf("------------------ Je suis dans la méthode déplacementPion\n");
    
    ECHEC = 1; //c'est une variable globale
    while(ECHEC == 1)
    {
        ECHEC == 0 ;
        verifDeplacementArrivee();
        
        if(joueurActif == 1)// si joueur blanc
        {
            printf("caseArrivee ligne : %d  colonne : %d    caseDepart.ligne : %d  colonne %d\n", caseArrivee.ligne, caseArrivee.colonne, caseDepart.ligne, caseDepart.colonne);
            if(( ((caseArrivee.ligne == caseDepart.ligne-1) || (caseArrivee.ligne == caseDepart.ligne-2)) && (caseArrivee.colonne == caseDepart.colonne)) && t[caseArrivee.ligne][caseArrivee.colonne] != ' ')
            {
                printf("Vous ne pouvez pas avancer car une piece bloque le passage... Veuillez recommencer !\n");
                ECHEC = 1;
            }
            else if((caseArrivee.ligne == caseDepart.ligne-2) && (caseArrivee.colonne == caseDepart.colonne) && (caseDepart.ligne == 6)) //pour avancer de deux case
            {
                ECHEC = 0;
            }
            else if (  (caseArrivee.ligne == caseDepart.ligne-1) && ((caseArrivee.colonne == caseDepart.colonne+1) || (caseArrivee.colonne == caseDepart.colonne-1)) && t[caseArrivee.ligne][caseArrivee.colonne] != ' ' )
            {
                printf("------- Vous avez éliminé une piece adverse ! --------");
                ECHEC = 0;
            }
            else if((caseArrivee.ligne != caseDepart.ligne-1) || (caseArrivee.colonne != caseDepart.colonne))
            {
                printf("Mouvement non valide : un pion ne peut se déplacer que d'une case vers l'avant... Veuillez recommencer !\n");
                ECHEC = 1;
            }
            else
            {
                ECHEC = 0 ;
            }
        }
        else if(joueurActif == 2) //si joueur noir
        {
            if(( ((caseArrivee.ligne == caseDepart.ligne+1) || (caseArrivee.ligne == caseDepart.ligne+2)) && (caseArrivee.colonne == caseDepart.colonne)) && t[caseArrivee.ligne][caseArrivee.colonne] != ' ')
            {
                printf("Vous ne pouvez pas avancer car une piece bloque le passage... Veuillez recommencer !\n");
                ECHEC = 1;
            }
            else if((caseArrivee.ligne == caseDepart.ligne+2) && (caseArrivee.colonne == caseDepart.colonne) && (caseDepart.ligne == 1)) //pour avancer de deux case
            {
                ECHEC = 0;
            }
            else if (  (caseArrivee.ligne == caseDepart.ligne+1) && ((caseArrivee.colonne == caseDepart.colonne+1) || (caseArrivee.colonne == caseDepart.colonne-1)) && t[caseArrivee.ligne][caseArrivee.colonne] != ' ' )
            {
                printf("------- Vous avez éliminé une piece adverse ! --------");
                ECHEC = 0;
            }
            else if((caseArrivee.ligne != caseDepart.ligne+1) || (caseArrivee.colonne != caseDepart.colonne))
            {
                printf("Mouvement non valide : un pion ne peut se déplacer que d'une case vers l'avant... Veuillez recommencer !\n");
                ECHEC = 1;
            }
            else
            {
                ECHEC = 0 ;
            }
        }
    }
    
    
    if(ECHEC == 0)
    {
        t[caseArrivee.ligne][caseArrivee.colonne] = t[caseDepart.ligne][caseDepart.colonne]; //je deplace la piece
        t[caseDepart.ligne][caseDepart.colonne] = ' ';
    }
    
}

//------------------------------------------------- procédure verification déplacement de la piece ------------------------------------------------ // 

void verifDeplacementArrivee()
{
  char alphabet[10]= "ABCDEFGH";
  int i = 0;
  char bidon;
  ECHEC =1; //echec est un variable globale
  while(ECHEC == 1) 
  {
    ECHEC = 0;
    printf("Où voulez-vous la déplacer? (ex : C9) : ");
    bidon = getchar();
    scanf("%c%d", &caseArrivee.charColonne, &caseArrivee.ligne);
    caseArrivee.ligne--; //pour que ça corresponde au tableau
    caseArrivee.charColonne = toupper(caseArrivee.charColonne);
    // test + test associé
    
    //-------pour trouver l'index de la LETTRE dans l'alphabet ----
    for(i ; i < strlen(alphabet) ; i++)
    {
      if(alphabet[i] == caseArrivee.charColonne)
      {
          caseArrivee.colonne = i;
      }
    }
    //-------pour vérifier si la colonne et la ligne existe ----
    if((caseArrivee.colonne < 0) || (caseArrivee.colonne > 7) || (caseArrivee.ligne < 0) || (caseArrivee.ligne > 7))
    {
        printf("CaseArrivé.ligne = %d    caseArrivee.colonne = %d", caseArrivee.ligne, caseArrivee.colonne);
        printf("Mauvaise saisie ! A1 est la première case, H8 est la dernière, Veuillez recommencer \n");
        ECHEC = 1 ;
    }
  }
}



void deplacementCavalier(){
    
    
}
/*


//------------------------------------------------- Test de la diagonale haut/gauche ------------------------------------------------ // GO CHAMPIONNE !!
void testDiagonalHG(int intColonne,
                    int ligne,
                    int caseArrivee) // Variable à définir 
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
        ECHEC = 1;
    }
    else
    {
        caseArrivee = pieceTrouve;
        pieceTrouve = ' ';
        printf("Déplacement effectué !\n");
        ECHEC = 0;
    }
    
    //Verif Echec au Roi/Pat
    
}

//..........................................Test de la diagonale haut/droit..........................................//
void testDiagonalHD(int intColonne,
                    int ligne,
                    int caseArrivee)
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
        ECHEC = 1;
    }
    else
    {
        caseArrivee = pieceTrouve;
        pieceTrouve = ' ';
        printf("Déplacement effectué !\n");
        ECHEC = 0;
    }
    
    //Verif Echec au Roi/Pat    
}

//..........................................Test de la diagonale bas/droit..........................................//
void testDiagonalBD(int intColonne,
                    int ligne,
                    int caseArrivee)
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
        ECHEC = 1;
    }
    else
    {
        caseArrivee = pieceTrouve;
        pieceTrouve = ' ';
        printf("Déplacement effectué !\n");
        ECHEC = 0;
    }
    
    //Verif Echec au Roi/Pat    
}

//..........................................Test de la diagonale bas/gauche..........................................//
void testDiagonalBG(int intColonne,
                    int ligne,
                    int caseArrivee)
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
        ECHEC = 1;
    }
    else
    {
        caseArrivee = pieceTrouve;
        pieceTrouve = ' ';
        printf("Déplacement effectué !\n");
        ECHEC = 0;
    }
    
    //Verif Echec au Roi/Pat    
}

//------------------------------------------- Test de la rangée vers la gauche (ligne) -----------------------------------------//
void testRangeeGauche(int intColonneDepart,
                int LigneDepart,
                int caseArrivee)
{
    int i, j = 0, Nope;
    
    for(i = 0 ; i < strlen(piecesDuJoueurActif) ; i++)
    {
        if(piecesDuJoueurActif[i] == caseArrivee)
        {
            Nope = 1;
        }
    }
    
    for(i = intColonneDepart; i> colArrivee; i--)
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
        ECHEC = 1;
    }
    else
    {
        caseArrivee = pieceTrouve;
        pieceTrouve = ' ';
        printf("Déplacement effectué !\n");
        ECHEC = 0;
    }
    
    //Verif Echec au Roi/Pat 
}


//------------------------------------------- Test de la rangée vers la droite (ligne) -----------------------------------------//
void testRangeeDroite(int intColonneDepart,
                      int LigneDepart,
                      int caseArrivee)
{
    int i, j = 0, Nope;
    
    for(i = 0 ; i < strlen(piecesDuJoueurActif) ; i++)
    {
        if(piecesDuJoueurActif[i] == caseArrivee)
        {
            Nope = 1;
        }
    }
    
    for(i = intColonneDepart; i< colArrivee; i++)
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
        ECHEC = 1;
    }
    else
    {
        caseArrivee = pieceTrouve;
        pieceTrouve = ' ';
        printf("Déplacement effectué !\n");
        ECHEC = 0;
    }
    
    //Verif Echec au Roi/Pat 
}

//---------------------------------------------- Test de la colonne vers le Haut -------------------------------------------------//
void testColonneHaut(int intColonne,
                    int ligne,
                    int caseArrivee)
{
        int i, j, Nope;
    
    for(i = 0 ; i < strlen(piecesDuJoueurActif) ; i++)
    {
        if(piecesDuJoueurActif[i] == caseArrivee)
        {
            Nope = 1;
        }
    }
    
    for(j = ligne-1 ; j> ligneArrivee  ; j--)
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
        ECHEC = 1;
    }
    else
    {
        caseArrivee = pieceTrouve;
        pieceTrouve = ' ';
        printf("Déplacement effectué !\n");
        ECHEC = 0;
    }
    
    //Verif Echec au Roi/Pat    
}


//---------------------------------------------- Test de la colonne vers le Bas -------------------------------------------------//
void testColonneHaut(int intColonne,
                    int ligne,
                    int caseArrivee)
{
        int i, j, Nope;
    
    for(i = 0 ; i < strlen(piecesDuJoueurActif) ; i++)
    {
        if(piecesDuJoueurActif[i] == caseArrivee)
        {
            Nope = 1;
        }
    }
    
    for(j = ligne-1 ; j< ligneArrivee  ; j++)
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
        ECHEC = 1;
    }
    else
    {
        caseArrivee = pieceTrouve;
        pieceTrouve = ' ';
        printf("Déplacement effectué !\n");
        ECHEC = 0;
    }
    
    //Verif Echec au Roi/Pat    
}

// */