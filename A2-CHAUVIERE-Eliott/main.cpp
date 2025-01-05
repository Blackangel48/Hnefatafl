#include <iostream>

using namespace std;

#include "functions.h"
#include "test.h"

int defaultColor = 0;
void itsGame(){
    color(defaultColor,0);
    displayHnefataflLogo();

    // choisir les noms des joueurs
    string player1Name;
    string player2Name;
    cout<<"Nom du joueur 1 : ";
    cin>>player1Name;
    cout<<"Nom du joueur 2 : ";
    cin>>player2Name;

    BoardSize aBoardSize;  //Définir la taille du plateau 11 ou 13
    while(!chooseSizeBoard(aBoardSize))
    {
        color(4,0);
        cout<<"Taille invalide"<<endl;
        color(defaultColor,0);
    }

    Board aBoard={nullptr,aBoardSize};  //créer et initialiser le plateau de jeu
    createBoard(aBoard);
    initializeBoard(aBoard);

    displayBoard(aBoard);  //afficher le plateau

    Position aPos = {0,0};  //initialiser les variables
    Position aPosEnd = {0,0};
    Game aGame;
    aGame.itsBoard = aBoard;
    aGame.itsPlayer1.itsName = player1Name;
    aGame.itsPlayer2.itsName = player2Name;
    Move aMove;
    do
    {
        do
        {
            cout<<"Au tour de '"<<aGame.itsCurrentPlayer->itsName<<"' qui joue : "<<aGame.itsCurrentPlayer->itsRole<<endl;

            while (!getPositionFromInput(aPos,aBoard))      //Position de la pièce à déplacer
            {
                color(4,0);
                cout<<"Position non-valide"<<endl;
                color(defaultColor,0);
            }
            while (!getPositionFromInput(aPosEnd,aBoard))   //Position d'arrivée de la pièce
            {
                color(4,0);
                cout<<"Position non-valide"<<endl;
                color(defaultColor,0);
            }
            aMove = {aPos,aPosEnd};
            if (!isValidMovement(aGame,aMove))              //vérification de la validité du mouvement
            {
                color(4,0);
                cout<<"Mouvement non-valide"<<endl;
                color(defaultColor,0);
            }

        }while (!isValidMovement(aGame,aMove));
        movePiece(aGame,aMove);     //déplacer la pièce
        capturePieces(aGame,aMove); //enlever les possibles pièces capturées
        displayBoard(aBoard);       //afficher le plateau
        switchCurrentPlayer(aGame); //change le joueur actif
    }while (!isGameFinished(aGame));
        cout<<endl<<"Le vainqueur est '"<<whoWon(aGame)->itsName<<"' qui était en "<<whoWon(aGame)->itsRole<<endl; //affiche le gagnant
}

void launchTest()
{
    //test_getPositionFromInput();
    //test_isEmptyCell();
    //test_isValidMovement();
    //test_movePiece();
    //test_capturePieces();
    //test_switchCurrentPlayer();
    //test_isSwordLeft();
    //test_isKingEscaped();
    //test_isKingCaptured();
}

int main()
{
    //launchTest();
    itsGame();
    return 0;
}
