/******************
Name: Lior Dvorin
ID: 215823469
Assignment: EX4
*******************/
#include <stdio.h>

int task1RobotPaths();
void task2HumanPyramid();
int task3ParenthesisValidator(char target);
void task4QueensBattle(char grid[][], int squareSize);
void task5CrosswordGenerator();

#define SIZEOFPYRAMID 5
#define PARENTHESES 4

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
                char grid[squareSize][squareSize];
                for(int i = 0; i < squareSize; i++)
                    for(int j = 0; j < squareSize; j++)
                        scanf("%c", &grid[i][j]);
                task4QueensBattle(grid, squareSize);
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
    char c = getchar();
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
/*int tsk3(int Parentheses[], char lastP) {
    char c = getchar();
    if(c == '\n')
        return Parentheses[0] == 0 && Parentheses[1] == 0 && Parentheses[2] == 0 && Parentheses[3] == 0;
    switch(c) {
        case ')': {
            if(Parentheses[0] > 0) {
                Parentheses[0]--;
                return tsk3(Parentheses, lastP);
            }
            return 0;
        }
        case '}': {
            if(Parentheses[1] > 0) {
                Parentheses[1]--;
                return tsk3(Parentheses, lastP);
            }
            return 0;
        }
        case ']': {
            if(Parentheses[2] > 0) {
                Parentheses[2]--;
                return tsk3(Parentheses, lastP);
            }
            return 0;
        }
        case '>': {
            if(Parentheses[3] > 0) {
                Parentheses[3]--;
                return tsk3(Parentheses, lastP);
            }
            return 0;
        }
    }


    switch (c) {
        case '(': {
            Parentheses[0]++;
            return tsk3(Parentheses, c);
        }
        case'{': {
            Parentheses[1]++;
            return tsk3(Parentheses, c);
        }
        case'[': {
            Parentheses[2]++;
            return tsk3(Parentheses, c);
        }
        case'<': {
            Parentheses[3]++;
            return tsk3(Parentheses, c);
        }
        default:
            return tsk3(Parentheses, lastP);
    }
}
void task3ParenthesisValidator(int Parentheses[], char lastP)
{
    char c = getchar();
    if(c == '\n') {
        printf("%d\n",Parentheses[0]);
        printf("%d\n",Parentheses[1]);
        printf("%d\n",Parentheses[2]);
        printf("%d\n",Parentheses[3]);

        if(Parentheses[0] == 0 && Parentheses[1] == 0 && Parentheses[2] == 0 && Parentheses[3] == 0)
            printf("The parentheses are balanced correctly. \n");
        else
            printf("The parentheses are not balanced correctly. \n");
        return;
    }
    switch (lastP){
        case '(': {
            if(c == ')')
                Parentheses[0]--;
            if(c == '}' || c == ']' || c == '>') {
                printf("The parentheses are not balanced correctly. \n");
                return;
            }
            break;
        }
        case'{': {
            if(c == '}')
                Parentheses[1]--;
            if(c == ')' || c == ']' || c == '>') {
                printf("The parentheses are not balanced correctly. \n");
                return;
            }
            break;
        }
        case'[': {
            if(c == ']')
                Parentheses[2]--;
            if(c == ')' || c == '}' || c == '>') {
                printf("The parentheses are not balanced correctly. \n");
                return;
            }
            break;
        }
        case'<': {
            if(c == '>')
                Parentheses[3]--;
            if(c == ')' || c == '}' || c == ']') {
                printf("The parentheses are not balanced correctly. \n");
                return;
            }
            break;
        }
        default: break;
    }
    switch (c) {
        case '(': {
            Parentheses[0]++;
            lastP = c;
            break;
        }
        case'{': {
            Parentheses[1]++;
            lastP = c;
            break;
        }
        case'[': {
            Parentheses[2]++;
            lastP = c;
            break;
        }
        case'<': {
            Parentheses[3]++;
            lastP = c;
            break;
        }
        default: break;
    }
    task3ParenthesisValidator(Parentheses, lastP);
}*/

void task4QueensBattle(char grid[][], int squareSize);
{

}

void task5CrosswordGenerator()
{

}