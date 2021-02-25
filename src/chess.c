#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bootcamp/chess.h"

#define lowerASCII 32

enum Type {
    NONE = 0,
    PAWN = 'p',
    KNIGHT = 'n',
    BISHOP = 'b',
    ROOK = 'r',
    QUEEN = 'q',
    KING = 'k',
};

enum Color {
    WHITE,
    BLACK
};

struct Piece{
    uint8_t type;
    uint8_t color;
};
static Piece board[64] = { {ROOK, BLACK}, {KNIGHT, BLACK}, {BISHOP, BLACK}, {QUEEN, BLACK}, {KING, BLACK}, {BISHOP, BLACK}, {KNIGHT, BLACK}, {ROOK, BLACK},
                    {PAWN, BLACK}, {PAWN, BLACK}, {PAWN, BLACK}, {PAWN, BLACK}, {PAWN, BLACK}, {PAWN, BLACK}, {PAWN, BLACK}, {PAWN, BLACK},
                    {NONE, 128}, {NONE, 128}, {NONE, 128}, {NONE, 128}, {NONE, 128}, {NONE, 128} , {NONE, 128}, {NONE, 128},
                    {NONE, 128}, {NONE, 128}, {NONE, 128}, {NONE, 128}, {NONE, 128}, {NONE, 128} , {NONE, 128}, {NONE, 128},
                    {NONE, 128}, {NONE, 128}, {NONE, 128}, {NONE, 128}, {NONE, 128}, {NONE, 128} , {NONE, 128}, {NONE, 128},
                    {NONE, 128}, {NONE, 128}, {NONE, 128}, {NONE, 128}, {NONE, 128}, {NONE, 128} , {NONE, 128}, {NONE, 128},
                    {PAWN, WHITE}, {PAWN, WHITE}, {PAWN, WHITE}, {PAWN, WHITE}, {PAWN, WHITE}, {PAWN, WHITE}, {PAWN, WHITE}, {PAWN, WHITE},
                    {ROOK, WHITE}, {KNIGHT, WHITE}, {BISHOP, WHITE}, {QUEEN, WHITE}, {KING, WHITE}, {BISHOP, WHITE}, {KNIGHT, WHITE}, {ROOK, WHITE}};
int knightMoves[8] = {-17, -15, -10, -6, 6, 10, 15, 17}; 
struct Chess
{

    uint8_t playerTurn;
    char boardString[73];
    uint8_t whiteKing;
    uint8_t blackKing; 
};




char* getBoard(Chess_t Chess){
    for (uint8_t u = 0; u < 8; u++)
    {
        for (uint8_t i = 0; i < 8; i++)
        {
            switch (board[u*8 + i].type)  
            {
            case PAWN:

                Chess->boardString[u*9 + i] = PAWN - lowerASCII * (1 - board[u*8 + i].color);
                break;

            case KNIGHT:

                Chess->boardString[u*9 + i] = KNIGHT - lowerASCII * (1 - board[u*8 + i].color);
                break;

            case BISHOP:

                Chess->boardString[u*9 + i] = BISHOP - lowerASCII * (1 - board[u*8 + i].color);
                break;

            case ROOK:

                Chess->boardString[u*9 + i] = ROOK - lowerASCII * (1 - board[u*8 + i].color);
                break;

            case QUEEN:

                Chess->boardString[u*9 + i] = QUEEN - lowerASCII * (1 - board[u*8 + i].color);
                break;

            case KING:
                Chess->boardString[u*9 + i] = KING - lowerASCII * (1 - board[u*8 + i].color);
                break;

            default:
                Chess->boardString[u*9 + i] = '#' + (i%2) * 8;
                break;
            }
        }
        Chess->boardString[u * 9 + 8] = '\n';
    }
    Chess -> boardString[72] = '\0';
    return Chess -> boardString;
}
bool canTheKingBeCaptured(Chess_t chessGame){
    uint8_t currentColor = chessGame ->playerTurn;
    uint8_t currentKing =  currentColor == WHITE ? chessGame ->whiteKing : chessGame->blackKing;
    //Check if Knight can capture King
    for (uint8_t i = 0; i < 8; i++)
    {
        if(board[currentKing + knightMoves[i]].type == KNIGHT && board[currentKing + knightMoves[i]].color != currentColor) return true;
    }
    uint8_t y = currentKing / 8;
    uint8_t x = currentKing % 8;

    //Check Right side
    for (uint8_t i = 1; i < 8 - x; i++)
    {
        if(board[currentKing + i].color == currentColor) break;
        if(i == 1 && board[currentKing + i].type == KING) return true;
        if(board[currentKing + i].type == ROOK || board[currentKing + i].type == QUEEN) return true;
        
    }
    //Check Left side
    for (uint8_t i = 1; i < x + 1; i++)
    {
        if(board[currentKing - i].color == currentColor) break;
        if(i == 1 && board[currentKing - i].type == KING) return true;
        if(board[currentKing - i].type == ROOK || board[currentKing - i].type == QUEEN) return true;
        
    }
    //Check front
    for (uint8_t i = 1; i < y + 1; i++)
    {
        if(board[currentKing - i * 8].color == currentColor) break;
        if(i == 1 && board[currentKing - i* 8].type == KING) return true;
        if(board[currentKing - i * 8].type == ROOK || board[currentKing - i * 8].type == QUEEN) return true;
        
    }
    //Check back
    for (uint8_t i = 1; i < 8 - y; i++)
    {
        if(board[currentKing + i * 8].color == currentColor) break;
        if(i == 1 && board[currentKing + i * 8].type == KING) return true;
        if(board[currentKing + i * 8].type == ROOK || board[currentKing + i * 8].type == QUEEN) return true;
        
    }
    //Check top right diagonal
    for (uint8_t i = 1; i < 8 - y; i++)
    {
        if(board[currentKing + i * 8].color == currentColor) break;
        if(i == 1 && board[currentKing + i * 8].type == KING) return true;
        if(board[currentKing + i * 8].type == ROOK || board[currentKing + i * 8].type == QUEEN) return true;
        
    }
    return false;
}
//Input as 0 - 7 
void movePiece(Chess_t chessGame, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
    UART_transmit(x1+ 0x30);
    UART_transmit(y1+ 0x30);
    UART_transmit(x2+ 0x30);
    UART_transmit(y2+ 0x30);
    uint8_t moveAllowed = true;
    //Get Piece
    Piece_t currentPiece = &board[x1 + y1 * 8];
    UART_transmit(currentPiece->type);
    UART_transmit('\n');
    //Check Right Color to Move
    if(currentPiece -> color != chessGame -> playerTurn){
        //ERROR
        return;
    }
    //Check Input
    if(x1 > 7 || x2 > 7 || y1 > 7 || y2 > 7){
        //ERROR
        return;
    } 

    switch (currentPiece->type)
            {

            case PAWN:

                //Not obstructed
                if( (board[x2 + y2 * 8].type != NONE && (x1 == x2)) || board[x2 + y2 * 8].color == chessGame->playerTurn){
                    moveAllowed = false;
                }

                //Legal move
                if(currentPiece -> color == WHITE){
                            //Move Up                                top-right                             top-left                                         First Pawn Move
                    if( !((x1 == x2 && (y1 - y2) == 1) || ((x1 == x2 + 1) && (y1 == y2 - 1)) || ((x1 == x2 - 1) && (y1 == y2 - 1)) || ((x1 == x2) && (y1 == 6) && (y2 == 4))) ){
                        moveAllowed = false;
                    }
                }else{
                    if( !((x1 == x2 && (y2 - y1) == 1) || ((x1 == x2 + 1) && (y1 == y2 + 1)) || ((x1 == x2 - 1) && (y1 == y2 + 1)) || ((x1 == x2) && (y1 == 1) && (y2 == 3))) ){
                        moveAllowed = false;
                    }
                }
                //Not Pinned
                


                break;

            case KNIGHT:

                
                break;

            case BISHOP:

               
                break;

            case ROOK:

             
                break;

            case QUEEN:

                
                break;

            case KING:
                
                break;

            default:
                //ERROR MESSAGE HERE
                break;
            }
    if (moveAllowed)
    {
        Piece none = {NONE, 128};
        board[y2 * 8 + x2] = board[y1 * 8 + x1];
        board[y1 * 8 + x1] = none;
        chessGame ->playerTurn ^= 1; 
    }
}


Chess_t chessGameInit(void){

    Chess_t chessGame = malloc(sizeof(Chess)); 
    chessGame -> playerTurn = WHITE;

    return chessGame;
}
