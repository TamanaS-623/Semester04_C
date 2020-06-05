#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ROW_SIZE 9
#define COLUMN_SIZE 9
#define MAX 9
#define MIN 1
#define USER_INPUT_ROW_NO 2

void printArray(int arr[][COLUMN_SIZE]);
void generateRandomNun(int inputArr[][COLUMN_SIZE]);

int validateSudokuGrid(int arr[][COLUMN_SIZE], int temp, int rowNo, int colNo);
void searchArray(int arr[][COLUMN_SIZE]);
int checkGridNo(int temp);
void getUserInput();

int main() {
    srand(time(NULL));

    int arr[ROW_SIZE][COLUMN_SIZE] =
                                    {{5,3,4,6,7,8,9,1,2},
                                    {6,7,2,1,9,5,3,4,8},
                                    {1,9,8,3,4,2,5,6,7},
                                    {8,5,9,7,6,1,4,2,3},
                                    {4,2,6,8,5,3,7,9,1},
                                    {7,1,3,9,2,4,8,5,6},
                                    {9,6,1,5,3,7,2,8,4},
                                    {2,8,7,4,1,9,6,3,5},
                                    {3,4,5,2,8,6,1,7,9}};
    printArray(arr) ;
    searchArray(arr);
    getUserInput();

    return 0;
}

void getUserInput() {
    char charArr[80];
    int inputArr[ROW_SIZE][COLUMN_SIZE]={0};
    int count = 0;
    int duplicate;
    int flag = 1;

    printf("\n\n******************** RULES OF THE GAME ********************\n");
    printf("You have to enter first 2 rows of Sudoku grid by following below guidlines\n" );

    for(int x = 0 ; x < USER_INPUT_ROW_NO ; x++) {
        while ((count == 9) || (flag == 1)) {
            flag = 1;
            printf("\n1. You must enter exactly ""nine distinct"" digits between (1 - 9)");
            printf("\n2. Use Space/Tab key to enter the next values");
            printf("\n3. Press 'Return' key after entering nine digits");
            printf("\nEnter row %d of your Sudoku grid:\n", x+1);

            fgets(charArr, sizeof(charArr), stdin);
            count = sscanf(charArr, "%d%d%d%d%d%d%d%d%d", &inputArr[x][0], &inputArr[x][1], &inputArr[x][2], &inputArr[x][3],
                           &inputArr[x][4], &inputArr[x][5], &inputArr[x][6], &inputArr[x][7], &inputArr[x][8]);

            if (count < 9) {
                printf("\nOops! only %d digits? Please enter exactly nine digits.", count);
                continue;
            }

            for (int i = 0; (i < count) && (flag != 0); i++) {
                duplicate = inputArr[x][i];
                for (int j = i + 1; j < count; j++) {
                    if (inputArr[x][j] == duplicate) {
                        printf("\nOops! No duplicates please! Enter nine distinct integers.");
                        flag = 0;
                        break;
                    }
                }
            }

            for (int i = 0; (i < count) && (flag != 0); i++) {
                if (((inputArr[x][i] < 1) || (inputArr[x][i] > 9))) {
                    printf("\nOops! One or more entries are outside the range (1 -9)!");
                    flag = 0;
                    break;
                }
            }
            if (count == 9 && flag == 1)
                break;
        }
    }

    generateRandomNun(inputArr);
}


void generateRandomNun(int inputArr[][COLUMN_SIZE]){
    int randNum;
    int flag;

    for (int i = 2; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int intArr[COLUMN_SIZE] = {0};
            int count = 0;

            while(count < COLUMN_SIZE){
                flag = 1;
                randNum = rand() % ((MAX-MIN)+MIN) + MIN;
                for(int k = 0 ; k <= count ; k++){
                    if(intArr[k] == randNum){
                        flag = 0;
                        break;
                    }
                }
                if(flag){
                    intArr[count] = randNum;
                    inputArr[i][j] = randNum;
                    count++;
                }
            }
        }
    }

    printArray(inputArr);
    searchArray(inputArr);
}

void searchArray(int arr[][COLUMN_SIZE]) {
    int result = 1;
    for (int i = 0; i < 9 ; ++i) {
        for (int j = 0; j < 9 ; ++j) {
            if (!(validateSudokuGrid(arr, arr[i][j], i, j))){
                result = 0;
                break;
            }
        }
        if(result == 0) break;
    }
    if(result == 1)
        printf("\nPerfect! Given Sudoku grid is valid.");
    else
        printf("\nSorry! Given Sudoku grid is invalid.");
}


int validateSudokuGrid(int arr[][COLUMN_SIZE], int temp, int rowNo, int colNo){
    for(int i = rowNo ; i < 1 ; i++){
        for(int j = 0 ; j < COLUMN_SIZE ; j++){
            if(j == colNo){
                continue;
            }
            if(arr[i][j] == temp){
                return 0;
            }
        }
    }

    for(int i = 0 ; i < ROW_SIZE ; i++){
        if( i == rowNo ){
            continue;
        }
        for(int j = colNo ; j < 1 ; j++){
            if(arr[i][j] == temp){
                return 0;
            }
        }
    }

    int rowStart = checkGridNo(rowNo);
    int colStart = checkGridNo(colNo);

    for (int i = rowStart ; i < 3 ; i++) {
        for (int j = colStart ; j < 3 ; j++) {
            if(i==rowNo && j==colNo){
                continue;
            }
            if(arr[i][j] == temp){
                return 0;
            }
        }
    }
    return 1;
}


void printArray(int arr[][COLUMN_SIZE]){
    puts("");
    for(int i = 0 ; i < ROW_SIZE ; i++){
        for(int j = 0 ; j < COLUMN_SIZE ; j++){
            printf("%d  ", arr[i][j]);
        }
        puts("");
    }
}

int checkGridNo(int temp){
    for(int i=1 ; i <= 2 ; i++){
        if(temp == 0 || temp == 1 || temp == 2){
            return 0;
        }
        if(temp == 3 || temp == 4 || temp == 5) {
            return 3;
        }
        if(temp == 6 || temp == 7 || temp == 8) {
            return 6;
        }
    }
}

//int squreCheck(int arr[][COLUMN_SIZE], int temp, int row, int col){
//    int rowStart = checkGridNo(row);
//    int colStart = checkGridNo(col);
//
//    for (int i = rowStart ; i < 3 ; i++) {
//        for (int j = colStart ; j < 3 ; j++) {
//            if(i==row && j==col){
//                continue;
//            }
//            if(arr[i][j] == temp){
//                return 0;
//            }
//        }
//    }
//    return 1;
//}
