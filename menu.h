

#include <time.h>
#include <conio.h>
#include "chessPos.h"

#define isLower(ch) ((ch<='z') && (ch>='a'))
#define toUpper(ch) (ch-'a'+'A')
#define EXIT 6
#define MAX_NAME_LEN 256
chessPos* scanAndfix(chessPos* pos);
void openingscreen();

chessPos* getStartingPos(chessPos*);
chessPos* reEnterPos(chessPos* pos);
void printmenu();
void delay(int number_of_seconds);
void freetreeaux(TreeNode* node);
void freetree(pathTree tr);