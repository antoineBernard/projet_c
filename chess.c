/*
-------TODO------ : 
    - travailler sur l'ergonomie
    - virer les printf en commentaire
    - Dégager les fautes d'orthographe
    - Debug Pat & Echec & Mat ----> cf. chess30.c
    - Debug, il affiche ROI NOIR EN ECHEC lors qu'on change de piece après avoir tenter un coup qui met son propre roi en echec
            l'affichage se corrige tout seul après le deplacement d'une piece
    - Debug, toujours l'affichage ROI NOIR EN ECHEC (le blanc aussi surement) = il s'affiche lorsqu'un roi en echec mange une piece pour s'en sortir.
        encore un fois, le bug se corrige quand on continue la parite
                --> voila un échiquier pour tester ce bug : F8 en B4 puis d2 en D4 (!message d'erreur!) donc on change de piece 2 et la "ROI NOIR EN ECEHC APPARAIT"
    char t[8] [8]={
    't','c','f','q','k','f','c','t',
    'p','p','p','p','p','p','p','p',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    'P','P','P','P',' ','P','P','P',
    'T','C','F','Q','K','F','C','T'
};


    Deuxieme Bug --> toujours avec le même échiquier F8 en B4 puis H2 en H3 puis B4 en D2 (ici on a l'affichage d'echec) puis E1 en D2 --> bug semble être corrigé


     ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     MODIFICATIONS EFFECTUEES : 01/05
     Marion : 
     Prévoir tout un jeu de tests pour vérifier que tout se passe bien (--> doc excel)
     
     Antoine : 
     - Creation du module d'initialisation de l'échequier
     - Suppression des modules de gestion du PAT (causait des bugs)
     - Affichage lorsqu'un pion devient une reine
     
     //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* ---------------------------------------- Déclaration des fonctions  ----------------------------------------*/

void affichage();
int  deplacementPiece();
void verifCaseChoisie();
int  verifDeplacementArrivee();
void deplacementPion();
void deplacementCavalier();
void deplacementRoi();
void changementDePiece();
void deplacementReineFouTour();
void verifEliminationPiece();
void testDiagonales();
void testRangeesColonnes();
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
void testMauvaiseSaisi();
void runTestEchecMatElimination();
void runTestEchecMatPion();
void testSiPat();
int runTestPatElimination(int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee, char echiquierDeTest[8][8]);
int runTestPatPion(int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee, char echiquierDeTest[8][8]);
int testSiEchecPat(int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee, char echiquierDeTest[8][8]);
int testDevantPat(int i, int j, char echiquierDeTest[8][8]);
int testArrierePat(int i, int j, char echiquierDeTest[8][8]);
int testDroitePat(int i, int j, char echiquierDeTest[8][8]);
int testGauchePat(int i, int j, char echiquierDeTest[8][8]);
int testDiagoHGPat(int i, int j, char echiquierDeTest[8][8]);
int testDiagoHDPat(int i, int j, char echiquierDeTest[8][8]);
int testDiagoBGPat(int i, int j, char echiquierDeTest[8][8]);
int testDiagoBDPat(int i, int j, char echiquierDeTest[8][8]);
void jeRoque();
void sauvegarde();
int chargement();
void initialisationEchiquier();
void videBuffer();
void affichagePat();

/* ----------------------------------------  Déclaration des types en global  ----------------------------------------*/
  struct infoCase                              
              {
                char charColonne;
                int ligne;
                int colonne;
              };

/*---------------------------------------- Déclaration des variables globales ----------------------------------------*/
/*
char t[8] [8]={
    't','c','f','q','k','f','c','t',
    'p','p','p','p','p','p','p','p',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    'P','P','P','P','P','P','P','P',
    'T','C','F','Q','K','F','C','T'
};*/
// ------> pour tester le Pat, on met H1 en A1 puis G3 en G2 puis H7 en H1 puis G3 en G2 puis A1 en F1
// ------> pour tester l'echec et mat, H1 en G1
/*
char t[8] [8]={
    't',' ',' ',' ',' ',' ',' ','Q',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ','k',' ',
    ' ',' ',' ',' ',' ',' ','F',' ',
    ' ',' ',' ',' ',' ','P','P',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    'P','P','P','P','P','P','C','T',
    'T','C','F','Q','K',' ',' ','T'
};*/
char t[8] [8]={
    ' ',' ',' ',' ',' ','T',' ','T',
    ' ',' ',' ',' ','T',' ','F',' ',
    ' ',' ',' ',' ',' ',' ','k','P',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ','P',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    'P','P','P','P','P','P',' ','T',
    'T','C','F','Q','K',' ',' ','T'
};


struct infoCase caseDepart; 
struct infoCase caseArrivee;
struct infoCase sauvegardeCaseArrivee;
struct infoCase sauvegardeCaseDepart;
char piecesDuJoueurActif[10];
int partietermine = 0;
int joueurActif;
int ECHEC; 
int flagTestSiEchecEtMat = 0;
int echecEtMatRoiBlanc = 0; 
int echecEtMatRoiNoir = 0;
int EchecNoir = 0;
int EchecBlanc = 0;
int RoiBlancEnECHEC = 0;
int RoiNoireEnECHEC = 0;
int changePiece = 0;
int percut = 0;
int roque = 0, roqueJ1 = 0, roqueJ2 = 0;
int Pat = 1;



/* ---------------------------------------- Procédure principale --------------------------------------- */
int main() 
{
    char choix[20] = "";
    
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
    printf("                                                                                                       \n");
    printf("                        *Jeux video garanti sans colorant ni conservateur*                        \n");
    printf("\n\n\n\n\n");
    
    printf("Hello World! et bienvenue sur le jeu d'échec !\n\n");
    
    while(choix[0] != '0')
    {
        partietermine = 0; roqueJ1 = 0; roqueJ2 = 0; 
        printf("-------------    MENU      -----------------\n");
        printf("    |  -1- Commencer une nouvelle partie | \n");
        printf("    |  -2- Charger une partie            | \n");
        printf("    |  -0- QUITTER                       | \n");
        printf("--------------------------------------------\n");
        
        printf("Choix : ");
        scanf("%s", choix);
        videBuffer();
         
        if(choix[0] >= '0' && choix[0] <= '2')
        {
            switch(choix[0])
            {
                case '0':
                    printf("Au revoir, et a bientot !\n");
                    break;
                
                case '1':
                    printf("\n\n");
                    printf("C'est parti !\n");
                    //initialisationEchiquier();
                    while(partietermine == 0)
                    {
                        joueurActif = 1;
                        affichage();
                        testSiPat();
                        if(Pat == 1 )
                        {
                            partietermine = 1;
                            affichagePat();
                        }
                        if(partietermine == 0)
                        {
                            partietermine = deplacementPiece();
                        }
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
                          testSiPat();
                          if(Pat == 1)
                          {
                              partietermine = 1;
                              affichagePat();
                          }
                          if(partietermine == 0)
                          {
                              partietermine = deplacementPiece();
                          }
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
                            testSiPat();
                            if(Pat == 1)
                            {
                                partietermine = 1;
                                affichagePat();
                            }
                            if(partietermine == 0)
                            {
                                partietermine = deplacementPiece();
                            }
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
                                testSiPat();
                                if(Pat == 1)
                                {
                                    partietermine = 1;
                                    affichagePat();
                                }
                                if(partietermine == 0)
                                {
                                    partietermine = deplacementPiece();
                                }
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
                            testSiPat();
                            if(Pat == 1)
                            {
                                partietermine = 1;
                                affichagePat();
                            }
                            if(partietermine == 0)
                            {
                                partietermine = deplacementPiece();
                            }
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
                                testSiPat();
                            if(Pat == 1)
                            {
                                partietermine = 1;
                                affichagePat();
                            }
                            if(partietermine == 0)
                            {
                                partietermine = deplacementPiece();
                            }
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


/* ---------------------------------------- Fonction initialisation de l'echiquier ----------------------------------------*/
void initialisationEchiquier()
{
    char echiquierOfficiel[8] [8]={
    't','c','f','q','k','f','c','t',
    'p','p','p','p','p','p','p','p',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    'P','P','P','P','P','P','P','P',
    'T','C','F','Q','K','F','C','T'
    };
    int i, j;

    for( i = 0 ; i <= 7 ; i++ )
    {
        for( j = 0 ; j <= 7 ; j++)
        {
            t[i][j] = echiquierOfficiel[i][j];
        }
    }
}

/* ---------------------------------------- Fonction pour vider le Buffer ----------------------------------------*/
void videBuffer()
{
    int purge = 0;
    while(purge != '\n')
    {
        purge = getchar();
    }
}
/* ---------------------------------------- Fonction affichage de l'echiquier ----------------------------------------*/
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
        if (roqueJ1 < 2 && joueurActif == 1 && t[7][4] == 'K' 
        && ((t[7][0] == 'T' && t[7][1] == ' ' && t[7][2] == ' ' && t[7][3] == ' ') 
        || (t[7][7] == 'T' && t[7][5] == ' ' && t[7][6] == ' ' )))
        {
            printf("  - 0- Abandonner la partie  1- Sauvegarder  2- Changer de piece  3- Faire un roque --\n");
        }
        else 
        {
            printf("  ----------- 0- Abandonner la partie  1- Sauvegarder  2- Changer de piece -----------\n");
        }
        printf("                         _____________________________________\n");
        printf("                         ----- Au joueur BLANC de jouer ! ----\n");
        printf("                           Avec les MAJUSCULES (P,T,C,F,Q,K)\n");
    }
    else if(joueurActif == 2)
    {
        if(roqueJ2 < 2 && joueurActif == 2 && t[0][4] == 'k' 
        && ((t[0][0] == 't' && t[0][1] == ' ' && t[0][2] == ' ' && t[0][3] == ' ')
        || (t[0][7] == 't' && t[0][5] == ' ' && t[0][6] == ' ')))

        {
            printf("  - 0- Abandonner la partie  1- Sauvegarder  2- Changer de piece  3- Faire un roque --\n");
        }
        else 
        {
            printf("  ----------- 0- Abandonner la partie  1- Sauvegarder  2- Changer de piece -----------\n");
        }
        printf("                         _____________________________________\n");
        printf("                         ----- Au joueur NOIR de jouer ! ----\n");
        printf("                           Avec les minuscules (p,t,c,f,q,k)\n");
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

/*--------------------------------------------- Fonction déplacement de piece ---------------------------------------------*/
int deplacementPiece()
{
    //printf("je suis dans déplacementPiece()\n");
    char alphabet[10]= "ABCDEFGH", choix[20];  
    int i = 0, numeroLigne;
    caseDepart.colonne = 0 ;
    char pieceTrouve, lettreColonne, videBuffer = 'z';
    ECHEC = 1; 

    while(ECHEC == 1 && partietermine == 0)
    {
        printf("Ou se trouve la piece que vous voulez deplacer? (ex : B2) : ");
        scanf("%s", choix);
        videBuffer();
        
        lettreColonne = toupper(choix[0]);
        numeroLigne = choix[1] - 48;
        
        /* Cas ou on choisit une option du menu */
        if(choix[0] >= '0' && choix[0] <= '3')
        {
            switch(choix[0])
            {
                case '0':
                    printf("Au revoir, et a bientot !\n\n\n");
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
        /* Cas ou la saisie ressemble aux coordonees d'une case */
        else if(lettreColonne >= 'A' && lettreColonne <= 'H' && numeroLigne >= 0 && numeroLigne <= 9)
        {
                ECHEC = 0;
                caseDepart.ligne = numeroLigne;
                caseDepart.ligne --;
                caseDepart.charColonne = lettreColonne;
                /* On verifie que cette case existe bien sur l'echiquier */
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
        
        if(changePiece == 0 && roque == 0)
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

/*--------------------------------------------- Validation de la case depart ---------------------------------------------*/
void verifCaseChoisie()
{
    char alphabet[10]= "ABCDEFGH"; 
    char pieceTrouve;
    int i= 0, j = 0, flagEspace = 0;

    /*-------pour trouver l'index de la LETTRE dans l'alphabet ----*/
    for(i ; i < 9 ; i++)
    {
      if(alphabet[i] == caseDepart.charColonne)
      {
          caseDepart.colonne = i;
      }
    }
    /*------- Pour vérifier si la case choisie existe sur l'échiquier ----*/
    if((caseDepart.colonne < 0) || (caseDepart.colonne > 7) || (caseDepart.ligne < 0) || (caseDepart.ligne > 7))
    {
        printf("Mauvaise saisie ! A1 est la première case, H8 est la dernière, Veuillez recommencer \n");
        ECHEC = 1;
    }
    else
    {
      pieceTrouve = t[caseDepart.ligne][caseDepart.colonne];
      
      if(pieceTrouve == 'P' || pieceTrouve == 'p')
      {
          {printf("La piece trouvée est : un Pion\n");}
      }
      else if(pieceTrouve == 'T' || pieceTrouve == 't')
      {
          {printf("La piece trouvée est : une Tour\n");}
      }
      else if(pieceTrouve == 'C' || pieceTrouve == 'c')
      {
          {printf("La piece trouvée est : un Cavalier\n");}
      }
      else if(pieceTrouve == 'F' || pieceTrouve == 'f')
      {
          {printf("La piece trouvée est : un Fou\n");}
      }
      else if(pieceTrouve == 'Q' || pieceTrouve == 'q')
      {
          {printf("La piece trouvée est : une Reine\n");}
      }
      else if(pieceTrouve == 'K' || pieceTrouve == 'k')
      {
          {printf("La piece trouvée est : un Roi\n");}
      }
    
      /*--------- Pour vérifier que le joueur a bien choisi une de ses pièces -----*/
       if(joueurActif == 1)
           {strcpy(piecesDuJoueurActif, "PTCFQK");}
       else
           {strcpy(piecesDuJoueurActif, "ptcfqk");}
           
      ECHEC = 1;
      for(j ; j < strlen(piecesDuJoueurActif) ; j++)
      {
          if(piecesDuJoueurActif[j] == pieceTrouve)
          {
            ECHEC = 0;
          }
          else if(pieceTrouve == ' ')
            {flagEspace = 1;}
      }
      if(ECHEC == 1)
      {
        if(flagEspace == 1)
            {printf("Vous avez choisi une case vide... Veuillez recommencer \n");}
        else
            {printf("Vous avez choisi une pièce de l'adversaire...Veuillez recommencer \n");}
      }
    }
}

/*--------------------------------------------- Validation de la case arrivee ---------------------------------------------*/ 
int verifDeplacementArrivee()
{
    char alphabet[10]= "ABCDEFGH", choix[20];
    int i = 0, numeroLigne;
    char lettreColonne, videBuffer = 'z';
    RoiBlancEnECHEC = 0;
    RoiNoireEnECHEC = 0;
    
    if(roque == 0 && changePiece == 0)
    {
        while(ECHEC == 1) 
        {

            printf("Ou voulez vous la deplacer? (ex : B2) : ");
            scanf("%s", choix);
            videBuffer();
            
            lettreColonne = toupper(choix[0]);
            numeroLigne = choix[1] - 48;
            
            if(choix[0] >= '0' && choix[0] <= '3')
            {
                switch(choix[0])
                {
                    case '0':
                        printf("Au revoir, et a bientot !\n");
                        partietermine = 1;
                        return partietermine;
                        break;
                    
                    case '1':
                        sauvegarde();
                        ECHEC = 1;
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

/*--------------------------------------------- Procédure deplacement Pion --------------------------------------------- */
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
                printf("\n\n               _____________________________________________________\n"); 
                printf("              *******  Votre Pion s'est transformé en Reine ! *******\n"); 
                printf("               -----------------------------------------------------\n");  
                
            }
            else if((joueurActif == 2) && (caseArrivee.ligne == 7))
            {
                t[caseArrivee.ligne][caseArrivee.colonne] = 'q';  
                printf("\n\n               _____________________________________________________\n"); 
                printf("              *******  Votre Pion s'est transformé en Reine ! *******\n"); 
                printf("               -----------------------------------------------------\n");  
                
            }
            else
            {
                t[caseArrivee.ligne][caseArrivee.colonne] = t[caseDepart.ligne][caseDepart.colonne]; 
            }
            t[caseDepart.ligne][caseDepart.colonne] = ' ';
        }           
}

/*--------------------------------------------- Procédure deplacement Cavalier ---------------------------------------------*/
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
/*--------------------------------------------- Deplacement Roi ---------------------------------------------*/
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

/*--------------------------------------------- Deplacement Reine/Fou/Tour ---------------------------------------------*/
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
        {verifEliminationPiece();}
    }

    else if((pieceChoisie == 'Q' || pieceChoisie == 'T') 
    && (caseDepart.ligne == caseArrivee.ligne || caseDepart.colonne == caseArrivee.colonne))
    {
        testRangeesColonnes();
        testSiEchec();
        if(ECHEC == 0)
        {verifEliminationPiece();}
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
        {roqueJ1++;}
        else if(joueurActif == 2 && pieceChoisie == 'T'
        &&((caseDepart.ligne == 0 && caseDepart.colonne == 7)
        ||(caseDepart.ligne == 0 && caseDepart.colonne == 0)))
        {roqueJ2++;}
        
        t[caseArrivee.ligne][caseArrivee.colonne] = t[caseDepart.ligne][caseDepart.colonne];         //je deplace la piece
        t[caseDepart.ligne][caseDepart.colonne] = ' ';
    }
}

/*--------------------------------------------- Procédure de gestion de l'elimination ---------------------------------------------*/ 
void verifEliminationPiece()
{
    
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
             printf("\n\n               _________________________________________________\n"); 
             printf("              *******  Vous avez pris une piece adverse ! *******\n"); 
             printf("               -------------------------------------------------\n");  
             ECHEC = 0;
        }
        else
        {ECHEC = 1;}
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
             printf("\n\n               _________________________________________________\n"); 
             printf("              *******  Vous avez pris une piece adverse ! *******\n"); 
             printf("               -------------------------------------------------\n");  
            ECHEC = 0;
        }
    }
}

/*--------------------------------------------- Test Diagonales ---------------------------------------------*/
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

/*--------------------------------------------- Test Rangées & Colonnes ---------------------------------------------*/
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

/*--------------------------------------------- Module de vérication de l'ECHEC au ROI ---------------------------------------------*/
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

/*--------------------------------------------- Affichage "ECHEC AU ROI BLANC" ---------------------------------------------*/
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
            printf("\n\n");
            printf("                _____________________________________________\n\n\n\n");
            printf("                                ECHEC ET MAT !\n\n");            
            printf("                ***        LE JOUEUR NOIR  GAGNE !        ***\n\n\n\n"); 
            printf("                ______________________________________________\n\n\n"); 
        }
        else
        {
            EchecBlanc = 1;
        }
    }
}

/*--------------------------------------------- Affichage "ECHEC AU ROI NOIR" ---------------------------------------------*/
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
            printf("\n\n");
            printf("                _____________________________________________\n\n\n\n");
            printf("                                ECHEC ET MAT !\n\n");            
            printf("                ***        LE JOUEUR BLANC GAGNE !        ***\n\n\n\n"); 
            printf("                ______________________________________________\n\n\n"); 
        }
        else
        {
            EchecNoir = 1;
        }
    }
}
/*--------------------------------------------- Affichage "PAT" ---------------------------------------------*/
void affichagePat()
{
   printf("\n\n");
   printf("                _____________________________________________\n\n\n\n");
   printf("                                     PAT !\n\n");            
   printf("                ***            Il y a EGALITE !           ***\n\n\n\n"); 
   printf("                ______________________________________________\n\n\n");  

}    
/*--------------------------------------------- Module de test devant pour tester l'ECHEC au roi ---------------------------------------------*/
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
        while((k < 8 ) && RoiBlancEnECHEC == 0 && RoiNoireEnECHEC == 0 && piecePercute == 0)
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
}
/*--------------------------------------------- Module de test derrière pour tester l'ECHEC au roi ---------------------------------------------*/
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

/*--------------------------------------------- Module de test a droite pour tester l'ECHEC au roi ---------------------------------------------*/
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

/*--------------------------------------------- Module de test a gauche pour tester l'ECHEC au roi ---------------------------------------------*/
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
/*--------------------------------------------- Module de test haut/gauche pour tester l'ECHEC au roi ---------------------------------------------*/
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

/*--------------------------------------------- Module de test haut/droite pour tester l'ECHEC au roi ---------------------------------------------*/
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

/*--------------------------------------------- Module de test bas/gauche pour tester l'ECHEC au roi ---------------------------------------------*/
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

/*--------------------------------------------- Module de test bas/droit pour tester l'ECHEC au roi ---------------------------------------------*/
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


/*--------------------------------------------- Module de vérication de l'ECHEC ET MAT au ROI ---------------------------------------------*/
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

/*--------------------------------------------- Verification possibilite deplacement ---------------------------------------------*/
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
/*--------------------------------------------- Verification possibilite deplacement Pion ---------------------------------------------*/
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

/*--------------------------------------------- Module de vérication du Pat ---------------------------------------------*/
void testSiPat()
{
    int ligneDepart, ligneArrivee, colonneDepart, colonneArrivee, echec = 1;
    char echiquierDeTest[8][8]={
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' '
    };
    int i, j, k, l, m, n, o, p;;

    for( i = 0 ; i <= 7 ; i++ )
    {
        for( j = 0 ; j <= 7 ; j++)
        {
            echiquierDeTest[i][j] = t[i][j];
        }
    }
    
    
    Pat = 1;//je met Pat à 1, le but est que le test le passe à 0 (on peut continuer à jouer dans ce cas là)
    
    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)//je parcours tout le tableau à la recherche des pieces
        {
            ligneDepart = i;
            colonneDepart = j;
            
            if((echiquierDeTest[i][j] == 'c' && joueurActif == 2) || (echiquierDeTest[i][j] == 'C' && joueurActif == 1) )
            {
                ligneArrivee = ligneDepart -2;
                colonneArrivee = colonneDepart -1;
                
                
                echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                
                echec = 1;

                ligneArrivee = ligneDepart -2;
                colonneArrivee = colonneDepart +1;
                
                echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;
                
                ligneArrivee = ligneDepart -1;
                colonneArrivee = colonneDepart -2;
                
                echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;


                ligneArrivee = ligneDepart -1;
                colonneArrivee = colonneDepart +2;
                
                echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;

            
                ligneArrivee = ligneDepart +2;
                colonneArrivee = colonneDepart -1;
                
                echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;


                ligneArrivee = ligneDepart +2;
                colonneArrivee = colonneDepart +1;
                
                echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;
                
                
                ligneArrivee = ligneDepart +1;
                colonneArrivee = colonneDepart -2;
                
                echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;
                    
                ligneArrivee = ligneDepart +1;
                colonneArrivee = colonneDepart +2;
                
                echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;

            }
            
            if(echiquierDeTest[i][j] == 'p' && joueurActif == 2)
            {
                if(i == 1 && t[ligneDepart+1][colonneDepart] == ' ' && t[ligneDepart +2][colonneDepart] == ' ') //avance de 2 cases pour le pion
                {
                    ligneArrivee= ligneDepart +2;
                    colonneArrivee = colonneDepart;
                    
                    echec = testSiEchecPat(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                    if(echec == 0)
                        Pat = 0;
                    echec = 1;
                }
                
                if(t[ligneDepart +1][colonneDepart] == ' ')
                {
                    ligneArrivee= ligneDepart +1;
                    colonneArrivee = colonneDepart;
                    
                    echec = testSiEchecPat(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                    if(echec == 0)
                        Pat = 0;
                    echec = 1;
                
                ligneArrivee= ligneDepart +1;
                colonneArrivee = colonneDepart +1;
                
                echec = runTestPatPion(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;
    
            
                ligneArrivee= ligneDepart +1;
                colonneArrivee = colonneDepart -1;
                
                echec = runTestPatPion(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;
                
                }

            }
            
            if(echiquierDeTest[i][j] == 'P' && joueurActif == 1)
            {
                if(i == 6 && t[5][j] == ' ' && t[4][j] == ' ') //avance de 2 cases pour le pion
                {
                    ligneArrivee= ligneDepart -2;
                    colonneArrivee = colonneDepart;
                    
                    
                    echec = testSiEchecPat(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                    if(echec == 0)
                        Pat = 0;
                    echec = 1;
  
                }
                
                if(t[ligneDepart -1][colonneDepart] == ' ')
                {
                    ligneArrivee= ligneDepart -1;
                    colonneArrivee = colonneDepart;
                    
                    echec = testSiEchecPat(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                    if(echec == 0)
                        Pat = 0;
                    echec = 1;
                }
                
                ligneArrivee= ligneDepart -1;
                colonneArrivee = colonneDepart +1;
                
                echec = runTestPatPion(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;
                
    
                ligneArrivee= ligneDepart -1;
                colonneArrivee = colonneDepart -1;
                
                echec = runTestPatPion(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;
                    
            }
            
            if((echiquierDeTest[i][j] == 'k' && joueurActif == 2 )|| (echiquierDeTest[i][j] == 'K' && joueurActif == 1))
            {
                ligneArrivee= ligneDepart -1;
                colonneArrivee = colonneDepart -1;
                
               echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;

                    
                ligneArrivee= ligneDepart -1;
                colonneArrivee = colonneDepart;
                
               echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;
                
                ligneArrivee= ligneDepart -1;
                colonneArrivee = colonneDepart +1;
                
               echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;
                
                ligneArrivee= ligneDepart;
                colonneArrivee = colonneDepart+1;
                
                echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;
                
                ligneArrivee= ligneDepart +1;
                colonneArrivee = colonneDepart +1;
                
                echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;
                
                ligneArrivee= ligneDepart +1;
                colonneArrivee = colonneDepart;
                
                echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;
                
                ligneArrivee= ligneDepart +1;
                colonneArrivee = colonneDepart -1;

                echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;
                
                ligneArrivee= ligneDepart;
                colonneArrivee = colonneDepart -1;

                echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                if(echec == 0)
                    Pat = 0;
                echec = 1;

            }
            
            
           if(((echiquierDeTest[i][j] == 't' || echiquierDeTest[i][j] == 'q') && joueurActif == 2) || ((echiquierDeTest[i][j] == 'T' || echiquierDeTest[i][j] == 'Q') && joueurActif == 1))
           {
                percut = 0;
                /* je check en haut */
                for(k= i ; k >= 0 ; k--)
                {
                    if(percut == 0 && (k != i))
                    {
                        ligneArrivee= k;
                        colonneArrivee = colonneDepart;
                        
                        echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                       if(echec == 0)
                            Pat = 0;
                         echec = 1;
                        
                    }
                }
                percut = 0; //je remet percut à 0 pour les autres tests
                
                /* je check en bas */
                for(l= i ; l < 8 ; l++)
                {
                    if(percut == 0 && (l != i))
                    {
                        ligneArrivee= l;
                        colonneArrivee = colonneDepart;
                        
                        echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                        if(echec == 0)
                              Pat = 0;
                        echec = 1;
                    }
                }
                percut = 0;
                
                /* je check a droite */
                for(m= j ; m < 8 ; m++)
                {
                    if(percut == 0 && (m != j))
                    {
                        ligneArrivee= ligneDepart;
                        colonneArrivee = m;
                        
                        echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                        if(echec == 0)
                            Pat = 0;
                        echec = 1;
                        
                    }
                }
                percut = 0;
                
                /* je check a gauche */
                for(n= j ; n >= 0 ; n--)
                {
                    if(percut == 0 && (n != j))
                    {
                        ligneArrivee= ligneDepart;
                        colonneArrivee = n;
                        
                        echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                        if(echec == 0)
                            Pat = 0;
                        echec = 1;

                    }  
                }
                percut = 0;
                
                 
            }
            
            if(((echiquierDeTest[i][j] == 'f' || echiquierDeTest[i][j] == 'q') && joueurActif == 2) || ((echiquierDeTest[i][j] == 'F' || echiquierDeTest[i][j] == 'Q') && joueurActif == 1))
            {  
                percut = 0;
                
                /* je check HG */
                for(o= i, p=j ; o >= 0, p >= 0 ; o-- , p--)
                {
                    if(percut == 0 && (o != i && p != j))
                    {
                        ligneArrivee= o;
                        colonneArrivee = p;
                        
                        echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                        if(echec == 0)
                            Pat = 0;
                        echec = 1;
                    }
                }
                percut = 0; //je remet percut à 0 pour les autres tests
                
                /* je check HD */
                for(o= i, p=j ; o >= 0, p < 8 ; o-- , p++)
                {
                    if(percut == 0 && (o != i && p != j))
                    {
                        ligneArrivee= o;
                        colonneArrivee = p;
                        
                        echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                        if(echec == 0)
                            Pat = 0;
                        echec = 1;
                    }
                }
                percut = 0;
                
                /* je check BD */
                for(o= i, p=j ; o < 8, p < 8 ; o++ , p++)
                {
                    if(percut == 0 && (o != i && p != j))
                    {
                        ligneArrivee= o;
                        colonneArrivee = p;
                        
                        echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                        if(echec == 0)
                            Pat = 0;
                        echec = 1;

                    }
                }
                percut = 0;
                
                /* je check BG */
                for(o= i, p=j ; o < 8, p >= 0 ; o++ , p--)
                {
                    if(percut == 0 && (o != i && p != j))
                    {
                        ligneArrivee= o;
                        colonneArrivee = p;
                        
                        echec = runTestPatElimination(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest);
                        if(echec == 0)
                            Pat = 0;
                        echec = 1;
                    }
                }
                percut = 0;

            }
            
        }
    }
    
}
    
    
//----------------------- pour gestion de l'élimination fictive dans le testSiPat()----------------------------//
int runTestPatElimination(int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee, char echiquierDeTest[8][8])
{
    //printf("je suis dans runTestEchecMatElimination\n");
    //printf("ligneDepart : %d , colonneDepart : %d , ligneArrivee : %d , colonneArrivee : %d\n", ligneDepart, colonneDepart, ligneArrivee, colonneArrivee);
    char valeurCaseMange = ' ', valeurEchec = 0;
   
    if(joueurActif == 2)
    {
        if(echiquierDeTest[ligneArrivee][colonneArrivee] != 't' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'f' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'c' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'k' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'q' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'p' )
        {
            /* sauvegarde de la piece visé en cas d'élimination*/
          valeurCaseMange = echiquierDeTest[ligneArrivee][colonneArrivee];
          valeurEchec = testSiEchecPat(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest); //il va tester si il peux faire ce coup, et test l'echec à chaque fois 
           /* on replace la piece visé car si il y a élimination il la effacé*/
          echiquierDeTest[ligneArrivee][colonneArrivee] = valeurCaseMange;
          //printf("valeurEchec : %d si ligneArrivee : %d , colonneArrivee : %d\n", valeurEchec, ligneArrivee, colonneArrivee);
          

        }
        if(echiquierDeTest[ligneArrivee][colonneArrivee] == 't' ||
           echiquierDeTest[ligneArrivee][colonneArrivee] == 'f' ||
           echiquierDeTest[ligneArrivee][colonneArrivee] == 'c' ||
           echiquierDeTest[ligneArrivee][colonneArrivee] == 'k' ||
           echiquierDeTest[ligneArrivee][colonneArrivee] == 'q' ||
           echiquierDeTest[ligneArrivee][colonneArrivee] == 'p' )
        {
            percut = 1;
        }
    }
    else if(joueurActif == 1)
    {
        if(echiquierDeTest[ligneArrivee][colonneArrivee] != 'T' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'F' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'C' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'K' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'Q' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'P' )
        {
          valeurCaseMange = echiquierDeTest[ligneArrivee][colonneArrivee];
          valeurEchec = testSiEchecPat(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest); //il va tester si il peux faire ce coup, et test l'echec à chaque fois 
           /* on replace la piece visé car si il y a élimination il la effacé*/
          echiquierDeTest[ligneArrivee][colonneArrivee] = valeurCaseMange;
         
        }
        if(echiquierDeTest[ligneArrivee][colonneArrivee] == 'T' ||
           echiquierDeTest[ligneArrivee][colonneArrivee] == 'F' ||
           echiquierDeTest[ligneArrivee][colonneArrivee] == 'C' ||
           echiquierDeTest[ligneArrivee][colonneArrivee] == 'K' ||
           echiquierDeTest[ligneArrivee][colonneArrivee] == 'Q' ||
           echiquierDeTest[ligneArrivee][colonneArrivee] == 'P' )
        {
            percut = 1;
        }
    }
    
    return valeurEchec;
}

int runTestPatPion(int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee, char echiquierDeTest[8][8])
{
    char valeurCaseMange, valeurEchec = 0;
    if(joueurActif == 2)
    {
        if(echiquierDeTest[ligneArrivee][colonneArrivee] != 't' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'f' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'c' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'k' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'q' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'p' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != ' ')
        {
          valeurCaseMange = echiquierDeTest[ligneArrivee][colonneArrivee];
          valeurEchec = testSiEchecPat(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest); //il va tester si il peux faire ce coup, et test l'echec à chaque fois 
           /* on replace la piece visé car si il y a élimination il la effacé*/
          echiquierDeTest[ligneArrivee][colonneArrivee] = valeurCaseMange;
        }  
    }
    else if(joueurActif == 1)
    {
        if(echiquierDeTest[ligneArrivee][colonneArrivee] != 'T' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'F' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'C' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'K' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'Q' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != 'P' &&
           echiquierDeTest[ligneArrivee][colonneArrivee] != ' ')
        {
          valeurCaseMange = echiquierDeTest[ligneArrivee][colonneArrivee];
          valeurEchec = testSiEchecPat(ligneDepart, colonneDepart, ligneArrivee, colonneArrivee, echiquierDeTest); //il va tester si il peux faire ce coup, et test l'echec à chaque fois 
           /* on replace la piece visé car si il y a élimination il la effacé*/
          echiquierDeTest[ligneArrivee][colonneArrivee] = valeurCaseMange;
        }  
    }
    return valeurEchec;
}
/*--------------------------------------------- Module de vérication de l'ECHEC au ROI pour le PAT---------------------------------------------*/
int testSiEchecPat(int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee, char echiquierDeTest[8][8])
{
    struct infoCase sauvegardeCaseDepartEchec;
    struct infoCase sauvegardeCaseArriveeEchec;
    
    sauvegardeCaseDepartEchec.ligne = ligneDepart;
    sauvegardeCaseDepartEchec.colonne = colonneDepart;
    
    sauvegardeCaseArriveeEchec.ligne = ligneArrivee;
    sauvegardeCaseArriveeEchec.colonne = colonneArrivee;
    
    char sauvegardePieceDepart = echiquierDeTest[ligneDepart][colonneDepart];
    char sauvegardePieceArrivee = echiquierDeTest[ligneArrivee][colonneArrivee];

    int valeurEchec = 0;
    int i, j;
    
    /* je deplace la piece pour tester si echec*/
    echiquierDeTest[ligneArrivee][colonneArrivee] = sauvegardePieceDepart;
    echiquierDeTest[ligneDepart][colonneDepart] = ' ';
    /* je parcours le tableau pour tester chaque piece*/
    for(i = 0 ; i < 8 ; i++)
    {
        //printf("---------on test la ligne : %d\n",i);
        for(j = 0 ; j < 8 ; j++)
        {
            if(echiquierDeTest[i][j] == 't' || echiquierDeTest[i][j] == 'T')
            {
                if(testDevantPat(i, j, echiquierDeTest)  == 1 ||
                   testArrierePat(i, j, echiquierDeTest) == 1 ||
                   testDroitePat(i, j, echiquierDeTest)  == 1 ||
                   testGauchePat(i, j, echiquierDeTest)  == 1)
                   {
                       valeurEchec = 1;
                   }
            }
            else if(echiquierDeTest[i][j] == 'p')
            { 
                if((echiquierDeTest[i + 1][j - 1] == 'K') ||
                   (echiquierDeTest[i + 1][j + 1] == 'K'))
                {
                    valeurEchec = 1; //si il est echec
                }

            }
            else if(echiquierDeTest[i][j] == 'P')
            {

                if((echiquierDeTest[i - 1][j - 1] == 'k') ||
                   (echiquierDeTest[i - 1][j + 1] == 'k'))
                {
                    valeurEchec = 1; //si il est echec
                }

            }
            else if(echiquierDeTest[i][j] == 'c')
            {
                if(((i- 2 < 8 && i- 2 >=0) && (j- 1 < 8 && j- 1 >= 0 ) && (echiquierDeTest[i - 2][j - 1] == 'K')) ||
                   ((i- 2 < 8 && i- 2 >=0) && (j+ 1 < 8 && j+ 1 >= 0 ) && (echiquierDeTest[i - 2][j + 1] == 'K')) ||
                   ((i- 1 < 8 && i- 1 >=0) && (j- 2 < 8 && j- 2 >= 0 ) && (echiquierDeTest[i - 1][j - 2] == 'K')) ||
                   ((i- 1 < 8 && i- 1 >=0) && (j+ 2 < 8 && j+ 2 >= 0 ) && (echiquierDeTest[i - 1][j + 2] == 'K')) ||
                   ((i+ 2 < 8 && i+ 2 >=0) && (j- 1 < 8 && j- 1 >= 0 ) && (echiquierDeTest[i + 2][j - 1] == 'K')) ||
                   ((i+ 2 < 8 && i+ 2 >=0) && (j+ 1 < 8 && j+ 1 >= 0 ) && (echiquierDeTest[i + 2][j + 1] == 'K')) ||
                   ((i+ 1 < 8 && i+ 1 >=0) && (j- 2 < 8 && j- 2 >= 0 ) && (echiquierDeTest[i + 1][j - 2] == 'K')) ||
                   ((i+ 1 < 8 && i+ 1 >=0) && (j+ 2 < 8 && j+ 2 >= 0 ) && (echiquierDeTest[i + 1][j + 2] == 'K')))
                {
                    //if(joueurActif != 1 && flagTestSiEchecEtMat != 1) --------> pour corrigé le prob echec et mat du c.. mais provoque d'autre soucis (on peut plus mettre en echec)
                        valeurEchec = 1; //si il est echec
                     
                }

            }
            else if(echiquierDeTest[i][j] == 'C')
            {
                if(((i- 2 < 8 && i- 2 >=0) && (j- 1 < 8 && j- 1 >= 0 ) && (echiquierDeTest[i - 2][j - 1] == 'k')) ||
                   ((i- 2 < 8 && i- 2 >=0) && (j+ 1 < 8 && j+ 1 >= 0 ) && (echiquierDeTest[i - 2][j + 1] == 'k')) ||
                   ((i- 1 < 8 && i- 1 >=0) && (j- 2 < 8 && j- 2 >= 0 ) && (echiquierDeTest[i - 1][j - 2] == 'k')) ||
                   ((i- 1 < 8 && i- 1 >=0) && (j+ 2 < 8 && j+ 2 >= 0 ) && (echiquierDeTest[i - 1][j + 2] == 'k')) ||
                   ((i+ 2 < 8 && i+ 2 >=0) && (j- 1 < 8 && j- 1 >= 0 ) && (echiquierDeTest[i + 2][j - 1] == 'k')) ||
                   ((i+ 2 < 8 && i+ 2 >=0) && (j+ 1 < 8 && j+ 1 >= 0 ) && (echiquierDeTest[i + 2][j + 1] == 'k')) ||
                   ((i+ 1 < 8 && i+ 1 >=0) && (j- 2 < 8 && j- 2 >= 0 ) && (echiquierDeTest[i + 1][j - 2] == 'k')) ||
                   ((i+ 1 < 8 && i+ 1 >=0) && (j+ 2 < 8 && j+ 2 >= 0 ) && (echiquierDeTest[i + 1][j + 2] == 'k')))
                {
                    //if(joueurActif != 2 && flagTestSiEchecEtMat != 1)
                        valeurEchec = 1; //si il est echec
                }    

            }
            else if(echiquierDeTest[i][j] == 'f' || echiquierDeTest[i][j] == 'F')
            {
                if(testDiagoHGPat(i,j, echiquierDeTest) == 1 || 
                   testDiagoHDPat(i,j, echiquierDeTest) == 1 ||
                   testDiagoBGPat(i,j, echiquierDeTest) == 1 ||
                   testDiagoBDPat(i,j, echiquierDeTest) == 1 )
                   {
                       valeurEchec = 1;
                   }
            }
            else if(echiquierDeTest[i][j] == 'q' || echiquierDeTest[i][j] == 'Q')
            {
                if(testDevantPat(i, j, echiquierDeTest)  == 1 ||
                   testArrierePat(i, j, echiquierDeTest) == 1 ||
                   testDroitePat(i, j, echiquierDeTest)  == 1 ||
                   testGauchePat(i, j, echiquierDeTest)  == 1 ||
                   testDiagoHGPat(i,j, echiquierDeTest)  == 1 ||
                   testDiagoHDPat(i,j, echiquierDeTest)  == 1 ||
                   testDiagoBGPat(i,j, echiquierDeTest)  == 1 ||
                   testDiagoBDPat(i,j, echiquierDeTest)  == 1)
                   {
                       valeurEchec = 1;
                   }
            }
            
        } 
    }
    /* je remets les pieces comme avant*/
    echiquierDeTest[sauvegardeCaseDepartEchec.ligne][sauvegardeCaseDepartEchec.colonne] = sauvegardePieceDepart;
    echiquierDeTest[sauvegardeCaseArriveeEchec.ligne][sauvegardeCaseArriveeEchec.colonne] = sauvegardePieceArrivee;
    
    return valeurEchec;
        
}



/*--------------------------------------------- Module de test devant pour tester l'ECHEC au roi pour le PAT ---------------------------------------------*/
int testDevantPat(int i, int j, char echiquierDeTest[8][8])
{
    //printf("----je viens d'entrer dans testDevant() \n");
    int valeurEchec = 0;
    int k = 0;
    int piecePercute = 0;
    piecePercute = 0;
    k = i + 1;
    //printf("J'ai trouver une tour noir !\n");         //      for(int k = 0 ; k < (8 - i) ; k++)
    if(echiquierDeTest[i][j] == 't'|| echiquierDeTest[i][j] == 'q')
    {    
        while((k < 8) && valeurEchec == 0 && piecePercute == 0)
        {
           // printf("---- dans le while avec K : %d et J : %d\n",k,j);
            //printf("----contenu : %c\n",t[k][j]);
            if(echiquierDeTest[k][j] == 'K')
            {
                valeurEchec = 1; //si echec
            }
            else if(echiquierDeTest[k][j] != ' ')
            {
                piecePercute = 1;
            }

            k++;
        }
    }
    else if(echiquierDeTest[i][j] == 'T'|| echiquierDeTest[i][j] == 'Q')
    {
            if(echiquierDeTest[k][j] == 'k')
            {
                valeurEchec = 1; //si echec
            }
            else if(echiquierDeTest[k][j] != ' ')
            {
                piecePercute = 1;
            }
            k++;
    }
    
    return valeurEchec;
}
/*--------------------------------------------- Module de test derrière pour tester l'ECHEC au roi ---------------------------------------------*/
int testArrierePat(int i, int j, char echiquierDeTest[8][8])
{
    //printf("----je viens d'entrer dans testArriere() \n");
    int k = 0;
    int piecePercute = 0;
    piecePercute = 0;
    int valeurEchec = 0;
    k = i - 1;
    if(echiquierDeTest[i][j] == 't'|| echiquierDeTest[i][j] == 'q')
    { 
        while((k >= 0 ) && valeurEchec == 0 && piecePercute == 0)
        {
            if(echiquierDeTest[k][j] == 'K')
            {
                valeurEchec = 1;//si echec
            }
            else if(echiquierDeTest[k][j] != ' ')
            {
                piecePercute = 1;
            }
            else
            {return 0;}
            k--;
        }
    }
    else if(echiquierDeTest[i][j] == 'T'|| echiquierDeTest[i][j] == 'Q')
    {
        while((k >= 0 ) && valeurEchec == 0 && piecePercute == 0)
        {
            if(echiquierDeTest[k][j] == 'k')
            {
                valeurEchec = 1;
            }
            else if(echiquierDeTest[k][j] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            k--;
        }
    }
    return valeurEchec;
}

/*--------------------------------------------- Module de test a droite pour tester l'ECHEC au roi ---------------------------------------------*/
int testDroitePat(int i, int j, char echiquierDeTest[8][8])
{
    //printf("----je viens d'entrer dans testDroite() \n");    
    int k = 0;
    int piecePercute = 0;
    piecePercute = 0;
    k = j + 1;
    int valeurEchec = 0;
    if(echiquierDeTest[i][j] == 't'|| echiquierDeTest[i][j] == 'q')
    { 
        while((k < 8 ) && valeurEchec == 0 && piecePercute == 0)
        {
            if(echiquierDeTest[i][k] == 'K')
            {
                valeurEchec = 1;//si echec
            }
            else if(echiquierDeTest[i][j] != ' ')
            {
                piecePercute = 1;
            }
            else
            {return 0;}
            k++;
        }
    }
    else if(echiquierDeTest[i][j] == 'T'|| echiquierDeTest[i][j] == 'Q')
    {
        while((k < 8 ) && valeurEchec == 0 && piecePercute == 0)
        {
            if(echiquierDeTest[i][k] == 'k')
            {
                valeurEchec = 1; //si echec
            }
            else if(echiquierDeTest[i][k] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            k++;
        }
    }
    return valeurEchec;
}

/*--------------------------------------------- Module de test a gauche pour tester l'ECHEC au roi ---------------------------------------------*/
int testGauchePat(int i, int j, char echiquierDeTest[8][8])
{
    //printf("----je viens d'entrer dans testGauche() \n");    
    int k = 0;
    int piecePercute = 0;
    piecePercute = 0;
    k = j - 1 ;
    int valeurEchec = 0;
    if(echiquierDeTest[i][j] == 't'|| echiquierDeTest[i][j] == 'q')
    { 
        while((k >= 0 ) && valeurEchec == 0 && piecePercute == 0)
        {
            if(echiquierDeTest[i][k] == 'K')
            {
                valeurEchec = 1;
            }
            else if(echiquierDeTest[i][k] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            k--;
        }
    }
    else if(echiquierDeTest[i][j] == 'T'|| echiquierDeTest[i][j] == 'Q')
    {
        while((k >= 0 ) && valeurEchec == 0 && piecePercute == 0)
        {
            if(echiquierDeTest[i][k] == 'k')
            {
                valeurEchec = 1;
            }
            else if(echiquierDeTest[i][k] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            k--;
        }
    }
    return valeurEchec;
}
/*--------------------------------------------- Module de test haut/gauche pour tester l'ECHEC au roi ---------------------------------------------*/
int testDiagoHGPat(int i, int j, char echiquierDeTest[8][8])
{
    //printf("----je viens d'entrer dans testDiagoHG() \n");    
    int l = 0, c = 0;
    int piecePercute = 0;
    int valeurEchec = 0;
    piecePercute = 0;
    l = i - 1;
    c = j - 1;
    
    if(echiquierDeTest[i][j] == 'f'|| echiquierDeTest[i][j] == 'q')
    {    
        while(l >= 0 && c >=0 && valeurEchec == 0 && piecePercute == 0 )
        {
            if(echiquierDeTest[l][c] == 'K')
            {
                valeurEchec = 1; 
            }
            else if(echiquierDeTest[l][c] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            l--;
            c--;
        }
    }
    else if(echiquierDeTest[i][j] == 'F'|| echiquierDeTest[i][j] == 'Q')
    {
        while(l >= 0 && c >=0 && valeurEchec == 0 &&  piecePercute == 0 )
        {
            if(echiquierDeTest[l][c] == 'k')
            {
                valeurEchec = 1; 
            }
            else if(echiquierDeTest[l][c] != ' ')
            {
                piecePercute = 1;
            }
            else
            {  }
            l--;
            c--;
        }
    }
    return valeurEchec;
}

/*--------------------------------------------- Module de test haut/droite pour tester l'ECHEC au roi ---------------------------------------------*/
int testDiagoHDPat(int i, int j, char echiquierDeTest[8][8])
{
    //printf("----je viens d'entrer dans testDiagoHD() \n");        
    int l = 0, c = 0;
    int valeurEchec = 0;
    int piecePercute = 0;
    piecePercute = 0;
    l = i - 1;
    c = j + 1;
    
    if(echiquierDeTest[i][j] == 'f' || echiquierDeTest[i][j] == 'q')
    {    
        while(l >= 0 && c < 8 && valeurEchec == 0 && piecePercute == 0 )
        {
            if(echiquierDeTest[l][c] == 'K')
            {
                valeurEchec = 1; 
            }
            else if(echiquierDeTest[l][c] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            l--;
            c++;
        }
    }
    else if(echiquierDeTest[i][j] == 'F'|| echiquierDeTest[i][j] == 'Q')
    {
        while(l >= 0 && c < 8 && valeurEchec == 0 && piecePercute == 0 )
        {
            if(echiquierDeTest[l][c] == 'k')
            {
                valeurEchec = 1; 
            }
            else if(echiquierDeTest[l][c] != ' ')
            {
                piecePercute = 1;
            }
            else
            { }
            l--;
            c++;
        }
    }
    return valeurEchec;
}

/*--------------------------------------------- Module de test bas/gauche pour tester l'ECHEC au roi ---------------------------------------------*/
int testDiagoBGPat(int i, int j, char echiquierDeTest[8][8])
{
    //printf("----je viens d'entrer dans testDiagoBG() \n");        
    int l = 0, c = 0;
    int valeurEchec = 0;
    int piecePercute = 0;
    piecePercute = 0;
    l = i + 1;
    c = j - 1;
    
    if(echiquierDeTest[i][j] == 'f' || echiquierDeTest[i][j] == 'q')
    { 
        while(l < 8 && c >= 0 && valeurEchec == 0 && piecePercute == 0 )
        {
            if(echiquierDeTest[l][c] == 'K')
            {
                valeurEchec = 1; 
            }
            else if(echiquierDeTest[l][c] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            l++;
            c--;
        }
    }
    else if(echiquierDeTest[i][j] == 'F'|| echiquierDeTest[i][j] == 'Q')
    {
        while(l < 8 && c >= 0 && valeurEchec == 0 && piecePercute == 0 )
        {
            if(echiquierDeTest[l][c] == 'k')
            {
                valeurEchec = 1; 
            }
            else if(echiquierDeTest[l][c] != ' ')
            {
                piecePercute = 1;
            }
            else
            { }
            l++;
            c--;
        }
    }
    return valeurEchec;
}

/*--------------------------------------------- Module de test bas/droit pour tester l'ECHEC au roi ---------------------------------------------*/
int testDiagoBDPat(int i, int j, char echiquierDeTest[8][8])
{
    
      //printf("----je viens d'entrer dans testDiagoBD() \n");    
    int l = 0, c = 0;
    int valeurEchec = 0;
    int piecePercute = 0;
    piecePercute = 0;
    l = i + 1;
    c = j + 1;
    
    if(echiquierDeTest[i][j] == 'f' || echiquierDeTest[i][j] == 'q')
    {
        while(l < 8 && c < 8 && valeurEchec == 0 && piecePercute == 0 )
        {
            if(echiquierDeTest[l][c] == 'K')
            {
                valeurEchec = 1; 
            }
            else if(echiquierDeTest[l][c] != ' ')
            {
                piecePercute = 1;
            }
            else
            {}
            l++;
            c++;
        }
    }    
    else if(echiquierDeTest[i][j] == 'F'|| echiquierDeTest[i][j] == 'Q')
    {
        while(l < 8 && c < 8 && valeurEchec == 0 && piecePercute == 0 )
        {
            if(echiquierDeTest[l][c] == 'k')
            {
                valeurEchec = 1; 
            }
            else if(echiquierDeTest[l][c] != ' ')
            {
                piecePercute = 1;
            }
            else
            { }
            l++;
            c++;
        }
    }
    return valeurEchec;
}



/*--------------------------------------------- Faire un roque ---------------------------------------------*/
void jeRoque()
{
    char choix[20] = "coucou";
    
    if(joueurActif == 1)
    {
        if(roqueJ1 < 2 && t[7][1] == ' ' && t[7][2] == ' ' && t[7][3] == ' ' 
        && t[7][5] == ' ' && t[7][6] == ' ' 
        && t[7][0] == 'T' && t[7][7] == 'T' && t[7][4] == 'K')
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
                videBuffer();
                
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
                        roque = 0;
                        break;
                        
                    default:
                        printf("Erreur de saisie, veuillez recommencer\n");
                        break;
                }
            }
                
        }
        
        else if(roqueJ1 < 2 && t[7][1] == ' ' && t[7][2] == ' ' && t[7][3] == ' ' 
        && t[7][0] == 'T' && t[7][4] == 'K' )
        {
            printf("---------------------------------\n");
            printf("--  1- Faire un grand roque    --\n");
            printf("--  2- Retour                  --\n");        
            printf("---------------------------------\n");

            while(choix[0] != '1' && choix[0] != '2')
            {
                printf("Choix : ");
                scanf("%s", choix);
                videBuffer();
                
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
                        roque = 0;
                        break;
                      
                    default:
                        printf("Erreur de saisie, veuillez recommencer\n");
                        break;
                }
            }
            
        }
        
        else if (roqueJ1 < 2 && t[7][5] == ' ' && t[7][6] == ' ' 
        && t[7][7] == 'T' && t[7][4] == 'K')
        {
            printf("---------------------------------\n");
            printf("--  1- Faire un petit roque    --\n");
            printf("--  2- Retour                  --\n");        
            printf("---------------------------------\n");
       
            while(choix[0] != '1' && choix[0] != '2')
            {
                printf("Choix : ");
                scanf("%s", choix);
                videBuffer();
                
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
                        roque = 0;
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
    
    else if(joueurActif == 2)
    {
        if(roqueJ2 < 2 && t[0][1] == ' ' && t[0][2] == ' ' && t[0][3] == ' ' 
        && t[0][5] == ' ' && t[0][6] == ' '
        && t[0][0] == 't' && t[0][7] == 't' && t[0][4] == 'k')
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
                videBuffer();
                
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
                        roque = 0;
                        break;
                    
                    default:
                        printf("Erreur de saisie, veuillez recommencer\n");
                        break;
                }
            }
                
        }
        
        else if(roqueJ2 < 2 && t[0][1] == ' ' && t[0][2] == ' ' && t[0][3] == ' '
        && t[0][0] == 't' && t[0][4] == 'k')
        {
            printf("---------------------------------\n");
            printf("--  1- Faire un grand roque    --\n");
            printf("--  2- Retour                  --\n");        
            printf("---------------------------------\n");
            
            while(choix[0] != '1' && choix[0] != '2')
            {
                printf("Choix : ");
                scanf("%s", choix);
                videBuffer();
                
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
                        roque = 0;
                        break;
                    
                    default:
                        printf("Erreur de saisie, veuillez recommencer\n");
                        break;
                }
            }
            
        }
        
        else if(roqueJ2 < 2 && t[0][5] == ' ' && t[0][6] == ' '
        && t[0][7] == 't' && t[0][4] == 'k')
        {
            printf("---------------------------------\n");
            printf("--  1- Faire un petit roque    --\n");
            printf("--  2- Retour                  --\n");        
            printf("---------------------------------\n");
        
            while(choix[0] != '1' && choix[0] != '2')
            {
                printf("Choix : ");
                scanf("%s", choix);
                videBuffer();
                
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
                        roque = 0;
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

/*--------------------------------------------- Sauvegarde ---------------------------------------------*/
void sauvegarde()
{	
    int i,j, joueurA;
    FILE *f1;
    char nomFichier[100], caseEnregistree;
    
    printf("Nom du fichier de sauvegarde : ");
    scanf("%s",nomFichier);
    videBuffer();
    
    f1 = fopen(nomFichier,"w");

    fprintf(f1,"%d%d%d", joueurActif, roqueJ1, roqueJ2); //pour le joueurActif
    
    
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

/*--------------------------------------------- Chargement ---------------------------------------------*/
int chargement()
{
    int i, j, retour;
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
            fscanf(f1, "%1d", &joueurActif);
            
            fseek(f1, 1, SEEK_SET);
            fscanf(f1, "%1d", &roqueJ1);
            
            fseek(f1, 2, SEEK_SET);
            fscanf(f1, "%1d", &roqueJ2);
            
            fseek(f1, 3, SEEK_SET);
            
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
        else if(NomFichier[0] == '0')
        {
            printf("Au revoir, et a bientot !\n");
            partietermine = 1;
            return partietermine;
        }
        else
        {
            printf("Impossible d'ouvrir le fichier %s\n", NomFichier);
            ECHEC = 1;
        }
    }
    
    fclose(f1);
}