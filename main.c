#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <time.h>
#include <string.h>
#include "sprites.h"

#define MAX_X 20
#define MAX_Y 80
#define PLAYER_Y 30
#define PIPE_GAP 5 //space inbetween opposing pipes
#define DRAW_PLAYER(X, Y) \
    (drawSprite(canv, player, player_fg, player_bg, player_rows, player_cols, X, Y))
#define DRAW_PIPE(X, Y) \
    do { \
        drawSprite(canv, pipe_down, NULL, pipe_down_bg, pipe_rows, pipe_cols, X, Y); \
        drawSprite(canv, pipe_up, NULL, pipe_up_bg, pipe_rows, pipe_cols, X + pipe_rows + PIPE_GAP, Y); \
    } while (0)
//Maximum and minimum x-coordinates for a pipe
#define MIN_PIPE (-pipe_rows + 2)
#define MAX_PIPE (MAX_X - (pipe_rows + PIPE_GAP + 2))
#define PIPE_COUNT 4
#define PIPE_SPACING 22

static struct termios old_termios;

static struct game {
    int pX;
    int vX;
    unsigned int score;
} game;

static struct pipe {
    int pX;
    int pY;
} pipes[PIPE_COUNT];

static canvas_t *canv;

//make sure subsequent terminal actions behave as expected
static void restoreTerminal(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_termios);
}

//enable raw mode, so input can be taken without having to press enter
static void startRawInput(void) {
    tcgetattr(STDIN_FILENO, &old_termios);

    struct termios modified = old_termios;
    modified.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDERR_FILENO, TCSAFLUSH, &modified);
}

static bool rawInputAvailable() {
    //using select() to check if input is available
    //this is more or less the example from the man page
    fd_set rfds;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100000;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    int ret = select(1, &rfds, NULL, NULL, &tv);
    if (ret == -1) {
            printf("An error has occured\n");
            exit(EXIT_FAILURE);
    }
    
    return ret;
}

static inline int randomPipeX() {
    return (rand() % (MAX_PIPE - MIN_PIPE + 1)) + MIN_PIPE;
}

static inline bool inPipeRangeX(int pipe) {
    for (int j=0; j<pipe_cols; j++) {
        for (int i=0; i<player_cols; i++) {
            if (pipes[pipe].pY+j == PLAYER_Y+i)
                return true;
        }
    }
    return false;
}

//return true if game is over
static bool updateState() {
    bool game_over = false;

    //move player
    game.vX += 1;
    game.pX += game.vX;

    //move pipes
    for (int i=0; i<PIPE_COUNT; i++) {
        pipes[i].pY--;
        if (pipes[i].pY < -4) {
            pipes[i].pY = MAX_Y;
            pipes[i].pX = randomPipeX();
        }
    }

    //check collision with pipes
    for (int i=0; i<PIPE_COUNT; i++) {
        if (inPipeRangeX(i) &&
            (game.pX < pipes[i].pX + pipe_rows || //top half
            game.pX + 1 > pipes[i].pX + pipe_rows + PIPE_GAP)) //bottom half
                game_over = true;
    }   

    //update score
    for (int i=0; i<PIPE_COUNT; i++) {
        if (PLAYER_Y == pipes[i].pY + pipe_cols)
            ++game.score;
    }

    //update canvas
    clearCanvas(canv);
    paintBg(canv, BBLUE);

    for (int i=0; i<PIPE_COUNT; i++) {
        DRAW_PIPE(pipes[i].pX, pipes[i].pY);
    }

    //check if player has hit top/bottom
    game_over |= !DRAW_PLAYER(game.pX, PLAYER_Y);
    
    //draw current score
    char message[30];
    sprintf(message, "Score: %u", game.score);
    setBg(canv, RESET_COLOUR);
    placeTextHor(canv, message, MAX_X-1, 0);

    refreshConsole(canv);

    return game_over;
}

static void resetGame() {
    game = (struct game){0, 0, 0};
    for (int i=0; i<PIPE_COUNT; i++) {
        pipes[i] = (struct pipe){randomPipeX(), MAX_Y + i*PIPE_SPACING};
    }
}

int main(void) {
    startRawInput();
    atexit(restoreTerminal);
    srand(time(NULL));

    //initialise/reset globals
    canv = newCanvas(MAX_X, MAX_Y);
    setBg(canv, BBLUE);
    resetGame();

    while(true) {
        bool input = rawInputAvailable();
        if (input) {
            char c;
            read(STDIN_FILENO, &c, 1);

            if (c == ' ') {
                game.vX = -3; //perform "jump"
            };
        }

        bool game_over = updateState();

        if (game_over) {
            usleep(500000);
            setBg(canv, RESET_COLOUR);
            for (int i=0; i<40; i++) {
                for (int j=0; j<7; j++) {
                    inputChar(canv, ' ', 3+j, 20+i);
                }
            }

            setFg(canv, RESET_COLOUR);
            for (int i=0; i<40; i++) {
                inputChar(canv, '=', 3, 20+i);
                inputChar(canv, '=', 9, 20+i);
                // inputChar(canv, '-', 7, 20+i);
            }
            placeTextHor(canv, "GAME OVER", 5, 34);
            char score[30];
            sprintf(score, "SCORE: %u", game.score);
            placeTextHor(canv, score, 7, 34);
            // placeTextHor(canv, "Press n to play again, press q to quit", 11, 21);

            refreshConsole(canv);
            break;
        }
    }

    deleteCanvas(canv);
    return 0;
}