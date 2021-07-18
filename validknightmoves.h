/*this library contains the all the functions regarding validknightmoves*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "chessPos.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>





bool inRange(int, int);
chessPos* createMoveArray(int x, int y, int*);
chessPosArray*** validKnightMoves();
void insert_values_in_array(int* ind, chessPos* arr, int x, int y);


