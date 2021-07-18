#pragma once
#include "chessPos.h"
bool is_cell_in_list(cell_info* arr, int row, int col, int ind);
bool SeenBefore(chessPosCell node, cell_info* info_arr, unsigned int size);
void insert_node_to_array(cell_info* arr, unsigned int* ind, chessPosCell* node);
void copyarr(cell_info* arr, cell_info* temp, int size);
cell_info* merge(cell_info* arr1, int size1, cell_info* arr2, int size2);
void cell_sort(cell_info* arr, int size);
void print_board(cell_info* arr, int size);
void display(chessPosList* lst);

chessPosCell* removeNode(chessPosCell* prev, chessPosCell* curr);
cell_info* Remove_doubles(chessPosList* lst, int* fin_size);