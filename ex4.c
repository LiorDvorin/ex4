/******************
Name: Lior Dvorin
ID: 215823469
Assignment: EX4
*******************/
#include <stdio.h>

#define SIZEOFPYRAMID 5
#define PARENTHESES 4
#define NUM_OF_CHARS 128
#define MAX_BOARD_SIZE 20

typedef struct {
    char grid[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
} Board;

int task1RobotPaths();
void task2HumanPyramid();
int task3ParenthesisValidator(char target);
void initializeArray(int array[], int size, int value, int index);
int task4QueensBattle(int squareSize, Board board, int column[squareSize], int row[squareSize],
                                int queens[NUM_OF_CHARS], int posRow, int posColumn, int numOfQueens);
void printSolution(Board board, int squareSize);
int checkAround(Board board, int squareSize, int posRow, int posColumn);
void task5CrosswordGenerator();


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
                int column[squareSize], row[squareSize];
                int queens[NUM_OF_CHARS];
                initializeArray(column, squareSize, 0, 0);
                initializeArray(row, squareSize, 0, 0);
                initializeArray(queens, NUM_OF_CHARS, 0, 0);
                if(!task4QueensBattle(squareSize, board, column, row, queens, 0, 0, 0))
                    printf("This puzzle cannot be solved. \n");
                break;
            }
            case 5: {
                task5CrosswordGenerator();
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
void task5CrosswordGenerator()
{

}