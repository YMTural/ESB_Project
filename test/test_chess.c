#include <unity.h>
#include "bootcamp/chess.h"

Piece empty = {NONE, 128};

    //From
    /*
    + p + # + # + p
    # + # + # + # +
    + # + # + # + #
    # + # + # + # +   
    + # + # + # + #
    # + # + # + # + 
    + # + # + # + #
    P + # + # + P +
    */
    //To
    /*
    Q p + # + # + #
    # + # + # + # +
    + # + # + # + #
    # + # + # + # +   
    + # + # + # + #
    # + # + # + # + 
    + # + # + # + #
    # + # + # + P q
    */
   
void test_illegalMoves(void){
                     
    Chess_t game = chessGameInit();
    //reset board

     
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 7, 7, 6, 6));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 6, 7, 6, 6));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 5, 7, 6, 6));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 4, 7 , 6, 6));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 3, 7, 6, 6));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 5, 6, 7, 3));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 7, 6, 6, 6));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 7, 6, 7, 3));  
}

void test_pawnMovement(void){
    Piece whitePawn = {PAWN, WHITE};
    Piece blackPawn = {PAWN, BLACK};
    for (size_t i = 0; i < 64; i++)
    {
        board[i] = empty;
    }

    Chess_t game = chessGameInit();
    board[62] = whitePawn;
    board[56] = whitePawn;
    board[1] = blackPawn;
    board[7] = blackPawn;

    for (uint8_t i = 0; i < 7; i++)
    {

        TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 0, 7-i, 0, 6-i));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, 7, i, 7, i+1));
        printf("%s",getBoard(game));

    }
    //To see the Moves, remove comment
    //TEST_FAIL();
}

void test_BishopMovement(void){
    Piece whiteBishop = {BISHOP, WHITE};
    Piece blackBishop = {BISHOP, BLACK};
    for (size_t i = 0; i < 64; i++)
    {
        board[i] = empty;
    }

    Chess_t game = chessGameInit();
    board[0] = blackBishop;
    board[56] = whiteBishop;

    for (uint8_t i = 0; i < 7; i++)
    {
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, i, 7-i, i+1, 6-i));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, i, i, i+1, i+1));
        printf("%s",getBoard(game));


    }
    //To see the Moves, remove comment
    //TEST_FAIL();
}

void test_knightMovement(void){
    Piece whiteKnight = {KNIGHT, WHITE};
    Piece blackKnight = {KNIGHT, BLACK};
    for (size_t i = 0; i < 64; i++)
    {
        board[i] = empty;
    }

    Chess_t game = chessGameInit();
    board[20] = blackKnight;
    board[44] = whiteKnight;
    
        //All Possbile Knight Moves
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 4, 5, 3, 3));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, 4, 2, 3, 4));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 3, 3, 4, 5));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, 3, 4, 4, 2));
        printf("%s",getBoard(game));

        TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 4, 5, 2, 4));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, 4, 2, 2, 3));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 2, 4, 4, 5));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, 2, 3, 4, 2));
        printf("%s",getBoard(game));

        TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 4, 5, 5, 3));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, 4, 2, 5, 4));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 5, 3, 4, 5));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, 5, 4, 4, 2));
        printf("%s",getBoard(game));

        TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 4, 5, 6, 4));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, 4, 2, 6, 3));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 6, 4, 4, 5));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, 6, 3, 4, 2));
        printf("%s",getBoard(game));

        //TEST_FAIL();

    
    //To see the Moves, remove comment
    //TEST_FAIL();
}

void test_rookMovement(void){
    Piece whitePawn = {PAWN, WHITE};
    Piece blackPawn = {PAWN, BLACK};
    Piece blackRook = {ROOK, BLACK};
    Piece whiteRook = {ROOK, WHITE};
    for (size_t i = 0; i < 64; i++)
    {
        board[i] = empty;
    }

    Chess_t game = chessGameInit();
    board[3] = blackPawn;
    board[5] = blackPawn;
    board[11] = blackPawn;
    board[12] = blackPawn;
    board[13] = blackPawn;

    board[3+7*8] = whitePawn;
    board[5+7*8] = whitePawn;
    board[3+6*8] = whitePawn;
    board[4+6*8] = whitePawn;
    board[5+6*8] = whitePawn;

    board[0] = whiteRook;
    board[16] = blackRook;
         printf("%s",getBoard(game));
    for (size_t i = 1; i < 8; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 0, i-1, 0, i));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, i-1, 2, i, 2));
        printf("%s",getBoard(game));       
    }
    for (size_t i = 7; i > 0; i--)
    {
        TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 0, i, 0, i-1));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, i, 2, i-1, 2));
        printf("%s",getBoard(game));       
    }    

    //To see the Moves, remove comment
    //TEST_FAIL();
    
}

void test_QueenHorzVertMovement(void){
    Piece whitePawn = {PAWN, WHITE};
    Piece blackPawn = {PAWN, BLACK};
    Piece blackRook = {QUEEN, BLACK};
    Piece whiteRook = {QUEEN, WHITE};
    for (size_t i = 0; i < 64; i++)
    {
        board[i] = empty;
    }

    Chess_t game = chessGameInit();
    board[3] = blackPawn;
    board[5] = blackPawn;
    board[11] = blackPawn;
    board[12] = blackPawn;
    board[13] = blackPawn;

    board[3+7*8] = whitePawn;
    board[5+7*8] = whitePawn;
    board[3+6*8] = whitePawn;
    board[4+6*8] = whitePawn;
    board[5+6*8] = whitePawn;

    board[0] = whiteRook;
    board[16] = blackRook;
         printf("%s",getBoard(game));
    for (size_t i = 1; i < 8; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 0, i-1, 0, i));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, i-1, 2, i, 2));
        printf("%s",getBoard(game));       
    }
    for (size_t i = 7; i > 0; i--)
    {
        TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 0, i, 0, i-1));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, i, 2, i-1, 2));
        printf("%s",getBoard(game));       
    }    

    //To see the Moves, remove comment
    //TEST_FAIL();
    
}
void test_QueenDiagMovement(void){
    Piece whitePawn = {PAWN, WHITE};
    Piece blackPawn = {PAWN, BLACK};
    Piece blackQueen = {QUEEN, BLACK};
    Piece whiteQueen = {QUEEN, WHITE};
    for (size_t i = 0; i < 64; i++)
    {
        board[i] = empty;
    }

    Chess_t game = chessGameInit();
    board[3] = blackPawn;
    board[5] = blackPawn;
    board[11] = blackPawn;
    board[12] = blackPawn;
    board[13] = blackPawn;

    board[3+7*8] = whitePawn;
    board[5+7*8] = whitePawn;
    board[3+6*8] = whitePawn;
    board[4+6*8] = whitePawn;
    board[5+6*8] = whitePawn;

    board[0] = blackQueen;
    board[56] = whiteQueen;

    for (uint8_t i = 0; i < 7; i++)
    {
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, i, 7-i, i+1, 6-i));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, i, i, i+1, i+1));
        printf("%s",getBoard(game));


    }
    for (uint8_t i = 7; i > 0; i--)
    {
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, i, 7-i, i-1, 8-i));
        printf("%s",getBoard(game));
        TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, i, i, i-1, i-1));
        printf("%s",getBoard(game));


    }
    //To see the Moves, remove comment
    //TEST_FAIL();
    
}

void test_kingMovement(void){

    Piece whiteKing = {KING, WHITE};
    Piece blackKing = {KING, BLACK};
    Chess_t game = chessGameInit();
    for (size_t i = 0; i < 64; i++)
    {
        board[i] = empty;
    }
    board[60] = whiteKing;
    board[4] = blackKing;

    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 4, 7, 4, 6));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, 4, 0, 4, 1));
    printf("%s",getBoard(game));

    TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 4, 6, 3, 5));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, 4, 1, 3, 2));
    printf("%s",getBoard(game));    

    TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 3, 5, 4, 4));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, 3, 2, 4, 1));
    printf("%s",getBoard(game)); 

    TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 4, 4, 3, 5));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, 4, 1, 3, 2));
    printf("%s",getBoard(game));

    TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 3, 5, 2, 5));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(WHITESTURN, movePiece(game, 3, 2, 4, 1));
    printf("%s",getBoard(game)); 

    TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 2, 5, 3, 5));
    printf("%s",getBoard(game));

    //To see the Moves, remove comment
    //TEST_FAIL();
}

void test_kingInCheckCantMoveOtherPiece(void){

    Piece whiteKing = {KING, WHITE};
    Piece blackKing = {KING, BLACK};
    Piece whiteQueen = {QUEEN, WHITE};
    Piece blackPawn = {PAWN, BLACK};
    Chess_t game = chessGameInit();
    for (size_t i = 0; i < 64; i++)
    {
        board[i] = empty;
    }
    board[60] = whiteKing;
    board[4] = blackKing;

    board[14] = whiteQueen;
    board[8] = blackPawn;
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(BLACKSTURN, movePiece(game, 6, 1, 4, 1));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 0, 1, 0, 2));

    //To see the Moves, remove comment
    //TEST_FAIL();
}

void test_QueenBlocked(void){

    Piece whiteKing = {KING, WHITE};
    Piece blackKing = {KING, BLACK};
    Piece whiteQueen = {QUEEN, WHITE};
    Piece whitePawn = {PAWN, WHITE};

    Chess_t game = chessGameInit();

    for (size_t i = 0; i < 64; i++)
    {
        board[i] = empty;
    }

    board[60] = whiteKing;
    board[4] = blackKing;
    board[19] = whiteQueen;
    board[10] = whitePawn;
    board[11] = whitePawn;
    board[12] = whitePawn;
    board[18] = whitePawn;
    board[20] = whitePawn;
    board[26] = whitePawn;
    board[27] = whitePawn;
    board[28] = whitePawn;

    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 3, 2, 2, 1));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 3, 2, 3, 1));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 3, 2, 4, 1));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 3, 2, 2, 2));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 3, 2, 4, 2));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 3, 2, 2, 3));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 3, 2, 3, 3));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 3, 2, 4, 3));

    //To see the Moves, remove comment
    //TEST_FAIL();

}
void test_QueenBlockedLongMove(void){

    Piece whiteKing = {KING, WHITE};
    Piece blackKing = {KING, BLACK};
    Piece whiteQueen = {QUEEN, WHITE};
    Piece whitePawn = {PAWN, WHITE};

    Chess_t game = chessGameInit();

    for (size_t i = 0; i < 64; i++)
    {
        board[i] = empty;
    }

    board[60] = whiteKing;
    board[4] = blackKing;
    board[19+8] = whiteQueen;
    board[10+8] = whitePawn;
    board[8+11] = whitePawn;
    board[12+8] = whitePawn;
    board[8+18] = whitePawn;
    board[20+8] = whitePawn;
    board[8+26] = whitePawn;
    board[27+8] = whitePawn;
    board[8+28] = whitePawn;

    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 3, 3, 0, 0));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 3, 3, 0, 7));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 3, 3, 7, 0));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 3, 3, 7, 7));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 3, 3, 3, 7));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 3, 3, 7, 3));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 3, 3, 3, 0));
    printf("%s",getBoard(game));
    TEST_ASSERT_EQUAL_UINT8(NOTPOSSIBLE, movePiece(game, 3, 3, 0, 3));

    //To see the Moves, remove comment
    //TEST_FAIL();

}

