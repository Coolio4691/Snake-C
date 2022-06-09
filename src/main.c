#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#include <conio.h>
#include <globals.h>
#include <grid.h>
#include <food.h>
#include <snake.h>

#include <sys/ioctl.h>

static struct termios oldt, newt;
static char inpBuffer;

static int snakeMove = 0;
static int snakeMoveMax = 9;

void handle_alarm(int sig) {
    if(snakeMove++ == snakeMoveMax) {
        snakeMove = 0;
        move();
    }

    printGrid();

}

void setupSignal(int signal, void (*callback)) {
    struct sigaction action;

    action.sa_handler = callback;
    action.sa_flags = 0;
    
    sigemptyset(&action.sa_mask);

    sigaction(signal, &action, NULL);
}

void gameOver() {
    textbackground(BLACK);
    textcolor(WHITE);
    clrscr();

    setcursorxy(0, 0);

    printf("\n #####     #    #     # #######    ####### #     # ####### ######  \n#     #   # #   ##   ## #          #     # #     # #       #     # \n#        #   #  # # # # #          #     # #     # #       #     # \n#  #### #     # #  #  # #####      #     # #     # #####   ######  \n#     # ####### #     # #          #     #  #   #  #       #   #   \n#     # #     # #     # #          #     #   # #   #       #    #  \n #####  #     # #     # #######    #######    #    ####### #     # \n");
    printf("\n\n                             Score: %d\n", score);
}

int main() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // get terminal size

    gridWidth = w.ws_col - 2;
    gridHeight = w.ws_row;

    if(gridWidth > 50) gridWidth = 50;
    if(gridHeight > 20) gridHeight = 20;

    gridSize = gridWidth * gridHeight;

    snake = (position*)malloc(gridSize * sizeof(position)); // allocate memory for snake array

    struct timespec realtime, uptime;
    clock_gettime(CLOCK_REALTIME, &realtime); // get real time
    clock_gettime(CLOCK_BOOTTIME, &uptime); // get boottime 

    splitmix32_seed((realtime.tv_nsec + uptime.tv_nsec) * uptime.tv_sec); // seed splitmix32 using (realtime nanoseconds + uptime nanoseconds) * uptime seconds 

    position head;
    head.x = (gridWidth / 2); // set x to middle height
    head.y = (gridHeight / 2); // set y to middle height

    snake[score] = head; // set middle as head position

    tcgetattr(stdin_fd, &oldt); // get current termios struct
    newt = oldt; // set new termios to old termios

    newt.c_lflag &= ~(ICANON); // set cannonical mode off
    newt.c_lflag &= ~(ECHO); // disable char echo
    newt.c_cc[VMIN] = 1; // set VMIN to 1 for less looping
    newt.c_cc[VTIME] = 0; // set VTIME to 0 for instant char input

    tcsetattr(stdin_fd, TCSANOW, &newt); // set termios flags

    setupSignal(SIGALRM, handle_alarm); // set alarm signal handler
    ualarm(printMove_delay_usec, printMove_delay_usec); // start alarm signal loop
    
    hidecursor();
    generateFoodPosition(); // randomize food position

    clrscr();

    while(!exitGame) {
        char inpBuffer = getchar();

        setmove(inpBuffer); // set snake direction to entered char if available and valid
    }

    gameOver();

    showcursor();
    tcsetattr(stdin_fd, TCSANOW, &oldt); // set termios back to old

    return 0;
}