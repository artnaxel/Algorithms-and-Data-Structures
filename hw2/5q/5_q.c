/*
 * Aleksandra Kondratjeva
 *
 *Išdėstyti šachmatų lentoje 5 karalienes, kad kiekvienas langelis būtų kontroliuojamas bent vienos iš jų.
*/
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define LENGTH 8 //board length

#define kMAX 5

int k = 0; //queen counter

int board[LENGTH][LENGTH] = {0}; //initializing the board

bool checkBoard(int x, int y);

void setQueen(int x, int y);

void removeQueen(int x, int y);

void printSolution();

int main(){
	clock_t startTime, endTime;

	startTime = clock();
	checkBoard(0, 0);
	printSolution();
	endTime = clock();

	double time_ = (double) (endTime - startTime) / CLOCKS_PER_SEC;
	printf("\nTime: %f\n", time_);
	return 0;
}

/*SEARCHING FOR THE EMPTY CELLS*/
bool checkBoard(int x, int y){

	setQueen(x, y);

	if (k == kMAX){
		for(int i = 0; i < LENGTH; i++){
            for(int j = 0; j < LENGTH; j++){
                if (board[i][j] == 0){	
				    removeQueen(x, y);
					return false;
				}
			}
		}
		return true;
	}
	else{				
		for(int i = 0; i < LENGTH; i++){
			for(int j = 0; j < LENGTH; j++){
				if(board[i][j] == 0){ //checking on the empty cell
					if(checkBoard(i, j)) //recursion
						return true;
				}
			}
		}
	 removeQueen(x, y);
		return false;
					
	}
}

/*SETTING THE QUEEN*/
void setQueen(int x, int y){ 
	k++;
	board[x][y] = -1;
	for(int i = 0; i < LENGTH; i++){

        //SETTING THE ROW AND THE COLUMN
		if (board[i][y] != -1)
            board[i][y]++;
		if (board[x][i] != -1)
            board[x][i]++;

        //SETTING DIAGONALS    
		int z = y - x + i;
		if((z >= 0) && (z < LENGTH))
            if(board[i][z] != -1)
                board[i][z]++;

		int l = y + x - i;         
		if((l >= 0) && (l < LENGTH))
            if(board[i][l] != -1)
                board[i][l]++;

		    }
}

/*REMOVING THE QUEEN*/
void removeQueen( int x, int y){
	board[x][y] = 0;
    k--;
	for(int i = 0; i < LENGTH; i++)
		for(int j = 0; j < LENGTH; j++){
			if ((board[i][y] != -1) && (board[i][j] != 0))
                board[i][y]--;
                    
			if ((board[x][i] != -1) && (board[i][j] != 0))
                board[x][i]--;

			int z = y - x + i;

			if((z >= 0) && (z < LENGTH))
                if((board[i][z]!=-1) && (board[i][j] != 0))
                    board[i][z]--;

			int l = y + x - i;    

			if((l >= 0) && (l < LENGTH))
                if((board[i][l]!=-1) && (board[i][j] != 0))
                    board[i][l]--;

		}
}


/* PRINTING SOLUTION */
void printSolution(){
	for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH ; j++){
			if (board[i][j] == -1){
				printf(" Q ");
			}
			else{
				printf(" %d ", board[i][j]);
			}
		}
        printf("\n");
	}
    
}

