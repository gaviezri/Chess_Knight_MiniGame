/* Omri Shachar - 315873471  Gal Aviezri - 208782912*/
#include "display.h"






void display(chessPosList* lst)
{
	int size;
	cell_info* list_val_arr = Remove_doubles(lst, &size);
	cell_sort(list_val_arr, size);
	print_board(list_val_arr, size);

}

cell_info* Remove_doubles(chessPosList* lst, int* fin_size)
{
	cell_info* res = (cell_info*)malloc(sizeof(cell_info) * 5);
	assert(res);
	unsigned int phycl_size_res = 5, lgcl_size_res=0;
	chessPosCell *curr = lst->head, *prev = NULL;
	while (curr)
	{
		if(phycl_size_res == lgcl_size_res)
		{
			phycl_size_res *= 2;
			res = (cell_info*)realloc(res, phycl_size_res * sizeof(cell_info));
			assert(res);
		}
		if (SeenBefore(*curr, res, lgcl_size_res))
			curr = removeNode(prev, curr);
		else
		{
			insert_node_to_array(res, &lgcl_size_res, curr);
			prev = curr;
			curr = curr->next;
		}
	}
	res = (cell_info*)realloc(res, sizeof(cell_info) * lgcl_size_res);
	assert(res);
	*fin_size = lgcl_size_res;

	return res;
}

chessPosCell* removeNode(chessPosCell* prev, chessPosCell* curr)
{
	chessPosCell* temp = curr->next;
	prev->next = curr->next;
	free(curr);
	return temp;
}

void insert_node_to_array(cell_info* arr, unsigned int* ind, chessPosCell* node)
{
	arr[*ind].original_index = (*ind) + 1;
	arr[*ind].position[0] = node->position[0];
	arr[*ind].position[1] = node->position[1];
	(*ind)++;
}
bool SeenBefore(chessPosCell node, cell_info* info_arr, unsigned int size)
{
	for (int i = 0 ; i < size ; i++)
	{
		if (node.position[0] == info_arr[i].position[0] && node.position[1] == info_arr[i].position[1])
			return true;
	}
	return false;
}

void print_board(cell_info* arr, int size)
{
	int row, col, ind = 0, gap=0;
	printf("\t|   |");
	for (row = 0; row < ROWS; row++)
	{
		printf(" %2c |", row + '1');
	}
	printf("\n\t");
	for (gap=0; gap < COLS; gap++)
		printf("------");
	printf("\n");
	for (row = 0; row < ROWS; row++)
	{
		printf("\t| %c |", row +'A');
		for (col = 0; col < COLS; col++)
		{
				
			if (is_cell_in_list(arr, row, col, ind))
			{
				printf(" %2d |", arr[ind].original_index);
				ind++;
			}
			else
			{
				printf("    |");
			}
			if (col == COLS - 1)
			{
				printf("\n\t");
				for (gap=0; gap < COLS+1; gap++)
					printf("-----");
				printf("\n");
			}
				
		}
	}
}

bool is_cell_in_list(cell_info* arr ,int row, int col, int ind)
{
	return(arr[ind].position[0] == 'A' + row  && arr[ind].position[1] == '1' + col);
}

void cell_sort(cell_info* arr, int size)
{
	if (size <= 1) return;
	
	cell_sort(arr, size / 2);
	cell_sort(arr + size / 2, size - size / 2);
	cell_info* temp = merge(arr, size / 2, arr + size / 2, size - size / 2);
	if (temp)
	{
		copyarr(arr, temp,size);
		free(temp);
	}
	else
	{
		printf("cell_sort failed - line 178 - NULL ptr return from \"merge\"");
	}
}

void copyarr(cell_info* arr, cell_info* temp, int size)
{
	for (int i = 0; i < size; i++)
		arr[i] = temp[i];
}

cell_info* merge(cell_info* arr1, int size1, cell_info* arr2, int size2)
{
	int indres = 0, ind1 = 0, ind2 = 0;
	cell_info* res = (cell_info*)malloc(sizeof(cell_info) * (size1 + size2));
	assert(res);

	while (ind1 < size1 && ind2 < size2)
	{
		if (arr1[ind1].position[0] == arr2[ind2].position[0])
		{
			if (arr1[ind1].position[1] < arr2[ind2].position[1])
			{
				res[indres] = arr1[ind1];
				ind1++;	
			}
			else
			{
				res[indres] = arr2[ind2];
				ind2++;
			}
		}
		else if (arr1[ind1].position[0] < arr2[ind2].position[0])
		{
			res[indres] = arr1[ind1];
			ind1++;
		}
		else
		{
			res[indres] = arr2[ind2];
			ind2++;
		}
		indres++;
	}
	while (ind1 < size1)
	{
		res[indres] = arr1[ind1];
		ind1++;
		indres++;
	}
	while (ind2 < size2)
	{
		res[indres] = arr2[ind2];
		ind2++;
		indres++;
	}
	return res;
}