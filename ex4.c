/******************
Name: Lior Dvorin
ID: 215823469
Assignment: EX4
*******************/
#include <stdio.h>
#include <string.h>

#define SIZEOFPYRAMID 5
#define PARENTHESES 4
#define NUM_OF_CHARS 128
#define MAX_BOARD_SIZE 20
#define MAX_CROSSWORD_SIZE 30
#define MAX_WORD_LENGTH 15
#define MAX_NUM_OF_WORDS 100

typedef struct {
    char grid[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
} Board;
typedef struct {
    char grid[MAX_CROSSWORD_SIZE][MAX_CROSSWORD_SIZE];
} Crossword;
typedef struct {
    int row;
    int column;
    int length;
    char direction;
    //char word[];
} Slot;

int task1RobotPaths();
void task2HumanPyramid();
int task3ParenthesisValidator(char target);
void initializeArray(int array[], int size, int value, int index);
int task4QueensBattle(int squareSize, Board board, int column[squareSize], int row[squareSize],
                                int queens[NUM_OF_CHARS], int posRow, int posColumn, int numOfQueens);
void printSolution(Board board, int squareSize);
int checkAround(Board board, int squareSize, int posRow, int posColumn);
int task5CrosswordGenerator(int squareSize, Crossword crossword, int numOfSlots, Slot slots[numOfSlots], int numOfWords,
    char words[numOfWords][MAX_WORD_LENGTH], char dupWords[numOfWords][MAX_WORD_LENGTH],int posRow, int posColumn,
                                                            int numOfInsertedWords, int index);
Crossword generateEmptyCrossword(int squareSize, Crossword board, int numOfSlots, Slot slots[numOfSlots],
                      int posRow, int posColumn,int numOfInsertedSlots, int index, char direction);
Crossword insertWord(Crossword board, char word[MAX_WORD_LENGTH], int posRow, int posColumn, int index
                                                                                        ,int wordLength, char direction);
void printCrosswordSolution(int squareSize, Crossword solution,int numOfSlots, Slot slots[numOfSlots]);
void organizeSlots(int numOfSlots, Slot slots[numOfSlots], int index);
void organizeSlotsByIndex(int numOfSlots, Slot slots[numOfSlots], int index);
void swapSlots(int numOfSlots, Slot slots[numOfSlots], int index1, int index2);
void duplicateWords(int numOfWords, char words[numOfWords][MAX_WORD_LENGTH], char dupWords[numOfWords][MAX_WORD_LENGTH], int index);
//int buildEmpty(Crossword board, );


int main()
{
    int task = -1;
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf("%d", &task))
        {
            switch (task)
            {
            case 1: {
                int x, y;
                printf("Please enter the coordinates of the robot (column, row): \n");
                scanf("%d %d",&x,&y);
                printf("The total number of paths the robot can take to reach home is: %d\n", task1RobotPaths(x,y));
                break;
            }
            case 2: {
                printf("Please enter the weights of the cheerleaders: \n");
                float arr[SIZEOFPYRAMID][SIZEOFPYRAMID];
                for(int i = 0 ; i < SIZEOFPYRAMID; i++) {
                    for (int j = 0 ; j < i+1; j++) {
                        scanf("%f", &arr[i][j]);
                        while (arr[i][j] <= 0) {
                            printf("Negative weights are not supported. \n");
                            scanf("%f", &arr[i][j]);
                        }
                    }
                }
                task2HumanPyramid(arr, 0, 0);
                break;
            }
            case 3: {
                printf("Please enter a term for validation: \n");
                scanf(" %[^\n]");
                if(task3ParenthesisValidator('\0'))
                    printf("The parentheses are balanced correctly. \n");
                else
                    printf("The parentheses are not balanced correctly. \n");
                scanf("%*[^\n]");
                scanf("%*c");
                break;
            }
            case 4: {
                printf("Please enter the board dimensions: \n");
                int squareSize;
                scanf("%d", &squareSize);
                printf("Please enter the %d*%d puzzle board\n", squareSize, squareSize);
                Board board;
                for(int i = 0; i < squareSize; i++)
                    for(int j = 0; j < squareSize; j++)
                        scanf(" %c", &board.grid[i][j]);
                int column[MAX_BOARD_SIZE], row[MAX_BOARD_SIZE];
                int queens[NUM_OF_CHARS];
                initializeArray(column, squareSize, 0, 0);
                initializeArray(row, squareSize, 0, 0);
                initializeArray(queens, NUM_OF_CHARS, 0, 0);
                if(!task4QueensBattle(squareSize, board, column, row, queens, 0, 0, 0))
                    printf("This puzzle cannot be solved. \n");
                break;
            }
            case 5: {
                printf("Please enter the dimensions of the crossword grid: \n");
                int squareSize, numOfSlots;
                scanf("%d", &squareSize);
                printf("Please enter the number of slots in the crossword: \n");
                scanf("%d", &numOfSlots);
                printf("Please enter the details for each slot (Row, Column, Length, Direction): \n");
                Slot slots[numOfSlots];
                for(int i = 0; i < numOfSlots; i++)
                    scanf("%d %d %d %c", &slots[i].row, &slots[i].column, &slots[i].length, &slots[i].direction);
                int numOfWords;
                printf("Please enter the number of words in the dictionary: \n");
                scanf("%d", &numOfWords);
                while(numOfWords<numOfSlots) {
                    printf("The dictionary must contain at least %d words. Please enter a valid dictionary size: \n"
                                                                                                            ,numOfSlots);
                    scanf("%d", &numOfWords);
                }
                printf("Please enter the words for the dictionary: \n");
                char words[MAX_NUM_OF_WORDS][MAX_WORD_LENGTH], dupWords[MAX_NUM_OF_WORDS][MAX_WORD_LENGTH];
                for(int i = 0; i < numOfWords; i++)
                    scanf(" %s", &words[i]);
                duplicateWords(numOfSlots, words, dupWords, 0);
                //organize the slots so the horizontal ones are checked first and then the vertical ones so i can insert them into the empty board
                organizeSlots(numOfSlots, slots, 0);
                for(int i = 0; i < numOfSlots; i++)
                    printf("%d %d %d %c\n", slots[i].row, slots[i].column, slots[i].length, slots[i].direction);
                //create a crossword board where the slots are marked
                Crossword emptyCrossword = generateEmptyCrossword(squareSize, emptyCrossword, numOfSlots, slots, 0,0,0,0,'H');
                //organize the slots by their position on the board for the inserting of the words in the correct order
                organizeSlotsByIndex(numOfSlots, slots, 0);
                for(int i = 0; i < numOfSlots; i++)
                    printf("%d %d %d %c\n", slots[i].row, slots[i].column, slots[i].length, slots[i].direction);
                for(int i = 0; i < squareSize; i++) {
                    for(int j = 0; j < squareSize; j++)
                        printf("%c", emptyCrossword.grid[i][j]);
                    printf("\n");
                }
                if(!task5CrosswordGenerator(squareSize, emptyCrossword,numOfSlots, slots, numOfWords, words, dupWords, 0, 0, 0, 0))
                    printf("This crossword cannot be solved. \n");
                break;
            }
            case 6:
                printf("Goodbye!\n");
            break;
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            scanf("%*s");
        }

    } while (task != 6);
    return 0;
}

int task1RobotPaths(int x, int y)
{
    if (x == 0 && y == 0)
        return 1;
    if(x == 0)
        return task1RobotPaths(x, y-1);
    if(y == 0)
        return task1RobotPaths(x-1, y);
    return task1RobotPaths(x-1,y) + task1RobotPaths(x,y-1);
}

void task2HumanPyramid(float arr[SIZEOFPYRAMID][SIZEOFPYRAMID], int lvl, int pos)
{
    if(lvl == 5)
        return;
    if(lvl == 0)
        printf("%.2f", arr[0][0]);
    else {
        float weight;
        if(pos / 2 < lvl / 2)
            weight = arr[lvl][pos]+(arr[lvl-1][pos]/2) + (arr[lvl-1][pos-1]/2);
        else
            weight = arr[lvl][pos]+(arr[lvl-1][pos-1]/2) + (arr[lvl-1][pos]/2);
        arr[lvl][pos] = weight;
        printf("%.2f ", weight);
    }
    if(pos < lvl)
        task2HumanPyramid(arr, lvl, pos+1);
    printf("\n");
    task2HumanPyramid(arr, lvl+1, 0);
}
int task3ParenthesisValidator(char target) {
    //char c = getchar();
    char c = fgetc(stdin);
    if(c == '\n') {
        if(target == '\0')
            return 1;
        return 0;
    }
    switch(c) {
        case '(':
            return task3ParenthesisValidator(')') && task3ParenthesisValidator(target);
        case '{':
            return task3ParenthesisValidator('}') && task3ParenthesisValidator(target) ;
        case '[':
            return task3ParenthesisValidator(']') && task3ParenthesisValidator(target);
        case '<':
            return task3ParenthesisValidator('>') && task3ParenthesisValidator(target);

    }
    if(c == ')' || c == '}' || c == ']' || c == '>') {
        if(c == target)
            return 1;
        return 0;
    }
    return task3ParenthesisValidator(target);

}

void initializeArray(int array[], int size, int value, int index) {
    if (index >= size) {
        return;
    }
    array[index] = value;
    initializeArray(array, size, value, index + 1);
}

int task4QueensBattle(int squareSize, Board board, int column[squareSize], int row[squareSize],
                                int queens[NUM_OF_CHARS], int posRow, int posColumn, int numOfQueens)
{
    //check if the program passed the last line and return the value accordingly
    if(posRow == squareSize) {
        if (numOfQueens == squareSize) {
            printSolution(board, squareSize);
            return 1;
        }
        return 0;
    }
    //check if position is not out of bounds
    if(posColumn == squareSize)
        return task4QueensBattle(squareSize, board, column, row, queens, posRow+1, 0, numOfQueens);
    //check if a queen can be placed
    if(queens[board.grid[posRow][posColumn]] == 1 || column[posColumn] == 1 || row[posRow] == 1 ||
                                                    checkAround(board,squareSize, posRow, posColumn))
        return task4QueensBattle(squareSize, board, column, row, queens, posRow, posColumn+1, numOfQueens);

    //copy the board and place queen on the copied board then check if the solution is possible
    Board copy = board;
    queens[copy.grid[posRow][posColumn]] = 1;
    //mark the queens as null char so i can differentiate between the board char and the queen mark char
    copy.grid[posRow][posColumn] = '\0';
    column[posColumn] = 1;
    row[posRow] = 1;
    if(task4QueensBattle(squareSize, copy, column, row, queens, posRow, posColumn+1, numOfQueens+1))
        return 1;

    //solution was not possible on the copied board so revert the queen placement and go to the next square
    queens[board.grid[posRow][posColumn]] = 0;
    column[posColumn] = 0;
    row[posRow] = 0;
    return task4QueensBattle(squareSize, board, column, row, queens, posRow, posColumn+1, numOfQueens);
}
void printSolution(Board board, int squareSize) {
    for(int i = 0; i < squareSize; i++) {
        for(int j = 0; j < squareSize; j++) {
            if(board.grid[i][j] == '\0')
                printf("X ");
            else
                printf("* ");
        }
        printf("\n");
    }
}

//check if there is not a queen around
int checkAround(Board board, int squareSize, int posRow, int posColumn) {
    if((posRow>0&&posColumn>0&&board.grid[posRow-1][posColumn-1]=='\0')||
        (posColumn<squareSize-1&&posRow>0&&board.grid[posRow-1][posColumn+1]=='\0')||
        (posRow<squareSize-1&&posColumn>0&&board.grid[posRow+1][posColumn-1]=='\0')||
        (posRow<squareSize-1&&posColumn<squareSize-1&&board.grid[posRow+1][posColumn+1]=='\0'))
        return 1;
    return 0;
}
int task5CrosswordGenerator(int squareSize, Crossword crossword, int numOfSlots, Slot slots[numOfSlots], int numOfWords,
        char words[numOfWords][MAX_WORD_LENGTH], char dupWords[numOfWords][MAX_WORD_LENGTH],int posRow, int posColumn,
                                int numOfInsertedWords, int index)
{
    //check if the program passed the last line and if solution was found
    if(posRow == squareSize) {
        if(numOfInsertedWords == numOfSlots) {
        printf("YES\n");
            printCrosswordSolution(squareSize, crossword,numOfSlots, slots);
            return 1;
        }
        printf("NO\n");
        return 0;
    }
    //check if the program passed the last column so it can continue to the next row
    if(posColumn == squareSize)
        return task5CrosswordGenerator(squareSize, crossword,numOfSlots, slots, numOfWords, words, dupWords, posRow+1, 0,
                                                                numOfInsertedWords, 0);
    //check if the program reached the position of a slot
    if(posRow == slots[numOfInsertedWords].row && posColumn == slots[numOfInsertedWords].column) {
        if(strlen(words[index]) == slots[numOfInsertedWords].length) {
            Crossword copy = insertWord(crossword, words[index], posRow, posColumn, 0, strlen(words[index]),
                                                                                    slots[numOfInsertedWords].direction);
            //check for the signal if the word cannot fit
            if(copy.grid[0][0] == '*') {
                copy.grid[0][0] = crossword.grid[0][0];
                if(task5CrosswordGenerator(squareSize, crossword,numOfSlots, slots, numOfWords, dupWords, dupWords,posRow,
                                                             posColumn+1,numOfInsertedWords, index+1))
                    return 1;
            }
            strcpy(dupWords[index], "0");
            numOfInsertedWords++;
            if(numOfInsertedWords <= numOfSlots && slots[numOfInsertedWords].column == posColumn &&
                                                                slots[numOfInsertedWords].row == posRow)
                if(task5CrosswordGenerator(squareSize, copy, numOfSlots, slots, numOfWords, dupWords, dupWords, posRow, posColumn,
                                                                numOfInsertedWords, 0))
                    return 1;
            if(task5CrosswordGenerator(squareSize, copy,numOfSlots, slots, numOfWords, dupWords, dupWords,posRow, posColumn+1,
                                                                numOfInsertedWords, 0))
                return 1;
        }
        return task5CrosswordGenerator(squareSize, crossword,numOfSlots, slots, numOfWords, words, words,posRow, posColumn,
                                                                numOfInsertedWords, index+1);
    }
    return task5CrosswordGenerator(squareSize, crossword,numOfSlots, slots, numOfWords, words, words, posRow, posColumn+1,
                                                                numOfInsertedWords, 0);
}
//function that inserts a word into the board
Crossword insertWord(Crossword board, char word[MAX_WORD_LENGTH], int posRow, int posColumn, int index,
                                                    int wordLength, char direction) {
    if(index == wordLength)
        return board;
    if(board.grid[posRow][posColumn] != '$') {
        if(board.grid[posRow][posColumn] == word[index])
            board.grid[posRow][posColumn] = word[index];
        //if the slot is blocked by a letter send a signal that the word cannot fit
        else {
            board.grid[0][0] = '*';
            return board;
        }
    }
    board.grid[posRow][posColumn] = word[index];

    if(direction == 'H')
        return insertWord(board, word, posRow, posColumn+1, index+1, wordLength, direction);
    return insertWord(board, word, posRow+1, posColumn, index+1, wordLength, direction);
}
Crossword generateEmptyCrossword(int squareSize, Crossword board, int numOfSlots, Slot slots[numOfSlots],
                                       int posRow, int posColumn,int numOfInsertedSlots, int index, char direction) {
    if(direction == 'V' && posColumn == squareSize) {
        return board;
    }
    if(direction == 'H') {
        if(posRow == squareSize)
            return generateEmptyCrossword(squareSize, board, numOfSlots, slots, 0,0,numOfInsertedSlots,0,'V');
        if(posColumn == squareSize)
            return generateEmptyCrossword(squareSize, board, numOfSlots, slots, posRow+1, 0,numOfInsertedSlots, 0, 'H');
        if(index > 0) {
            board.grid[posRow][posColumn] = '$';
            return generateEmptyCrossword(squareSize, board, numOfSlots, slots, posRow, posColumn+1,numOfInsertedSlots,
                                                                                        index-1, 'H');
        }
        if(posRow == slots[numOfInsertedSlots].row && posColumn == slots[numOfInsertedSlots].column &&
                                                            slots[numOfInsertedSlots].direction == 'H') {
            board.grid[posRow][posColumn] = '$';
            numOfInsertedSlots++;
            return generateEmptyCrossword(squareSize, board, numOfSlots, slots, posRow, posColumn+1,numOfInsertedSlots,
                                                                    slots[numOfInsertedSlots-1].length-1, 'H');
        }
        board.grid[posRow][posColumn] = '#';
        return generateEmptyCrossword(squareSize, board, numOfSlots, slots, posRow, posColumn+1,numOfInsertedSlots, 0, 'H');
    }

    if(posRow == squareSize)
        return generateEmptyCrossword(squareSize, board, numOfSlots, slots, 0, posColumn+1,numOfInsertedSlots, 0, 'V');
    if(index > 0) {
        board.grid[posRow][posColumn] = '$';
        return generateEmptyCrossword(squareSize, board, numOfSlots, slots, posRow+1, posColumn,numOfInsertedSlots,
                                                                                    index-1, 'V');
    }
    if(posRow == slots[numOfInsertedSlots].row && posColumn == slots[numOfInsertedSlots].column &&
                                            slots[numOfInsertedSlots].direction == 'V') {
        board.grid[posRow][posColumn] = '$';
        numOfInsertedSlots++;
        return generateEmptyCrossword(squareSize, board, numOfSlots, slots, posRow+1, posColumn,numOfInsertedSlots,
                                                                         slots[numOfInsertedSlots-1].length-1, 'V');
    }
    if(board.grid[posRow][posColumn] != '$')
        board.grid[posRow][posColumn] = '#';
    return generateEmptyCrossword(squareSize, board, numOfSlots, slots, posRow+1, posColumn,numOfInsertedSlots, 0, 'V');
}
void organizeSlots(int numOfSlots, Slot slots[numOfSlots], int index) {
    if (index >= numOfSlots - 1)
        return;

    // Compare current slot with next slot
    if ((slots[index].direction == 'V' && slots[index + 1].direction == 'H') ||
        (slots[index].direction == slots[index + 1].direction &&
         ((slots[index].direction == 'H' && slots[index].row > slots[index + 1].row) ||
          (slots[index].direction == 'V' && slots[index].column > slots[index + 1].column)))) {

        swapSlots(numOfSlots, slots, index, index + 1);

        if (index > 0) {
            organizeSlots(numOfSlots, slots, index - 1);
            return;
        }
          }

    // Move to next position
    organizeSlots(numOfSlots, slots, index + 1);
}
/*void organizeSlots(int numOfSlots, Slot slots[numOfSlots], int index) {
    if (index >= numOfSlots - 1)
        return;
    // Compare current slot with next slot
    if ((slots[index].direction == 'V' && slots[index + 1].direction == 'H') ||

        (slots[index].direction == slots[index + 1].direction &&
         (slots[index].row > slots[index + 1].row ||
          (slots[index].row == slots[index + 1].row &&
           slots[index].column > slots[index + 1].column)))) {
        swapSlots(numOfSlots, slots, index, index + 1);
        if (index >= 0) {
            organizeSlots(numOfSlots, slots, index - 1);
            return;
        }
    }
    // Move to next position
    organizeSlots(numOfSlots, slots, index + 1);
}*/
void organizeSlotsByIndex(int numOfSlots, Slot slots[], int index) {
    if (index >= numOfSlots - 1)
        return;

    if ((slots[index].row > slots[index + 1].row) ||
        (slots[index].row == slots[index + 1].row && slots[index].column > slots[index + 1].column)) {
        swapSlots(numOfSlots, slots, index, index + 1);
        if (index >= 0) {
            organizeSlotsByIndex(numOfSlots, slots, index - 1);
            return;
        }
        }

    organizeSlotsByIndex(numOfSlots, slots, index + 1);
}
//function to swap the places of 2 slots
void swapSlots(int numOfSlots, Slot slots[numOfSlots], int i, int j) {
    Slot temp = slots[i];
    slots[i] = slots[j];
    slots[j] = temp;
}
void printCrosswordSolution(int squareSize, Crossword solution,int numOfSlots, Slot slots[numOfSlots]) {
    for(int i = 0; i < squareSize; i++) {
        printf("| ");
        for(int j = 0; j < squareSize; j++) {
            printf("%c ", solution.grid[i][j]);
        }
        printf("|\n");
    }
}
void duplicateWords(int numOfWords, char words[numOfWords][MAX_WORD_LENGTH], char dupWords[numOfWords][MAX_WORD_LENGTH], int index) {
    if(index == numOfWords)
        return;
    strcpy(dupWords[index], words[index]);
    duplicateWords(numOfWords, words, dupWords, index+1);
}