#ifndef __GLOBALS_H__
#define __GLOBALS_H__

typedef long int uint32_t;
typedef struct {
    int x;
    int y;
} position;

typedef enum { false, true } bool;

static int gridWidth = 22;
static int gridHeight = 11;
static int gridSize = 0;

#define printMove_delay_usec 10000    

#define stdin_fd 0

#define GRID_BORDER_COLOUR LIGHTBLUE
#define SNAKE_COLOUR WHITE 
#define FOOD_COLOUR LIGHTRED

static position* snake;
static position food;
static int score = 0;

static int exitGame = 0;

int strSize(char* str) {
    int size = 0;
    while(*str++) size++;

    return size;
}

#endif