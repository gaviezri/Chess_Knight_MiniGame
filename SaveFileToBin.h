#ifndef SAVETOBIN_H
#define SAVETOBIN_H
#define CHAR_TOBIN(ch)   ch-'A'
#define NUM_TOBIN(ch)   ch-'1'
#define BIN_TOCHAR(byte) byte + 'A'
#define BIN_TONUM(byte) byte + '1'
#include "chessPos.h"
short int getListLen(chessPosList* list);
void saveListToBinFile(char* file_name, chessPosList* Pos_list);
#endif