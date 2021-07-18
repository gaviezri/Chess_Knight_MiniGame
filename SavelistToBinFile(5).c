#include "SaveFileToBin.h"

void saveListToBinFile(char* file_name, chessPosList* Pos_list)
{
	short iteration = 0,extraflush_flag = 0;
	BYTE* buffer;
	BYTE MASK1 = 0, MASK2 = 0, RESMASK = 0,MASK3,MASK4 = 0;
	chessPosCell* curr = Pos_list->head;
	FILE* fp = fopen(file_name, "wb+");
	assert(fp);

	short unsigned int length = getListLen(Pos_list);

	fwrite(&length, sizeof(short unsigned int), 1, fp);

	while (curr)
	{
		MASK1 = CHAR_TOBIN(curr->position[0]);
		MASK2 = NUM_TOBIN(curr->position[1]);
		switch (iteration%3)
		{
		case 0: //overflow = 2 (1 left at next byte)
			MASK1 <<= 5 ; 
			MASK2 <<= 2;
			RESMASK = MASK1 | MASK2; //two zero at the LSB
			if (curr->next)
			{
				MASK4 = CHAR_TOBIN(curr->next->position[0]);
				MASK4 >>= 1;
				RESMASK |= MASK4;
			}
			break;
		case 1: //overflow = 1 (2 left at next byte)
			    MASK3 = MASK2;
				MASK1 <<= 7;
				MASK2 <<= 4;
				RESMASK = MASK1 | MASK2;
				if (curr->next)
				{
					MASK4 = CHAR_TOBIN(curr->next->position[0]);
					MASK4 <<= 1;
					RESMASK |= MASK4;
					MASK1 = NUM_TOBIN(curr->next->position[1]);
					MASK1 >>= 2;
					RESMASK = RESMASK | MASK1;
					if (!(curr->next->next))
					{
						MASK1 = NUM_TOBIN(curr->next->position[1]);
						MASK1 <<= 6;
						extraflush_flag = 1;
					}
				}
				break;
		case 2: 
				
				MASK2 <<= 6;
				curr = curr->next;
				if (curr)
				{
					MASK1 = CHAR_TOBIN(curr->position[0]);
					MASK1 <<= 3;
					RESMASK = MASK1 | MASK2;
					RESMASK |= NUM_TOBIN(curr->position[1]);
				}
				break;
		default:
			break;
		}
	fwrite(&RESMASK,BYTE_SIZE,BYTE_SIZE,fp);
	if (extraflush_flag)
		fwrite(&MASK1, BYTE_SIZE, BYTE_SIZE, fp);
	fflush(fp);
	iteration++;
	curr = curr->next;
	}
	fclose(fp);
}


short int getListLen(chessPosList* list)
{
	chessPosCell* curr = list->head;
	short int ret = 0;
	while (curr)
	{
		ret++;
		curr = curr->next;
	}
	return ret;
}