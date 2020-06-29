#ifndef GRID_COMPONENT_H
#define GRID_COMPONENT_H

#include "../component.h"
#include "../constants.h"
#include "../entity.h"
#include "../game.h"
#include "SDL2/SDL.h"
#include "stdlib.h"

#define COLUMNS 180
#define LINES 140

struct Cell {
    SDL_Rect body;
    bool status;
    bool next_status;    
};

class GridComponent: public Component
{
    private:
        Cell matrix[180][140];        

    public:
        GridComponent()
        {            
        }
        
        void initialize() override 
        {            
            for(int i = 0; i != COLUMNS; i += 1){
                for(int j = 0; j != LINES; j += 1) {                    
                    this->matrix[i][j].body = {
                        i*5, 
                        j*5, 
                        5, 
                        5
                    };                                                                
                    this->matrix[i][j].status = false;
                }                
            }
            this->matrix[3][9].status = true;
            this->matrix[3][10].status = true;
            this->matrix[4][9].status = true;
            this->matrix[4][10].status = true;
            
            this->matrix[15][7].status = true;
            this->matrix[16][7].status = true;
            this->matrix[14][8].status = true;
            this->matrix[13][9].status = true;
            this->matrix[13][10].status = true;            
            this->matrix[13][11].status = true;
            this->matrix[14][12].status = true;
            this->matrix[15][13].status = true;
            this->matrix[16][13].status = true;
            
            this->matrix[18][10].status = true;
            
            this->matrix[19][8].status = true;
            this->matrix[20][9].status = true;
            this->matrix[20][10].status = true;
            this->matrix[20][11].status = true;
            this->matrix[19][12].status = true;
            this->matrix[21][10].status = true;

            this->matrix[24][7].status = true;
            this->matrix[25][7].status = true;
            this->matrix[24][8].status = true;
            this->matrix[25][8].status = true;
            this->matrix[24][9].status = true;
            this->matrix[25][9].status = true;
            this->matrix[21][10].status = true;
            this->matrix[26][10].status = true;
            this->matrix[26][6].status = true;

            this->matrix[28][5].status = true;
            this->matrix[28][6].status = true;
            this->matrix[28][10].status = true;
            this->matrix[28][11].status = true;
            
            this->matrix[38][7].status = true;
            this->matrix[39][7].status = true;
            this->matrix[38][8].status = true;
            this->matrix[39][8].status = true;            
	    }

        void update(float delta_time) override 
        {            
            for(int i = 0; i != COLUMNS-1; i += 1){
                for(int j = 0; j != LINES-1; j += 1) {
                    Cell& current = this->matrix[i][j];                                        

                    if (i > 160 || j > 120) {
                        current.status = false;
                    }else {
                        int neighbours_factor =
                        this->matrix[i-1][j+1].status + 
                        this->matrix[i][j+1].status +
                        this->matrix[i+1][j+1].status +
                        this->matrix[i-1][j].status +
                        this->matrix[i+1][j].status +
                        this->matrix[i-1][j-1].status +
                        this->matrix[i][j-1].status + 
                        this->matrix[i+1][j-1].status;                                                             

                    if((neighbours_factor == 2 || neighbours_factor == 3) && current.status == true)
                        current.next_status = true;                    
                    else if(neighbours_factor == 3 && current.status == 0)
                        current.next_status = true;
                    else
                        current.next_status = false;                    
                    }                    
                }
            }
        }

        void render() override 
        {            
            for(int i = 0; i != COLUMNS; i += 1){
                for(int j = 0; j != LINES; j += 1) {
                    this->matrix[i][j].status = this->matrix[i][j].next_status;
                    if(this->matrix[i][j].status) {
                        SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
		                SDL_RenderFillRect(Game::renderer, &this->matrix[i][j].body);
                    }else {
                        SDL_SetRenderDrawColor(Game::renderer, 30, 30, 30, 255);
                        SDL_RenderFillRect(Game::renderer, &this->matrix[i][j].body);
                    }
                }
            }            
        }
};

#endif