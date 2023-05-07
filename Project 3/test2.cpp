#include "geesespotter_lib.h"
#include <iostream>

char *createBoard(std::size_t xdim, std::size_t ydim)
{
    char *p=new char[xdim*ydim];
    for(int i=0;i<xdim*ydim;i++)
    {
        p[i]=0;
    }
    return p;
}

void cleanBoard(char *board) {

    delete board;
    board = nullptr;    

};

void printBoard(char *board, std::size_t xdim, std::size_t ydim)
{


    for(int i=0;i<xdim*ydim;i++)
    {
        if((i%xdim)==0 && i!=0)
        {
            std::cout<<std::endl;
        }

        if( (board[i] & markedBit()) == markedBit() )
        {
            std::cout<<"M";
        }else if( (board[i]&hiddenBit()) == hiddenBit())
        {
            std::cout<<"*";
        }else
        {
            std::cout<<(board[i]&valueMask());
        }
        
    }
    std::cout<<std::endl;
}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim)
{
    for(int i=0;i<xdim*ydim;i++)
    {
        board[i]=board[i]|hiddenBit();
    }
}

int mark(char *board, std::size_t xdim, std::size_t ydim,std::size_t xloc, std::size_t yloc)
{
    if( (board[xloc*xdim+yloc]&0xf0) == 0 )
    {
        return 2;
    }else
    {
        board[xloc*xdim+yloc]=board[xloc*xdim+yloc]|markedBit();
        return 0;
    }
    
}

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim)
{
	char temporary[100][100] = {};
	for (int i = 0; i < ydim*xdim; i++){

		temporary[i / xdim][i%xdim] = board[i];
	
    }

	for (int i = 0; i < xdim; i++){

		for (int j = 0; j < ydim; j++){

			if (temporary[i][j] == 9){

				if ( (j - 1 >= 0) && (i - 1 >= 0) && (temporary[i - 1][j - 1] != 9) ){

					temporary[i - 1][j - 1]++;

				} else if ( (j - 1 >= 0) && (temporary[i ][j-1] != 9)){

                    temporary[i ][j-1]++;
                
                } else if (j - 1 >= 0 && i+1<xdim && (temporary[i + 1][j-1] != 9)){

                    temporary[i + 1][j-1]++;

                } else if (i - 1 >= 0 && (temporary[i-1][j ] != 9)){

                    temporary[i-1][j]++;

                } else if (i + 1 < xdim&&(temporary[i+1][j ] != 9)){

                    temporary[i+1][j ]++;

                } else if (j + 1 < ydim && i - 1 >= 0 && (temporary[i - 1][j + 1] != 9)){

                    temporary[i - 1][j + 1]++;

                } else if (j + 1 < ydim && (temporary[i ][j+1] != 9)){

                    temporary[i ][j+1]++;

                } else if (j + 1 < ydim && i + 1 < xdim && (temporary[i + 1][j + 1] != 9) ){

                    temporary[i + 1][j + 1]++;

                }

			}
		}
	}

	int temp{0};
	
    for (int i = 0; i < xdim; i++){

		for (int j = 0; j < ydim; j++){

			board[temp] = temporary[i][j];
			temp++;
		
        }
	}
}

int reveal(char *board, std::size_t xdim, std::size_t ydim,std::size_t xloc, std::size_t yloc){

    
}

bool isGameWon(char *board, std::size_t xdim, std::size_t ydim)
{
    int num{0};

    for(int item = 0; item < (xdim*ydim); item++){

        if( (board[item] & 240) == 0 ){

            num+=1;
        
        } else if ((board[item] & 240) != 0 && (board[item]&valueMask()) == 9){

            num+=1;

        }
    }

    if (num == xdim*ydim){

        return true;
    
    } else {
        
        return false;
    
    }
    
}



