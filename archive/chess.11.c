/*

system("clear");

a ajouter a l'affichage ? 

  "Voulez vous donnez un nom aux joueurs?  (O/N):"         //si choix non : "joueur1" et "joueur2" par défault (a afficher)
     "Joueur 1 (pieces blanche), quel est votre nom ? :"
     "joueur 2 (pieces noir)" quel est votre nom ?: "
  "Antoine joue les pièces blanchmake cees, Marion les noires" 
  
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
    -   test de saisie (plusieurs)
    -   pouvoir abandonner la partie
    -   travailler sur l'ergonomie
    -   dans testSiEchec(), factoriser pour que la boucle s'arrête dès le premier echec
    - Possibilité d'enregistrement
    - Possibilité de quitter la partie (ou d'abandonner) en cours de partie        (system("clear");)
    - 

    
    
*/
/*
     ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     MODIFICATIONS EFFECTUEES : 13/04
     Marion : Pour verifCaseChoisie : enlève les paramètres et véfifie qu'elle s'utilise avec les variables globales, c'est tout =)
     
     Antoine :
     12/04 -> la gestion de la mise en echec est quasiment fini (il reste qu'a gérer le test des diagonales), tout fonctionne          parfaitement :) on peut déjà jouer avec : tour, pion, cavalier avec la gestion de la mise en ECHEC.
     
     //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define NONTROUVE -1 
// ---------------------------------------- Déclaration des fonctions ------------------

void affichage();
void deplacementPiece();
char verifCaseChoisie(char charColonne, 
                   int ligne,
                   int intColonne);
void deplacementPion();
void verifDeplacementArrivee();
void verifEliminationPiece();
void deplacementCavalier();
void deplacementRoi();
void changementDePiece();
void deplacementReineFouTour();
void testRangeesColonnes();
void testDiagonales();
void testSiEchec();
    void affichageEchecRoiBlanc();
    void affichageEchecRoiNoire();
    void testSiPat();
    void testDevant(int i, int j);
    void testArriere(int i, int j);
    void testDroite(int i, int j);
    void testGauche(int i, int j);
    void testDiagoHG(int i, int j);
    void testDiagoHD(int i, int j);
    void testDiagoBG(int i, int j);
    void testDiagoBD(int i, int j);
void testSiEchecEtMat();


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
int RoiBlancEnECHEC = 0;
int RoiNoireEnECHEC = 0;

// ---------------------------------------- Procédure principale ------------------
main() 
{
    //le compteur pour compter les tours : sera utile pour savoir si il y a égalité (lorsqu'un joueur n'a plus qu'un roi, s'il survit 50 coups ya égalité je crois)
    int choix, compteur,i, milieu;
    
printf("_______________________________________________________________________________________________________\n");
printf("_______________________________________________________________________________________________________\n");
printf("   .d8888b.  888    888 8888888888  .d8888b.   .d8888b.      8888888b. 8888888  .d8888b.   8888888888   *\n");
printf("  d88P  Y88b 888    888 888        d88P  Y88b d88P  Y88b     888   Y88b  888   d88P  Y88b  888       \n");
printf("  888    888 888    888 888        Y88b.      Y88b.          888    888  888   Y88b.       888       \n");
printf("  888        8888888888 8888888     Y888b.    Y888b.         888   d88P  888    Y888b.     8888888   \n");
printf("  888        888    888 888            Y88b.     Y88b.       8888888P    888       Y88b.   888       \n");
printf("  888    888 888    888 888              888       888       888         888         888   888       \n");
printf("  Y88b  d88P 888    888 888        Y88b  d88P Y88b  d88P     888         888   Y88b  d88P  888       \n");
printf("   Y8888P    888    888 8888888888   Y8888P     Y8888P       888       8888888  Y8888P     8888888888\n");
printf("_______________________________________________________________________________________________________\n");
printf("_______________________________________________________________________________________________________\n\n\n");
printf("                                                                                                       \n");
printf("                        *Jeux video garanti sans colorant ni conservateur*     \n");
printf("\n\n\n\n\n");


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
        printf("\n\n");
        printf("C'est parti !\n");
       
        
        while(partietermine == 0)
        {
          affichage();
          joueurActif = 1;
          printf("------- Au joueur BLANC de jouer : (P,T,C,F,Q,K) -------\n");
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
          printf("------- Au joueur NOIR de jouer : (p,t,c,f,q,k) -------\n");
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
        //printf("la partie est terminée, le vainqueur est : ", nomVainqueur)
      break;
      case 0:
        printf("Au revoir, et a bientot (coquin) !\n");
      break;
    }
}    
 
// --------------------------------------------- Fonction affichage du plateau--------------------
void affichage()
{
  int i;
  printf("\n\n\n\n\n");
  printf("        A         B         C         D         E         F         G         H\n");
  printf("-----------------------------------------------------------------------------------\n");
  
  for (i=0; i<=7; i++) 
    {
    /*on créé le tableau et le remplit avec la case du tableau t*/
    printf("%d  |    %c    |    %c    |    %c    |    %c    |    %c    |    %c    |    %c    |    %c    |\n", i+1, t[i][0], t[i][1], t[i][2], t[i][3], t[i][4], t[i][5], t[i][6], t[i][7]);
    printf("------------------------------------------------------------------------------------\n");
    }
    if(joueurActif == 1)
    {
         printf("                       ____________________________________ \n");
         printf("                       ----- Au joueur BLANC de jouer ! ----\n");
    }
    else if(joueurActif == 2)
    {
         printf("                       ____________________________________ \n");
         printf("                       ----- Au joueur NOIR de jouer ! ----\n");
    }
    
    if(RoiBlancEnECHEC == 1)
    { 
        printf("                    ****** ROI BLANC EN ECHEC ! ********\n");
    }
    else if(RoiNoireEnECHEC == 1)
    {
        printf("                    ****** ROI NOIR EN ECHEC ! ********\n");
    }
  printf("\n\n\n\n\n");
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
      pieceTrouve = toupper(pieceTrouve);

       //rangeeDepart = ligneDepart ;
           
                // A PARTIR D'ICI ON A ACCES AUX VARIABLES caseDepart.colonne, pieceTrouve, caseDepart.ligne pour le reste des fonctions 
        
      printf("\n\n");
  }
  
  printf("\n\n");
  
  printf("caseDepart.colonne = %d   pieceTrouve = %c  caseDepart.ligne = %d \n", caseDepart.colonne, pieceTrouve ,caseDepart.ligne);
 
  if(pieceTrouve == 'P')
    {
        deplacementPion();
    }
  else if(pieceTrouve == 'C')
    {
        deplacementCavalier();
    }
  else if(pieceTrouve == 'Q' || pieceTrouve == 'F' || pieceTrouve == 'T')
    {
        deplacementReineFouTour();
    }
  else if(pieceTrouve == 'K')
    {
        deplacementRoi();
    }
}

// --------------------------------------------- Fonction verifCaseChoisie ------------------------------------------------//
char verifCaseChoisie()
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

//------------------------------------------------- procédure déplacement pion ------------------------------------------------ 
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
            
            if(joueurActif == 1)
            {
                if(((caseArrivee.ligne == caseDepart.ligne-2) && 
                     (caseArrivee.colonne == caseDepart.colonne)) && 
                     t[caseArrivee.ligne-1][caseArrivee.colonne] != ' ')
                    {
                        printf("Vous ne pouvez pas avancer car une piece bloque le passage... Veuillez recommencer !\n");
                        ECHEC = 1;
                    }
                else if(  ( (caseArrivee.ligne == caseDepart.ligne-2) && 
                            (caseArrivee.colonne == caseDepart.colonne) && 
                            (caseDepart.ligne == 6) ) //pour avancer de deux case
                       || ( (caseArrivee.ligne == caseDepart.ligne-1) && (caseArrivee.colonne == caseDepart.colonne) ) 
                       || (
                            (caseArrivee.ligne == caseDepart.ligne-1) && 
                            ( (caseArrivee.colonne == caseDepart.colonne-1) || (caseArrivee.colonne == caseDepart.colonne+1) ) &&
                            (  t[caseArrivee.ligne][caseArrivee.colonne] != ' ' &&
                               t[caseArrivee.ligne][caseArrivee.colonne] != 'P' &&
                               t[caseArrivee.ligne][caseArrivee.colonne] != 'T' &&
                               t[caseArrivee.ligne][caseArrivee.colonne] != 'C' &&
                               t[caseArrivee.ligne][caseArrivee.colonne] != 'F' &&
                               t[caseArrivee.ligne][caseArrivee.colonne] != 'Q' &&
                               t[caseArrivee.ligne][caseArrivee.colonne] != 'K'  )
                          )
                       )
                    {
                        printf("mouvement licite\n");
                        testSiEchec();
                        if(ECHEC == 0)
                        {    
                          verifEliminationPiece();
                        }
                    }
                else
                {
                    printf("Mouvement non valide, souvenez-vous, le pion se déplace d'une case en avant, veuillez recommencer !");
                    ECHEC = 1;
                }
            }
            if(joueurActif == 2)
            {
                if(((caseArrivee.ligne == caseDepart.ligne+2) && 
                     (caseArrivee.colonne == caseDepart.colonne)) && 
                     t[caseArrivee.ligne+1][caseArrivee.colonne] != ' ')
                    {
                        printf("Vous ne pouvez pas avancer car une piece bloque le passage... Veuillez recommencer !\n");
                        ECHEC = 1;
                    }
                else if(  ( (caseArrivee.ligne == caseDepart.ligne+2) && 
                            (caseArrivee.colonne == caseDepart.colonne) && 
                            (caseDepart.ligne == 1) ) //pour avancer de deux case
                       || ( (caseArrivee.ligne == caseDepart.ligne+1) && (caseArrivee.colonne == caseDepart.colonne) ) 
                       || (
                            (caseArrivee.ligne == caseDepart.ligne+1) && 
                            ( (caseArrivee.colonne == caseDepart.colonne-1) || (caseArrivee.colonne == caseDepart.colonne+1) ) &&
                            (  t[caseArrivee.ligne][caseArrivee.colonne] != ' ' &&
                               t[caseArrivee.ligne][caseArrivee.colonne] != 'p' &&
                               t[caseArrivee.ligne][caseArrivee.colonne] != 't' &&
                               t[caseArrivee.ligne][caseArrivee.colonne] != 'c' &&
                               t[caseArrivee.ligne][caseArrivee.colonne] != 'f' &&
                               t[caseArrivee.ligne][caseArrivee.colonne] != 'q' &&
                               t[caseArrivee.ligne][caseArrivee.colonne] != 'k'  )
                          )
                       )
                    {
                        printf("mouvement licite\n");
                        testSiEchec();
                        if(ECHEC == 0)
                        {    
                          verifEliminationPiece();
                        }
                    }
                else
                {
                    printf("Mouvement non valide, souvenez-vous, le pion se déplace d'une case en avant, veuillez recommencer !");
                    ECHEC = 1;
                }
            }
        }  
    }
            
        if(ECHEC == 0 && changePiece == 0)
        {
            if((joueurActif == 1) && (caseArrivee.ligne == 0)) //si il arrive au bout il devient une reine
            {
                t[caseArrivee.ligne][caseArrivee.colonne] = 'Q';  
            }
            else if((joueurActif == 2) && (caseArrivee.ligne == 7))
            {
                t[caseArrivee.ligne][caseArrivee.colonne] = 'q';  
            }
            else
            {
            t[caseArrivee.ligne][caseArrivee.colonne] = t[caseDepart.ligne][caseDepart.colonne]; 
            }
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
    RoiBlancEnECHEC = 0;
    RoiNoireEnECHEC = 0;
    
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


//------------------------------------------------- procédure de gestion de l'élimination------------------------------------------------ // 

void verifEliminationPiece()
{
    printf("--------------je suis entrée dans verifEliminationPiece, et ECHEC = %d\n",ECHEC );
    
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
             printf("------- Vous avez éliminé une piece adverse ! --------\n"); 
             ECHEC = 0;
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
            printf("------- Vous avez éliminé une piece adverse ! --------\n"); 
            ECHEC = 0;
        }
    }
}

//------------------------------------------------- procédure déplacement Cavalier ------------------------------------------------ 
void deplacementCavalier()
{
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
                testSiEchec();
                if(ECHEC == 0)
                {    
                   testSiEchec();
                   if(ECHEC == 0)
                   {    
                        verifEliminationPiece();
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
               (caseArrivee.ligne == caseDepart.ligne)   && (caseArrivee.colonne == caseDepart.colonne-1)||
               (caseArrivee.ligne == caseDepart.ligne-1) && (caseArrivee.colonne == caseDepart.colonne-1))
            {
                printf("mouvement licite\n");
                
                testSiEchec();
                if(ECHEC == 0)
                {    
                    verifEliminationPiece();
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

//------------------------- Deplacement Reine/Fou/Tour --------------------//
void deplacementReineFouTour()
{
    printf("--- Je suis dans deplacementReineFouTour\n");
    ECHEC = 1;
    int i = caseDepart.ligne, j = caseDepart.colonne;
    char pieceChoisie = toupper(t[i][j]);
    
    while(ECHEC == 1)
    {
        ECHEC = 0;
        verifDeplacementArrivee();
        
        if(changePiece == 0)
        {
            if((pieceChoisie == 'Q' || pieceChoisie == 'F') 
            && caseDepart.ligne != caseArrivee.ligne && caseDepart.colonne != caseArrivee.colonne)
            {
                printf("--- Deplacement de la reine ou du fou en diagonale\n");
                printf("Mouvement licite\n");
                testDiagonales();
                testSiEchec();
            }
            else if((pieceChoisie == 'Q' || pieceChoisie == 'T') 
            && (caseDepart.ligne == caseArrivee.ligne || caseDepart.colonne == caseArrivee.colonne))
            {
                printf("--- Deplacement de la reine ou de la tour en colonne ou rangee\n");
                printf("Mouvement licite\n");
                testRangeesColonnes();
                testSiEchec();
            }
            else
            {
                printf("Mouvement non valide\n");
                ECHEC = 1;
            }
        }
    }
    
    
    if(ECHEC == 0 && changePiece == 0)
    {
        verifEliminationPiece();
        t[caseArrivee.ligne][caseArrivee.colonne] = t[caseDepart.ligne][caseDepart.colonne];         //je deplace la piece
        t[caseDepart.ligne][caseDepart.colonne] = ' ';
        printf("Déplacement effectué !\n");
    }
}

//-------------------------- Module changementDePiece -----------------------//
void changementDePiece()
{
    printf("---------------je suis entrée dans la méthode changementDePiece\n");
    changePiece = 0;
    int choix;
    printf("---------------------------------\n");
    printf("--  1- Déplacer la piece       --\n");
    printf("--  2- Choisir une autre piece --\n");
    /*if(*roque possible*)
    {
    printf("--  3- Faire un roque          --\n");
    }
    */
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
         /*
        case 3:
            ECHEC = 0;
            jeRoque();
        break;
        */
    }
}

//---------------------------- Test Diagonales ---------------------------//
void testDiagonales()
{
    printf("je rentre !!!!!\n");
    int i, j;
    char pieceBloquante;
    char alphabet[10] = "ABCDEFGH";
    
    printf("--- Deplacement de la reine ou du fou en diagonale\n");
    if(caseDepart.ligne > caseArrivee.ligne && caseDepart.colonne > caseArrivee.colonne)
    {
        printf("----- testDiagonalHG\n");

        //---- Pour vérifier si aucune pièce ne bloque le passage (en remontant en haut à gauche)
        for(i = caseDepart.ligne-1, j = caseDepart.colonne-1; i> caseArrivee.ligne , j> caseArrivee.colonne; i--, j--)
        {
            if(t[i][j] != ' ')
            {
                ECHEC = 1;
                pieceBloquante = t[i][j];
            }
        }
    }
    else if(caseDepart.ligne > caseArrivee.ligne && caseDepart.colonne < caseArrivee.colonne)
    {
        printf("----- testDiagonalHD\n");
        
        //---- Pour vérifier si aucune pièce ne bloque le passage (en remontant en haut à droite)
        for(i = caseDepart.ligne-1, j = caseDepart.colonne+1; i> caseArrivee.ligne , j< caseArrivee.colonne; i--, j++)
        {
            if(t[i][j] != ' ')
            {
                ECHEC = 1;
                pieceBloquante = t[i][j];
            }
        }
    }
    else if(caseDepart.ligne < caseArrivee.ligne && caseDepart.colonne < caseArrivee.colonne)
    {
        printf("----- testDiagonalBD\n");    
        
        //---- Pour vérifier si aucune pièce ne bloque le passage (en se déplaçant vers le bas et la gauche)
        for(i = caseDepart.ligne+1, j = caseDepart.colonne+1; i< caseArrivee.ligne , j< caseArrivee.colonne; i++, j++)
        {
            if(t[i][j] != ' ')
            {
                ECHEC = 1;
                pieceBloquante = t[i][j];
            }
        }
    }
    else if(caseDepart.ligne < caseArrivee.ligne && caseDepart.colonne > caseArrivee.colonne)
    {
        printf("----- testDiagonalBG\n");    
        
        //---- Pour vérifier si aucune pièce ne bloque le passage (en descendant vers la gauche)
        for(i = caseDepart.ligne+1, j = caseDepart.colonne-1; i< caseArrivee.ligne , j> caseArrivee.colonne; i++, j--)
        {
            if(t[i][j] != ' ')
            {
                ECHEC = 1;
                pieceBloquante = t[i][j];
            }
        }
    }
    
        
    if(ECHEC == 1)
    {
        printf("La pièce %c en %c%d bloque le passage\n", pieceBloquante, alphabet[j], (i+1));
    }
    else
    {
        ECHEC = 0 ;
    }
    
    //Verif Echec au Roi/Pat
}

//----------------------- Test Rangées & Colonnes --------------------------//
void testRangeesColonnes()
{
    char pieceBloquante;
    char alphabet[10]= "ABCDEFGH";
    int i, j;
    
    //------ Test Rangée Gauche
    if(caseDepart.ligne == caseArrivee.ligne && caseDepart.colonne > caseArrivee.colonne)
    {
        printf("----- testRangeeGauche");
        i = caseDepart.ligne;
    
        //---- Pour vérifier si aucune pièce ne bloque le passage (vers la gauche)
        for(j = caseDepart.colonne-1; j > caseArrivee.colonne; j--)
        {
            if(t[i][j] != ' ')
            {
                ECHEC = 1;
                pieceBloquante = t[i][j];
            }
        }
    }
    //------ Test Rangée Droite
    else if(caseDepart.ligne == caseArrivee.ligne && caseDepart.colonne < caseArrivee.colonne)
    {
        printf("----- testRangeeDroite");    
        i = caseDepart.ligne;
        
        //---- Pour vérifier si aucune pièce ne bloque le passage (vers la droite)
        for(j = caseDepart.colonne+1; j < caseArrivee.colonne; j++)
        {
            if(t[i][j] != ' ')
            {
                ECHEC = 1;
                pieceBloquante = t[i][j];
            }
        }
    }
    //------ Test Colonne Bas
    else if(caseDepart.ligne < caseArrivee.ligne && caseDepart.colonne == caseArrivee.colonne)
    {
        printf("-----je suis dans testColonneBas\n");
        j = caseDepart.colonne;
        
        //---- Pour vérifier si aucune pièce ne bloque le passage (vers le bas)
        for(i = caseDepart.ligne+1; i < caseArrivee.ligne; i++)
        {
            if(t[i][j] != ' ')
            {
                ECHEC = 1;
                pieceBloquante = t[i][j];
            }
        }
    }
    //------ Test Colonne Haut
    else if(caseDepart.ligne > caseArrivee.ligne && caseDepart.colonne == caseArrivee.colonne)
    {
        printf("-----je suis dans testColonneHaut\n");
        j = caseDepart.colonne;
        
        //---- Pour vérifier si aucune pièce ne bloque le passage (vers le haut)
        for(i = caseDepart.ligne-1; i > caseArrivee.ligne; i--)
        {
            if(t[i][j] != ' ')
            {
                ECHEC = 1;
                pieceBloquante = t[i][j];
                printf("i : %d, j : %d\n", i, j);
            }
        }
    }
    
    if(ECHEC == 1)
    {
        printf("La pièce %c en %c%d bloque le passage\n", pieceBloquante, alphabet[j], i+1);//ici, le i est faux car la boucle for au dessus à continué, même après avoir trouvé la piece bloquante, tu auras le même soucis pour le J (pour ranger droite et gauche)
    
    }
    else
    {
        ECHEC = 0 ;
    }
    
    //Verif Echec au Roi/Pat
}




//----------------------- Module de vérication de l'ECHEC au ROI --------------------------
void testSiEchec()
{   
    //printf("----je viens d'entrer dans testSiEchec() \n");
    RoiBlancEnECHEC = 0;
    RoiNoireEnECHEC = 0;
    int i, j;
    
    /* je deplace la piece pour tester si echec*/
    t[caseArrivee.ligne][caseArrivee.colonne] = t[caseDepart.ligne][caseDepart.colonne];
    t[caseDepart.ligne][caseDepart.colonne] = ' ';

    /* je parcours le tableau pour tester chaque piece*/
    for(i = 0 ; i < 8 ; i++)
    {
        //printf("---------on test la ligne : %d\n",i);
        for(j = 0 ; j < 8 ; j++)
        {
            if(t[i][j] == 't' || t[i][j] == 'T')
            {
                testDevant(i, j);
                testArriere(i, j);
                testDroite(i, j);
                testGauche(i, j);
            }
            else if(t[i][j] == 'p')
            { 
                if((t[i + 1][j - 1] == 'K') ||
                   (t[i + 1][j + 1] == 'K'))
                {
                    affichageEchecRoiBlanc();
                }
            }
            else if(t[i][j] == 'P')
            {
                if((t[i + 1][j - 1] == 'k') ||
                   (t[i + 1][j + 1] == 'k'))
                {
                    printf("P\n");
                    affichageEchecRoiNoire();
                }
            }
            else if(t[i][j] == 'c')
            {
                if(((i- 2 < 8 && i- 2 >=0) && (j- 1 < 8 && j- 1 >= 0 ) && (t[i - 2][j - 1] == 'K')) ||
                   ((i- 2 < 8 && i- 2 >=0) && (j+ 1 < 8 && j+ 1 >= 0 ) && (t[i - 2][j + 1] == 'K')) ||
                   ((i- 1 < 8 && i- 1 >=0) && (j- 2 < 8 && j- 2 >= 0 ) && (t[i - 1][j - 2] == 'K')) ||
                   ((i- 1 < 8 && i- 1 >=0) && (j+ 2 < 8 && j+ 2 >= 0 ) && (t[i - 1][j + 2] == 'K')) ||
                   ((i+ 2 < 8 && i+ 2 >=0) && (j- 1 < 8 && j- 1 >= 0 ) && (t[i + 2][j - 1] == 'K')) ||
                   ((i+ 2 < 8 && i+ 2 >=0) && (j+ 1 < 8 && j+ 1 >= 0 ) && (t[i + 2][j + 1] == 'K')) ||
                   ((i+ 1 < 8 && i+ 1 >=0) && (j- 2 < 8 && j- 2 >= 0 ) && (t[i + 1][j - 2] == 'K')) ||
                   ((i+ 1 < 8 && i+ 1 >=0) && (j+ 2 < 8 && j+ 2 >= 0 ) && (t[i + 1][j + 2] == 'K')))
                {
                    printf("c\n");
                    affichageEchecRoiBlanc();
                }
            }
            else if(t[i][j] == 'C')
            {
                if(((i- 2 < 8 && i- 2 >=0) && (j- 1 < 8 && j- 1 >= 0 ) && (t[i - 2][j - 1] == 'k')) ||
                   ((i- 2 < 8 && i- 2 >=0) && (j+ 1 < 8 && j+ 1 >= 0 ) && (t[i - 2][j + 1] == 'k')) ||
                   ((i- 1 < 8 && i- 1 >=0) && (j- 2 < 8 && j- 2 >= 0 ) && (t[i - 1][j - 2] == 'k')) ||
                   ((i- 1 < 8 && i- 1 >=0) && (j+ 2 < 8 && j+ 2 >= 0 ) && (t[i - 1][j + 2] == 'k')) ||
                   ((i+ 2 < 8 && i+ 2 >=0) && (j- 1 < 8 && j- 1 >= 0 ) && (t[i + 2][j - 1] == 'k')) ||
                   ((i+ 2 < 8 && i+ 2 >=0) && (j+ 1 < 8 && j+ 1 >= 0 ) && (t[i + 2][j + 1] == 'k')) ||
                   ((i+ 1 < 8 && i+ 1 >=0) && (j- 2 < 8 && j- 2 >= 0 ) && (t[i + 1][j - 2] == 'k')) ||
                   ((i+ 1 < 8 && i+ 1 >=0) && (j+ 2 < 8 && j+ 2 >= 0 ) && (t[i + 1][j + 2] == 'k')))
                {
                    //printf("C\n");
                    affichageEchecRoiNoire();
                }    
            }
            else if(t[i][j] == 'f' || t[i][j] == 'F')
            {
                //printf("f\n");
                testDiagoHG(i, j);
                testDiagoHD(i, j); 
                testDiagoBG(i, j);
                testDiagoBD(i, j);
            }
            else if(t[i][j] == 'q' || t[i][j] == 'Q')
            {
                //printf("q\n");
                testDevant(i, j);
                testArriere(i, j);
                testDroite(i, j);
                testGauche(i, j);
                testDiagoHG(i, j);
                testDiagoHD(i, j); 
                testDiagoBG(i, j);
                testDiagoBD(i, j);
            }
            
        }
    }
    /* je remet les pieces comme avant*/
    t[caseDepart.ligne][caseDepart.colonne] = t[caseArrivee.ligne][caseArrivee.colonne];
    t[caseArrivee.ligne][caseArrivee.colonne] = ' ';
    
    if((joueurActif == 1 && RoiBlancEnECHEC == 1) || (joueurActif == 2 && RoiNoireEnECHEC ==1)) 
    {
        ECHEC = 1 ;
        printf(" Déplacement impossible, il met votre Roi en ECHEC ! Veuillez recommencer\n ");
    }
}

void affichageEchecRoiBlanc()
{
    RoiBlancEnECHEC = 1;
    if(joueurActif == 1)
    {
        ECHEC = 1;
    }
    printf("*******************************\n");
    printf("***    ECHEC au roi blanc   ***\n"); 
    printf("*******************************\n");
}

void affichageEchecRoiNoire()
{
    RoiNoireEnECHEC = 1;
    if(joueurActif == 2)
    {
        ECHEC = 1;
    }
    printf("*******************************\n");
    printf("***    ECHEC au roi noir    ***\n"); 
    printf("*******************************\n"); 
}
//---------------------- Module de test devant pour tester l'ECHEC au roi
void testDevant(int i, int j)
{
    //printf("----je viens d'entrer dans testDevant() \n");
    int k = 0;
    int piecePercute = 0;
    piecePercute = 0;
    k = i + 1;
    //printf("J'ai trouver une tour noir !\n");         //      for(int k = 0 ; k < (8 - i) ; k++)
    if(t[i][j] == 't'|| t[i][j] == 'q')
    {    
        while((k < 8) && RoiBlancEnECHEC == 0 && RoiNoireEnECHEC == 0 && piecePercute == 0)
        {
           // printf("---- dans le while avec K : %d et J : %d\n",k,j);
            //printf("----contenu : %c\n",t[k][j]);
            if(t[k][j] == 'K')
            {
                affichageEchecRoiBlanc();
            }
            else if(t[k][j] != ' ')
            {
                piecePercute = 1;
                //printf("j'ai percuté une piece ligne : %d | colonne : %d \n",k,j);
            }
            else
            {}
            k++;
        }
    }
    else if(t[i][j] == 'T'|| t[i][j] == 'Q')
    {
            if(t[k][j] == 'k')
            {
                affichageEchecRoiNoire();
            }
            else if(t[k][j] != ' ')
            {
                piecePercute = 1;
                //printf("j'ai percuté une piece ligne : %d | colonne : %d \n",k,j);
            }
            else
            {}
            k++;
    }
}
//---------------------- Module de test derrière pour tester l'ECHEC au roi
void testArriere(int i, int j)
{
    //printf("----je viens d'entrer dans testArriere() \n");
    int k = 0;
    int piecePercute = 0;
    piecePercute = 0;
    k = i - 1;
    if(t[i][j] == 't'|| t[i][j] == 'q')
    { 
        while((k >= 0 ) && RoiBlancEnECHEC == 0 && RoiNoireEnECHEC == 0 && piecePercute == 0)
        {
            if(t[k][j] == 'K')
            {
                affichageEchecRoiBlanc();
            }
            else if(t[k][j] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            k--;
        }
    }
    else if(t[i][j] == 'T'|| t[i][j] == 'Q')
    {
        while((k >= 0 ) && RoiBlancEnECHEC == 0 && RoiNoireEnECHEC == 0 && piecePercute == 0)
        {
            if(t[k][j] == 'k')
            {
                affichageEchecRoiNoire();
            }
            else if(t[k][j] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            k--;
        }
    }
}

//---------------------- Module de test a droite pour tester l'ECHEC au roi
void testDroite(int i, int j)
{
    //printf("----je viens d'entrer dans testDroite() \n");    
    int k = 0;
    int piecePercute = 0;
    piecePercute = 0;
    k = j + 1;
    
    if(t[i][j] == 't'|| t[i][j] == 'q')
    { 
        while((k < 8 ) && RoiBlancEnECHEC == 0 && RoiNoireEnECHEC == 0 && piecePercute == 0)
        {
            if(t[i][k] == 'K')
            {
                affichageEchecRoiBlanc();
            }
            else if(t[i][k] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            k++;
        }
    }
    else if(t[i][j] == 'T'|| t[i][j] == 'Q')
    {
        while((k < 8 ) && RoiBlancEnECHEC == 0 && RoiNoireEnECHEC == 0 && piecePercute == 0)
        {
            if(t[i][k] == 'k')
            {
                affichageEchecRoiNoire();
            }
            else if(t[i][k] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            k++;
        }
    }
}

//---------------------- Module de test a gauche pour tester l'ECHEC au roi
void testGauche(int i, int j)
{
    //printf("----je viens d'entrer dans testGauche() \n");    
    int k = 0;
    int piecePercute = 0;
    piecePercute = 0;
    k = j - 1 ;
    
    if(t[i][j] == 't'|| t[i][j] == 'q')
    { 
        while((k >= 0 ) && RoiBlancEnECHEC == 0 && RoiNoireEnECHEC == 0 && piecePercute == 0)
        {
            if(t[i][k] == 'K')
            {
                affichageEchecRoiBlanc();
            }
            else if(t[i][k] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            k--;
        }
    }
    else if(t[i][j] == 'T'|| t[i][j] == 'Q')
    {
        while((k >= 0 ) && RoiBlancEnECHEC == 0 && RoiNoireEnECHEC == 0 && piecePercute == 0)
        {
            if(t[i][k] == 'k')
            {
                affichageEchecRoiNoire();
            }
            else if(t[i][k] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            k--;
        }
    }
}

void testDiagoHG(int i, int j)
{
    //printf("----je viens d'entrer dans testDiagoHG() \n");    
    int l = 0, c = 0;
    int piecePercute = 0;
    piecePercute = 0;
    l = i - 1;
    c = j - 1;
    
    if(t[i][j] == 'f'|| t[i][j] == 'q')
    {    
        while(l >= 0 && c >=0 && RoiBlancEnECHEC == 0 && RoiNoireEnECHEC == 0 && piecePercute == 0 )
        {
            if(t[l][c] == 'K')
            {
                affichageEchecRoiBlanc();
            }
            else if(t[l][c] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            l--;
            c--;
        }
    }
    else if(t[i][j] == 'F'|| t[i][j] == 'Q')
    {
        while(l >= 0 && c >=0 && RoiBlancEnECHEC == 0 && RoiNoireEnECHEC == 0 && piecePercute == 0 )
        {
            if(t[l][c] == 'k')
            {
                affichageEchecRoiNoire();
            }
            else if(t[l][c] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            l--;
            c--;
        }
    }
}

void testDiagoHD(int i, int j)
{
    //printf("----je viens d'entrer dans testDiagoHD() \n");        
    int l = 0, c = 0;
    int piecePercute = 0;
    piecePercute = 0;
    l = i - 1;
    c = j + 1;
    
    if(t[i][j] == 'f' || t[i][j] == 'q')
    {    
        while(l >= 0 && c < 8 && RoiBlancEnECHEC == 0 && RoiNoireEnECHEC == 0 && piecePercute == 0 )
        {
            if(t[l][c] == 'K')
            {
                affichageEchecRoiBlanc();
            }
            else if(t[l][c] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            l--;
            c++;
        }
    }
    else if(t[i][j] == 'F'|| t[i][j] == 'Q')
    {
        while(l >= 0 && c < 8 && RoiBlancEnECHEC == 0 && RoiNoireEnECHEC == 0 && piecePercute == 0 )
        {
            if(t[l][c] == 'k')
            {
                affichageEchecRoiNoire();
            }
            else if(t[l][c] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            l--;
            c++;
        }
    }
}

void testDiagoBG(int i, int j)
{
    //printf("----je viens d'entrer dans testDiagoBG() \n");        
    int l = 0, c = 0;
    int piecePercute = 0;
    piecePercute = 0;
    l = i + 1;
    c = j - 1;
    
    if(t[i][j] == 'f' || t[i][j] == 'q')
    { 
        while(l < 8 && c >= 0 && RoiBlancEnECHEC == 0 && RoiNoireEnECHEC == 0 && piecePercute == 0 )
        {
            if(t[l][c] == 'K')
            {
                affichageEchecRoiBlanc();
            }
            else if(t[l][c] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            l++;
            c--;
        }
    }
    else if(t[i][j] == 'F'|| t[i][j] == 'Q')
    {
        while(l < 8 && c >= 0 && RoiBlancEnECHEC == 0 && RoiNoireEnECHEC == 0 && piecePercute == 0 )
        {
            if(t[l][c] == 'k')
            {
                affichageEchecRoiNoire();
            }
            else if(t[l][c] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            l++;
            c--;
        }
    }
}

void testDiagoBD(int i, int j)
{
    //printf("----je viens d'entrer dans testDiagoBD() \n");    
    int l = 0, c = 0;
    int piecePercute = 0;
    piecePercute = 0;
    l = i + 1;
    c = j + 1;
    
    if(t[i][j] == 'f' || t[i][j] == 'q')
    {
        while(l < 8 && c < 8 && RoiBlancEnECHEC == 0 && RoiNoireEnECHEC == 0 && piecePercute == 0 )
        {
            if(t[l][c] == 'K')
            {
                affichageEchecRoiBlanc();
            }
            else if(t[l][c] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            l++;
            c++;
        }
    }    
    else if(t[i][j] == 'F'|| t[i][j] == 'Q')
    {
        while(l < 8 && c < 8 && RoiBlancEnECHEC == 0 && RoiNoireEnECHEC == 0 && piecePercute == 0 )
        {
            if(t[l][c] == 'k')
            {
                affichageEchecRoiNoire();
            }
            else if(t[l][c] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            l++;
            c++;
        }
    }
}


//----------------------- Module de vérication de l'ECHEC ET MAT au ROI --------------------------//
void testSiEchecEtMat()
{
    /*
        il faudra utiliser testSiEchec avec les differents mouvement du Roi ET des autres joueurs de la même couleur (pour protéger le ROI)
    
    */
}


//----------------------- Module de vérication du Pat --------------------------//
void testSiPat()
{
    /*
        -
    
    */
}
//----------------------- Faire un roque ----------------------------//
void jeRoque()
{
    int choix = -1;
    /*if(*grand roque ET petit roque possibles*)
    {
        printf("---------------------------------\n");
        printf("--  1- Faire un grand roque    --\n");
        printf("--  2- Faire un petit roque    --\n");
        printf("---------------------------------\n");
        
        switch(choix)
        {
            case 1:
                
            break;
                
            case2 : 
                
            break;
        }
    }
    
    else if(*grand roque possible*)
    {
        
    }
    
    else if (*petit roque possible*)
    {
        
    }
    */
}