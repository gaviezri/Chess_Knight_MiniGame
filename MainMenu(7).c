
#include "menu.h"
#include "LoadDisplay.h"
#include "validknightmoves.h"
#include "findPathCoversAll.h"
#include "CreatepathTree.h"
#include "SaveFileToBin.h"

void main()
{


	
	openingscreen();
	puts("\n\t[208782912 - Gal Aviezri] --- [315873471 - Omri Shahar]");
	delay(3);
	char FILENAME[MAX_NAME_LEN];
	chessPos* pos = NULL;
	pathTree tree;
	chessPosList* posList=NULL;
	tree.root = NULL;
	int choice=0;
	/*clearscreen - after each step*/
	while (true)
	{
		
		
		if (choice == 5)
			delay(30);//show printed board for 30 seconds and start over
		system("cls");
		/*notify last action was done!*/
		if (choice>=1 && choice<=6)
			printf("----Option %d Executed!----\n", choice);
		
		printmenu();
		choice = getchar() - '0';
		
		
		getchar();/*discard '\n'*/
		switch (choice)
		{
			case 1:
				if (pos)
					free(pos);
				puts("enter in 'A1' form: ");
				pos = getStartingPos(pos);
				break;
			case 2:
				if (!pos)
					pos = reEnterPos(pos);
				tree = findAllPossibleKnightPaths(pos);			
				break;
			case 3:
				if (!pos)
					pos = reEnterPos(pos);
				if (!(tree.root))
					tree = findAllPossibleKnightPaths(pos);
				posList = findKnightPathCoveringAllBoard(&tree);
				break;
			case 4:
				puts("please enter the file name where the path will be save: ");
				gets(FILENAME);
				if (!posList)
				{
					if (!pos)
						pos = reEnterPos(pos);
					if (!(tree.root))
						tree = findAllPossibleKnightPaths(pos);
					posList = findKnightPathCoveringAllBoard(&tree);
				}
				freetree(tree);
				saveListToBinFile(FILENAME,posList);
				freeList(posList->head);
				free(posList);
				posList = NULL;
				break;
			case 5:
				puts("please enter the file name you wish to load: ");
				gets(FILENAME);
					short res = checkAndDisplayPathFromFile(FILENAME);
				switch (res)
				{
				case -1:
					puts("\nerror reading file - lets try again.\n");
					break;
				case 1:
					puts("\nthe file contains invalid play- lets try again.\n");
					break;
				case 2:
					puts("\n ALL BOARD WAS COVERED!!!!!");
					break;
				case 3:
					puts("\nBoard isn't fully covered.");
					break;
				}
				puts("\n\tBoard is now presented for 30 seconds");
				free(pos);
				pos = NULL;
				if (posList)
				{
					if (posList->head)
						freeList(posList->head);
					free(posList);
				}
				break;
			case 6:
				free(pos);
				_fcloseall();
				exit(EXIT);
			default:
				printf("Invalid Key\n Please Select either of the options above:\n");
				delay(3);
				break;
		}
	}
}

chessPos* reEnterPos(chessPos* pos)
{
	printf("No Starting Position Entered!\n");
	printf("Enter a knight's starting position:\n");
	pos = getStartingPos(pos);
	return pos;
}

chessPos* getStartingPos(chessPos* pos)
{
	pos = (chessPos*)malloc(sizeof(chessPos));
	assert(pos);
	pos = scanAndfix(pos);

	while (!inRange((*pos)[0] - 'A', (*pos)[1] - '0'))
	{
		printf("Invalid Input!\nEnter a knight's starting position:\n");
		pos = scanAndfix(pos);
	}
	return pos;
}
chessPos* scanAndfix(chessPos* pos)
{
	(*pos)[0] = getchar();
	(*pos)[1] = getchar();
	getchar();/*discard '\n'*/
	if (isLower((*pos)[0]))
		(*pos)[0] = toUpper((*pos)[0]);
	return pos;
}
void printmenu()
{
	printf("Welcome To \"A Night with The Knight\"\nPlease Select A Mode:\n####################################\n");
	printf("1. Enter a knight's starting position\n");
	printf("2. Create all possible knight paths\n");
	printf("3. Find a knight's path covering all board\n");
	printf("4. Save knight's path covering all board to file\n");
	printf("5. Load and display path from file\n");
	printf("6. Exit\n\n");
}

void delay(int number_of_seconds)
{
	int milli_seconds = 1000 * number_of_seconds;
	char ch;
	// Storing start time
	clock_t start_time = clock();
	puts("\n\t\tpress any key to continue");
	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds)
		if (_kbhit())
		{
			_getch();
			break;
		}
}
void openingscreen()
{
	puts("                                                      _:_");
	puts("                                                     '-.-'");
	puts("                                            ()      __.'.__");
	puts("                                         .-:--:-.  |_______|");
	puts("                                  ()      \\____/    \\=====/");
	puts("                                  /\\      {====}     )___(");
	puts("                       (\\=,      //\\\\      )__(     /_____\\");
	puts("       __    |'-'-'|  //  .\\    (    )    /____\\     |   |");
	puts("      /  \\   |_____| (( \\_  \\    )__(      |  |      |   |");
	puts("      \\__/    |===|   ))  `\\_)  /____\\     |  |      |   |");
	puts("     /____\\   |   |  (/     \\    |  |      |  |      |   |");
	puts("      |  |    |   |   | _.-'|    |  |      |  |      |   |");
	puts("      |__|    )___(    )___(    /____\\    /____\\    /_____\\");
	puts("     (====)  (=====)  (=====)  (======)  (======)  (=======)");
	puts("     }===={  }====={  }====={  }======{  }======{  }======={");
	puts(" MTA(______)(_______)(_______)(________)(________)(_________)");
}


void freetree(pathTree tr)
{
	if (tr.root)
		freetreeaux(tr.root);
}

void freetreeaux(TreeNode* node)
{
	if (!node)
		return;
	TreeNodeListCell* curr = node->Next_Possible_Positions,*prev;
	while (curr)
	{
		freetreeaux(curr->node);
		prev = curr;
		curr = curr->Next;
		free(prev);
	}
	free(node);
}