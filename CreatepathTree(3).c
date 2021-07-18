#include "CreatepathTree.h"
#include "listlib.h"


pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
	chessPosArray*** Possible_Moves_Board = validKnightMoves();
	pathTree TreeRes;
	create_tree(&TreeRes, Possible_Moves_Board, *startingPosition);
	return TreeRes;
}

void create_tree(pathTree* ptr,chessPosArray*** PossibleMoves,chessPos pos) 
{	
	chessPos* been_there = (chessPos*)malloc(sizeof(chessPos));
	assert(been_there);
	unsigned int Phyc_size = 1, Log_size = 0;
	ptr->root = create_tree_rec(NULL,pos,&been_there,&Phyc_size,&Log_size, PossibleMoves);
	free(been_there);
}

TreeNode* create_tree_rec(chessPos prev,chessPos newpos,chessPos** been_there, unsigned int *phyc_size, unsigned int *log_size, chessPosArray*** PossibleMoves)
{	
	
	TreeNodeListCell* temp, * first;
	TreeNode* root = NULL;
	if (!AnyMovesLeft(newpos, PossibleMoves, been_there, *log_size))
	{	
		(*log_size)--; /*if we reached end of the specific path, logical size is decreased by 1 to ignore the last been_there value*/
		return root;
	}
	updateBeenThere(prev, been_there, phyc_size, log_size);

	root = InitializeRoot(newpos, PossibleMoves, *been_there, *phyc_size, *log_size);
	temp = root->Next_Possible_Positions;

	while (temp)
	{	
		temp->node = create_tree_rec(root->position,temp->node->position,been_there, phyc_size, log_size, PossibleMoves);
		temp = temp->Next;
	}
	(*log_size)--;
	return root;
}

bool AnyMovesLeft(chessPos pos,chessPosArray*** PossibleMoves, chessPos** been_there, unsigned int log_size)
{/* this function returns true if given position wasnt seen before <-> we havent been there*/
	int j = 0;
	if (!log_size)
		return true;
	for(j;j< PossibleMoves[pos[0] - 'A'][pos[1] - '1']->size;j++)
		if (!seenBefore(PossibleMoves[pos[0] - 'A'][pos[1] - '1']->positions[j],*been_there,log_size))/*in case position not seen before */
				return true;
	return false;
}

TreeNode* InitializeRoot(chessPos pos,chessPosArray*** Board,chessPos* been_there, unsigned int phyc_size, unsigned int log_size)
{
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	assert(root);
	root->position[0] = pos[0];
	root->position[1] = pos[1];
	root->Next_Possible_Positions = CreatePossiblePathList(root->position, Board, been_there, log_size);
	return root;

}

void updateBeenThere(chessPos pos, chessPos** been_there, unsigned int* phyc_size, unsigned int* log_size)
{
	if (!pos)
		return;
	if ((*phyc_size) == (*log_size))
	{
		(*phyc_size) *= 2;
		*been_there = realloc(*been_there, (*phyc_size) * sizeof(chessPos));
		assert(*been_there);
	}
	(*been_there)[(*log_size)][0] = pos[0];
	(*been_there)[(*log_size)][1] = pos[1];
	(*log_size)++;
}

TreeNodeListCell* CreatePossiblePathList(chessPos pos ,chessPosArray*** Board,chessPos* been_there, unsigned int log_size)/*NOT FEEDED ALL NEXTS*/
{
	int  i, size = Board[pos[0] - 'A'][pos[1] - '1']->size;
	TreeNodeListCell* curr, * prev=NULL, *first=NULL;

	if (!log_size)
	{
		for (i = 0; i < size; i++)
		{
			curr = CreateNew_TreeNodeListCell(Board[pos[0] - 'A'][pos[1] - '1']->positions[i]);
			if (!i)
			{
				prev = first = curr;
			}
			else
			{
				prev->Next = curr;
				prev = prev->Next;
			}
			curr = curr->Next;
		}
	}
	else
	{
		for (i = 0; i < size; i++)
		{
			if (!seenBefore(Board[pos[0] - 'A'][pos[1] - '1']->positions[i],been_there,log_size))
			{
				curr = CreateNew_TreeNodeListCell(Board[pos[0] - 'A'][pos[1] - '1']->positions[i]);
				if (!first)
				{
					prev = first = curr;
				}
				else
				{
					prev->Next = curr;
					prev = prev->Next;
				}
				curr = curr->Next;
			}
		}	
	}
	return first;
}


/*this function checks if a possible move is valid (was not seen before) ---- if it was seen before it will return true (=not valid) else returns false*/
bool seenBefore(chessPos pos, chessPos* has_been, unsigned int size)																						/*****<=size******/
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (pos[0] == has_been[i][0] && pos[1] == has_been[i][1])
		{
			return true;
		}
	}
	return false;
}

/// <summary>
/// MAIN 
/// BDKIKA 
/// </summary>
