#include <iostream>

using namespace std;

#include "functions.h"
#include "test.h"


void isGame(){
    color(0,0);
    displayHnefataflLogo();

    BoardSize aBoardSize;

    while(!chooseSizeBoard(aBoardSize))
        cout<<"Taille invalide"<<endl;

    Board aBoard={nullptr,aBoardSize};
    createBoard(aBoard);
    initializeBoard(aBoard);
    displayBoard(aBoard);
    Position aPos = {0,0};
    Position aPosEnd = {0,0};
    Game aGame;
    aGame.itsBoard = aBoard;
    Move aMove;
    for (int i = 0; i < 10; ++i) {
        do
        {

            while (!getPositionFromInput(aPos,aBoard))
            {
                cout<<"Position non-valide"<<endl;
            }
            while (!getPositionFromInput(aPosEnd,aBoard))
            {
                cout<<"Position non-valide"<<endl;
            }
            aMove = {aPos,aPosEnd};
            if (!isValidMovement(aGame,aMove))
            {
                color(4,0);
                cout<<"Mouvement non-valide"<<endl;
                color(0,0);
            }
        }while (!isValidMovement(aGame,aMove));
        movePiece(aGame,aMove);
        displayBoard(aBoard);
        // switchCurrentPlayer
    }
}

void launchTest()
{
    //test_getPositionFromInput();
    //test_isEmptyCell();
    //test_isValidMovement();
    //test_movePiece();
}

int main()
{
    //launchTest();
    isGame();
    return 0;
}
