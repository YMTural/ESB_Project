#include <unity.h>
#include "bootcamp/chess.h"

Piece empty = {NONE, 128};


    /*
    + # + # + # + p
    # + # + # + # +
    + # + # + # + #
    # + # + # + # +   
    + # + # + # + #
    # + # + # + # + 
    + # + # + # + #
    P + # + # + # +
    */
void test_pawnMovement(void){
    Piece whitePawn = {PAWN, WHITE};
    Piece blackPawn = {PAWN, BLACK};
    for (size_t i = 0; i < 64; i++)
    {
        board[i] = empty;
    }

    Chess_t game = chessGameInit();
    
    board[56] = whitePawn;
    board[7] = blackPawn;

    for (uint i = 0; i < 6; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, ));
        TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece());
    }
    
    
}