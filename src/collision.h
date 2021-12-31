#pragma once


#include "types.h"
#include <stdlib.h>
#include "macros.h"

Collision wallCollision(Bot *bots, Vector2 *walls, float *pixdim){
    int numOfCollisions = 0;
    int *collidedBots = (int*)malloc(BOTnum * sizeof(int));
    for(int i = 0; i < BOTnum; i++){
        for(int j = 0; j < WALLmax; j++){
            if(  ((bots[i].pos.x <= walls[j].x + *pixdim && bots[i].pos.x + *pixdim >= walls[j].x ) && ( bots[i].pos.y + *pixdim >= walls[j].y  && bots[i].pos.y <= walls[j].y + *pixdim))   ){
                collidedBots[numOfCollisions] = i;
                j = WALLmax; // end loop
                numOfCollisions++;
            }
            
        }
        
    }
    
    return (Collision){collidedBots, numOfCollisions};
    
}