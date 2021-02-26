#include "build/temp/_test_chess.c"
#include "libs/bootcamp/chess.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"


Piece empty = {NONE, 128};

void test_illegalMoves(void){



    Chess_t game = chessGameInit();







    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 7, 7, 6, 6))), (

   ((void *)0)

   ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 6, 7, 6, 6))), (

   ((void *)0)

   ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 5, 7, 6, 6))), (

   ((void *)0)

   ), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 4, 7 , 6, 6))), (

   ((void *)0)

   ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 7, 6, 6))), (

   ((void *)0)

   ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 5, 6, 7, 3))), (

   ((void *)0)

   ), (UNITY_UINT)(46), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 7, 6, 6, 6))), (

   ((void *)0)

   ), (UNITY_UINT)(48), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 7, 6, 7, 3))), (

   ((void *)0)

   ), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_UINT8);

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



        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 0, 7-i, 0, 6-i))), (

       ((void *)0)

       ), (UNITY_UINT)(70), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 7, i, 7, i+1))), (

       ((void *)0)

       ), (UNITY_UINT)(72), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));



    }





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

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, i, 7-i, i+1, 6-i))), (

       ((void *)0)

       ), (UNITY_UINT)(95), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, i, i, i+1, i+1))), (

       ((void *)0)

       ), (UNITY_UINT)(97), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));





    }





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





        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 4, 5, 3, 3))), (

       ((void *)0)

       ), (UNITY_UINT)(120), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 4, 2, 3, 4))), (

       ((void *)0)

       ), (UNITY_UINT)(122), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 3, 4, 5))), (

       ((void *)0)

       ), (UNITY_UINT)(124), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 4, 4, 2))), (

       ((void *)0)

       ), (UNITY_UINT)(126), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));



        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 4, 5, 2, 4))), (

       ((void *)0)

       ), (UNITY_UINT)(129), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 4, 2, 2, 3))), (

       ((void *)0)

       ), (UNITY_UINT)(131), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 2, 4, 4, 5))), (

       ((void *)0)

       ), (UNITY_UINT)(133), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 2, 3, 4, 2))), (

       ((void *)0)

       ), (UNITY_UINT)(135), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));



        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 4, 5, 5, 3))), (

       ((void *)0)

       ), (UNITY_UINT)(138), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 4, 2, 5, 4))), (

       ((void *)0)

       ), (UNITY_UINT)(140), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 5, 3, 4, 5))), (

       ((void *)0)

       ), (UNITY_UINT)(142), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 5, 4, 4, 2))), (

       ((void *)0)

       ), (UNITY_UINT)(144), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));



        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 4, 5, 6, 4))), (

       ((void *)0)

       ), (UNITY_UINT)(147), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 4, 2, 6, 3))), (

       ((void *)0)

       ), (UNITY_UINT)(149), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 6, 4, 4, 5))), (

       ((void *)0)

       ), (UNITY_UINT)(151), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 6, 3, 4, 2))), (

       ((void *)0)

       ), (UNITY_UINT)(153), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));













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

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 0, i-1, 0, i))), (

       ((void *)0)

       ), (UNITY_UINT)(191), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, i-1, 2, i, 2))), (

       ((void *)0)

       ), (UNITY_UINT)(193), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

    }

    for (size_t i = 7; i > 0; i--)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 0, i, 0, i-1))), (

       ((void *)0)

       ), (UNITY_UINT)(198), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, i, 2, i-1, 2))), (

       ((void *)0)

       ), (UNITY_UINT)(200), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

    }









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

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 0, i-1, 0, i))), (

       ((void *)0)

       ), (UNITY_UINT)(237), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, i-1, 2, i, 2))), (

       ((void *)0)

       ), (UNITY_UINT)(239), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

    }

    for (size_t i = 7; i > 0; i--)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 0, i, 0, i-1))), (

       ((void *)0)

       ), (UNITY_UINT)(244), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, i, 2, i-1, 2))), (

       ((void *)0)

       ), (UNITY_UINT)(246), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

    }









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

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, i, 7-i, i+1, 6-i))), (

       ((void *)0)

       ), (UNITY_UINT)(283), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, i, i, i+1, i+1))), (

       ((void *)0)

       ), (UNITY_UINT)(285), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));





    }

    for (uint8_t i = 7; i > 0; i--)

    {

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, i, 7-i, i-1, 8-i))), (

       ((void *)0)

       ), (UNITY_UINT)(293), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, i, i, i-1, i-1))), (

       ((void *)0)

       ), (UNITY_UINT)(295), UNITY_DISPLAY_STYLE_UINT8);

        printf("%s",getBoard(game));





    }







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

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 4, 7, 4, 6))), (

   ((void *)0)

   ), (UNITY_UINT)(318), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 4, 0, 4, 1))), (

   ((void *)0)

   ), (UNITY_UINT)(320), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 4, 6, 3, 5))), (

   ((void *)0)

   ), (UNITY_UINT)(323), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 4, 1, 3, 2))), (

   ((void *)0)

   ), (UNITY_UINT)(325), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 5, 4, 4))), (

   ((void *)0)

   ), (UNITY_UINT)(328), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 2, 4, 1))), (

   ((void *)0)

   ), (UNITY_UINT)(330), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 4, 4, 3, 5))), (

   ((void *)0)

   ), (UNITY_UINT)(333), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 4, 1, 3, 2))), (

   ((void *)0)

   ), (UNITY_UINT)(335), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 5, 2, 5))), (

   ((void *)0)

   ), (UNITY_UINT)(338), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((WHITESTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 2, 4, 1))), (

   ((void *)0)

   ), (UNITY_UINT)(340), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 2, 5, 3, 5))), (

   ((void *)0)

   ), (UNITY_UINT)(343), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));







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

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((BLACKSTURN)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 6, 1, 4, 1))), (

   ((void *)0)

   ), (UNITY_UINT)(367), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 0, 1, 0, 2))), (

   ((void *)0)

   ), (UNITY_UINT)(369), UNITY_DISPLAY_STYLE_UINT8);







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

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 2, 2, 1))), (

   ((void *)0)

   ), (UNITY_UINT)(402), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 2, 3, 1))), (

   ((void *)0)

   ), (UNITY_UINT)(404), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 2, 4, 1))), (

   ((void *)0)

   ), (UNITY_UINT)(406), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 2, 2, 2))), (

   ((void *)0)

   ), (UNITY_UINT)(408), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 2, 4, 2))), (

   ((void *)0)

   ), (UNITY_UINT)(410), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 2, 2, 3))), (

   ((void *)0)

   ), (UNITY_UINT)(412), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 2, 3, 3))), (

   ((void *)0)

   ), (UNITY_UINT)(414), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 2, 4, 3))), (

   ((void *)0)

   ), (UNITY_UINT)(416), UNITY_DISPLAY_STYLE_UINT8);









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

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 3, 0, 0))), (

   ((void *)0)

   ), (UNITY_UINT)(449), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 3, 0, 7))), (

   ((void *)0)

   ), (UNITY_UINT)(451), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 3, 7, 0))), (

   ((void *)0)

   ), (UNITY_UINT)(453), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 3, 7, 7))), (

   ((void *)0)

   ), (UNITY_UINT)(455), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 3, 3, 7))), (

   ((void *)0)

   ), (UNITY_UINT)(457), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 3, 7, 3))), (

   ((void *)0)

   ), (UNITY_UINT)(459), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 3, 3, 0))), (

   ((void *)0)

   ), (UNITY_UINT)(461), UNITY_DISPLAY_STYLE_UINT8);

    printf("%s",getBoard(game));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((NOTPOSSIBLE)), (UNITY_INT)(UNITY_UINT8 )((movePiece(game, 3, 3, 0, 3))), (

   ((void *)0)

   ), (UNITY_UINT)(463), UNITY_DISPLAY_STYLE_UINT8);









}
