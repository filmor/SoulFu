#include "gameseed.h"

unsigned int game_seed;

void generate_game_seed(void)
{
    // <ZZ> This function generates a new game seed...
    srand(time(0));
    game_seed = (rand()&255);  game_seed<<=8;
    game_seed |= (rand()&255);  game_seed<<=8;
    game_seed |= (rand()&255);  game_seed<<=8;
    game_seed |= (rand()&255);
    log_message("INFO:   Set game seed to %d", game_seed);
}
