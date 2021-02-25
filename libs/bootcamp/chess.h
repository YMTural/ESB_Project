#ifndef CHESS_H
#define CHESS_H


typedef struct Piece Piece;

typedef Piece* Piece_t;

typedef struct Chess Chess;

typedef Chess* Chess_t;


Chess_t chessGameInit(void);
char* getBoard(Chess_t Chess);
void movePiece(Chess_t chessGame, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
#endif