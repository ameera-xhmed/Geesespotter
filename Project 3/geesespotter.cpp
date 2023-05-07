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
void display6Bits(char c);
void display6Bits(char c) {
   std::cout << " ["; // leading space -helps readability
   for (char mask{0b100000}; mask > 0; mask = mask >> 1) {
     std::cout << ((mask & c) != 0); // 1 if non zero
   }
   std::cout << "] "; // trailing space -helps readability
}

void printBoard(char *board, std::size_t xdim, std::size_t ydim){ //Function 3
    char shifthidden = (1 << 5);
    char shiftmark = (1 << 4);

    for (int m{0}; m < ydim; m++){
        for(int i{0}; i < xdim; i++){
            //if marked M 
            std::size_t arrayindex{m*xdim + i};

            if( (board[arrayindex] & shiftmark) == shiftmark ){
                std::cout << "M";
            }
            //if hidden *
            else if( (board[arrayindex] & shifthidden) == shifthidden ){ 
                std::cout << "*";
            }
            //if revealed print value
            else{  
                std::cout << (board[arrayindex] & valueMask());
            }
            //display6Bits(board[arrayindex]);
        }
        std::cout << '\n';
    }
}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim){//Function 5
    char shift = (1 << 5);
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
    char shifthidden = (1 << 5);
    char shiftmark = (1 << 4);

    std::size_t i{yloc * xdim + xloc};

    if((board[i] & shifthidden) == 0){
        return 2;
    }
    else{
        board[i] ^= shiftmark;
        return 0;
    }      
}

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim){//Function 4
    char *temparray{ new char[xdim*ydim]};
    for(int s{0}; s < (xdim*ydim); s++){
        temparray[s] = board[s];
    }
    
    for(int i{0}; i < (ydim*xdim); i++){
        if((board[i] & valueMask()) == 9){ //if there is goose
            int x{}; int y{};
            x = (i % xdim); 
            y = (i / xdim); 

            if( ((x+1) < xdim) && (board[i+1] != 9 )){ //right of goose
                temparray[i+1] ++;
            }
            if( ((x-1) >= 0) && (board[i-1] !=9)){ //left of goose
                temparray[i-1] ++;
            }
            if (((y-xdim) >= 0) && (board[i-xdim] != 9)){ //top of goose
                temparray[i-xdim] ++;
            }
            if( ((y+1 < ydim)) && (board[i+xdim]!= 9)){ //bottom of goose
                temparray[i+xdim] ++;
            }
            if(((x-1) >= 0) && ((y+1) < ydim) && (board[i+(xdim-1)] != 9)){ //bottom left corner of goose
                temparray[i+(xdim-1)] ++;
            }
            if(((x+1) < xdim) && ((y+1) < ydim) && (board[i+(xdim+1)] != 9)){ //bottom right corner of goose
                temparray[i+(xdim+1)] ++;
            }
            if(((x-1) >= 0) && ((y-ydim) >= 0) && (board[i-(xdim+1)] != 9)){ //top left corner of goose
                temparray[i-(xdim+1)] ++;
            }
            if(((x+1) < xdim) && ((y-xdim) >= 0) && (board[i-(xdim-1)] != 9)){ //top right corner of goose
                temparray[i-(xdim-1)] ++; 
            } 
        }    
    }

    for(int m{0}; m < (xdim*ydim); m++){
        board[m] = temparray[m]; //set original board back
    } 
}

bool isGameWon(char *board, std::size_t xdim, std::size_t ydim){//Function 8
    int feildcounter{0};
    char shifthidden = (1 << 5);
    int geese{0};
  
    for(int i{0}; i < (xdim*ydim); i++){ 
        if((board[i] & valueMask()) == 9){
             geese += 1; //counting number of geese there were in the field
        }
    }

    for(int i=0; i < (xdim*ydim); i++){
        if( ((board[i] & shifthidden) != shifthidden) && ((board[i] & valueMask()) != 9) ){ //if feilds other than goose feild have been revealed
            feildcounter += 1;
        }
    }

    if(feildcounter == ((xdim*ydim)-geese)){
        return 1; //game wons
    }
    else{
        return 0; //game lost
    }
}

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){//Function 6  
    char shifthidden = (1 << 5);
    char shiftmark = (1 << 4);

    std::size_t i{yloc * xdim + xloc};

    int x{}; int y{};
    x = xloc;
    y = yloc;
  
    char *temparray{ new char[xdim*ydim]}; //temp array to store board values
    for(int s{0}; s < (xdim*ydim); s++){
        temparray[s] = board[s];
    }

    if((board[i] & valueMask()) == 9){ //if revealed field has goose
        return 9;
    }

    else if ((board[i] & shiftmark) == shiftmark){ //if feild is marked
        return 1;
    }
        
    else if((board[i] & shifthidden) != shifthidden) { //if feild is unhidden and unmarked (already revealed)
        return 2;       
    }

    else{ //if feild is hidden and unmarked then reveal
        temparray[i] ^= shifthidden; //reveal selected feild
            
        if ((board[i] & valueMask()) == 0){ //if revealed feild is 0 then reveal feilds around it 
            
            if(((x+1) < xdim)){ //right of the feild; check if right of feild is not a goose
                if((board[i+1] & shifthidden) == shifthidden){ //check if neighbour is hidden before revealing
                    temparray[i+1] ^= shifthidden;
                }
            }

            if(((x-1) >= 0)){ //left of the feild
                if((board[i-1] & shifthidden) == shifthidden){
                    temparray[i-1] ^= shifthidden;
                }
            }

            if(((y-xdim) >= 0)){ //top of the feild
                if((board[i-xdim] & shifthidden) == shifthidden){
                    temparray[i-xdim] ^= shifthidden;
                }
            }

            if(((y+1) < ydim)){ //bottom of the feild
                if((board[i+xdim] & shifthidden) == shifthidden){
                    temparray[i+xdim] ^= shifthidden;
                }
            }
            if(((x-1) >= 0) && ((y+1) < ydim)){ //bottom left corner of the feild
                if((board[i+(xdim-1)] & shifthidden) == shifthidden){
                    temparray[i+(xdim-1)] ^= shifthidden;
                }
            }
            if(((x+1) < xdim) && ((y+1) < ydim)){ //bottom right corner of the feild
                if((board[i+(xdim+1)] & shifthidden) == shifthidden){
                    temparray[i+(xdim+1)] ^= shifthidden;
                }
            }

            if(((x-1) >= 0) && ((y-ydim) >= 0)){ //top left corner of the feild
                if((board[i-(xdim+1)] & shifthidden) == shifthidden){
                    temparray[i-(xdim+1)] ^= shifthidden;
                }
            }

            if(((x+1) < xdim) && ((y-xdim) >= 0)){ //top right corner  
                if((board[i-(xdim-1)] & shifthidden) == shifthidden){
                    temparray[i-(xdim-1)] ^= shifthidden;
                }
            }
        }
        for(int m{0}; m < (xdim*ydim); m++){
            board[m] = temparray[m]; // set original board back
        } 
    }
    return 0;
}
//g++ -o main .\geesespotter.cpp .\geesespotter_lib.cpp -std=c++11
//.\main.exe