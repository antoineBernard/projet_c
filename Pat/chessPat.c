/*
-------TODO------ : 
    - test de saisie (plusieurs) => sur les switch aussi : bug si char
    - travailler sur l'ergonomie
    - dans testSiEchec(), factoriser pour que la boucle s'arrête dès le premier echec
    - Possibilité d'enregistrement
    - virer les printf en commentaire



     ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     MODIFICATIONS EFFECTUEES : 21/04
     Marion : 
     Prévoir tout un jeu de tests pour vérifier que tout se passe bien (--> doc excel)
     
     Antoine : 
     
     //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* ---------------------------------------- Déclaration des fonctions  ----------------------------------------*/

void affichage();
int  deplacementPiece();
void chargement();
void sauvegarde();
void verifCaseChoisie();
void deplacementPion();
int  verifDeplacementArrivee();
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
void jeRoque();
void testMauvaiseSaisi();
void runTestEchecMatElimination();
void runTestEchecMatPion();


/* ----------------------------------------  Déclaration des types en global  ----------------------------------------*/
  struct infoCase                              
              {
                char charColonne;
                int ligne;
                int colonne;
              };

/*---------------------------------------- Déclaration des variables globales ----------------------------------------*/

/*char t[8] [8]={
    't','c','f','q','k','f','c','t',
    'p','p','p','p','p','p','p','p',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    'P','P','P','P','P','P','P','P',
    'T','C','F','Q','K','F','C','T'
};*/

char t[8] [8]={
    ' ',' ',' ',' ',' ',' ',' ','Q',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ','k',' ',
    ' ',' ',' ',' ',' ',' ','F',' ',
    ' ',' ',' ',' ',' ','P','P',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    'P','P','P','P','P','P','C','T',
    'T','C','F','Q','K',' ',' ','T'
};


int partietermine = 1;
int echecEtMatRoiBlanc = 1; 
int echecEtMatRoiNoir = 1;
int flagTestSiEchecEtMat = 0;
int joueurActif;
char piecesDuJoueurActif[10];
int ECHEC; 
int changePiece = 0;
struct infoCase caseDepart; 
struct infoCase caseArrivee;
struct infoCase sauvegardeCaseArrivee;
struct infoCase sauvegardeCaseDepart;
int RoiBlancEnECHEC = 0;
int RoiNoireEnECHEC = 0;
int percut = 0;
int roque = 0, roqueJ1 = 0, roqueJ2 = 0;
int EchecNoir = 0;
int EchecBlanc = 0;

/* ---------------------------------------- Procédure principale --------------------------------------- */
int main() 
{
    char choix[20] = "";
    
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
    printf("                        *Jeux video garanti sans colorant ni conservateur*                        \n");
    printf("\n\n\n\n\n");
    
    printf("Hello World! et bienvenue sur le jeu d'échec !\n\n");
    
    while(choix[0] != '0' && partietermine == 1 && (echecEtMatRoiBlanc == 1 || echecEtMatRoiNoir == 1))
    {
        
        printf("-------------    MENU      -----------------\n");
        printf("    |  -1- Commencer une nouvelle partie | \n");
        printf("    |  -2- Charger une partie            | \n");
        printf("    |  -0- QUITTER                       | \n");
        printf("--------------------------------------------\n");
        
        printf("Choix : ");
        scanf("%s", choix);
        
        partietermine = 0;
         
        if(choix[0] >= '0' && choix[0] <= '2' && partietermine == 0)
        {
            echecEtMatRoiBlanc =0; echecEtMatRoiNoir = 0;
            switch(choix[0])
            {
                case '0':
                    printf("Au revoir, et a bientot !\n");
                    break;
                
                case '1':
                    printf("\n\n");
                    printf("C'est parti !\n");
                    while(partietermine == 0)
                    {
                        joueurActif = 1;
                        affichage();
                        partietermine = deplacementPiece();
                        if(changePiece == 1)
                        {
                             while(changePiece == 1) 
                             {
                                 affichage();
                                 changePiece = 0;
                                 partietermine = deplacementPiece();
                             }
                        }
                        if(partietermine == 0)     
                        {
                          joueurActif = 2;
                          affichage();
                          partietermine = deplacementPiece();
                          if(changePiece == 1)
                          {
                             while(changePiece == 1) 
                             {
                                 affichage();
                                 changePiece = 0;
                                 partietermine = deplacementPiece();
                             }
                          }
                        }
                    }
                    break;
                    
                case '2':
                    chargement();
                    
                    printf("\n\n");
                    printf("C'est parti !\n");
                    
                    testSiEchec();
                    
                    if(joueurActif == 1)
                    {
                        while(partietermine == 0)
                        {
                            joueurActif = 1;
                            affichage();
                            partietermine = deplacementPiece();
                            if(changePiece == 1)
                            {
                                while(changePiece == 1) 
                                {
                                    affichage();
                                    changePiece = 0;
                                    partietermine = deplacementPiece();
                                }
                            }
                            if(partietermine == 0)     
                            {
                                joueurActif = 2;
                                affichage();
                                partietermine = deplacementPiece();
                                if(changePiece == 1)
                                {
                                    while(changePiece == 1) 
                                    {
                                        affichage();
                                        changePiece = 0;
                                        partietermine = deplacementPiece();
                                    }
                                }
                            }
                        }
                    }
                    else if(joueurActif == 2)
                    {
                        while(partietermine == 0)
                        {
                            joueurActif = 2;
                            affichage();
                            partietermine = deplacementPiece();
                            if(changePiece == 1)
                            {
                                while(changePiece == 1) 
                                {
                                    affichage();
                                    changePiece = 0;
                                    partietermine = deplacementPiece();
                                }
                            }
                            if(partietermine == 0)     
                            {
                                joueurActif = 1;
                                affichage();
                                partietermine = deplacementPiece();
                                if(changePiece == 1)
                                {
                                    while(changePiece == 1) 
                                    {
                                        affichage();
                                        changePiece = 0;
                                        partietermine = deplacementPiece();
                                    }
                                }
                            }
                        }
                    }
                    break;
            }
        }
        else
        {
            printf("Vous n'avez pas choisi une option du menu ! Veuillez recommencer\n");
            ECHEC  = 1;
        }
    }
    return 0;
}
// ---------------------------------------- Fonction affichage du plateau--------------------
void affichage()
{
  int i;
printf("\n\n\n\n\n");
  printf("          A         B         C         D         E         F         G         H\n");
  printf("  ------------------------------------------------------------------------------------\n");
  
  for (i=0; i<=7; i++) 
    {
        /*on créé le tableau et le remplit avec la case du tableau t*/
        printf("     |         |         |         |         |         |         |         |         |\n"); 
        printf("  %d  |    %c    |    %c    |    %c    |    %c    |    %c    |    %c    |    %c    |    %c    |\n", i+1, t[i][0], t[i][1], t[i][2], t[i][3], t[i][4], t[i][5], t[i][6], t[i][7]);
        printf("     |         |         |         |         |         |         |         |         |\n");         
        printf("  ------------------------------------------------------------------------------------\n");
    }
    printf("\n");
    if(joueurActif == 1)
    {
        if((roqueJ1 < 2 && joueurActif == 1 )
        && ((t[7][5] == ' ' && t[7][6] == ' ' ) || (t[7][1] == ' ' && t[7][2] == ' ' && t[7][3] == ' ')))
        {
            printf("  ------- 0- Quitter  1- Sauvegarder  2- Changer de piece  3- Faire un roque ---------\n");
        }
        else 
        {
            printf("  ------------------ 0- Quitter  1- Sauvegarder  2- Changer de piece -----------------\n");
        }
        printf("                         _____________________________________\n");
        printf("                         ----- Au joueur BLANC de jouer ! ----\n");
        printf("                           Avec les MAJUSCULES (P,T,C,F,Q,K)\n");
    }
    else if(joueurActif == 2)
    {
        if((roqueJ2 < 2 && joueurActif == 2 )
        && ((t[0][5] == ' ' && t[0][6] == ' ') || (t[0][1] == ' ' && t[0][2] == ' ' && t[0][3] == ' ')))
        {
            printf("  ------- 0- Quitter  1- Sauvegarder  2- Changer de piece  3- Faire un roque ---------\n");
        }
        else 
        {
            printf("  ------------------ 0- Quitter  1- Sauvegarder  2- Changer de piece -----------------\n");
        }
        printf("                         _____________________________________\n");
        printf("                         ----- Au joueur NOIR de jouer ! ----\n");
        printf("                          Avec les minsuscules (p,t,c,f,q,k)\n");
    }
    
    if(EchecBlanc == 1)
    { 
        printf("\n\n");
        printf("                          ******** ROI BLANC EN ECHEC ! ******\n");
        EchecBlanc = 0;
    }
    else if(EchecNoir == 1)
    {
        printf("\n\n");
        printf("                          ******** ROI NOIR EN ECHEC ! *******\n");
        EchecNoir = 0;
    }
  printf("\n\n\n");
}

// --------------------------------------------- Fonction déplacement de piece----------------------------//
int deplacementPiece()
{
    //printf("je suis dans déplacementPiece()\n");
    char alphabet[10]= "ABCDEFGH", choix[20];  
    int i = 0, numeroLigne;
    caseDepart.colonne = 0 ;
    char pieceTrouve, lettreColonne;
    ECHEC = 1; 
    
    while(ECHEC == 1 && partietermine == 0)
    {
        printf("Ou se trouve la piece que vous voulez deplacer? (ex : B2) : ");
        scanf("%s", choix);
        
        lettreColonne = toupper(choix[0]);
        numeroLigne = choix[1] - 48;
        
        if(choix[0] >= '0' && choix[0] <= '3')
        {
            switch(choix[0])
            {
                case '0':
                    printf("Au revoir et a bientot !\n");
                    partietermine = 1;
                    return partietermine;
                    break;
                
                case '1':
                    sauvegarde();
                    ECHEC = 1;
                    roque = 0;
                    break;
                
                case '2':
                    ECHEC = 0;
                    changePiece = 1;
                    roque = 0;
                    break;
                    
                case '3':
                    ECHEC = 0;
                    roque = 1;
                    jeRoque();
                    break;
            }
        }
        else if(lettreColonne >= 'A' && lettreColonne <= 'H' && numeroLigne >= 0 && numeroLigne <= 9)
        {
                ECHEC = 0;
                caseDepart.ligne = numeroLigne;
                caseDepart.charColonne = lettreColonne;
                caseDepart.ligne --;
                verifCaseChoisie();
                pieceTrouve = t[caseDepart.ligne][caseDepart.colonne] ;
                pieceTrouve = toupper(pieceTrouve);
        }
        else
        {
            printf("Mauvaise saisie. Veuillez choisir une des options du menu ou indiquer une case.\n");
            ECHEC  = 1;
        }
    }    
    
    ECHEC =1;
    while(ECHEC == 1)
    {
        partietermine = verifDeplacementArrivee();
        ECHEC = 0;
        
        if(partietermine == 1)
        {
            return partietermine;
        }
        
        if(changePiece ==0 && roque == 0)
        {
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
        
    }
    return partietermine;    
}   

// --------------------------------------------- Fonction verifCaseChoisie ------------------------------------------------//
void verifCaseChoisie()
{
    char alphabet[10]= "ABCDEFGH";  //pour trouver l'emplacement dans le tableau dans la fonction rechercheCase().. A=0, B=1...
    char pieceTrouve, bidon;
    int i= 0,j = 0, flagEspace = 0;

    //-------pour trouver l'index de la LETTRE dans l'alphabet ----
    for(i ; i < 9 ; i++)
    {
      if(alphabet[i] == caseDepart.charColonne)
      {
          caseDepart.colonne = i;
      }
    }
    //-------pour vérifier si la colonne et la ligne existe ----
    if((caseDepart.colonne < 0) || (caseDepart.colonne > 7) || (caseDepart.ligne < 0) || (caseDepart.ligne > 7))
    {
        printf("Mauvaise saisie ! A1 est la première case, H8 est la dernière, Veuillez recommencer \n");
        ECHEC = 1;
    }
    else
    {
      char bidon;
      pieceTrouve = t[caseDepart.ligne][caseDepart.colonne];
      // + Je suggère qu'on donne des noms à la colonne et à la ligne de la pièce, c'est utile pour la suite
      printf("la piece trouvée est : %c\n", pieceTrouve);
    
      //---------pour vérifier que c'est une piece de la bonne COULEUR (rien de raciste) -----//
       if(joueurActif == 1)
           {strcpy(piecesDuJoueurActif, "PTCFQK");}
       else
           {strcpy(piecesDuJoueurActif, "ptcfqk");}
           
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
}

//------------------------------------------------- procédure déplacement pion ------------------------------------------------
void deplacementPion()
{

    if(joueurActif == 1)
    {
        if(    ((caseArrivee.ligne == caseDepart.ligne-1 && caseArrivee.colonne == caseDepart.colonne && t[caseArrivee.ligne][caseArrivee.colonne] != ' ')) ||
               ((caseArrivee.ligne == caseDepart.ligne-2 && caseArrivee.colonne == caseDepart.colonne && t[caseArrivee.ligne][caseArrivee.colonne] != ' ' && t[caseDepart.ligne -1][caseArrivee.colonne] != ' ')) )
        {
            
            printf("caseDepart.ligne = %d , caseDepart.colonne = %d\n", caseDepart.ligne, caseDepart.colonne);
            printf("caseArrivee.ligne = %d , caseArrivee.colonne = %d\n", caseArrivee.ligne, caseArrivee.colonne);
            
            printf("Vous ne pouvez pas avancer car une piece bloque le passage... Veuillez recommencer !\n");
            ECHEC = 1;
        }
        else if(  ( (caseArrivee.ligne == caseDepart.ligne-2) && 
                    (caseArrivee.colonne == caseDepart.colonne) && 
                    (caseDepart.ligne == 6)) //pour avancer de deux case 
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
                testSiEchec();
                if(ECHEC == 0)
                {    
                  verifEliminationPiece();
                }
            }
        else
        {
            printf("Mouvement non valide, souvenez-vous, le pion se déplace d'une case en avant, veuillez recommencer !\n");
            ECHEC = 1;
        }
    }
    if(joueurActif == 2)
    {
        if(((caseArrivee.ligne == caseDepart.ligne+1 && caseArrivee.colonne == caseDepart.colonne && t[caseArrivee.ligne][caseArrivee.colonne] != ' ')) ||
               ((caseArrivee.ligne == caseDepart.ligne+2 && caseArrivee.colonne == caseDepart.colonne && t[caseArrivee.ligne][caseArrivee.colonne] != ' ' && t[caseDepart.ligne +1][caseArrivee.colonne] != ' ')) )
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
                testSiEchec();
                if(ECHEC == 0)
                {    
                  verifEliminationPiece();
                }
            }
        else
        {
            printf("Mouvement non valide, souvenez-vous, le pion se déplace d'une case en avant, veuillez recommencer !\n");
            ECHEC = 1;
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

int verifDeplacementArrivee()
{
    //printf("je suis dans verifDeplacementArrivee\n");
    char alphabet[10]= "ABCDEFGH", choix[20];
    int i = 0, numeroLigne;
    char lettreColonne;
    RoiBlancEnECHEC = 0;
    RoiNoireEnECHEC = 0;
    
    if(roque == 0)
    {
        while(ECHEC == 1) 
        {

            printf("Ou voulez vous la deplacer? (ex : B2) : ");
            scanf("%s", choix);
            
            lettreColonne = toupper(choix[0]);
            numeroLigne = choix[1] - 48;
            
            if(choix[0] >= '0' && choix[0] <= '3')
            {
                switch(choix[0])
                {
                    case '0':
                        printf("Au revoir et a bientot !\n");
                        partietermine = 1;
                        return partietermine;
                        break;
                    
                    case '1':
                        sauvegarde();
                        break;
                    
                    case '2':
                        ECHEC = 0;
                        changePiece = 1;
                        roque = 0;
                        break;
                        
                    case '3':
                        ECHEC = 0;
                        roque = 1;
                        jeRoque();
                        break;
                }
            }
            else if(lettreColonne >= 'A' && lettreColonne <= 'H' && numeroLigne >= 0 && numeroLigne <= 9)
            {
                ECHEC = 0;
                caseArrivee.ligne = numeroLigne;
                caseArrivee.charColonne = lettreColonne;
                caseArrivee.ligne --;
                
                for(i ; i < strlen(alphabet) ; i++)
                {
                    if(alphabet[i] == caseArrivee.charColonne)
                    {
                        caseArrivee.colonne = i;
                    }
                }
                
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
            else
            {
                printf("Mauvaise saisie. Veuillez choisir une des options du menu ou indiquer une case.\n");
                ECHEC  = 1;
            }
        }
    }
    
    return 0;
}


//------------------------------------------------- procédure de gestion de l'élimination------------------------------------------------ // 

void verifEliminationPiece()
{
   //printf("je suis entrée dans verifEliminationPiece, et ECHEC = %d\n",ECHEC );
    
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
    if((caseArrivee.ligne == caseDepart.ligne-2 && caseArrivee.colonne == caseDepart.colonne-1) ||
       (caseArrivee.ligne == caseDepart.ligne-2 && caseArrivee.colonne == caseDepart.colonne+1) ||
       (caseArrivee.ligne == caseDepart.ligne-1 && caseArrivee.colonne == caseDepart.colonne-2) ||
       (caseArrivee.ligne == caseDepart.ligne-1 && caseArrivee.colonne == caseDepart.colonne+2) ||
       (caseArrivee.ligne == caseDepart.ligne+2 && caseArrivee.colonne == caseDepart.colonne-1) ||
       (caseArrivee.ligne == caseDepart.ligne+2 && caseArrivee.colonne == caseDepart.colonne+1) ||               
       (caseArrivee.ligne == caseDepart.ligne+1 && caseArrivee.colonne == caseDepart.colonne-2) ||
       (caseArrivee.ligne == caseDepart.ligne+1 && caseArrivee.colonne == caseDepart.colonne+2))
    {
        testSiEchec();
        if(ECHEC == 0)
        {
            verifEliminationPiece();
        }
    }
    else
    {
        printf("Mouvement non valide, souvenez-vous, le cavalier se déplace en 'L'.\n");
        ECHEC = 1;
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

    if((caseArrivee.ligne == caseDepart.ligne-1) && (caseArrivee.colonne == caseDepart.colonne)  ||
       (caseArrivee.ligne == caseDepart.ligne-1) && (caseArrivee.colonne == caseDepart.colonne+1)||
       (caseArrivee.ligne == caseDepart.ligne)   && (caseArrivee.colonne == caseDepart.colonne+1)||
       (caseArrivee.ligne == caseDepart.ligne+1) && (caseArrivee.colonne == caseDepart.colonne+1)||
       (caseArrivee.ligne == caseDepart.ligne+1) && (caseArrivee.colonne == caseDepart.colonne)  || 
       (caseArrivee.ligne == caseDepart.ligne+1) && (caseArrivee.colonne == caseDepart.colonne-1)||
       (caseArrivee.ligne == caseDepart.ligne)   && (caseArrivee.colonne == caseDepart.colonne-1)||
       (caseArrivee.ligne == caseDepart.ligne-1) && (caseArrivee.colonne == caseDepart.colonne-1))
    {
        testSiEchec();
        if(ECHEC == 0)   
        {
            verifEliminationPiece();
        }
    }
    else
    {
        printf("Mouvement non valide, souvenez-vous, le roi se déplace d'une case autour de lui.\n");
        ECHEC = 1;
    }

   if(ECHEC == 0 && changePiece == 0 && roque == 0)
   {
        if(joueurActif == 1)
        {
            roqueJ1 = 2;
        }
        else if(joueurActif == 2)
        {
            roqueJ2 = 2;
        }
        
        t[caseArrivee.ligne][caseArrivee.colonne] = t[caseDepart.ligne][caseDepart.colonne];         //je deplace la piece
        t[caseDepart.ligne][caseDepart.colonne] = ' ';
   }
}

/*------------------------- Deplacement Reine/Fou/Tour --------------------*/
void deplacementReineFouTour()
{

    int i = caseDepart.ligne, j = caseDepart.colonne;
    char pieceChoisie = toupper(t[i][j]);
    int mouvementLicite = 0;
    
    mouvementLicite = 0;
    for(i= caseDepart.ligne-1, j= caseDepart.colonne-1; i>= 0 , j>= 0; i--, j--)
    {
        
        if(i == caseArrivee.ligne && j == caseArrivee.colonne)
        {
            mouvementLicite = 1;
        }
    }
    for(i= caseDepart.ligne-1, j= caseDepart.colonne+1; i>= 0 , j<= 7; i--, j++)
    {
        if(i == caseArrivee.ligne && j == caseArrivee.colonne)
        {
            
            mouvementLicite = 1;
        }
    }
    for(i= caseDepart.ligne+1, j= caseDepart.colonne+1; i<= 7, j<= 7; i++, j++)
    {
        if(i == caseArrivee.ligne && j == caseArrivee.colonne)
        {
            mouvementLicite = 1;
        }
    }

    for(i= caseDepart.ligne+1, j= caseDepart.colonne-1; i<= 7, j>= 0; i++, j--)
    {
        if(i == caseArrivee.ligne && j == caseArrivee.colonne)
        {
            mouvementLicite = 1;
            
        }
    }
    if ((pieceChoisie == 'Q' || pieceChoisie == 'F') && mouvementLicite)
    {
        testDiagonales();
        testSiEchec();
        if(ECHEC == 0)
        {
            verifEliminationPiece();
        }
    }

    else if((pieceChoisie == 'Q' || pieceChoisie == 'T') 
    && (caseDepart.ligne == caseArrivee.ligne || caseDepart.colonne == caseArrivee.colonne))
    {
        testRangeesColonnes();
        testSiEchec();
        if(ECHEC == 0)
        {
            verifEliminationPiece();
        }
    }
    else
    {
        if(pieceChoisie == 'Q')
        {
            printf("Mouvement non valide, souvenez-vous, la reine se déplace en diagonale ou en ligne droite.\n");
            ECHEC = 1;
        }
        else if(pieceChoisie == 'F')
        {
            printf("Mouvement non valide, souvenez-vous, le fou se déplace en diagonale.\n");
            ECHEC = 1;
        }
        else if(pieceChoisie == 'T')
        {
            printf("Mouvement non valide, souvenez-vous, la tour se déplace en ligne droite.\n");
            ECHEC = 1;
        }
    }

    
    if(ECHEC == 0 && changePiece == 0)
    {
        /* Test pour Roque */
        if(joueurActif == 1 && pieceChoisie == 'T'
        && ((caseDepart.ligne == 7 && caseDepart.colonne == 7) 
        ||(caseDepart.ligne == 7 && caseDepart.colonne == 0)))
        {
            roqueJ1++;
        }
        else if(joueurActif == 2 && pieceChoisie == 'T'
        &&((caseDepart.ligne == 0 && caseDepart.colonne == 7)
        ||(caseDepart.ligne == 0 && caseDepart.colonne == 0)))
        {
            roqueJ2++;
        }
        
        t[caseArrivee.ligne][caseArrivee.colonne] = t[caseDepart.ligne][caseDepart.colonne];         //je deplace la piece
        t[caseDepart.ligne][caseDepart.colonne] = ' ';
    }
}

//---------------------------- Test Diagonales ---------------------------//
void testDiagonales()
{
    int i, j, l, c;
    char pieceBloquante;
    char alphabet[10] = "ABCDEFGH";
    

    if(caseDepart.ligne > caseArrivee.ligne && caseDepart.colonne > caseArrivee.colonne)
    {

        //---- Pour vérifier si aucune pièce ne bloque le passage (en remontant en haut à gauche)
        for(i = caseDepart.ligne-1, j = caseDepart.colonne-1; i> caseArrivee.ligne , j> caseArrivee.colonne; i--, j--)
        {
            if(t[i][j] != ' ')
            {
                ECHEC = 1;
                pieceBloquante = t[i][j];
                l = i;
                c = j;
            }
        }
    }
    else if(caseDepart.ligne > caseArrivee.ligne && caseDepart.colonne < caseArrivee.colonne)
    {
        
        //---- Pour vérifier si aucune pièce ne bloque le passage (en remontant en haut à droite)
        for(i = caseDepart.ligne-1, j = caseDepart.colonne+1; i> caseArrivee.ligne , j< caseArrivee.colonne; i--, j++)
        {
            if(t[i][j] != ' ')
            {
                ECHEC = 1;
                pieceBloquante = t[i][j];
                l = i;
                c = j;
            }
        }
    }
    else if(caseDepart.ligne < caseArrivee.ligne && caseDepart.colonne < caseArrivee.colonne)
    {
        
        //---- Pour vérifier si aucune pièce ne bloque le passage (en se déplaçant vers le bas et la gauche)
        for(i = caseDepart.ligne+1, j = caseDepart.colonne+1; i< caseArrivee.ligne , j< caseArrivee.colonne; i++, j++)
        {
            if(t[i][j] != ' ')
            {
                ECHEC = 1;
                pieceBloquante = t[i][j];
                l = i;
                c = j;
            }
        }
    }
    else if(caseDepart.ligne < caseArrivee.ligne && caseDepart.colonne > caseArrivee.colonne)
    {
        
        //---- Pour vérifier si aucune pièce ne bloque le passage (en descendant vers la gauche)
        for(i = caseDepart.ligne+1, j = caseDepart.colonne-1; i< caseArrivee.ligne , j> caseArrivee.colonne; i++, j--)
        {
            if(t[i][j] != ' ')
            {
                ECHEC = 1;
                pieceBloquante = t[i][j];
                l = i;
                c = j;
            }
        }
    }
        
    if(ECHEC == 1)
    {
        printf("La pièce %c en %c%d bloque le passage\n", pieceBloquante, alphabet[c], (l+1));
    }
    else
    {
        ECHEC = 0 ;
    }

}

//----------------------- Test Rangées & Colonnes --------------------------//
void testRangeesColonnes()
{
    char pieceBloquante;
    char alphabet[10]= "ABCDEFGH";
    int i, j, l, c;
    
    //------ Test Rangée Gauche
    if(caseDepart.ligne == caseArrivee.ligne && caseDepart.colonne > caseArrivee.colonne)
    {
        i = caseDepart.ligne;
    
        //---- Pour vérifier si aucune pièce ne bloque le passage (vers la gauche)
        for(j = caseDepart.colonne-1; j > caseArrivee.colonne; j--)
        {
            if(t[i][j] != ' ')
            {
                ECHEC = 1;
                pieceBloquante = t[i][j];
                l = i;
                c = j;
            }
        }
    }
    //------ Test Rangée Droite
    else if(caseDepart.ligne == caseArrivee.ligne && caseDepart.colonne < caseArrivee.colonne)
    {
        i = caseDepart.ligne;
        
        //---- Pour vérifier si aucune pièce ne bloque le passage (vers la droite)
        for(j = caseDepart.colonne+1; j < caseArrivee.colonne; j++)
        {
            if(t[i][j] != ' ')
            {
                ECHEC = 1;
                pieceBloquante = t[i][j];
                l = i;
                c = j;
            }
        }
    }
    //------ Test Colonne Bas
    else if(caseDepart.ligne < caseArrivee.ligne && caseDepart.colonne == caseArrivee.colonne)
    {
        j = caseDepart.colonne;
        
        //---- Pour vérifier si aucune pièce ne bloque le passage (vers le bas)
        for(i = caseDepart.ligne+1; i < caseArrivee.ligne; i++)
        {
            if(t[i][j] != ' ')
            {
                ECHEC = 1;
                pieceBloquante = t[i][j];
                l = i;
                c = j;
            }
        }
    }
    //------ Test Colonne Haut
    else if(caseDepart.ligne > caseArrivee.ligne && caseDepart.colonne == caseArrivee.colonne)
    {
        j = caseDepart.colonne;
        
        //---- Pour vérifier si aucune pièce ne bloque le passage (vers le haut)
        for(i = caseDepart.ligne-1; i > caseArrivee.ligne; i--)
        {
            if(t[i][j] != ' ')
            {
                ECHEC = 1;
                pieceBloquante = t[i][j];
                l = i;
                c = j;
            }
        }
    }
    
    if(ECHEC == 1)
    {
        printf("La pièce %c en %c%d bloque le passage\n", pieceBloquante, alphabet[c], l+1);
    }
    else
    {
        ECHEC = 0 ;
    }
}




/* ----------------------- Module de vérication de l'ECHEC au ROI -------------------------- */
void testSiEchec()
{   
    
    struct infoCase sauvegardeCaseDepartEchec;
    struct infoCase sauvegardeCaseArriveeEchec;
    
    sauvegardeCaseDepartEchec.ligne = caseDepart.ligne;
    sauvegardeCaseDepartEchec.colonne = caseDepart.colonne;
    
    sauvegardeCaseArriveeEchec.ligne = caseArrivee.ligne;
    sauvegardeCaseArriveeEchec.colonne = caseArrivee.colonne;
    
    char sauvegardePieceDepart = t[caseDepart.ligne][caseDepart.colonne];
    char sauvegardePieceArrivee = t[caseArrivee.ligne][caseArrivee.colonne];
    
    RoiBlancEnECHEC = 0;
    RoiNoireEnECHEC = 0;
    int i, j;
    
    /* je deplace la piece pour tester si echec*/
    t[caseArrivee.ligne][caseArrivee.colonne] = sauvegardePieceDepart;
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

                if((t[i - 1][j - 1] == 'k') ||
                   (t[i - 1][j + 1] == 'k'))
                {
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
                  
                  
                    //if(joueurActif != 1 && flagTestSiEchecEtMat != 1) --------> pour corrigé le prob echec et mat du c.. mais provoque d'autre soucis (on peut plus mettre en echec)
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
                    //if(joueurActif != 2 && flagTestSiEchecEtMat != 1)
                        affichageEchecRoiNoire();
                }    
            }
            else if(t[i][j] == 'f' || t[i][j] == 'F')
            {
                testDiagoHG(i, j);
                testDiagoHD(i, j); 
                testDiagoBG(i, j);
                testDiagoBD(i, j);
            }
            else if(t[i][j] == 'q' || t[i][j] == 'Q')
            {
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
    /* je remets les pieces comme avant*/
    t[sauvegardeCaseDepartEchec.ligne][sauvegardeCaseDepartEchec.colonne] = sauvegardePieceDepart;
    t[sauvegardeCaseArriveeEchec.ligne][sauvegardeCaseArriveeEchec.colonne] = sauvegardePieceArrivee;
    
    if(((joueurActif == 1 && RoiBlancEnECHEC == 1) || (joueurActif == 2 && RoiNoireEnECHEC ==1)) && flagTestSiEchecEtMat == 0) 
    {
        ECHEC = 1 ;
        printf(" Déplacement impossible, il met votre Roi en ECHEC ! Veuillez recommencer\n ");
    }
    
    if(flagTestSiEchecEtMat == 1)//pour ignorer les erreurs dans le cas du test pour l'échec et mat
        ECHEC = 0;
        
        
    caseDepart.ligne = sauvegardeCaseDepartEchec.ligne;
    caseDepart.colonne = sauvegardeCaseDepartEchec.colonne;
    
    caseArrivee.ligne = sauvegardeCaseArriveeEchec.ligne;
    caseArrivee.colonne = sauvegardeCaseArriveeEchec.colonne;
    
    t[caseDepart.ligne][caseDepart.colonne] = sauvegardePieceDepart;
}

void affichageEchecRoiBlanc()
{
    RoiBlancEnECHEC = 1;
    if(joueurActif == 1)
    {
        ECHEC = 1;
    }
    
    if(flagTestSiEchecEtMat == 0)
    {
        testSiEchecEtMat();
        if(echecEtMatRoiBlanc == 1)
        {
            partietermine = 1;
            printf("                _____________________________________________\n\n\n\n\n\n\n");
            printf("                                 ECHEC ET MAT !\n");            
            printf("                ***          le joueur NOIR GAGNE !      ***\n\n\n\n\n\n\n"); 
            printf("                ______________________________________________\n"); 
        }
        else
        {
            EchecBlanc = 1;
        }
    }
}

void affichageEchecRoiNoire()
{
    RoiNoireEnECHEC = 1;
    if(joueurActif == 2)
    {
        ECHEC = 1;
    }
    
    if(flagTestSiEchecEtMat == 0)
    {

        testSiEchecEtMat();
        if(echecEtMatRoiNoir == 1)
        {
            partietermine = 1;
            printf("                _____________________________________________\n\n\n\n\n\n\n");
            printf("                                 ECHEC ET MAT !\n");            
            printf("                ***          le joueur BLANC GAGNE !      ***\n\n\n\n\n\n\n"); 
            printf("                ______________________________________________\n"); 
        }
        else
        {
            EchecNoir = 1;
        }
    }
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
            {            }
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
    sauvegardeCaseDepart.ligne = caseDepart.ligne;
    sauvegardeCaseDepart.colonne = caseDepart.colonne;
    
    sauvegardeCaseArrivee.ligne = caseArrivee.ligne;
    sauvegardeCaseArrivee.colonne = caseArrivee.colonne;
    
    flagTestSiEchecEtMat = 1;
    int i,j,k,l,m,n,o,p;
    int roiNoireSauve = 0 ;
    int roiBlancSauve = 0 ;
    
    if(joueurActif == 2)
    {
        echecEtMatRoiBlanc = 1;
        echecEtMatRoiNoir = 0;
    }
    else if(joueurActif == 1)
    {
        echecEtMatRoiBlanc = 0;
        echecEtMatRoiNoir = 1;
    }
 
    
    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)//je parcours tout le tableau à la recherche des pieces
        {   
            roiNoireSauve = 0;
            roiBlancSauve = 0;
            caseDepart.ligne = i;
            caseDepart.colonne = j;
            if((t[i][j] == 'c' && joueurActif == 1) || (t[i][j] == 'C' && joueurActif == 2))
            {
                caseArrivee.ligne = caseDepart.ligne -2;
                caseArrivee.colonne = caseDepart.colonne -1;
                
                runTestEchecMatElimination();

                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;

                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1;

                caseArrivee.ligne = caseDepart.ligne -2;
                caseArrivee.colonne = caseDepart.colonne +1;
                
                runTestEchecMatElimination();

                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;

                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1;

                caseArrivee.ligne = caseDepart.ligne -1;
                caseArrivee.colonne = caseDepart.colonne -2;
                
                runTestEchecMatElimination();

                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;

                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1;

                  
                caseArrivee.ligne = caseDepart.ligne -1;
                caseArrivee.colonne = caseDepart.colonne +2;
                
                runTestEchecMatElimination();

                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;
                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1;


                caseArrivee.ligne = caseDepart.ligne +2;
                caseArrivee.colonne = caseDepart.colonne -1;
                
                runTestEchecMatElimination();

                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;

                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1;

                
                caseArrivee.ligne = caseDepart.ligne +2;
                caseArrivee.colonne = caseDepart.colonne +1;
                
                runTestEchecMatElimination();
                
                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;
                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1;

                      
                caseArrivee.ligne = caseDepart.ligne +1;
                caseArrivee.colonne = caseDepart.colonne -2;
                
                runTestEchecMatElimination();

                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;

                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1;

                  
                caseArrivee.ligne = caseDepart.ligne +1;
                caseArrivee.colonne = caseDepart.colonne +2;
                
                runTestEchecMatElimination();
                
                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;

                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1;

                
                if(joueurActif == 1 && roiNoireSauve == 1)
                    echecEtMatRoiNoir = 0;

                else if(joueurActif == 2 && roiBlancSauve == 1)
                    echecEtMatRoiBlanc = 0;

                 
                 
                caseDepart.ligne = sauvegardeCaseDepart.ligne;
                caseDepart.colonne = sauvegardeCaseDepart.colonne;

                caseArrivee.ligne = sauvegardeCaseArrivee.ligne;
                caseArrivee.colonne = sauvegardeCaseArrivee.colonne;
            }
            
            if(t[i][j] == 'p' && joueurActif == 1)
            {
                if(i == 1 && t[caseDepart.ligne+1][caseDepart.colonne] == ' ' && t[caseDepart.ligne +2][caseDepart.colonne] == ' ') //avance de 2 cases pour le pion
                {
                    caseArrivee.ligne = caseDepart.ligne +2;
                    caseArrivee.colonne = caseDepart.colonne;
                    
                    testSiEchec();
                    
                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;
                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1;
                        
                }
                
                if(t[caseDepart.ligne +1][caseDepart.colonne] == ' ')
                {
                    caseArrivee.ligne = caseDepart.ligne +1;
                    caseArrivee.colonne = caseDepart.colonne;
                    
                    testSiEchec();
                    if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                         roiNoireSauve = 1;
                     else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                         roiBlancSauve = 1;
                }
                
                caseArrivee.ligne = caseDepart.ligne +1;
                caseArrivee.colonne = caseDepart.colonne +1;
                
                runTestEchecMatPion();
                
                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;
                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1; 
    
            
                caseArrivee.ligne = caseDepart.ligne +1;
                caseArrivee.colonne = caseDepart.colonne -1;
                
                runTestEchecMatPion();
                
                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;
                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1;
                    
                    
                if(joueurActif == 1 && roiNoireSauve == 1)
                    echecEtMatRoiNoir = 0;
                else if(joueurActif == 2 && roiBlancSauve == 1)
                    echecEtMatRoiBlanc = 0;

                 
                caseDepart.ligne = sauvegardeCaseDepart.ligne;
                caseDepart.colonne = sauvegardeCaseDepart.colonne;

                caseArrivee.ligne = sauvegardeCaseArrivee.ligne;
                caseArrivee.colonne = sauvegardeCaseArrivee.colonne;
            }
            
            
            
            if(t[i][j] == 'P' && joueurActif == 2)
            {
                if(i == 6 && t[5][j] == ' ' && t[4][j] == ' ') //avance de 2 cases pour le pion
                {
                    caseArrivee.ligne = caseDepart.ligne -2;
                    caseArrivee.colonne = caseDepart.colonne;
                    
                    testSiEchec();
                    
                    if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                        roiNoireSauve = 1;
                    else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                        roiBlancSauve = 1;
                        
                }
                
                if(t[caseDepart.ligne -1][caseDepart.colonne] == ' ')
                {
                    caseArrivee.ligne = caseDepart.ligne -1;
                    caseArrivee.colonne = caseDepart.colonne;
                    
                    testSiEchec();
                    if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                        roiNoireSauve = 1;
                    else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                        roiBlancSauve = 1;
                }
                
                caseArrivee.ligne = caseDepart.ligne -1;
                caseArrivee.colonne = caseDepart.colonne +1;
                
                runTestEchecMatPion();
                
                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;
                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1; 
    
            
                caseArrivee.ligne = caseDepart.ligne -1;
                caseArrivee.colonne = caseDepart.colonne -1;
                
                runTestEchecMatPion();
                
                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;
                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1; 
                    
                    
                if(joueurActif == 1 && roiNoireSauve == 1)
                    echecEtMatRoiNoir = 0;
                else if(joueurActif == 2 && roiBlancSauve == 1)
                    echecEtMatRoiBlanc = 0;


                 
                caseDepart.ligne = sauvegardeCaseDepart.ligne;
                caseDepart.colonne = sauvegardeCaseDepart.colonne;

                caseArrivee.ligne = sauvegardeCaseArrivee.ligne;
                caseArrivee.colonne = sauvegardeCaseArrivee.colonne;
            }
            
            if((t[i][j] == 'k' && joueurActif == 1 )|| (t[i][j] == 'K' && joueurActif == 2))
            {
                caseArrivee.ligne = caseDepart.ligne -1;
                caseArrivee.colonne = caseDepart.colonne -1;
                
               runTestEchecMatElimination();

                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;

                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1; 
                    
                caseArrivee.ligne = caseDepart.ligne -1;
                caseArrivee.colonne = caseDepart.colonne;
                
               runTestEchecMatElimination();

                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;

                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1; 
                
                caseArrivee.ligne = caseDepart.ligne -1;
                caseArrivee.colonne = caseDepart.colonne +1;
                
               runTestEchecMatElimination();

                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;

                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1;              
                
                caseArrivee.ligne = caseDepart.ligne;
                caseArrivee.colonne = caseDepart.colonne+1;
                
                runTestEchecMatElimination();

                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;

                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1;                  
                
                caseArrivee.ligne = caseDepart.ligne +1;
                caseArrivee.colonne = caseDepart.colonne +1;
                
                runTestEchecMatElimination();

                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;
                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1;                
                
                caseArrivee.ligne = caseDepart.ligne +1;
                caseArrivee.colonne = caseDepart.colonne;
                
                runTestEchecMatElimination();

                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;

                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1;            
                
                caseArrivee.ligne = caseDepart.ligne +1;
                caseArrivee.colonne = caseDepart.colonne -1;

                runTestEchecMatElimination();

                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;

                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1;                   
                
                caseArrivee.ligne = caseDepart.ligne;
                caseArrivee.colonne = caseDepart.colonne -1;

                runTestEchecMatElimination();

                if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                    roiNoireSauve = 1;

                else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                    roiBlancSauve = 1; 
                 
                 if(joueurActif == 1 && roiNoireSauve == 1)
                     echecEtMatRoiNoir = 0;

                 else if(joueurActif == 2 && roiBlancSauve == 1)
                     echecEtMatRoiBlanc = 0;

                 
                caseDepart.ligne = sauvegardeCaseDepart.ligne;
                caseDepart.colonne = sauvegardeCaseDepart.colonne;

                caseArrivee.ligne = sauvegardeCaseArrivee.ligne;
                caseArrivee.colonne = sauvegardeCaseArrivee.colonne;
            }
            
            
           if(((t[i][j] == 't' || t[i][j] == 'q') && joueurActif == 1) || ((t[i][j] == 'T' || t[i][j] == 'Q') && joueurActif == 2))
           {
                percut = 0;
                /* je check en haut */
                for(k= i ; k >= 0 ; k--)
                {
                    if(percut == 0 && (k != i))
                    {
                        caseArrivee.ligne = k;
                        caseArrivee.colonne = caseDepart.colonne;
                        
                        runTestEchecMatElimination();
                        
                        if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                            roiNoireSauve = 1;
                        else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                            roiBlancSauve = 1;
                    }
                }
                percut = 0; //je remet percut à 0 pour les autres tests
                
                /* je check en bas */
                for(l= i ; l < 8 ; l++)
                {
                    if(percut == 0 && (l != i))
                    {
                        caseArrivee.ligne = l;
                        caseArrivee.colonne = caseDepart.colonne;
                        
                        runTestEchecMatElimination();
                        
                        if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                            roiNoireSauve = 1;
                        else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                            roiBlancSauve = 1;

                            
                    }
                }
                percut = 0;
                
                /* je check a droite */
                for(m= j ; m < 8 ; m++)
                {
                    if(percut == 0 && (m != j))
                    {
                        caseArrivee.ligne = caseDepart.ligne;
                        caseArrivee.colonne = m;
                        
                        runTestEchecMatElimination();
                        
                        if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                            roiNoireSauve = 1;
                        else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                            roiBlancSauve = 1;
                    }
                }
                percut = 0;
                
                /* je check a gauche */
                for(n= j ; n >= 0 ; n--)
                {
                    if(percut == 0 && (n != j))
                    {
                        caseArrivee.ligne = caseDepart.ligne;
                        caseArrivee.colonne = n;
                        
                        runTestEchecMatElimination();
                        
                        if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                            roiNoireSauve = 1;
                        else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                            roiBlancSauve = 1;
                    }  
                }
                percut = 0;
                
                if(joueurActif == 1 && roiNoireSauve == 1)
                     echecEtMatRoiNoir = 0;
                else if(joueurActif == 2 && roiBlancSauve == 1)
                     echecEtMatRoiBlanc = 0;

                 
                caseDepart.ligne = sauvegardeCaseDepart.ligne;
                caseDepart.colonne = sauvegardeCaseDepart.colonne;

                caseArrivee.ligne = sauvegardeCaseArrivee.ligne;
                caseArrivee.colonne = sauvegardeCaseArrivee.colonne;
            }
            
            
            if(((t[i][j] == 'f' || t[i][j] == 'q') && joueurActif == 1) || ((t[i][j] == 'F' || t[i][j] == 'Q') && joueurActif == 2))
            {  
                percut = 0;
                
                /* je check HG */
                for(o= i, p=j ; o >= 0, p >= 0 ; o-- , p--)
                {
                    if(percut == 0 && (o != i && p != j))
                    {
                        caseArrivee.ligne = o;
                        caseArrivee.colonne = p;
                        
                        runTestEchecMatElimination();
                        
                        if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                            roiNoireSauve = 1;
                        else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                            roiBlancSauve = 1;
                    }
                }
                percut = 0; //je remet percut à 0 pour les autres tests
                
                /* je check HD */
                for(o= i, p=j ; o >= 0, p < 8 ; o-- , p++)
                {
                    if(percut == 0 && (o != i && p != j))
                    {
                        caseArrivee.ligne = o;
                        caseArrivee.colonne = p;
                        
                        runTestEchecMatElimination();
                        
                        if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                            roiNoireSauve = 1;
                        else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                            roiBlancSauve = 1;

                    }
                }
                percut = 0;
                
                /* je check BD */
                for(o= i, p=j ; o < 8, p < 8 ; o++ , p++)
                {
                    if(percut == 0 && (o != i && p != j))
                    {
                        caseArrivee.ligne = o;
                        caseArrivee.colonne = p;
                        
                        runTestEchecMatElimination();
                        
                        if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                            roiNoireSauve = 1;
                        else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                            roiBlancSauve = 1;

                    }
                }
                percut = 0;
                
                /* je check BG */
                for(o= i, p=j ; o < 8, p >= 0 ; o++ , p--)
                {
                    if(percut == 0 && (o != i && p != j))
                    {
                        caseArrivee.ligne = o;
                        caseArrivee.colonne = p;
                        
                        runTestEchecMatElimination();
                        
                        if(joueurActif == 1 && RoiNoireEnECHEC == 0)
                            roiNoireSauve = 1;
                        else if(joueurActif == 2 && RoiBlancEnECHEC == 0)
                            roiBlancSauve = 1;

                    }
                }
                percut = 0;
                
                if(joueurActif == 1 && roiNoireSauve == 1)
                    echecEtMatRoiNoir = 0;
                else if(joueurActif == 2 && roiBlancSauve == 1)
                     echecEtMatRoiBlanc = 0;
                
                 
                caseDepart.ligne = sauvegardeCaseDepart.ligne;
                caseDepart.colonne = sauvegardeCaseDepart.colonne;

                caseArrivee.ligne = sauvegardeCaseArrivee.ligne;
                caseArrivee.colonne = sauvegardeCaseArrivee.colonne;
            }
            
        }
        
    }
    

    
    /* ---------- une fois que tu auras enlever les printf("le roi noir peut se sauver lui même, tu peux rempalcer tout les if(roiNoirsSauve == 1) par une seule ci-dessous." -----------*/    
    //if(roiNoireSauve == 0)
    //    echecEtMatRoiNoir = 1;
        
    flagTestSiEchecEtMat = 0 ;
    
}

void runTestEchecMatElimination()
{
    char valeurCaseMange;
   
    if(joueurActif == 1)//si c'est le joueurBlanc, c'est les pieces noire qui doivent sauver le roi
    {
        if(t[caseArrivee.ligne][caseArrivee.colonne] != 't' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'f' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'c' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'k' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'q' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'p' )
        {
            /* sauvegarde de la piece visé en cas d'élimination*/
          valeurCaseMange = t[caseArrivee.ligne][caseArrivee.colonne];
          
          testSiEchec(); //il va tester si il peux faire ce coup, et test l'echec à chaque fois 
           /* on replace la piece visé car si il y a élimination il la effacé*/
          t[caseArrivee.ligne][caseArrivee.colonne] = valeurCaseMange;

        }
        if(t[caseArrivee.ligne][caseArrivee.colonne] == 't' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'f' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'c' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'k' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'q' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'p' )
        {
            percut = 1;
        }
    }
    else if(joueurActif == 2)//si c'est le joueur Noir c'est les pieces blanches qui doivent sauver le roi
    {
        if(t[caseArrivee.ligne][caseArrivee.colonne] != 'T' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'F' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'C' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'K' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'Q' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'P' )
        {
            /* sauvegarde de la piece visé en cas d'élimination*/
          valeurCaseMange = t[caseArrivee.ligne][caseArrivee.colonne];
        
          testSiEchec(); //il va tester si il peux faire ce coup, et test l'echec à chaque fois 
                      
           /* on replace la piece visé car si il y a élimination il la effacé*/
          t[caseArrivee.ligne][caseArrivee.colonne] = valeurCaseMange;
        }
        if(t[caseArrivee.ligne][caseArrivee.colonne] == 'T' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'F' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'C' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'K' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'Q' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'P' )
        {
            percut = 1;
        }
    }

}

void runTestEchecMatPion()
{
    char valeurCaseMange;
    if(joueurActif == 1)//si c'est le joueurBlanc, c'est les pieces noire qui doivent sauver le roi
    {
        if(t[caseArrivee.ligne][caseArrivee.colonne] != 't' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'f' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'c' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'k' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'q' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'p' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != ' ')
        {
          valeurCaseMange = t[caseArrivee.ligne][caseArrivee.colonne];//j'utilise une variable pour stocké la case "mangé" pendant le test
        
          testSiEchec(); //il va tester si il peux faire ce coup, et test l'echec à chaque fois 
          
          t[caseArrivee.ligne][caseArrivee.colonne] = valeurCaseMange;//je remet la piece manger pendant le test
        }  
    }
    else if(joueurActif == 2)//si c'est le joueur Noirn c'est les pieces blanches qui doivent sauver le roi
    {
        if(t[caseArrivee.ligne][caseArrivee.colonne] != 'T' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'F' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'C' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'K' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'Q' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'P' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != ' ')
        {
          valeurCaseMange = t[caseArrivee.ligne][caseArrivee.colonne];
        
          testSiEchec(); //il va tester si il peux faire ce coup, et test l'echec à chaque fois 
          
          t[caseArrivee.ligne][caseArrivee.colonne] = valeurCaseMange;
        }  
    }
    

}

//----------------------- Module de vérication du Pat --------------------------//
void testSiPat()
{
    printf("je suis entré dans testSiPat()\n");
    /*
        tu ne peux bouger aucune piece sans mettre ton roi en echec
        
        
        Déclaration de fonction :
            void testSiPat();
            void runTestPatElimination();
            void runTestPatPion();
        
        
        a mettre dans le case 1 ligne 230 et le case 2 :
        
        TestSiPat();
        if(Pat == 1)
        {
            partietermine = 1; //peut être ça ? 
            //la faut afficher la fin de partie
        }
        
        
        
        variable globale = 
            int Pat;
    */
    
    sauvegardeCaseDepart.ligne = caseDepart.ligne;
    sauvegardeCaseDepart.colonne = caseDepart.colonne;
    
    sauvegardeCaseArrivee.ligne = caseArrivee.ligne;
    sauvegardeCaseArrivee.colonne = caseArrivee.colonne;
    
    int i,j,k,l,m,n,o,p;

    
    Pat = 1;//je met Pat à 1, le but est que le test le passe à 0 (on peut continuer à jouer dans ce cas là)
    

    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)//je parcours tout le tableau à la recherche des pieces
        {
            caseDepart.ligne = i;
            caseDepart.colonne = j;
            
            if((t[i][j] == 'c' && joueurActif == 2) || (t[i][j] == 'C' && joueurActif == 1) )
            {
                caseArrivee.ligne = caseDepart.ligne -2;
                caseArrivee.colonne = caseDepart.colonne -1;
                
                runTestPatElimination();
                
                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                    Pat = 0; //on peut faire un mouvement sans mettre son roi en Echec
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0;

                caseArrivee.ligne = caseDepart.ligne -2;
                caseArrivee.colonne = caseDepart.colonne +1;
                
                runTestPatElimination();

                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                    Pat = 0; 
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0;

                caseArrivee.ligne = caseDepart.ligne -1;
                caseArrivee.colonne = caseDepart.colonne -2;
                
                runTestPatElimination();

                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                    Pat = 0; 
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0;

                caseArrivee.ligne = caseDepart.ligne -1;
                caseArrivee.colonne = caseDepart.colonne +2;
                
                runTestPatElimination();

                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                    Pat = 0; 
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0;
            
                caseArrivee.ligne = caseDepart.ligne +2;
                caseArrivee.colonne = caseDepart.colonne -1;
                
                runTestPatElimination();

                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                    Pat = 0;
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0;

                caseArrivee.ligne = caseDepart.ligne +2;
                caseArrivee.colonne = caseDepart.colonne +1;
                
                runTestPatElimination();
                
                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                    Pat = 0; 
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0;
                
                
                caseArrivee.ligne = caseDepart.ligne +1;
                caseArrivee.colonne = caseDepart.colonne -2;
                
                runTestPatElimination();

                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                    Pat = 0; 
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0;
                    
                caseArrivee.ligne = caseDepart.ligne +1;
                caseArrivee.colonne = caseDepart.colonne +2;
                
                runTestPatElimination();
                
                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                    Pat = 0; 
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0;

                caseDepart.ligne = sauvegardeCaseDepart.ligne;
                caseDepart.colonne = sauvegardeCaseDepart.colonne;

                caseArrivee.ligne = sauvegardeCaseArrivee.ligne;
                caseArrivee.colonne = sauvegardeCaseArrivee.colonne;
            }
            
            if(t[i][j] == 'p' && joueurActif == 2)
            {
                if(i == 1 && t[caseDepart.ligne+1][caseDepart.colonne] == ' ' && t[caseDepart.ligne +2][caseDepart.colonne] == ' ') //avance de 2 cases pour le pion
                {
                    caseArrivee.ligne = caseDepart.ligne +2;
                    caseArrivee.colonne = caseDepart.colonne;
                    
                    testSiEchec();
                    
                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                    Pat = 0; 
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0;
                        
                }
                
                if(t[caseDepart.ligne +1][caseDepart.colonne] == ' ')
                {
                    caseArrivee.ligne = caseDepart.ligne +1;
                    caseArrivee.colonne = caseDepart.colonne;
                    
                    testSiEchec();
                    if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                       Pat = 0; 
                    else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                      Pat = 0;
                }
                
                caseArrivee.ligne = caseDepart.ligne +1;
                caseArrivee.colonne = caseDepart.colonne +1;
                
                runTestPatPion();
                
                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                    Pat = 0; 
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0; 
    
            
                caseArrivee.ligne = caseDepart.ligne +1;
                caseArrivee.colonne = caseDepart.colonne -1;
                
                runTestPatPion();
                
                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                    Pat = 0; 
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0;
                    
                caseDepart.ligne = sauvegardeCaseDepart.ligne;
                caseDepart.colonne = sauvegardeCaseDepart.colonne;

                caseArrivee.ligne = sauvegardeCaseArrivee.ligne;
                caseArrivee.colonne = sauvegardeCaseArrivee.colonne;
            }
            
            if(t[i][j] == 'P' && joueurActif == 1)
            {
                if(i == 6 && t[5][j] == ' ' && t[4][j] == ' ') //avance de 2 cases pour le pion
                {
                    caseArrivee.ligne = caseDepart.ligne -2;
                    caseArrivee.colonne = caseDepart.colonne;
                    
                    testSiEchec();
                    
                    if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                        Pat = 0;
  
                }
                
                if(t[caseDepart.ligne -1][caseDepart.colonne] == ' ')
                {
                    caseArrivee.ligne = caseDepart.ligne -1;
                    caseArrivee.colonne = caseDepart.colonne;
                    
                    testSiEchec();
                    if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                        Pat = 0;
                }
                
                caseArrivee.ligne = caseDepart.ligne -1;
                caseArrivee.colonne = caseDepart.colonne +1;
                
                runTestPatPion();
                
                if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                        Pat = 0; 
    
            
                caseArrivee.ligne = caseDepart.ligne -1;
                caseArrivee.colonne = caseDepart.colonne -1;
                
                runTestPatPion();
                
                if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                        Pat = 0;
                        
                caseDepart.ligne = sauvegardeCaseDepart.ligne;
                caseDepart.colonne = sauvegardeCaseDepart.colonne;

                caseArrivee.ligne = sauvegardeCaseArrivee.ligne;
                caseArrivee.colonne = sauvegardeCaseArrivee.colonne;
            }
            
            if((t[i][j] == 'k' && joueurActif == 2 )|| (t[i][j] == 'K' && joueurActif == 1))
            {
                printf("j'ai trouvé le roi, Pat : %d\n",Pat);
                caseArrivee.ligne = caseDepart.ligne -1;
                caseArrivee.colonne = caseDepart.colonne -1;
                
               runTestPatElimination();

                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                {
                    Pat = 0; 
                    printf("cas 1\n");
                }
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0;
                    
                caseArrivee.ligne = caseDepart.ligne -1;
                caseArrivee.colonne = caseDepart.colonne;
                
               runTestPatElimination();

                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                {
                    Pat = 0; 
                    printf("cas 2\n");
                }
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0; 
                
                caseArrivee.ligne = caseDepart.ligne -1;
                caseArrivee.colonne = caseDepart.colonne +1;
                
               runTestPatElimination();

                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                {
                    Pat = 0; 
                    printf("cas 3\n");
                }
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0;              
                
                caseArrivee.ligne = caseDepart.ligne;
                caseArrivee.colonne = caseDepart.colonne+1;
                
                runTestPatElimination();

                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                {
                    Pat = 0; 
                    printf("cas 4\n");
                }
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0;                  
                
                caseArrivee.ligne = caseDepart.ligne +1;
                caseArrivee.colonne = caseDepart.colonne +1;
                
                runTestPatElimination();

                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                 {
                    Pat = 0; 
                    printf("cas 5\n");
                }
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0;                
                
                caseArrivee.ligne = caseDepart.ligne +1;
                caseArrivee.colonne = caseDepart.colonne;
                
                runTestPatElimination();

                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                {
                    Pat = 0; 
                    printf("cas 6\n");
                }
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0;           
                
                caseArrivee.ligne = caseDepart.ligne +1;
                caseArrivee.colonne = caseDepart.colonne -1;

                runTestPatElimination();

                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                {
                    Pat = 0; 
                    printf("cas 7\n");
                }
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0;                  
                
                caseArrivee.ligne = caseDepart.ligne;
                caseArrivee.colonne = caseDepart.colonne -1;

                runTestPatElimination();

                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                {
                    Pat = 0; 
                    printf("cas 8\n");
                }
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0; 
                    
                    
                caseDepart.ligne = sauvegardeCaseDepart.ligne;
                caseDepart.colonne = sauvegardeCaseDepart.colonne;

                caseArrivee.ligne = sauvegardeCaseArrivee.ligne;
                caseArrivee.colonne = sauvegardeCaseArrivee.colonne;

            }
            
            
           if(((t[i][j] == 't' || t[i][j] == 'q') && joueurActif == 2) || ((t[i][j] == 'T' || t[i][j] == 'Q') && joueurActif == 1))
           {
                percut = 0;
                /* je check en haut */
                for(k= i ; k >= 0 ; k--)
                {
                    if(percut == 0 && (k != i))
                    {
                        caseArrivee.ligne = k;
                        caseArrivee.colonne = caseDepart.colonne;
                        
                        runTestPatElimination();
                        
                        if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                            Pat = 0; 
                        else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                            Pat = 0;
                    }
                }
                percut = 0; //je remet percut à 0 pour les autres tests
                
                /* je check en bas */
                for(l= i ; l < 8 ; l++)
                {
                    if(percut == 0 && (l != i))
                    {
                        caseArrivee.ligne = l;
                        caseArrivee.colonne = caseDepart.colonne;
                        
                        runTestPatElimination();
                        
                        if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                            Pat = 0; 
                        else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                            Pat = 0;

                            
                    }
                }
                percut = 0;
                
                /* je check a droite */
                for(m= j ; m < 8 ; m++)
                {
                    if(percut == 0 && (m != j))
                    {
                        caseArrivee.ligne = caseDepart.ligne;
                        caseArrivee.colonne = m;
                        
                        runTestPatElimination();
                        
                        if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                            Pat = 0; 
                        else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                            Pat = 0;
                    }
                }
                percut = 0;
                
                /* je check a gauche */
                for(n= j ; n >= 0 ; n--)
                {
                    if(percut == 0 && (n != j))
                    {
                        caseArrivee.ligne = caseDepart.ligne;
                        caseArrivee.colonne = n;
                        
                        runTestPatElimination();
                        
                        if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                            Pat = 0; 
                        else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                            Pat = 0;
                    }  
                }
                percut = 0;
                
                caseDepart.ligne = sauvegardeCaseDepart.ligne;
                caseDepart.colonne = sauvegardeCaseDepart.colonne;

                caseArrivee.ligne = sauvegardeCaseArrivee.ligne;
                caseArrivee.colonne = sauvegardeCaseArrivee.colonne;
                 
            }
            
            if(((t[i][j] == 'f' || t[i][j] == 'q') && joueurActif == 2) || ((t[i][j] == 'F' || t[i][j] == 'Q') && joueurActif == 1))
            {  
                percut = 0;
                
                /* je check HG */
                for(o= i, p=j ; o >= 0, p >= 0 ; o-- , p--)
                {
                    if(percut == 0 && (o != i && p != j))
                    {
                        caseArrivee.ligne = o;
                        caseArrivee.colonne = p;
                        
                        runTestPatElimination();
                        
                        if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                            Pat = 0; 
                        else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                            Pat = 0;
                    }
                }
                percut = 0; //je remet percut à 0 pour les autres tests
                
                /* je check HD */
                for(o= i, p=j ; o >= 0, p < 8 ; o-- , p++)
                {
                    if(percut == 0 && (o != i && p != j))
                    {
                        caseArrivee.ligne = o;
                        caseArrivee.colonne = p;
                        
                        runTestPatElimination();
                        
                        if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                            Pat = 0; 
                        else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                            Pat = 0;

                    }
                }
                percut = 0;
                
                /* je check BD */
                for(o= i, p=j ; o < 8, p < 8 ; o++ , p++)
                {
                    if(percut == 0 && (o != i && p != j))
                    {
                        caseArrivee.ligne = o;
                        caseArrivee.colonne = p;
                        
                        runTestPatElimination();
                        
                        if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                            Pat = 0; 
                        else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                            Pat = 0;

                    }
                }
                percut = 0;
                
                /* je check BG */
                for(o= i, p=j ; o < 8, p >= 0 ; o++ , p--)
                {
                    if(percut == 0 && (o != i && p != j))
                    {
                        caseArrivee.ligne = o;
                        caseArrivee.colonne = p;
                        
                        runTestPatElimination();
                        
                        if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                            Pat = 0; 
                        else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                            Pat = 0;

                    }
                }
                percut = 0;
                
                
                if(joueurActif == 2 && RoiNoireEnECHEC == 0)
                    Pat = 0; 
                else if(joueurActif == 1 && RoiBlancEnECHEC == 0)
                    Pat = 0;
                
                 
                caseDepart.ligne = sauvegardeCaseDepart.ligne;
                caseDepart.colonne = sauvegardeCaseDepart.colonne;

                caseArrivee.ligne = sauvegardeCaseArrivee.ligne;
                caseArrivee.colonne = sauvegardeCaseArrivee.colonne;
                
            }
            
        }
    }
        printf("je sors de testSiPat() avec pat = %d\n", Pat);
}
//----------------------- pour gestion de l'élimination fictive dans le testSiPat()----------------------------//
void runTestPatElimination()
{
    char valeurCaseMange;
   
    if(joueurActif == 2)
    {
        if(t[caseArrivee.ligne][caseArrivee.colonne] != 't' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'f' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'c' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'k' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'q' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'p' )
        {
            /* sauvegarde de la piece visé en cas d'élimination*/
          valeurCaseMange = t[caseArrivee.ligne][caseArrivee.colonne];
          printf("Avant testSiEchec , RoiNoireEnECHEC = %d\n", RoiNoireEnECHEC);
          testSiEchec(); //il va tester si il peux faire ce coup, et test l'echec à chaque fois 
           /* on replace la piece visé car si il y a élimination il la effacé*/
           printf("Aprés testSiEchec, RoiNoireEnECHEC = %d\n", RoiNoireEnECHEC);
          t[caseArrivee.ligne][caseArrivee.colonne] = valeurCaseMange;

        }
        if(t[caseArrivee.ligne][caseArrivee.colonne] == 't' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'f' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'c' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'k' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'q' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'p' )
        {
            percut = 1;
        }
    }
    else if(joueurActif == 1)
    {
        if(t[caseArrivee.ligne][caseArrivee.colonne] != 'T' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'F' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'C' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'K' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'Q' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'P' )
        {
            /* sauvegarde de la piece visé en cas d'élimination*/
          valeurCaseMange = t[caseArrivee.ligne][caseArrivee.colonne];
        
          testSiEchec(); //il va tester si il peux faire ce coup, et test l'echec à chaque fois 
                      
           /* on replace la piece visé car si il y a élimination il la effacé*/
          t[caseArrivee.ligne][caseArrivee.colonne] = valeurCaseMange;
        }
        if(t[caseArrivee.ligne][caseArrivee.colonne] == 'T' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'F' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'C' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'K' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'Q' ||
           t[caseArrivee.ligne][caseArrivee.colonne] == 'P' )
        {
            percut = 1;
        }
    }

}

void runTestPatPion()
{
    char valeurCaseMange;
    if(joueurActif == 2)
    {
        if(t[caseArrivee.ligne][caseArrivee.colonne] != 't' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'f' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'c' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'k' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'q' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'p' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != ' ')
        {
          valeurCaseMange = t[caseArrivee.ligne][caseArrivee.colonne];//j'utilise une variable pour stocké la case "mangé" pendant le test
        
          testSiEchec(); //il va tester si il peux faire ce coup, et test l'echec à chaque fois 
          
          t[caseArrivee.ligne][caseArrivee.colonne] = valeurCaseMange;//je remet la piece manger pendant le test
        }  
    }
    else if(joueurActif == 1)
    {
        if(t[caseArrivee.ligne][caseArrivee.colonne] != 'T' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'F' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'C' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'K' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'Q' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != 'P' &&
           t[caseArrivee.ligne][caseArrivee.colonne] != ' ')
        {
          valeurCaseMange = t[caseArrivee.ligne][caseArrivee.colonne];
        
          testSiEchec(); //il va tester si il peux faire ce coup, et test l'echec à chaque fois 
          
          t[caseArrivee.ligne][caseArrivee.colonne] = valeurCaseMange;
        }  
    }
    

}



    
}
//----------------------- Faire un roque ----------------------------//
void jeRoque()
{
    char choix[20] = "coucou";
    if(joueurActif == 1)
    {
        if(roqueJ1 < 2 && t[7][1] == ' ' && t[7][2] == ' ' && t[7][3] == ' ' 
        && t[7][5] == ' ' && t[7][6] == ' ')
        {
            printf("---------------------------------\n");
            printf("--  1- Faire un grand roque    --\n");
            printf("--  2- Faire un petit roque    --\n");
            printf("--  3- Retour                  --\n");        
            printf("---------------------------------\n");
       
            while(choix[0] != '1' && choix[0] != '2' && choix[0] != '3')
            {
                printf("Choix : ");
                scanf("%s", choix);
                
                switch(choix[0])
                {
                    case '1':
                        t[7][2] = 'K';
                        t[7][3] = 'T';
                        t[7][0] = ' ';
                        t[7][4] = ' ';
                        ECHEC = 0;
                        roqueJ1 = 2;
                        break;
                        
                    case '2': 
                        t[7][6] = 'K';
                        t[7][5] = 'T';
                        t[7][7] = ' ';
                        t[7][4] = ' ';
                        ECHEC = 0;
                        roqueJ1 = 2;
                        break;
                    
                    case '3':
                        ECHEC = 1;
                        break;
                        
                    default:
                        printf("Erreur de saisie, veuillez recommencer\n");
                        break;
                }
            }
                
        }
        
        else if(roqueJ1 < 2 && t[7][1] == ' ' && t[7][2] == ' ' && t[7][3] == ' ')
        {
            printf("---------------------------------\n");
            printf("--  1- Faire un grand roque    --\n");
            printf("--  2- Retour                  --\n");        
            printf("---------------------------------\n");

            while(choix[0] != '1' && choix[0] != '2')
            {
                printf("Choix : ");
                scanf("%s", choix);
                
                switch(choix[0])
                {
                    case '1':
                        t[7][2] = 'K';
                        t[7][3] = 'T';
                        t[7][0] = ' ';
                        t[7][4] = ' ';
                        ECHEC = 0;
                        roqueJ1 = 2;
                        break;
                        
                    case '2':
                        ECHEC = 1;
                        break;
                      
                    default:
                        printf("Erreur de saisie, veuillez recommencer\n");
                        break;
                }
            }
            
        }
        
        else if (roqueJ1 < 2 && t[7][5] == ' ' && t[7][6] == ' ')
        {
            printf("---------------------------------\n");
            printf("--  1- Faire un petit roque    --\n");
            printf("--  2- Retour                  --\n");        
            printf("---------------------------------\n");
       
            while(choix[0] != '1' && choix[0] != '2')
            {
                printf("Choix : ");
                scanf("%s", choix);
                
                switch(choix[0])
                {
                    case '1':
                        t[7][6] = 'K';
                        t[7][5] = 'T';
                        t[7][7] = ' ';
                        t[7][4] = ' ';
                        ECHEC = 0;
                        roqueJ1 = 2;
                        break;
                        
                    case '2':
                        ECHEC = 1;
                        break;
                      
                    default:
                        printf("Erreur de saisie, veuillez recommencer\n");
                        break;
                }
            }
            
        }
        else
        {
            printf("Vous ne pouvez pas faire de roque\n");
            ECHEC = 1;
            roque = 0;
        }
    }
    
    else if(joueurActif == 2)
    {
        if(roqueJ2 < 2 && t[0][1] == ' ' && t[0][2] == ' ' && t[0][3] == ' ' 
        && t[0][5] == ' ' && t[0][6] == ' ')
        {
            printf("---------------------------------\n");
            printf("--  1- Faire un grand roque    --\n");
            printf("--  2- Faire un petit roque    --\n");
            printf("--  3- Retour                  --\n");        
            printf("---------------------------------\n");
       
            while(choix[0] != '1' && choix[0] != '2' && choix[0] != '3')
            {
                printf("Choix : ");
                scanf("%s", choix);
                
                switch(choix[0])
                {
                    case '1':
                        t[0][2] = 'k';
                        t[0][3] = 't';
                        t[0][0] = ' ';
                        t[0][4] = ' ';
                        ECHEC = 0;
                        roqueJ2 = 2;
                        break;
                        
                    case '2': 
                        t[0][6] = 'k';
                        t[0][5] = 't';
                        t[0][7] = ' ';
                        t[0][4] = ' ';
                        ECHEC = 0;
                        roqueJ2 = 2;
                        break;
                    
                    case '3':
                        ECHEC = 1;
                        break;
                    
                    default:
                        printf("Erreur de saisie, veuillez recommencer\n");
                        break;
                }
            }
                
        }
        
        else if(roqueJ2 < 2 && t[0][1] == ' ' && t[0][2] == ' ' && t[0][3] == ' ' )
        {
            printf("---------------------------------\n");
            printf("--  1- Faire un grand roque    --\n");
            printf("--  2- Retour                  --\n");        
            printf("---------------------------------\n");
            
            while(choix[0] != '1' && choix[0] != '2')
            {
                printf("Choix : ");
                scanf("%s", choix);
                
                switch(choix[0])
                {
                    case '1':
                        t[0][2] = 'k';
                        t[0][3] = 't';   
                        t[0][0] = ' ';
                        t[0][4] = ' ';
                        ECHEC = 0;
                        roqueJ2 = 2;
                        break;
                        
                    case '2':
                        ECHEC = 1;
                        break;
                    
                    default:
                        printf("Erreur de saisie, veuillez recommencer\n");
                        break;
                }
            }
            
        }
        
        else if(roqueJ2 < 2 && t[0][5] == ' ' && t[0][6] == ' ')
        {
            printf("---------------------------------\n");
            printf("--  1- Faire un petit roque    --\n");
            printf("--  2- Retour                  --\n");        
            printf("---------------------------------\n");
        
            while(choix[0] != '1' && choix[0] != '2')
            {
                printf("Choix : ");
                scanf("%s", choix);
                
                switch(choix[0])
                {
                    case '1':
                        t[0][6] = 'k';
                        t[0][5] = 't';
                        t[0][7] = ' ';
                        t[0][4] = ' ';
                        ECHEC = 0;
                        roqueJ2 = 2;
                        break;
                        
                    case '2':
                        ECHEC = 1;
                        break;
                    
                    default:
                        printf("Erreur de saisie, veuillez recommencer\n");
                        break;
                }
            }
            
        }
        else
        {
            printf("Vous ne pouvez pas faire de roque !\n");
            ECHEC = 1;
            roque = 0;
        }
    }    

}

//..........................Sauvegarde............................//
void sauvegarde()
{	
    int i,j, joueurA;
    FILE *f1;
    char nomFichier[100], caseEnregistree;
    
    printf("Nom du fichier de sauvegarde : ");
    scanf("%s",nomFichier);
    f1 = fopen(nomFichier,"w");
    
    joueurA = joueurActif;
    fprintf(f1,"%d", joueurA); //pour le joueurActif
    
    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)
        {
            caseEnregistree = t[i][j];
            fprintf(f1,"%c",caseEnregistree);
        }
    }
    
    fclose(f1);
    printf("C'est fait mon capitaine ! Votre partie est sauvegardee !\n");

}

//...........................Chargement...........................//
void chargement()
{
    int i, j, joueurA, siEchec, retour;
    char NomFichier[100], caseEnregistree;
    FILE *f1 = NULL;
    ECHEC = 1;
    
    while(ECHEC == 1)
    {
        printf("Quel fichier voulez vous ouvrir? ");
    	scanf("%s", NomFichier);
    
    	f1 = fopen(NomFichier,"r");
        
        if(f1 != NULL)
        {
            ECHEC = 0;
            fscanf(f1, "%d", &joueurA);
    	    joueurActif = joueurA;
            fseek(f1, 1, SEEK_SET);
            
            while(! feof(f1))
        	{    
                for(i = 0; i < 8; i++)
                {
                    for(j = 0; j < 8; j++)
                    {
                        retour = fscanf(f1,"%c", &caseEnregistree);
                        if(retour != EOF)
                        {
                        	t[i][j] = caseEnregistree;
                        }
                    }
                }
        		
        	}
        }
        else
        {
            printf("Impossible d'ouvrir le fichier %s\n", NomFichier);
            ECHEC = 1;
        }
    }
    
    fclose(f1);
}