#pragma once

#include "chessPos.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
chessPosCell* find_and_create_path(int cellsleft, TreeNode* curr_node, chessPosList* List);
chessPosCell* initCell(chessPos pos);

