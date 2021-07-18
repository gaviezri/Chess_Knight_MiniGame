
#ifndef LB_H
#define LB_H


void makeEmpty(TreeNodeListCell* head);


void insertChessPosToEndList(chessPos pos, TreeNodeListCell* nextmoves_first);

TreeNodeListCell* CreateNew_TreeNodeListCell(chessPos pos);

void freeTreeNodeList(TreeNodeListCell* first);

void makeEmpty(TreeNodeListCell* head)
{
	head = NULL;
}

void insertChessPosToEndList(chessPos pos, TreeNodeListCell* nextmoves_first)
{
	TreeNodeListCell* NEW = CreateNew_TreeNodeListCell(pos);
	TreeNodeListCell* curr = nextmoves_first;
	if (curr)
	{
		while (curr->Next)
		{
			curr = curr->Next;
		}
		curr->Next = NEW;
	}
	else
	{
		nextmoves_first = NEW;
	}
}

TreeNodeListCell* CreateNew_TreeNodeListCell(chessPos pos)
{/*create new cell, init the node inside with NEXTS as NULL and inserting position.*/
	TreeNodeListCell* NEW = (TreeNodeListCell*)malloc(sizeof(TreeNodeListCell));
	assert(NEW);
	NEW->Next = NULL;
	NEW->node = (TreeNode*)malloc(sizeof(TreeNode));
	assert(NEW->node);
	NEW->node->Next_Possible_Positions = NULL;

	NEW->node->position[0] = pos[0];
	NEW->node->position[1] = pos[1];
	return NEW;
}


void freeTreeNodeList(TreeNodeListCell* first)
{
	if (!first)
		return;
	else
	{
		freeTreeNodeList(first->Next);
		freeTreeNodeList(first->node->Next_Possible_Positions);
		free(first->node);
		free(first);
	}

}

void freeList(chessPosCell* first)
{
	if (!first)
		return;
	else
	{
		freeList(first->next);
		free(first);
	}

}

#endif