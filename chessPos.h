#ifndef CP_H
#define CP_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
typedef char chessPos[2];
typedef struct _treeNode TreeNode;
typedef struct _treeNodeListCell TreeNodeListCell;
#define ShakeBITS(bit,left,right) ((bit<<=left)\
                                  &&(bit>>=right))
typedef unsigned char BYTE;
#define BYTE_SIZE 1
#define ROWS 5
#define COLS 5

typedef struct _chessPosArray 
{
	unsigned int size;
	chessPos* positions;
}chessPosArray;




  
typedef struct _chessPosCell {
	chessPos position;
	struct  _chessPosCell* next;

}chessPosCell;

typedef struct _chessPosList {
	chessPosCell* head;
	chessPosCell* tail;
}chessPosList;

typedef struct _cellinfoarray {
	chessPos position;
	int original_index;

}cell_info;

typedef struct _treeNode {
	chessPos position;
	TreeNodeListCell* Next_Possible_Positions;

}TreeNode;


typedef struct _treeNodeListCell {
	TreeNode* node;
	struct _treeNodeListCell* Next;

}TreeNodeListCell;



typedef struct _pathTree {
	TreeNode* root;
}pathTree;

#endif