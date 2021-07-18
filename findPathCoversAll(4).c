#pragma once
#include "findPathCoversAll.h"
#include "CreatepathTree.h"




chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)
{
	chessPosList* First = (chessPosList*)malloc(sizeof(chessPosList));
	assert(First);
	unsigned int boardsize = ROWS * COLS;
	First->head = find_and_create_path(boardsize-1, path_tree->root, First);
	if (!(First->head))
		First->tail = NULL;
	
	return First;
}

chessPosCell* find_and_create_path(int cellsleft, TreeNode* curr_node, chessPosList* List)
{	
	chessPosCell* res = initCell(curr_node->position);
	
	if (cellsleft == 0) /*if there are no cells left, create list tail*/
	{
		List->tail = res;
		res->next = NULL;
		return res;
	}
	else if (cellsleft != 0 && curr_node->Next_Possible_Positions == NULL) /*if ther are no more possible moves left and the board is not empty return NULL*/
	{
		free(res);
		return NULL;
	}
	else
	{
		TreeNodeListCell* temp = curr_node->Next_Possible_Positions;
		
		if (temp)
		{
			while (temp->node)
			{
				res->next = find_and_create_path(cellsleft - 1, temp->node, List);

				if (res->next)
					return res;

				if (temp->Next)
					temp = temp->Next;
				else
					break;
			}
		}
		free(res);
		return NULL;
	}
}

chessPosCell* initCell(chessPos pos)
{
	chessPosCell* res = (chessPosCell*)malloc(sizeof(chessPosCell));
	assert(res);
	strncpy(res->position,pos, 2);
	return res;
}
//
//void main()
//{ 
//	chessPos st[2] = { 'A','1' };
//	pathTree tr = findAllPossibleKnightPaths(st);
//	chessPosList* david = findKnightPathCoveringAllBoard(&tr);
//	int j = 5;
//}