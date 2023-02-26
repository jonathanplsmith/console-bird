#ifndef BIRD_SPRITES_H
#define BIRD_SPRITES_H

#include "canvas/consoleCanvas.h" //change later!

const int player_rows = 2;
const int player_cols = 4;
const char player[] = {
' ', '\\', 'O', '>',
'\\', '\\', '\\', ' ' 
};
const colour_t player_fg[] = {
YELLOW, YELLOW, WHITE, RED,
YELLOW, YELLOW, YELLOW, YELLOW
};
const colour_t player_bg[] = {
BBLUE, BYELLOW, BYELLOW, BYELLOW,
BYELLOW, BYELLOW, BYELLOW, BBLUE
};


const int pipe_rows = 14;
const int pipe_cols = 6;
const char pipe_down[] = {
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' '
};
const colour_t pipe_down_bg[] = {
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN
};

const char pipe_up[] = {
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' '
};
const colour_t pipe_up_bg[] = {
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE,
BBLUE, BGREEN, BGREEN, BGREEN, BGREEN, BBLUE
};
#endif