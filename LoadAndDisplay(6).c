
#include "display.h"
#include "SaveFileToBin.h"
#include "validknightmoves.h"
#include "LoadDisplay.h"


bool isValid(chessPosList moves);
int checkAndDisplayPathFromFile(char* file_name)
{
	chessPosList moves_list;
	chessPosCell* curr;
	moves_list.head = NULL;
	BYTE raw_input, mask1, mask2,overflow;
	int i, iteration = 0, flag = 0;
	FILE* fp = fopen(file_name, "rb");
	if (fp)
	{
		short unsigned int elements_count;
		if (1 != fread(&elements_count, sizeof(short unsigned int), 1, fp))
		{
			printf("file corrupted! - line 10 (LoadAndDisplay(6).c)");
			exit(0);
		}
		//create a list of the data uncompressed
		curr = moves_list.head = (chessPosCell*)malloc(sizeof(chessPosCell));
		assert(curr);

		for (i = 0; i < elements_count && !feof(fp);iteration++)
		{
			fread(&raw_input, BYTE_SIZE, BYTE_SIZE, fp);
			mask1 = raw_input; /*duplicates the original current byte*/
			switch (iteration%3) 
			{
			case 0:
				if (i > 0)
				{
					curr = curr->next=(chessPosCell*)malloc(sizeof(chessPosCell));
					assert(curr);
				}
				mask2 = mask1; /*duplicates the original current byte*/
				// ' . ' - indicates unknown binary value ' x ' indicates desired 3 bits
				ShakeBITS(mask1, 0, 5); //mask1 >>= 5; // |x|x|x|.|.|.|.|.| --> |0|0|0|0|0|X|X|X| 5 right, 0 left
				curr->position[0] = BIN_TOCHAR(mask1);

				ShakeBITS(mask2, 3, 5);
				// |.|.|.|X|X|X|.|.| --> |X|X|X|.|.|0|0|0|	3 left
				// |X|X|X|.|.|0|0|0| --> |0|0|0|0|0|X|X|X|	5 right
				curr->position[1] = BIN_TONUM(mask2);
				i++;
				if (i < elements_count)
				{
					curr->next = (chessPosCell*)malloc(sizeof(chessPosCell));
					assert(curr->next);
					curr = curr->next;
					ShakeBITS(overflow = raw_input, 6, 5);
					
				}
				break;
			case 1:
				ShakeBITS(mask1, 0, 7);
				
				curr->position[0] = BIN_TOCHAR((overflow | mask1));

				mask1 = mask2 = raw_input; /*duplicates the original current byte*/
				ShakeBITS(mask1, 1, 5);
				curr->position[1] = BIN_TONUM(mask1);
				i++;
				mask1 = overflow = mask2; /*duplicates the original current byte*/
				if (i < elements_count)
				{
					curr->next = (chessPosCell*)malloc(sizeof(chessPosCell));
					assert(curr->next);
					curr = curr->next;
					ShakeBITS(mask1, 4, 5);
					ShakeBITS(overflow, 7, 5);
					curr->position[0] = BIN_TOCHAR(mask1);
				}
				break;
			case 2:
				ShakeBITS(mask1, 0, 6);
				curr->position[1] = BIN_TONUM(overflow | mask1);
				i++;
				mask1 = raw_input; /*duplicates the original current byte*/
				if (i<elements_count)
				{
					curr->next = (chessPosCell*)malloc(sizeof(chessPosCell));
					assert(curr->next);
					curr = curr->next;
					ShakeBITS(mask1, 2, 5);
					curr->position[0] = BIN_TOCHAR(mask1);
					mask1 = raw_input;
					ShakeBITS(mask1, 5, 5);
					curr->position[1] = BIN_TONUM(mask1);
					i ++;
				}
				break;
			}

		}
		curr->next = NULL;
		fclose(fp);
		if(!isValid)
		{
			 freeList(moves_list.head);
			 return 1;
		}
		else
		{
			display(&moves_list);
			short int size = getListLen(&moves_list);
			if (size == elements_count)
				return 2;
			return 3;
		}
	}
	return -1;
}
bool isValid(chessPosList moves)
{
	chessPosArray*** possible = validKnightMoves();
	chessPosCell* curr = moves.head;
	short flag = 0;
	while (curr->next)
	{
		flag = 0;
		for (short i = 0; i < possible[CHAR_TOBIN(curr->position[0])][NUM_TOBIN(curr->position[1])]->size && flag!=1; i++)
		{
			if (!strncmp(possible[CHAR_TOBIN(curr->position[0])][NUM_TOBIN(curr->position[1])]->positions[i], curr->next->position, 2))
				flag = 1;
		}
		if (flag == 0)
			return false;
		curr = curr->next;
	}
	return true;
}

