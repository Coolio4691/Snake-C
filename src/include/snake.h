#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <stdio.h>
#include <stdlib.h>

#include <globals.h>
#include <grid.h>

char dir = '\0';

void addSegment();

void snakeCollision() {
    position pos = snake[0];
    int snakeIdx = positionToIndex(pos.x, pos.y);

    if(isOnBorder(snakeIdx)) {
        exitGame = true;
        return;
    }

    position* segment = snake;
    for(int i = 1; i <= score; i++) {
        *segment++;

        if(pos.x != segment->x) continue;
        if(pos.y != segment->y) continue;
         
        exitGame = true;
        return;
    }

    if(indexOnFood(snakeIdx)) {
        addSegment();

        generateFoodPosition();
    }
}

void move() {
    for (int i = score; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    switch (dir) {
        case 'w': {
            snake[0].y -= 1;
            break;
        }
        case 's': {
            snake[0].y += 1;
            break;
        }
        case 'a': {
            snake[0].x -= 1;
            break;
        }
        case 'd': {
            snake[0].x += 1;
            break;
        }
        default:
            break;
    }

    snakeCollision();
}

void setmove(char nextdir) {
    if(dir == nextdir) return;
    int doMove = 0;

    switch(nextdir) {
        case 'w': case 'W': {
            if(snake[1].x == snake[0].x) {
                if(snake[1].y + 1 == snake[0].y) {
                    break;
                }
            }

            dir = 'w';
            break;
        }
        case 's': case 'S': {
            if(snake[1].x == snake[0].x) {
                if(snake[1].y - 1 == snake[0].y) {
                    break;
                }
            }
            
            dir = 's';
            break;
        }
        case 'a': case 'A': {
            if(snake[1].x + 1 == snake[0].x) {
                if(snake[1].y == snake[0].y) {
                    break;
                }
            }
            
            dir = 'a';
            break;
        }
        case 'd': case 'D': {
            if(snake[1].x - 1 == snake[0].x) {
                if(snake[1].y == snake[0].y) {
                    break;
                }
            }
            
            dir = 'd';
            break;
        }
        case 27:
            exitGame = 1;
            return;
        default:
            break;
    }
}

void addSegment() {
    position pos;

    switch(score) {
        case 0: {
            switch (dir) {
                case 'w': {
                    pos.y = snake[score].y + 1;
                    pos.x = snake[score].x;
                    break;
                }
                case 's': {
                    pos.y = snake[score].y - 1;
                    pos.x = snake[score].x;
                    break;
                }
                case 'a': {
                    pos.x = snake[score].x + 1;
                    pos.y = snake[score].y;
                    break;
                }
                case 'd': {
                    pos.x = snake[score].x - 1;
                    pos.y = snake[score].y;
                    break;
                }
                default:
                    pos.x = snake[score].x - 1;
                    pos.y = snake[score].y;
                    break;
            }
            break;
        }
        default:
            pos = snake[score];
            break;
    }

    snake[++score] = pos;
}

#endif