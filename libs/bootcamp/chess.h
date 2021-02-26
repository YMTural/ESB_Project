#include "bootcamp/debug.h"
#ifndef CHESS_H
#define CHESS_H


struct Piece{
    uint8_t type;
    uint8_t color;
};


typedef struct Piece Piece;

typedef Piece* Piece_t;

typedef struct Chess Chess;

typedef Chess* Chess_t;

extern Piece board[64];

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

enum feedBack{
    WHITESTURN,
    BLACKSTURN,
    NOTPOSSIBLE,
    NOPIECESELECTED,
    CHECK,
    CHECKMATE,
    STALEMATE
};

/**
 * @brief
 *  Initalizes a chessGame
 * @return
 *  chessGame handle
 * 
 * 
 */ 

Chess_t chessGameInit(void);

/**
 * @brief
 *  Creates an ASCII representation of the current board
 * @param Chess
 *  The Chess Game being played
 * @return
 *  ASCII-Board String
 * 
 */
char* getBoard(Chess_t Chess);
/**
 * @brief
 *  Tries to move the piece at position x1,y1 to x2,y2
 *  Returns a feedback code about the outcome
 * @param chessGame 
 *  chess game which is being played
 * @param x1
 *  x-Position of the Piece
 * @param y1
 *  y-Position of the Piece
 * @param x2
 *  x-Position of destination
 * @param y2
 *  y-Position of destination
 * @return
 *  Result of move
 *  
 * 
 * 
 */
uint8_t movePiece(Chess_t chessGame, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
#endif