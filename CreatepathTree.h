#pragma once
#include "validknightmoves.h" 



#define PHYC_SIZE 1
#define LOGI_SIZE 0

pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
bool seenBefore(chessPos pos, chessPos* has_been, unsigned int size);
void create_tree(pathTree* ptr, chessPosArray*** PossibleMoves, chessPos pos);
TreeNode* InitializeRoot(chessPos pos, chessPosArray*** Board, chessPos* been_there, unsigned int phyc_size, unsigned int log_size);
TreeNode* create_tree_rec(chessPos prev, chessPos newpos, chessPos** been_there, unsigned int* phyc_size, unsigned int* log_size, chessPosArray*** PossibleMoves);
TreeNodeListCell* CreatePossiblePathList(chessPos pos, chessPosArray*** Board, chessPos* been_there, unsigned int log_size);
void updateBeenThere(chessPos pos, chessPos** been_there, unsigned int* phyc_size, unsigned int* log_size);
bool AnyMovesLeft(chessPos pos, chessPosArray*** PossibleMoves, chessPos** been_there, unsigned int log_size);
