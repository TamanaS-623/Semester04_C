#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ROW_SIZE 9
#define COLUMN_SIZE 9
#define MAX 9
#define MIN 1
#define USER_INPUT_ROW_NO 2

void displayArray(int arr[][COLUMN_SIZE]);
int check(int arr[][9], int num, int rowNo, int colNo);
void randomNumGenerator();


void searchArray(int arr[][9]);

void getUserInput();

int main() {
    srand(time(NULL));

    //randomNumGenerator();



//    int arr[ROW_SIZE][COLUMN_SIZE] =
//                                    {{5,3,4,6,7,8,9,1,2},
//                                    {6,7,2,1,9,5,3,4,8},
//                                    {1,9,8,3,4,2,5,6,7},
//                                    {8,5,9,7,6,1,4,2,3},
//                                    {4,2,6,8,5,3,7,9,1},
//                                    {7,1,3,9,2,4,8,5,6},
//                                    {9,6,1,5,3,7,2,8,4},
//                                    {2,8,7,4,1,9,6,3,5},
//                                    {3,4,5,2,8,6,1,7,9}};
//    displayArray(arr) ;
//    searchArray(arr);


    getUserInput();

    return 0;
}
//take row 1 and row 2
void getUserInput() {
    char charArr[80];
    int inputArr[ROW_SIZE][COLUMN_SIZE];
    int count = 0;
    int duplicate;
    int flag = 1;

    printf("\n\n******************** Rules of the game ********************\n");
    printf("-You are asked to enter first 2 row of Sudoku grid\n" );


    for(int x = 0 ; x < USER_INPUT_ROW_NO ; x++) {

        while ((count == 9) || (flag == 1)) {
            flag = 1;
            printf("\n1. You must enter exactly nine distinct digits between (1 - 9)");
            printf("\n2. Use Space/Tab key to enter the next values");
            printf("\n3. Press 'Return' key after entering nine digits");
            printf("\nEnter row %d of your Sudoku grid:\n", x+1);

            fgets(charArr, sizeof(charArr), stdin);
            count = sscanf(charArr, "%d%d%d%d%d%d%d%d%d", &inputArr[x][0], &inputArr[x][1], &inputArr[x][2], &inputArr[x][3],
                           &inputArr[x][4], &inputArr[x][5], &inputArr[x][6], &inputArr[x][7], &inputArr[x][8]);

            if (count < 9) {
                printf("\nPlease enter Exacly nine digits. You have entered %d digits. ", count);
                continue;
            }


                for (int i = 0; (i < count) && (flag != 0); i++) {
                    duplicate = inputArr[x][i];
                    for (int j = i + 1; j < count; j++) {
                        if (duplicate == inputArr[x][j]) {
                            printf("\nEnter nine distinct integers, No duplicates please");
                            flag = 0;
                            break;
                        }
                    }

            }
            for (int i = 0; (i < count) && (flag != 0); i++) {
                if (((inputArr[x][i] < 1) || (inputArr[x][i] > 9)) && (flag == 1)) {
                    printf("\nOne or more entries are outside the range (1 -9)!");
                    flag = 0;
                    break;
                }
            }
            if (count == 9 && flag == 1)
                break;
        }
    }

    for (int k = 0; k < USER_INPUT_ROW_NO; ++k) {
        for (int i = 0; i < COLUMN_SIZE; ++i) {
            printf("%d  ", inputArr[k][i]);
        }
        printf("\n");
    }
}


void displayArray(int arr[][COLUMN_SIZE]){
    for(int i = 0 ; i < ROW_SIZE ; i++){
        for(int j = 0 ; j < COLUMN_SIZE ; j++){
            printf("%d   ", arr[i][j]);
        }
        puts("");
    }
    puts("");
}

void searchArray(int arr[][COLUMN_SIZE]) {
    int result = 1;
    for (int i = 0; i < 9 ; ++i) {
        for (int j = 0; j < 9 ; ++j) {
            if (!(check(arr, arr[i][j], i, j))){
                result = 0;
                break;
            }
        }
        if(result == 0) break;
    }
    if(result == 1)
        printf("Given Sudoku grid is valid");
    else
        printf("Given Sudoku grid is invalid");
}


int check(int arr[][COLUMN_SIZE], int num, int rowNo, int colNo){
    int result = 1;

    for(int i = rowNo ; i < 1 ; i++){
        for(int j = 0 ; j < COLUMN_SIZE ; j++){
            if(j == colNo){
                continue;
            }
            if(arr[i][j] == num){
                result = 0;
                break;
            }
        }
    }

    for(int i = 0 ; i < ROW_SIZE ; i++){
        if( i == rowNo ){
            continue;
        }
        for(int j = colNo ; j < 1 ; j++){
            if(arr[i][j] == num){
                result = 0;
                break;
            }
        }
    }
    return result;
}



void randomNumGenerator(){
    int intArr[COLUMN_SIZE]={0};
    int randNum;
    int flag;
    int count = 0;

    while(count < COLUMN_SIZE){
        flag = 1;
        randNum = rand() % ((MAX-MIN)+MIN) + MIN;
        for(int i = 0 ; i <= count ; i++){
            if(intArr[i] == randNum){
                flag = 0;
                break;
            }
        }
        if(flag){
            intArr[count] = randNum;
            count++;
        }
    }
    for(int i = 0 ; i < sizeof(intArr)/sizeof(intArr[0]) ; i++){
        printf("\n%d", intArr[i]);
    }

}