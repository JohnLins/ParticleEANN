#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#include "types.h"
#include "collision.h"
#include "macros.h"









int main()
{
    
    int width = 40;
    int height = 40;
    int infoBoxWidth = 500;
    
    float pixdim = 15;
    
    float stepLen = 3;
    
    
    
    const int SW = pixdim * width;
    const int SH = pixdim * height;
    
    int used = 0;
    
    Vector2 *wall = (Vector2 *)malloc(WALLmax * sizeof(Vector2));
    
    
    Vector2 rewardBoxPos = (Vector2){2* pixdim, 2*pixdim};
   
   
   float bestRewardForDisplay = 0;
   float *bestDNAForDisplay = (float*)malloc(10 * sizeof(float));
 

 
        Bot *bots = (Bot*)malloc(BOTnum * sizeof(Bot));
        srand(time(0));
        for(int i = 0; i < BOTnum; i++){
            bots[i].DNA = (float*)malloc(DNAlen * sizeof(float));
            bots[i].invReward= 0;
            bots[i].pos =(Vector2){SW/2,SH/2};
            bots[i].status = 1;
           
           //init DNA
            for(int j = 0; j < DNAlen; j++){
                bots[i].DNA[j] = ((rand() / (float) RAND_MAX) * (4*PI)) - (PI*2); // between -PI/2 and PI/2
            }
        }
    
   bestDNAForDisplay = bots[0].DNA;
    
   
    int index = 0;
      
    InitWindow(SW + infoBoxWidth, SH, "Evo | John Lins");
    SetTargetFPS(60);
    while (!WindowShouldClose())    
    {
        BeginDrawing();

            ClearBackground(WHITE);
            
            
            DrawRectangleV(rewardBoxPos, (Vector2){pixdim, pixdim}, GREEN);
            
            
            if(IsMouseButtonDown(0) && used < WALLmax){
                
               wall[used] = (Vector2){(int)(GetMousePosition().x/pixdim) * pixdim,(int)(GetMousePosition().y/pixdim) * pixdim };
                
                used ++;
            }
            
            
            //draw wall
            for(int i = 0; i < used; i++){
                DrawRectangleV(wall[i], (Vector2){pixdim, pixdim}, RED);
                
                
              
            }
            
            
                
              DrawText(FormatText("Best Reward (lower is better): %d", (int)bestRewardForDisplay), SW + 20, 20, 15, BLACK);
              
              DrawText("First 10 elements of DNA:", SW + 20, 40, 15, BLACK);
              for(int i = 0; i < 10; i++){
                  DrawText(FormatText("???? %d: %f", i, bestDNAForDisplay[i]), SW + 20, 70 + i*15 , 12, BLACK);
              }
             //collision detection and timer /* check if they hit the walls */
            //for(int j = 0; j < BOTnum; j++){
                Collision collisionIndexs = wallCollision(bots, wall, &pixdim);
                    for(int i = 0; i < collisionIndexs.numOfCollisions; i++){
                        bots[collisionIndexs.collidedBots[i]].invReward= sqrtf(  powf(bots[collisionIndexs.collidedBots[i]].pos.x - rewardBoxPos.x, 2) + powf(bots[collisionIndexs.collidedBots[i]].pos.y - rewardBoxPos.y, 2)  );//distance
                        bots[collisionIndexs.collidedBots[i]].status = 0; // hit
                    }
              //  } 
               
           //Draw bots
           for(int i = 0; i < BOTnum; i++){
             
               
                DrawRectangle(bots[i].pos.x, bots[i].pos.y, pixdim, pixdim, BLUE);
  
                if(bots[i].status == 1 && index <= DNAlen){
                    bots[i].pos.x += stepLen * cosf(bots[i].DNA[index]);
                    bots[i].pos.y += stepLen * sinf(bots[i].DNA[index]);
                } else if (index > DNAlen){
                    
      
                    
                    int bestIndex = 0;
                    for(int k = 0; k < BOTnum; k++){
                        if(bots[k].status == 1){ bots[k].invReward = sqrtf(  powf(bots[k].pos.x - rewardBoxPos.x, 2) + powf(bots[k].pos.y - rewardBoxPos.y, 2)  );}//distance
                        if(bots[k].invReward < bots[bestIndex].invReward){
                            bestIndex = k;
                        }
                        
                    }
                    
                    printf("Best reward: %f \n", bots[bestIndex].invReward);
                    bestRewardForDisplay = bots[bestIndex].invReward;
                    bestDNAForDisplay = bots[bestIndex].DNA;
                    
                   
                    
                    
                    
                    for(int j = 0; j < BOTnum; j++){
                        
                       //Re init DNA strand of best DNA with noise
                        for(int d = 0; d < DNAlen; d++){
                            bots[j].DNA[d] = bots[bestIndex].DNA[d] + (((rand() / (float) RAND_MAX)* (PI * 2 /6)) - (PI /6)); 
                        }
                        
                        
                        bots[j].status = 1;
                        
                        bots[j].pos = (Vector2){SW/2,SH/2};
                        
                    }
                    index = 0;
                    //i = BOTnum;
                } 
                
                
           }  index++;
           
           
            
            
          
          
          if(!IsKeyDown('B')){
               for(int i = 0; i < width; i++){
                    DrawLine(i*pixdim, 0, i*pixdim, SH, GRAY);
               }        
               
               for(int i = 0; i < height; i++){
                    DrawLine(0, i*pixdim, SW, i*pixdim, GRAY);
               }  
          }    
          
         
            
      
        EndDrawing();
        
        
        
    }
    
    CloseWindow();     

    return 0;
}