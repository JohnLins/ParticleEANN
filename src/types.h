#pragma once


typedef struct Bot {
    float *DNA;
    float invReward;
    Vector2 pos;
    bool status;
} Bot;

typedef struct Collision {
    int *collidedBots;
    int numOfCollisions;
} Collision;