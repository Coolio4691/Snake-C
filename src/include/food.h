#ifndef __FOOD_H__
#define __FOOD_H__

#include <globals.h>
#include <splitmix32.h>

void generateFoodPosition() {
    food.x = (splitmix32() % (gridWidth - 2)) + 1; // set a maximum and use 0 + 1 as a minimum
    food.y = (splitmix32() % (gridHeight - 3)) + 1; // set a maximum and use 0 + 1 as a minimum

    position* segment = snake; // create pointer to snake
    int i = 0; // initialize i to 0

    while(i++ <= score) { // loop until i == snakelength
        if(segment->x == food.x && segment->y == food.y) {
            generateFoodPosition(); // regenerate position until spot is free

            return;
        }

        *segment++; // go to next segment by incrementing pointer
    }
}

#endif