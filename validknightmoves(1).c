#include "validknightmoves.h"

chessPosArray*** validKnightMoves()
{
	int row, col, size = 0;
	/*allocate rows*/
	chessPosArray*** resMatrix = (chessPosArray***)malloc(sizeof(chessPosArray**) * ROWS);                    
	assert(resMatrix);
	/*allocate cols*/
	for (row = 0; row < ROWS; row++)
	{
		resMatrix[row] = (chessPosArray**)malloc(sizeof(chessPosArray*) * COLS);
		assert(resMatrix[row]);
	}

	for (row = 0; row < ROWS; row++)
	{
		for (col = 0; col < COLS; col++)                                                                 
		{/*allocate each "cell" and fill possible moves data for knight */
			resMatrix[row][col] = (chessPosArray*)malloc(sizeof(chessPosArray));
			assert(resMatrix[row][col]);
			resMatrix[row][col]->positions = createMoveArray(row, col, &size);
			resMatrix[row][col]->size = size;
		}
	}

	return resMatrix;
}

bool inRange(int x, int y)
{
	return((0 <= x) && (0 <= y) && (COLS > y) && (ROWS > x));                                                              /*changed to 4X4 board for seif 3 */
}

chessPos* createMoveArray(int x, int y, int* size)
{
	int ind_counter = 0;
	/*initialize the possible moves to maximum = 8 */                                                                           //////////////////////////////////
	chessPos* Valid_Moves = (chessPos*)malloc(sizeof(chessPos) * COLS); /*   <<<< --------      */

	if (inRange(x - 2, y + 1))/*2up 1right*/
	{
		insert_values_in_array(&ind_counter, Valid_Moves, x - 2, y + 1);
	}
	if (inRange(x - 1, y + 2))/*1up 2right*/
	{
		insert_values_in_array(&ind_counter, Valid_Moves, x - 1, y + 2);
	}
	if (inRange(x + 1, y + 2))/*1down 2right*/
	{
		insert_values_in_array(&ind_counter, Valid_Moves, x + 1, y + 2);
	}
	if (inRange(x + 2, y + 1))/*2down 1right*/
	{
		insert_values_in_array(&ind_counter, Valid_Moves, x + 2, y + 1);
	}
	if (inRange(x + 2, y - 1))/*2down 1left*/
	{
		insert_values_in_array(&ind_counter, Valid_Moves, x + 2, y - 1);
	}
	if (inRange(x + 1, y - 2))/*1down 2left*/
	{
		insert_values_in_array(&ind_counter, Valid_Moves, x + 1, y - 2);
	}
	if (inRange(x - 1, y - 2))/*1up 2left*/
	{
		insert_values_in_array(&ind_counter, Valid_Moves, x - 1, y - 2);
	}
	if (inRange(x - 2, y - 1))/*2up 1left*/
	{
		insert_values_in_array(&ind_counter, Valid_Moves, x - 2, y - 1);
	}

	if (ind_counter < COLS)																												 /*changed to 4 for seif 3!*/
	{
		Valid_Moves = (chessPos*)realloc(Valid_Moves, ind_counter * sizeof(chessPos));
		assert(Valid_Moves);
	}

	(*size) = ind_counter;
	return Valid_Moves;
}

void insert_values_in_array(int* ind, chessPos* arr, int x, int y)
{
	/*rows = A-H  ,   cols = 1-8*/
	arr[*ind][0] = x + 'A';
	arr[*ind][1] = y + '1';

	(*ind)++;
}