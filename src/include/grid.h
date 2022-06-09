#ifndef __GRID_H__
#define __GRID_H__

#include <string.h>
#include <stdlib.h>

#include <globals.h>
#include <conio.h>

int positionToIndex(int x, int y) {
    return gridWidth * y + x;
}

position indexToPosition(int index) {
    position pos;

    pos.x = index % gridWidth;
    pos.y = index / gridWidth;

    return pos;
}

bool isOnBorder(int index) {
    position pos = indexToPosition(index);


    if(pos.x == 0 || pos.x == gridWidth - 1)
        return 1;

    if(pos.y == 0 || pos.y == gridHeight - 1)
        return 1;
    
    return 0;
}

bool indexOnFood(int index) {
    position pos = indexToPosition(index);

    if(pos.x != food.x)
        return 0;
    if(pos.y != food.y)
        return 0;

    return 1;
}

void printGrid() {
    int lines = 2;
    setcursorxy(0, lines);

    for(int i = 0; i < gridSize; i++) {
        int colour = BLACK;
        int backgroundColour = BLACK;
        char* c = (char*) malloc(1);
        c[0] = ' '; // allow free(c);
        
        if(isOnBorder(i)) {
            colour = GRID_BORDER_COLOUR;
            backgroundColour = GRID_BORDER_COLOUR;
        }

        for(int p = 0; p <= score; p++) {
            position pos = snake[p];

            if(positionToIndex(pos.x, pos.y) == i) {
                colour = SNAKE_COLOUR;
                backgroundColour = SNAKE_COLOUR;

                break;
            }
        }
        
        if(colour == BLACK && indexOnFood(i)) {
            free(c);

            int sz = strSize("●\0");
            c = malloc(sz);
            strcpy(c, "●\0");

            colour = FOOD_COLOUR;
        }

        textbackground(backgroundColour);
        textcolor(colour);

        
        printf("%s", c);

        if((i + 1) % gridWidth == 0 && i != gridSize - 1) 
            setcursorxy(0, ++lines);
    }
}

#endif