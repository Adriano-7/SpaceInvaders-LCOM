#ifndef STATE_H
#define STATE_H

enum State {MENU, LEADERBOARD, GAME, PAUSE, GAMEOVER, EXIT};

void changeState(enum State* state, enum State newState);
#endif
