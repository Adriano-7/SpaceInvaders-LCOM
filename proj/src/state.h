#ifndef STATE_H
#define STATE_H
enum State {MENU, LEADERBOARD, GAME, PAUSE, GAMEOVER, EXIT};

extern enum State* state;

void changeState(enum State newState);
#endif
