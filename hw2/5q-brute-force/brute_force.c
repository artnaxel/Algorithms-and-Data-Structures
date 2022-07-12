/*
 * Aleksandra Kondratjeva
 *
 * Išdėstyti šachmatų lentoje 5 karalienes, kad kiekvienas langelis būtų kontroliuojamas bent vienos iš jų.
*/
#include <stdio.h>
#include <time.h>
//
#define LENGTH 8 //board length
#define QCELL 64 //quantity of cells
//
int board[LENGTH + 1][LENGTH + 1]; ///2d array for board
int a[QCELL + 1]; ///array for cells
//
int qZero = 0; //counters for zeros
//
void printSolution();
//
void bruteForce();
//
int main (){
    clock_t startTime, endTime;
    
    startTime = clock();
    bruteForce();
    printSolution();
    endTime = clock();

    double time_ = (double) (endTime - startTime) / CLOCKS_PER_SEC;
    printf("\nTime: %f", time_);
    return 0;   
}

/*BRUTE FORCE ALGORITHM*/
void bruteForce(){

    //q1, q2, q3, q4, q5 - counters for queens' positions
    for (int q1 = 1; q1 <= QCELL - 4; q1++){
        for (int q2 = q1 + 1; q2 <= QCELL - 3; q2++){
            for (int q3 = q2 + 1; q3<=QCELL - 2; q3++ ){
                for (int q4 = q3 + 1; q4 <= QCELL - 1; q4++ ){
                    for (int q5 = q4 + 1; q5 <= QCELL; q5++ ){
                        for (int l = 1; l <= QCELL; l++ ){
                            a[l]=0; // set zeros, 0 - cell isn't under attack
                        }

    //queens are placed in sequence
    a[q1] = 2; // cell with the first queen
    a[q2] = 2; //cell with the second queen
    a[q3] = 2; //cell with the third queen
    a[q4] = 2; //cell with the fourth queen
    a[q5] = 2; //cell with the fifth queen

    int k = 1;

    //save the value of a[] in the f[][] (set the sequence of queens to the board)
    for (int i = 1; i <= LENGTH; i++ )
        for (int j = 1; j <= LENGTH; j++ ){
            board[i][j] = a[k];
            k++;
        }
        
        for (int i = 1; i <= LENGTH; i++ ){
            for (int j = 1; j <= LENGTH; j++ ){
                if (board[i][j] == 2){ //if there's a queen in the cell{
                    for (int m = 1; m <= LENGTH ; m++)
                        if (board[i][m] != 2 )
                            board[i][m] = 1; //set row to 1 (the row is under queen's attack)
                    for (int m = 1; m <= LENGTH ; m++ )
                        if (board[m][j] != 2 )
                        board[m][j] = 1; //set column to 1 (the column is under queen's attack)

                    //set main diagonal to 1 (to the right and to the left)
                    for (int m = 1; m <= LENGTH; m++ )
                        if ( board[i + m][j + m] != 2 )
                            if ((i + m <= LENGTH) && (j + m <= LENGTH))
                                board[i + m][j + m] = 1;

                    for (int m = 1; m  <= LENGTH; m++ )
                        if ( board[i - m][j - m] != 2 )
                            if ( (i - m >= 1) && (j - m >= 1) )
                                board[i - m][j - m] = 1;

                    //set secondary diagonal to 1 (to right and to left)
                    for (int m = 1; m <= LENGTH; m++)
                        if ( board[i - m][j + m] != 2 )
                            if ((i - m >= 1) && (j + m <= LENGTH ) )
                                board[i - m][j + m] = 1;

                    for (int m = 1; m <= LENGTH; m++)
                        if ( board[i + m][j - m] != 2 )
                            if ((i + m <= LENGTH) && (j - m >= 1))
                                board[i + m][j - m] = 1;
                }
            }
        }
        qZero = 0;
        //searching for 0 (cells that aren't under attack)
        for (int i = 1; i <= LENGTH; i++ )
            for (int j = 1; j <= LENGTH; j++ ){
                if (board[i][j] == 0 )
                qZero++;
            }
        if (qZero == 0){
            return;
        }
                    }
                }
            }
        }
    }
}

/*PRINTING SOLUTION*/
void printSolution(){
    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9 ; j++){
            if(board[i][j] == 2){
                printf(" Q ");
            }
            else{
                printf(" %d ", board[i][j]);
            }
        }
    printf("\n");
    }
}