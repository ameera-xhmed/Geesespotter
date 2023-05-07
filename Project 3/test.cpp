#include <iostream>
#include "geesespotter_lib.h"

char *createBoard(std::size_t xdim, std::size_t ydim){ //Function 1
    char *array{ new char[xdim*ydim]};
    for(int i{0}; i < (xdim*ydim); i++){
        array[i] = 0;
    }
    return array;
}

void cleanBoard(char *board){ //Function 2
    delete [] board;
    board = nullptr;
}

void printBoard(char *board, std::size_t xdim, std::size_t ydim){ //Function 3
    int shifthidden = (1 << 5);
    int shiftmark = (1 << 4);

    for (int m{0}; m < ydim; m++){
        for(int i{0}; i < xdim; i++){
            //if hidden * 
            if( (board[i] & shifthidden) == board[i] ){
                std::cout << "*";
            }

            //if marked M
            else if( (board[i] & shiftmark) == board[i] ){ 
                std::cout << "M";
            }

            //if revealed print value
            else{  
                std::cout << board[i];
            }
        }
        std::cout << "\n";
    }
}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim){//Function 5
    int shift = (1 << 5);
    char *temparray{ new char[xdim*ydim]};
    for(int i{0}; i < (xdim*ydim); i++){
        temparray[i] = board[i];
    }
    for(int i{0}; i < (xdim*ydim); i++){
        temparray[i] ^= shift;
        board[i] = temparray[i];
    }
}
int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){//Function 7
    int shift = (1 << 4);
    char *temparray{ new char[xdim*ydim]};
    for(int i{0}; i < (xdim*ydim); i++){
        temparray[i] = board[i];
    }
    for(int i{0}; i < (xdim*ydim); i++){
        temparray[i] ^= shift;
        board[i] = temparray[i];
    }

    return 0;
}


void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim){//Function 4
}
bool isGameWon(char *board, std::size_t xdim, std::size_t ydim){//Function 8
    return 0;
}
int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){//Function 6
    return 0;
}

//g++ -o main .\test.cpp .\geesespotter_lib.cpp -std=c++11
//.\main.exe