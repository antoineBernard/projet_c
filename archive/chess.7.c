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



-------TODO------ : 
    - REFACTOR = creation d'un module de eliminationPiece() avec le code issus de la ligne 501 à 585 SEULEMENT LA GESTION DE                          ELIMINATION
    - La gestion du  "il y a une piece amie dans la case d'arrivée" est déjà fait dans VerifDeplacementPiece, tu peux le retirer du code ci-dessus
    -   dans ce refactor, changer les tests avec des boucles (plus efficient)
    - lorsqu'un pion arrive au bout de la map, il devient une reine

    
    
*/
/*
     ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     MODIFICATIONS EFFECTUEES : 02/04
     Marion : Modules terminés (diagonales, rangées et colonnes). Je m'occupe du déroulement et de l'appel pour la semaine prochaine !
     Suggestion : créer un module qui traduit "l'icone" de la pièce (genre 'P') en nom de pièce? (genre Pion)   
                            --- VU par antoine-- -> hésite pas à faire des printf pour débugger :)
     
     Antoine :
     
     //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define NONTROUVE -1 
// ---------------------------------------- Déclaration des fonctions ------------------

void retoursLigne(int nbLignes);
void affichage();
void deplacementPiece();
char verifCaseChoisie(char charColonne, 
                   int ligne,
                   int intColonne);
void deplacementPion();
void verifDeplacementArrivee();
void deplacementCavalier();
void deplacementRoi();
void deplacementReine();
void deplacementFou();
void deplacementTour();
void changementDePiece();
void deplacementFou();
void testColonneHaut();
void testColonneBas();
void testDiagonalBD();
void testDiagonalBG();
void testDiagonalHD();
void testDiagonalHG();
void testRangeeDroite();
void testRangeeGauche();
// ---------------------------------------- Déclaration des types en global ------------------
  struct infoCase                              
              {
                char charColonne;
                int ligne;
                int colonne;
              };
//||

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
char joueurBlanc[20] = "Joueur1";  // A déclarer dans le main?
char joueurNoir[20] = "Joueur2"; 
char piecesDuJoueurActif[10];
int ECHEC, changePiece = 0;
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
          joueurActif = 1;
          printf("-------au joueur BLANC de jouer : (P,T,C,F,Q,K)-------\n");
          deplacementPiece();
          if(changePiece == 1)
          {
             while(changePiece == 1) 
             {
                 affichage();
                 changePiece = 0;
                 deplacementPiece();
             }
          }
          affichage();
          joueurActif = 2;
          printf("-------au joueur NOIR de jouer : (p,t,c,f,q,k)-------\n");
          deplacementPiece();
          if(changePiece == 1)
          {
             while(changePiece == 1) 
             {
                 affichage();
                 changePiece = 0;
                 deplacementPiece();
             }
          }
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
void deplacementPiece()
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
      printf("quelle piece voulez-vous déplacer ? ( ex: B2) : ");  
      
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
 
  if(pieceTrouve == 'p' || pieceTrouve == 'P')
    {
        deplacementPion();
    }
  else if(pieceTrouve == 't' || pieceTrouve == 'T')
    {
        deplacementTour();
    }
  else if(pieceTrouve == 'c' || pieceTrouve == 'C')
    {
        deplacementCavalier();
    }
  else if(pieceTrouve == 'f' || pieceTrouve == 'F')
    {
        deplacementFou();
    }
  else if(pieceTrouve == 'q' || pieceTrouve == 'Q')
    {
        deplacementReine();    
    }
  else if(pieceTrouve == 'k' || pieceTrouve == 'K')
    {
        deplacementRoi();
    }
}

// --------------------------------------------- Fonction verifCaseChoisie ------------------------------------------------//
char verifCaseChoisie(char charColonne,
                   int ligne,
                   int intColonne)
{
    char alphabet[10]= "ABCDEFGH";  //pour trouver l'emplacement dans le tableau dans la fonction rechercheCase().. A=0, B=1...
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
        
        if(changePiece == 0)
        {
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
                else if (  (caseArrivee.ligne == caseDepart.ligne-1) && ((caseArrivee.colonne == caseDepart.colonne+1) || (caseArrivee.colonne == caseDepart.colonne-1)) && (t[caseArrivee.ligne][caseArrivee.colonne] != ' ' &&
                                              t[caseArrivee.ligne][caseArrivee.colonne] != 'P' &&
                                              t[caseArrivee.ligne][caseArrivee.colonne] != 'T' &&
                                              t[caseArrivee.ligne][caseArrivee.colonne] != 'C' &&
                                              t[caseArrivee.ligne][caseArrivee.colonne] != 'F' &&
                                              t[caseArrivee.ligne][caseArrivee.colonne] != 'Q' &&
                                              t[caseArrivee.ligne][caseArrivee.colonne] != 'K') )
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
                else if((caseArrivee.ligne == caseDepart.ligne+2) && (caseArrivee.colonne == caseDepart.colonne) && (caseDepart.ligne == 1)) //pour avancer de deux cases
                {
                    ECHEC = 0;
                }
                else if (  (caseArrivee.ligne == caseDepart.ligne+1) && ((caseArrivee.colonne == caseDepart.colonne+1) || (caseArrivee.colonne == caseDepart.colonne-1)) && (t[caseArrivee.ligne][caseArrivee.colonne] != ' ' &&
                                              t[caseArrivee.ligne][caseArrivee.colonne] != 'p' &&
                                              t[caseArrivee.ligne][caseArrivee.colonne] != 't' &&
                                              t[caseArrivee.ligne][caseArrivee.colonne] != 'c' &&
                                              t[caseArrivee.ligne][caseArrivee.colonne] != 'f' &&
                                              t[caseArrivee.ligne][caseArrivee.colonne] != 'q' &&
                                              t[caseArrivee.ligne][caseArrivee.colonne] != 'k') )
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
    int i = 0, choix = 0;
    char bidon;
    ECHEC =1; //echec est un variable globale

    changementDePiece();
    
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
        //---- Pour vérifier si une pièce du joueur se trouve déjà sur la case d'arrivée
        for(i = 0 ; i < strlen(piecesDuJoueurActif) ; i++)
        {
            if(piecesDuJoueurActif[i] == t[caseArrivee.ligne][caseArrivee.colonne])
            {
                printf("Une de vos pièces est déjà sur la case %c%d\n", 
                caseArrivee.charColonne, caseArrivee.ligne + 1);
                ECHEC = 1;
            }
        }
    }
}

//------------------------------------------------- procédure déplacement Cavalier ------------------------------------------------ 
void deplacementCavalier(){
    printf("------------------ Je suis dans la méthode déplacementCavalier\n");
    ECHEC = 1; //c'est une variable globale

    
    while(ECHEC == 1)
    {
        ECHEC = 0 ;
        verifDeplacementArrivee(); 
        
        if(changePiece == 0)//il n'a pas choisi de changer de piece
        {
            
            
            if((caseArrivee.ligne == caseDepart.ligne-2 && caseArrivee.colonne == caseDepart.colonne-1) ||
               (caseArrivee.ligne == caseDepart.ligne-2 && caseArrivee.colonne == caseDepart.colonne+1) ||
               (caseArrivee.ligne == caseDepart.ligne-1 && caseArrivee.colonne == caseDepart.colonne-2) ||
               (caseArrivee.ligne == caseDepart.ligne-1 && caseArrivee.colonne == caseDepart.colonne+2) ||
               (caseArrivee.ligne == caseDepart.ligne+2 && caseArrivee.colonne == caseDepart.colonne-1) ||
               (caseArrivee.ligne == caseDepart.ligne+2 && caseArrivee.colonne == caseDepart.colonne+1) ||               
               (caseArrivee.ligne == caseDepart.ligne+1 && caseArrivee.colonne == caseDepart.colonne-2) ||
               (caseArrivee.ligne == caseDepart.ligne+1 && caseArrivee.colonne == caseDepart.colonne+2))
            {
                printf("mouvement licite\n");
                if(joueurActif == 1)
                {
                    if(t[caseArrivee.ligne][caseArrivee.colonne] == ' ')
                    {
                        ECHEC = 0;
                    }
                    else if(t[caseArrivee.ligne][caseArrivee.colonne] == 'p' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 't' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'c' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'f' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'q' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'k')
                    {
                         printf("------- Vous avez éliminé une piece adverse ! --------"); 
                         ECHEC = 0;
                    }
                    else if(t[caseArrivee.ligne][caseArrivee.colonne] == 'P' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'T' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'C' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'F' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'Q' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'K')
                    {
                        printf("Une de vos pieces est sur la case d'arrivée.. recommencez\n"); 
                        ECHEC = 1;
                    }
                    else
                    {
                        ECHEC = 1;
                    }
                }
                else if(joueurActif == 2)
                {
                    if(t[caseArrivee.ligne][caseArrivee.colonne] == ' ')
                    {
                        ECHEC = 0;
                    }
                    else if(t[caseArrivee.ligne][caseArrivee.colonne] == 'P' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'T' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'C' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'F' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'Q' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'K')
                    {
                        printf("------- Vous avez éliminé une piece adverse ! --------"); 
                        ECHEC = 0;
                    }
                    else if(t[caseArrivee.ligne][caseArrivee.colonne] == 'p' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 't' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'c' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'f' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'q' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'k')
                    {
                        printf("Une de vos pieces est sur la case d'arrivée.. recommencez\n"); 
                        ECHEC = 1;
                    }
                    else
                    {
                        ECHEC = 1;
                    }
                }  
            }
            else
            {
                printf("Mouvement non valide, souvenez-vous, le cavalier se déplace en 'L'");
                ECHEC = 1;
            }
        }
   
    }
    
   if(ECHEC == 0 && changePiece == 0)
   {
        t[caseArrivee.ligne][caseArrivee.colonne] = t[caseDepart.ligne][caseDepart.colonne];         //je deplace la piece
        t[caseDepart.ligne][caseDepart.colonne] = ' ';
   }
}
//------------------------- Deplacement Roi ------------------------------//
void deplacementRoi()
{
    printf("------------------ Je suis dans la méthode déplacementRoi\n");
    ECHEC = 1 ;
    
    while(ECHEC == 1)
    {
        ECHEC == 0 ;
        verifDeplacementArrivee();
        printf("--- je viens de sortie de verifDeplacementArrivee\n");
        if(changePiece == 0)
        {
            if((caseArrivee.ligne == caseDepart.ligne-1) && (caseArrivee.colonne == caseDepart.colonne)  ||
               (caseArrivee.ligne == caseDepart.ligne-1) && (caseArrivee.colonne == caseDepart.colonne+1)||
               (caseArrivee.ligne == caseDepart.ligne)   && (caseArrivee.colonne == caseDepart.colonne+1)||
               (caseArrivee.ligne == caseDepart.ligne+1) && (caseArrivee.colonne == caseDepart.colonne+1)||
               (caseArrivee.ligne == caseDepart.ligne+1) && (caseArrivee.colonne == caseDepart.colonne)  || 
               (caseArrivee.ligne == caseDepart.ligne+1) && (caseArrivee.colonne == caseDepart.colonne-1)||
               (caseArrivee.ligne == caseDepart.ligne)   && (caseArrivee.colonne == caseDepart.colonne-1)  ||
               (caseArrivee.ligne == caseDepart.ligne-1) && (caseArrivee.colonne == caseDepart.colonne-1))
            {
                printf("mouvement licite\n");
                if(joueurActif == 1)
                {
                    if(t[caseArrivee.ligne][caseArrivee.colonne] == ' ')
                    {
                        ECHEC = 0;
                    }
                    else if(t[caseArrivee.ligne][caseArrivee.colonne] == 'p' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 't' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'c' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'f' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'q' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'k')
                    {
                         printf("------- Vous avez éliminé une piece adverse ! --------"); 
                         ECHEC = 0;
                    }
                    else if(t[caseArrivee.ligne][caseArrivee.colonne] == 'P' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'T' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'C' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'F' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'Q' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'K')
                    {
                        printf("Une de vos pieces est sur la case d'arrivée.. recommencez\n"); 
                        ECHEC = 1;
                    }
                    else
                    {
                        ECHEC = 1;
                    }
                }
                else if(joueurActif == 2)
                {
                    if(t[caseArrivee.ligne][caseArrivee.colonne] == ' ')
                    {
                        ECHEC = 0;
                    }
                    else if(t[caseArrivee.ligne][caseArrivee.colonne] == 'P' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'T' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'C' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'F' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'Q' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'K')
                    {
                        printf("------- Vous avez éliminé une piece adverse ! --------"); 
                        ECHEC = 0;
                    }
                    else if(t[caseArrivee.ligne][caseArrivee.colonne] == 'p' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 't' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'c' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'f' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'q' ||
                            t[caseArrivee.ligne][caseArrivee.colonne] == 'k')
                    {
                        printf("Une de vos pieces est sur la case d'arrivée.. recommencez\n"); 
                        ECHEC = 1;
                    }
                    else 
                    {
                        ECHEC = 1;
                    }
                }  
            }
            else
            {
                printf("Mouvement non valide, souvenez-vous, le roi se déplace d'une case autour de lui\n");
                ECHEC = 1;
            }
        }
    }
    
   if(ECHEC == 0 && changePiece == 0)
   {
        t[caseArrivee.ligne][caseArrivee.colonne] = t[caseDepart.ligne][caseDepart.colonne];         //je deplace la piece
        t[caseDepart.ligne][caseDepart.colonne] = ' ';
   }
}
//------------------------- Deplacement Reine -----------------------------//
void deplacementReine()
{
    printf("---je suis dans deplacementReine");
    ECHEC = 1;
    
    while(ECHEC == 1)
    {
        ECHEC = 0 ;
        verifDeplacementArrivee(); 
        
        if(changePiece == 0)//il n'a pas choisi de changer de piece
        {
            if(caseDepart.ligne != caseArrivee.ligne && caseDepart.colonne != caseArrivee.colonne)
            {
                if(caseDepart.ligne > caseArrivee.ligne && caseDepart.colonne > caseArrivee.colonne)
                {
                    testDiagonalHG();
                }
                else if(caseDepart.ligne > caseArrivee.ligne && caseDepart.colonne < caseArrivee.colonne)
                {
                    testDiagonalHD();
                }
                else if(caseDepart.ligne < caseArrivee.ligne && caseDepart.colonne < caseArrivee.colonne)
                {
                    testDiagonalBD();
                }
                else if(caseDepart.ligne < caseArrivee.ligne && caseDepart.colonne > caseArrivee.colonne)
                {
                    testDiagonalBG();
                }
            }
            else
            {
                if(caseDepart.ligne == caseArrivee.ligne && caseDepart.colonne > caseArrivee.colonne)
                {
                    testRangeeGauche();
                }
                else if(caseDepart.ligne == caseArrivee.ligne && caseDepart.colonne < caseArrivee.colonne)
                {
                    testRangeeDroite();
                }
                else if(caseDepart.ligne > caseArrivee.ligne && caseDepart.colonne == caseArrivee.colonne)
                {
                    testColonneBas();
                }
                else if(caseDepart.ligne > caseArrivee.ligne && caseDepart.colonne == caseArrivee.colonne)
                {
                    testColonneHaut();
                }
            }
        }
    }    
}

//-------------------------- Deplacement Tour --------------------------------//
void deplacementTour()
{
    printf("-----je suis dans deplacementTour");
    ECHEC = 1;
    
    while(ECHEC == 1)
    {
        ECHEC = 0 ;
        verifDeplacementArrivee(); 
        
        if(changePiece == 0)//il n'a pas choisi de changer de piece
        {
            if(caseDepart.ligne == caseArrivee.ligne || caseDepart.colonne == caseArrivee.colonne)
            {
                if(caseDepart.ligne == caseArrivee.ligne && caseDepart.colonne > caseArrivee.colonne)
                {
                    testRangeeGauche();
                }
                else if(caseDepart.ligne == caseArrivee.ligne && caseDepart.colonne < caseArrivee.colonne)
                {
                    testRangeeDroite();
                }
                else if(caseDepart.ligne > caseArrivee.ligne && caseDepart.colonne == caseArrivee.colonne)
                {
                    testColonneBas();
                }
                else if(caseDepart.ligne > caseArrivee.ligne && caseDepart.colonne == caseArrivee.colonne)
                {
                    testColonneHaut();
                }
            }
            else
            {
                printf("Erreur de déplacement !");
            }
        }
    }    
}
//-------------------------- Deplacement Fou -------------------------------//
void deplacementFou()
{
    printf("---- je suis dans deplacementFou");
    ECHEC = 1;
    
    while(ECHEC == 1)
    {
        ECHEC = 0 ;
        verifDeplacementArrivee(); 
        
        if(changePiece == 0)//il n'a pas choisi de changer de piece
        {
            if(caseDepart.ligne != caseArrivee.ligne && caseDepart.colonne != caseArrivee.colonne)
            {
                if(caseDepart.ligne > caseArrivee.ligne && caseDepart.colonne > caseArrivee.colonne)
                {
                    testDiagonalHG();
                }
                else if(caseDepart.ligne > caseArrivee.ligne && caseDepart.colonne < caseArrivee.colonne)
                {
                    testDiagonalHD();
                }
                else if(caseDepart.ligne < caseArrivee.ligne && caseDepart.colonne < caseArrivee.colonne)
                {
                    testDiagonalBD();
                }
                else if(caseDepart.ligne < caseArrivee.ligne && caseDepart.colonne > caseArrivee.colonne)
                {
                    testDiagonalBG();
                }
            }
            else
            {
                printf("Erreur de déplacement !");
            }
            
        }    
    }
}

//-------------------------- Module changementDePiece -----------------------//
void changementDePiece()
{
    printf("---------------je suis entrée dans la méthode changementDePiece");
    changePiece = 0;
    int choix;
    printf("---------------------------------\n");
    printf("--  1- Déplacer la piece       --\n");
    printf("--  2- Choisir une autre piece --\n");
    printf("---------------------------------\n");
    scanf("%d", &choix);
    
    switch(choix)
    {
        case 1:
        break;
        
        case 2:
            ECHEC = 0;
            changePiece = 1;
        break;
    }
}

//------------------------------------------------- Test de la diagonale haut/gauche ------------------------------------------------ // GO CHAMPIONNE !!
void testDiagonalHG()
{
    printf("----- testDiagonalHG");
    int i, j, Nope;
    char pieceBloquante;
    

    
    //---- Pour vérifier si aucune pièce ne bloque le passage (en remontant en haut à gauche)
    for(i = caseDepart.ligne, j = caseDepart.colonne; i> caseArrivee.ligne , j> caseArrivee.colonne; i--, j--)
    {
        if(t[i][j] != ' ')
        {
            Nope = 2;
            pieceBloquante = t[i][j];
        }
        
    }
    
    if(Nope == 1 && Nope == 2)
    {
        printf("Une de vos pièces est déjà sur la case %c%d, et la pièce %c y bloque l'accès\n", 
        caseArrivee.charColonne, caseArrivee.ligne, pieceBloquante);
        ECHEC = 1;
    }
    else if(Nope == 1)
    {
        printf("Une de vos pièces est déjà sur cette case !\n");
        ECHEC = 1;
    }
    else if(Nope == 2)
    {
        printf("La pièce *nom pièce* en %c%d bloque le passage\n", 
        caseArrivee.charColonne, caseArrivee.ligne);
        ECHEC = 1;
    }
    else
    {
        t[caseArrivee.ligne][caseArrivee.colonne] = t[caseDepart.ligne][caseDepart.colonne];
        t[caseDepart.ligne][caseDepart.colonne] = ' ';
        printf("Déplacement effectué !\n");
        ECHEC = 0;
    }
    
    //Verif Echec au Roi/Pat
    
}

//..........................................Test de la diagonale haut/droit..........................................//
void testDiagonalHD()
{
    printf("----- testDiagonalHD");
    int i, j, Nope;
    char pieceBloquante;
    
    //---- Pour vérifier si une pièce du joueur se trouve déjà sur la case d'arrivée
    for(i = 0 ; i < strlen(piecesDuJoueurActif) ; i++)
    {
        if(piecesDuJoueurActif[i] == t[caseArrivee.ligne][caseArrivee.colonne])
        {
            Nope = 1;
        }
    }
    
    //---- Pour vérifier si aucune pièce ne bloque le passage (en remontant en haut à droite)
    for(i = caseDepart.ligne, j = caseDepart.colonne; i> caseArrivee.ligne , j< caseArrivee.colonne; i--, j++)
    {
        if(t[i][j] != ' ')
        {
            Nope = 2;
            pieceBloquante = t[i][j];
        }
        
    }
    
    if(Nope == 1 && Nope == 2)
    {
        printf("Une de vos pièces est déjà sur la case %c%d, et la pièce %c y bloque l'accès\n", 
        caseArrivee.charColonne, caseArrivee.ligne, pieceBloquante);
        ECHEC = 1;
    }
    else if(Nope == 1)
    {
        printf("Une de vos pièces est déjà sur cette case !\n");
        ECHEC = 1;
    }
    else if(Nope == 2)
    {
        printf("La pièce %c en %c%d bloque le passage\n", 
        pieceBloquante, caseArrivee.charColonne, caseArrivee.ligne);
        ECHEC = 1;
    }
    else
    {
        t[caseArrivee.ligne][caseArrivee.colonne] = t[caseDepart.ligne][caseDepart.colonne];
        t[caseDepart.ligne][caseDepart.colonne] = ' ';
        printf("Déplacement effectué !\n");
        ECHEC = 0;
    }
    
    //Verif Echec au Roi/Pat
    
}

//..........................................Test de la diagonale bas/droit..........................................//
void testDiagonalBD()

{
    printf("----- testDiagonalBD");    
    int i, j, Nope;
    char pieceBloquante;
    
    //---- Pour vérifier si une pièce du joueur se trouve déjà sur la case d'arrivée
    for(i = 0 ; i < strlen(piecesDuJoueurActif) ; i++)
    {
        if(piecesDuJoueurActif[i] == t[caseArrivee.ligne][caseArrivee.colonne])
        {
            Nope = 1;
        }
    }
    
    //---- Pour vérifier si aucune pièce ne bloque le passage (en se déplaçant vers le bas et la gauche)
    for(i = caseDepart.ligne, j = caseDepart.colonne; i< caseArrivee.ligne , j< caseArrivee.colonne; i++, j++)
    {
        if(t[i][j] != ' ')
        {
            Nope = 2;
            pieceBloquante = t[i][j];
        }
        
    }
    
    if(Nope == 1 && Nope == 2)
    {
        printf("Une de vos pièces est déjà sur la case %c%d, et la pièce %c y bloque l'accès\n", 
        caseArrivee.charColonne, caseArrivee.ligne, pieceBloquante);
        ECHEC = 1;
    }
    else if(Nope == 1)
    {
        printf("Une de vos pièces est déjà sur cette case !\n");
        ECHEC = 1;
    }
    else if(Nope == 2)
    {
        printf("La pièce %c en %c%d bloque le passage\n", 
        pieceBloquante, caseArrivee.charColonne, caseArrivee.ligne);
        ECHEC = 1;
    }
    else
    {
        t[caseArrivee.ligne][caseArrivee.colonne] = t[caseDepart.ligne][caseDepart.colonne];
        t[caseDepart.ligne][caseDepart.colonne] = ' ';
        printf("Déplacement effectué !\n");
        ECHEC = 0;
    }
    
    //Verif Echec au Roi/Pat
    
}



//..........................................Test de la diagonale bas/gauche..........................................//
void testDiagonalBG()
{
    printf("----- testDiagonalBG");    
    int i, j, Nope;
    char pieceBloquante;
    
    //---- Pour vérifier si une pièce du joueur se trouve déjà sur la case d'arrivée
    for(i = 0 ; i < strlen(piecesDuJoueurActif) ; i++)
    {
        if(piecesDuJoueurActif[i] == t[caseArrivee.ligne][caseArrivee.colonne])
        {
            Nope = 1;
        }
    }
    
    //---- Pour vérifier si aucune pièce ne bloque le passage (en descendant vers la gauche)
    for(i = caseDepart.ligne, j = caseDepart.colonne; i< caseArrivee.ligne , j> caseArrivee.colonne; i++, j--)
    {
        if(t[i][j] != ' ')
        {
            Nope = 2;
            pieceBloquante = t[i][j];
        }
        
    }
    
    if(Nope == 1 && Nope == 2)
    {
        printf("Une de vos pièces est déjà sur la case %c%d, et la pièce %c y bloque l'accès\n", 
        caseArrivee.charColonne, caseArrivee.ligne, pieceBloquante);
        ECHEC = 1;
    }
    else if(Nope == 1)
    {
        printf("Une de vos pièces est déjà sur cette case !\n");
        ECHEC = 1;
    }
    else if(Nope == 2)
    {
        printf("La pièce %c en %c%d bloque le passage\n", 
        pieceBloquante, caseArrivee.charColonne, caseArrivee.ligne);
        ECHEC = 1;
    }
    else
    {
        t[caseArrivee.ligne][caseArrivee.colonne] = t[caseDepart.ligne][caseDepart.colonne];
        t[caseDepart.ligne][caseDepart.colonne] = ' ';
        printf("Déplacement effectué !\n");
        ECHEC = 0;
    }
    
    //Verif Echec au Roi/Pat
    
}

//------------------------------------------- Test de la rangée vers la gauche (ligne) -----------------------------------------//
void testRangeeGauche()
{
    printf("----- testRangeeGauche");
    int i, j, Nope;
    char pieceBloquante;
    
    //---- Pour vérifier si une pièce du joueur se trouve déjà sur la case d'arrivée
    for(i = 0 ; i < strlen(piecesDuJoueurActif) ; i++)
    {
        if(piecesDuJoueurActif[i] == t[caseArrivee.ligne][caseArrivee.colonne])
        {
            Nope = 1;
        }
    }
    
    //---- Pour vérifier si aucune pièce ne bloque le passage (vers la gauche)
    for(i = caseDepart.colonne; i> caseArrivee.colonne; i--)
    {
        if(t[i][j] != ' ')
        {
            Nope = 2;
            pieceBloquante = t[i][j];
        }
    }
    
    if(Nope == 1 && Nope == 2)
    {
        printf("Une de vos pièces est déjà sur la case %c%d, et la pièce %c y bloque l'accès\n", 
        caseArrivee.charColonne, caseArrivee.ligne, pieceBloquante);
        ECHEC = 1;
    }
    else if(Nope == 1)
    {
        printf("Une de vos pièces est déjà sur cette case !\n");
        ECHEC = 1;
    }
    else if(Nope == 2)
    {
        printf("La pièce %c en %c%d bloque le passage\n", 
        pieceBloquante, caseArrivee.charColonne, caseArrivee.ligne);
        ECHEC = 1;
    }
    else
    {
        t[caseArrivee.ligne][caseArrivee.colonne] = t[caseDepart.ligne][caseDepart.colonne];
        t[caseDepart.ligne][caseDepart.colonne] = ' ';
        printf("Déplacement effectué !\n");
        ECHEC = 0;
    }
    
    //Verif Echec au Roi/Pat
    
}



//------------------------------------------- Test de la rangée vers la droite (ligne) -----------------------------------------//
void testRangeeDroite()

{
    printf("----- testRangeeDroite");    
    int i, j, Nope;
    char pieceBloquante;
    
    //---- Pour vérifier si une pièce du joueur se trouve déjà sur la case d'arrivée
    for(i = 0 ; i < strlen(piecesDuJoueurActif) ; i++)
    {
        if(piecesDuJoueurActif[i] == t[caseArrivee.ligne][caseArrivee.colonne])
        {
            Nope = 1;
        }
    }
    
    //---- Pour vérifier si aucune pièce ne bloque le passage (vers la droite)
    for(i = caseDepart.colonne; i< caseArrivee.colonne; i++)
    {
        if(t[i][j] != ' ')
        {
            Nope = 2;
            pieceBloquante = t[i][j];
        }
    }
    
    if(Nope == 1 && Nope == 2)
    {
        printf("Une de vos pièces est déjà sur la case %c%d, et la pièce %c y bloque l'accès\n", 
        caseArrivee.charColonne, caseArrivee.ligne, pieceBloquante);
        ECHEC = 1;
    }
    else if(Nope == 1)
    {
        printf("Une de vos pièces est déjà sur cette case !\n");
        ECHEC = 1;
    }
    else if(Nope == 2)
    {
        printf("La pièce %c en %c%d bloque le passage\n", 
        pieceBloquante, caseArrivee.charColonne, caseArrivee.ligne);
        ECHEC = 1;
    }
    else
    {
        t[caseArrivee.ligne][caseArrivee.colonne] = t[caseDepart.ligne][caseDepart.colonne];
        t[caseDepart.ligne][caseDepart.colonne] = ' ';
        printf("Déplacement effectué !\n");
        ECHEC = 0;
    }
    
    //Verif Echec au Roi/Pat
    
}


//---------------------------------------------- Test de la colonne vers le Haut -------------------------------------------------//
void testColonneHaut()
{
    printf("-----je suis dans testColonneHaut");
    int i, j, Nope;
    char pieceBloquante;
    
    //---- Pour vérifier si une pièce du joueur se trouve déjà sur la case d'arrivée
    for(i = 0 ; i < strlen(piecesDuJoueurActif) ; i++)
    {
        if(piecesDuJoueurActif[i] == t[caseArrivee.ligne][caseArrivee.colonne])
        {
            Nope = 1;
        }
    }
    
    //---- Pour vérifier si aucune pièce ne bloque le passage (vers le haut)
    for(j = caseDepart.ligne; j > caseArrivee.ligne; j--)
    {
        if(t[i][j] != ' ')
        {
            Nope = 2;
            pieceBloquante = t[i][j];
        }
    }
    
    if(Nope == 1 && Nope == 2)
    {
        printf("Une de vos pièces est déjà sur la case %c%d, et la pièce %c y bloque l'accès\n", 
        caseArrivee.charColonne, caseArrivee.ligne, pieceBloquante);
        ECHEC = 1;
    }
    else if(Nope == 1)
    {
        printf("Une de vos pièces est déjà sur cette case !\n");
        ECHEC = 1;
    }
    else if(Nope == 2)
    {
        printf("La pièce %c en %c%d bloque le passage\n", 
        pieceBloquante, caseArrivee.charColonne, caseArrivee.ligne);
        ECHEC = 1;
    }
    else
    {
        t[caseArrivee.ligne][caseArrivee.colonne] = t[caseDepart.ligne][caseDepart.colonne];
        t[caseDepart.ligne][caseDepart.colonne] = ' ';
        printf("Déplacement effectué !\n");
        ECHEC = 0;
    }
    
    //Verif Echec au Roi/Pat
    
}

//---------------------------------------------- Test de la colonne vers le Bas -------------------------------------------------//
void testColonneBas()
{
    printf("-----je suis dans testColonneBas");
    int i, j, Nope;
    char pieceBloquante;
    
    //---- Pour vérifier si une pièce du joueur se trouve déjà sur la case d'arrivée
    for(i = 0 ; i < strlen(piecesDuJoueurActif) ; i++)
    {
        if(piecesDuJoueurActif[i] == t[caseArrivee.ligne][caseArrivee.colonne])
        {
            Nope = 1;
        }
    }
    
    //---- Pour vérifier si aucune pièce ne bloque le passage (vers le haut)
    for(j = caseDepart.ligne; j < caseArrivee.ligne; j++)
    {
        if(t[i][j] != ' ')
        {
            Nope = 2;
            pieceBloquante = t[i][j];
        }
    }
    
    if(Nope == 1 && Nope == 2)
    {
        printf("Une de vos pièces est déjà sur la case %c%d, et la pièce %c y bloque l'accès\n", caseArrivee.charColonne, caseArrivee.ligne, pieceBloquante);
        ECHEC = 1;
    }
    else if(Nope == 1)
    {
        printf("Une de vos pièces est déjà sur cette case !\n");
        ECHEC = 1;
    }
    else if(Nope == 2)
    {
        printf("La pièce %c en %c%d bloque le passage\n", pieceBloquante, caseArrivee.charColonne, caseArrivee.ligne);
        ECHEC = 1;
    }
    else
    {
        t[caseArrivee.ligne][caseArrivee.colonne] = t[caseDepart.ligne][caseDepart.colonne];
        t[caseDepart.ligne][caseDepart.colonne] = ' ';
        printf("Déplacement effectué !\n");
        ECHEC = 0;
    }
    
    //Verif Echec au Roi/Pat
}