#include <iostream>
#include <cctype>
#include <cstdlib>
#include <windows.h>
using namespace std;
#include "functions.h"

void color(int txtColor,int bgColor) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,bgColor*16+txtColor);
}

void clearConsole();

void displayHnefataflLogo()
{
    cout<<"   `▓▓▓▓▒  `▓▓▓▓▒`▓▓▓▒   `▓▓▓▒`▓▓▓▓▓▓▓▓▓▒ ▒▓▓▓▓▓▓▓▓▓▒  ▓▓▒  ▓▓▓▓▓▓▓▓▓▓▓▓▒  ▓▓▒     ▓▓▓▓▓▓▓▓▓▓▒ ▓▓▓▓▓▒'"<<endl;
    cout<<"     ▓▓▒     ▓▓▒   ▓▓▓▒    ▓▒   ▓▓▒    ▓▒   ▓▓▒   `▓▒ ;▓▓▒  ▓▒   ▓▓▒   ▓▒ ;▓▓▒       ▓▓▒    ▓▒  ▓▓▒"<<endl;
    cout<<"     ▓▓▒     ▓▓▒   ▓▒▓▓▒   ▓▒   ▓▓▒  ▓▒     ▓▓▒  ▓▒  ,▓▒▓▓▒      ▓▓▒     ,▓▒▓▓▒      ▓▓▒  ▓▒    ▓▓▒"<<endl;
    cout<<"     ▓▓▓▓▓▓▓▓▓▓▒   ▓▒ `▓▓▒ ▓▒   ▓▓▓▓▓▓▒     ▓▓▓▓▓▓▒ ,▓▒ `▓▓▒     ▓▓▒    ,▓▒ `▓▓▒     ▓▓▓▓▓▓▒    ▓▓▒"<<endl;
    cout<<"     ▓▓▒     ▓▓▒   ▓▒  `▓▓▒▓▒   ▓▓▒  ▓▒     ▓▓▒  ▓▒ ▓▓▓▓▓▓▓▓▒    ▓▓▒    ▓▓▓▓▓▓▓▓▒    ▓▓▒  ▓▒    ▓▓▒     ▓▒"<<endl;
    cout<<"     ▓▓▒     ▓▓▒   ▓▒    ▓▓▓▒   ▓▓▒     ▓▒  ▓▓▒    ▓▒     ▓▓▓▒   ▓▓▒   ▓▒     ▓▓▓▒   ▓▓▒        ▓▓▒    ▓▓▒"<<endl;
    cout<<"   .▓▓▓▓▒  .▓▓▓▓▒.▓▓▓▒    ▓▓▓▒ ▓▓▓▓▓▓▓▓▓▓▒.▓▓▓▓▒. ▓▓▓▒   .▓▓▓▓▒.▓▓▓▓▒.▓▓▓▒   .▓▓▓▓▒ ▓▓▓▓▒     .▓▓▓▓▓▓▓▓▓▓▒"<<endl;
    cout<<"   by echauvie at IUT LR"<<endl;
}

bool chooseSizeBoard(BoardSize& aBoardSize){
    int input;
    cout<<"Choisissez une taille de plateau (11 ou 13):"<<endl;
    if (cin>>input){
        switch (input) {
        case 13:
            aBoardSize=BIG;
            return true;
            break;
        case 11:
            aBoardSize=LITTLE;
            return true;
            break;
        default:
            return false;
            break;
        }
    }
    else {
        cin.clear();
        cin.ignore(255,'\n');
    }
}

bool createBoard(Board& aBoard){
    try {
        aBoard.itsCells = new Cell*[aBoard.itsSize];
        for (int i = 0; i < aBoard.itsSize; ++i) {
            aBoard.itsCells[i] = new Cell[aBoard.itsSize];
        }
        return true;
    } catch (const bad_alloc e) {
        deleteBoard(aBoard);
        return false;
    }

}

void deleteBoard(Board& aBoard){}

void displayBoard(const Board& aBoard)
{
    char letter='A';
    int number=1;
    char piece;
    cout<<endl<<"    ";
    for (int i = 0; i < aBoard.itsSize; ++i) { //première ligne avec nombres
        if (number<10) cout<<"  "<<number++<<" ";
        else cout<<" "<<number++<<" ";
    }cout<<" ";

    for (int i = 0; i < aBoard.itsSize; ++i) {

        cout<<endl<<"    +";
        for (int j = 0; j < aBoard.itsSize; ++j) { //lignes de delimitation
            cout<<"---+";
        }

        cout<<endl<<"  "<<letter++<<" "; //début avec lettre
        for (int j = 0; j < aBoard.itsSize; ++j) { //lignes avec valeurs
            cout<<"| ";
            switch (aBoard.itsCells[i][j].itsPieceType) {
            case NONE:
                switch (aBoard.itsCells[i][j].itsCellType) {
                case NORMAL:
                    piece=' ';
                    break;
                case FORTRESS:
                    color(8,0);
                    piece='#';
                    break;
                case CASTLE:
                    color(7,0);
                    piece='^';
                    break;
                default:
                    break;// ░▒▓  °±²
                }
                break;
            case SHIELD:
                color(9,0);
                piece='U';
                break;
            case SWORD:
                color(12,0);
                piece='X';
                break;
            case KING:
                color(4,0);
                piece='K';
                break;
            default:
                break;
            }
            cout<< piece <<" ";
            color(0,0);
        }cout<<"|";
    }

    cout<<endl<<"    +";
    for (int i = 0; i < aBoard.itsSize; ++i) { //dernière ligne
        cout<<"---+";
    }
    cout<<endl;
}

void initializeBoard(Board& aBoard){
    int mid=aBoard.itsSize/2; //5 ou 7
    int size=aBoard.itsSize-1; //10 ou 12
    for (int i = 0; i <= size; ++i) {     //initialize at empty everywhere
        for (int j = 0; j <= size; ++j) {
            aBoard.itsCells[i][j].itsCellType=NORMAL;
            aBoard.itsCells[i][j].itsPieceType=NONE;
        }
    }
    for (int i = mid-2; i < mid+3; ++i) {      //place the sword/attackant
        aBoard.itsCells[i][0].itsPieceType=SWORD;
        aBoard.itsCells[i][size].itsPieceType=SWORD;
        aBoard.itsCells[0][i].itsPieceType=SWORD;
        aBoard.itsCells[size][i].itsPieceType=SWORD;
    }
    aBoard.itsCells[mid][1].itsPieceType=SWORD;
    aBoard.itsCells[mid][size-1].itsPieceType=SWORD;
    aBoard.itsCells[1][mid].itsPieceType=SWORD;
    aBoard.itsCells[size-1][mid].itsPieceType=SWORD;

    aBoard.itsCells[0][0].itsCellType=FORTRESS; //place the cell type
    aBoard.itsCells[0][size].itsCellType=FORTRESS;
    aBoard.itsCells[size][0].itsCellType=FORTRESS;
    aBoard.itsCells[size][size].itsCellType=FORTRESS;
    aBoard.itsCells[mid][mid].itsCellType=CASTLE;

    aBoard.itsCells[mid][mid].itsPieceType=KING;  //place the shield/defensor
    if (aBoard.itsSize==11)
    {
        for (int i = 1; i < 3; ++i) {
            aBoard.itsCells[mid+i][mid].itsPieceType=SHIELD;
            aBoard.itsCells[mid-i][mid].itsPieceType=SHIELD;
            aBoard.itsCells[mid][mid+i].itsPieceType=SHIELD;
            aBoard.itsCells[mid][mid-i].itsPieceType=SHIELD;
        }
        aBoard.itsCells[mid+1][mid+1].itsPieceType=SHIELD;
        aBoard.itsCells[mid-1][mid+1].itsPieceType=SHIELD;
        aBoard.itsCells[mid+1][mid-1].itsPieceType=SHIELD;
        aBoard.itsCells[mid-1][mid-1].itsPieceType=SHIELD;
    }
    else //taille 13
    {
        for (int i = 1; i < 4; ++i) {
            aBoard.itsCells[mid+i][mid].itsPieceType=SHIELD;
            aBoard.itsCells[mid-i][mid].itsPieceType=SHIELD;
            aBoard.itsCells[mid][mid+i].itsPieceType=SHIELD;
            aBoard.itsCells[mid][mid-i].itsPieceType=SHIELD;
        }
    }
}

bool isValidPosition(const Position& aPos, const Board& aBoard){
    return ((aPos.itsCol>=0 && aPos.itsCol<aBoard.itsSize) && (aPos.itsRow>=0 && aPos.itsRow<aBoard.itsSize));
}

bool getPositionFromInput(Position& aPosition, const Board& aBoard){
    string input;
    int size=0;
    int col;
    int row;
    cout<<endl<<"Saisir une position :";
    cin>>input;

    while (input[size]!='\0')  //calculer la taille de la string
    {
        size++;
    }
    //cout<<"size:"<<size<<endl;

    if (size==2)
    {
        /*bool res=isdigit(input[1]);
        cout<<"Test '"<<input[1]<<"' is digit : "<<boolalpha<<res<<endl;*/
        if (isdigit(input[1]))
        {
            row=(input[1]-'1');
            //cout<<"row : "<<row<<endl;
        }
        else
            return false;
    }
    else if (size==3)
    {
        /*bool res=isdigit(input[1]);
        bool res2=isdigit(input[2]);
        cout<<"Test '"<<input[1]<<"' is digit : "<<boolalpha<<res<<endl;
        cout<<"Test '"<<input[2]<<"' is digit : "<<boolalpha<<res2<<endl;*/
        if (isdigit(input[1]) && isdigit(input[2]))
        {
            //row=(input[1]-'0')*10 + (input[2]-'1');
            //cout<<"row : "<<row<<endl;
        }
        else
            return false;
    }

    //cout<<"Test '"<<input[0]<<"' is char a->z or A->Z : "<<boolalpha<<(input[0] <= 'z' && input[0] >= 'a' || input[0] <= 'Z' && input[0] >= 'A')<<endl;
    if ((input[0] <= 'z' && input[0] >= 'a') || (input[0] <= 'Z' && input[0] >= 'A')) //Premier caractère parmis a->z ou A->Z
    {
        if (input[0] <= 'z' && input[0] >= 'a') //a->z
            col = (input[0]-'a');
        else if (input[0] <= 'Z' && input[0] >= 'A') //A->Z
            col = (input[0]-'A');
        //cout<<"col : "<<col<<endl;

        //cout<<"Test "<<col<<","<<row<<" is valid position : "<<boolalpha<<(isValidPosition({col,row},aBoard))<<endl;
        if (isValidPosition({row,col},aBoard))
        {
            //cout<<"Définition de position a : "<<"("<<col<<","<<row<<")"<<endl;
            aPosition={col,row};
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

bool isEmptyCell(const Board& aBoard, const Position& aPos){
    return (aBoard.itsCells[aPos.itsRow][aPos.itsCol].itsPieceType == NONE);
}

bool isValidMovement(const Game& aGame, const Move& aMove){
 //Whether the starting position contains a piece of the active player
 //(either a SWORD for the ATTACK player or a SHIELD/KING for the DEFENSE player).
    //cout<<"# Start (Row,Col) : ("<<aMove.itsStartPosition.itsRow<<','<<aMove.itsStartPosition.itsCol<<") Piece : "<<aGame.itsBoard.itsCells[aMove.itsStartPosition.itsRow][aMove.itsStartPosition.itsCol].itsPieceType<<endl;
    //cout<<"# End   (Row,Col) : ("<<aMove.itsEndPosition.itsRow<<','<<aMove.itsEndPosition.itsCol<<") Piece : "<<aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow][aMove.itsEndPosition.itsCol].itsPieceType<<endl;

    if (aGame.itsCurrentPlayer->itsRole == ATTACK) //attack player
    {
        if (!(aGame.itsBoard.itsCells[aMove.itsStartPosition.itsRow][aMove.itsStartPosition.itsCol].itsPieceType == SWORD))
        {
            //cout<<"# False : Pas de piece ou piece de l'adversaire : Piece : "<<aGame.itsBoard.itsCells[aMove.itsStartPosition.itsRow][aMove.itsStartPosition.itsCol].itsPieceType<<endl;
            return false;
        }
    }
    else //defense player
        if (!(aGame.itsBoard.itsCells[aMove.itsStartPosition.itsRow][aMove.itsStartPosition.itsCol].itsPieceType == SHIELD || aGame.itsBoard.itsCells[aMove.itsStartPosition.itsRow][aMove.itsStartPosition.itsCol].itsPieceType == KING))
        {
            //cout<<"# False : Pas de piece ou piece de l'adversaire : Piece : "<<aGame.itsBoard.itsCells[aMove.itsStartPosition.itsRow][aMove.itsStartPosition.itsCol].itsPieceType<<endl;
            return false;
        }

 //Whether the move is along the same row or column (horizontal or vertical movement).
    int dist;
    int dir;
    string angle;
    if (aMove.itsStartPosition.itsCol == aMove.itsEndPosition.itsCol && aMove.itsStartPosition.itsRow == aMove.itsEndPosition.itsRow)
        return false;
    else if (aMove.itsStartPosition.itsCol == aMove.itsEndPosition.itsCol)
    {
        // cout<<"# Dist : "<<(aMove.itsEndPosition.itsRow - aMove.itsStartPosition.itsRow)<<endl/*<<"|-> dist : "<<aMove.itsEndPosition.itsRow<<" - "<<aMove.itsStartPosition.itsRow<<endl*/;
        dist = aMove.itsEndPosition.itsRow - aMove.itsStartPosition.itsRow;
        dir = (dist>=0)?1:-1;
        angle = "col";
    }
    else if (aMove.itsStartPosition.itsRow == aMove.itsEndPosition.itsRow)
    {
        // cout<<"# Dist : "<<(aMove.itsEndPosition.itsCol - aMove.itsStartPosition.itsCol)<<endl/*<<"|-> dist : "<<aMove.itsEndPosition.itsCol<<" - "<<aMove.itsStartPosition.itsCol<<endl*/;
        dist = aMove.itsEndPosition.itsCol - aMove.itsStartPosition.itsCol;
        dir = (dist>=0)?1:-1;
        angle = "row";
    }
    else
        return false;
    // cout<<"# Angle : "<<angle<<endl;
    // cout<<"# Dist : "<<dist<<" , absolu : "<<abs(dist)<<endl;

 //Whether there are any obstacles (other pieces or fortresses) in the path of the move.     (aBoard.itsCells[aPos.itsCol][aPos.itsRow].itsPieceType == NONE);
    Position startPos = aMove.itsStartPosition;
    //cout<<"# If KING (Row,Col) : ("<<aMove.itsStartPosition.itsRow<<','<<aMove.itsStartPosition.itsCol<<')'<<" Piece : "<<aGame.itsBoard.itsCells[aMove.itsStartPosition.itsRow][aMove.itsStartPosition.itsCol].itsPieceType<<endl;
    if (aGame.itsBoard.itsCells[aMove.itsStartPosition.itsRow][aMove.itsStartPosition.itsCol].itsPieceType != KING) //Piece != KING
    {
        if (angle == "col")
        {
            for (int i = 1; i <= abs(dist); ++i)
            {
                //cout<<"# ("<<startPos.itsRow+(i*dir)<<','<<startPos.itsCol<<") Empty Cell : "<<boolalpha<<isEmptyCell(aGame.itsBoard,{ startPos.itsRow+(i*dir), startPos.itsCol })<<endl;
                if (isEmptyCell(aGame.itsBoard,{ startPos.itsRow+(i*dir), startPos.itsCol }) == false || (aGame.itsBoard.itsCells[startPos.itsRow+(i*dir)][startPos.itsCol].itsCellType != NORMAL))
                    return false;
            }
        }
        else if (angle == "row")
        {
            for (int i = 1; i <= abs(dist); ++i)
            {
                //cout<<"# ("<<startPos.itsRow<<','<<startPos.itsCol+(i*dir)<<") Empty Cell : "<<boolalpha<<isEmptyCell(aGame.itsBoard,{ startPos.itsRow, startPos.itsCol+(i*dir) })<<endl;
                if (!(isEmptyCell(aGame.itsBoard,{ startPos.itsRow, startPos.itsCol +(i*dir) }) && (aGame.itsBoard.itsCells[startPos.itsRow][startPos.itsCol+(i*dir)].itsCellType == NORMAL)))
                    return false;
            }
        }
    }
    else //Piece = KING
    {
        if (angle == "col")
        {
            for (int i = 1; i <= abs(dist); ++i)
            {
                //cout<<"("<<startPos.itsRow+(i*dir)<<','<<startPos.itsCol<<") Empty Cell : "<<boolalpha<<isEmptyCell(aGame.itsBoard,{ startPos.itsRow+(i*dir), startPos.itsCol })<<endl;
                if (!(isEmptyCell(aGame.itsBoard,{ startPos.itsRow+(i*dir), startPos.itsCol })))
                    return false;
            }
        }
        else if (angle == "row")
        {
            for (int i = 1; i <= abs(dist); ++i)
            {
                //cout<<"("<<startPos.itsRow<<','<<startPos.itsCol+(i*dir)<<") Empty Cell : "<<boolalpha<<isEmptyCell(aGame.itsBoard,{ startPos.itsRow, startPos.itsCol+(i*dir) })<<endl;
                if (!(isEmptyCell(aGame.itsBoard,{ startPos.itsRow, startPos.itsCol +(i*dir) })))
                    return false;
            }
        }
    }

    return true;

 //Additionally, the function ensures that fortresses are not crossed by the player,unless the player is the KING, in which case it is allowed.
}

void movePiece(Game& aGame, const Move& aMove)
{
    aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow][aMove.itsEndPosition.itsCol].itsPieceType = aGame.itsBoard.itsCells[aMove.itsStartPosition.itsRow][aMove.itsStartPosition.itsCol].itsPieceType;
    aGame.itsBoard.itsCells[aMove.itsStartPosition.itsRow][aMove.itsStartPosition.itsCol].itsPieceType = NONE;
}

void capturePieces(Game& aGame, const Move& aMove)   // PLACE THE KING EVERYWHERE AND DUPLICATE FOR THE DEFENSOR
{
    if (aGame.itsCurrentPlayer->itsRole == ATTACK)
    {
        /* RIGHT */
        if (isValidPosition({aMove.itsEndPosition.itsRow+1,aMove.itsEndPosition.itsCol},aGame.itsBoard) && isValidPosition({aMove.itsEndPosition.itsRow+2,aMove.itsEndPosition.itsCol},aGame.itsBoard))
        {
            if ( (aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow+1][aMove.itsEndPosition.itsCol].itsPieceType == SHIELD) && ( (aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow+2][aMove.itsEndPosition.itsCol].itsPieceType == SWORD || aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow+2][aMove.itsEndPosition.itsCol].itsPieceType == KING ) || (aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow+2][aMove.itsEndPosition.itsCol].itsCellType != NONE) ) )
            {
                //delete piece (end+1,end)
                aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow+1][aMove.itsEndPosition.itsCol].itsPieceType = NONE;
            }
        }
        /* LEFT */
        if (isValidPosition({aMove.itsEndPosition.itsRow-1,aMove.itsEndPosition.itsCol},aGame.itsBoard) && isValidPosition({aMove.itsEndPosition.itsRow-2,aMove.itsEndPosition.itsCol},aGame.itsBoard))
        {
            if ( (aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow-1][aMove.itsEndPosition.itsCol].itsPieceType == SHIELD) && ( (aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow-2][aMove.itsEndPosition.itsCol].itsPieceType == SWORD) || (aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow-2][aMove.itsEndPosition.itsCol].itsCellType != NONE) ) )
            {
                aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow-1][aMove.itsEndPosition.itsCol].itsPieceType = NONE;
            }
        }
        /* UP */
        if (isValidPosition({aMove.itsEndPosition.itsRow,aMove.itsEndPosition.itsCol-1},aGame.itsBoard) && isValidPosition({aMove.itsEndPosition.itsRow,aMove.itsEndPosition.itsCol-2},aGame.itsBoard))
        {
            if ( (aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow][aMove.itsEndPosition.itsCol-1].itsPieceType == SHIELD) && ( (aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow][aMove.itsEndPosition.itsCol-2].itsPieceType == SWORD) || (aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow][aMove.itsEndPosition.itsCol-2].itsCellType != NONE) ) )
            {
                aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow][aMove.itsEndPosition.itsCol-1].itsPieceType = NONE;
            }
        }
        /* DOWN */
        if (isValidPosition({aMove.itsEndPosition.itsRow,aMove.itsEndPosition.itsCol+1},aGame.itsBoard) && isValidPosition({aMove.itsEndPosition.itsRow,aMove.itsEndPosition.itsCol+2},aGame.itsBoard))
        {
            if ( (aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow][aMove.itsEndPosition.itsCol+1].itsPieceType == SHIELD) && ( (aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow][aMove.itsEndPosition.itsCol+2].itsPieceType == SWORD) || (aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow][aMove.itsEndPosition.itsCol+2].itsCellType != NONE) ) )
            {
                aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow][aMove.itsEndPosition.itsCol+1].itsPieceType = NONE;
            }
        }
    }

}

void switchCurrentPlayer(Game& aGame)
{
    cout<<"aGame.itsCurrentPlayer"<<endl;
    // if (aGame.itsCurrentPlayer)
}

bool isSwordLeft(const Board& aBoard){
    return true;
}

Position getKingPosition(const Board& aBoard){
    return {0,0};
}
bool isKingEscaped(const Board& aBoard){
    return true;
}
bool isKingCaptured(const Board& aBoard, Position aKingPos /*= {-1, -1}*/){
    return true;
}
bool isGameFinished(const Game& aGame){
    return true;
}
Player* whoWon(const Game& aGame){
    return nullptr;
}

