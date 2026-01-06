#include "../../includes/header.h"

void update_loop(t_data *t) {
    SDL_SetRenderDrawColor(t->renderer, 0,0,0,255);
    SDL_RenderClear(t->renderer);
    draw_ray(t);
    draw_grid(t, true);
    SDL_RenderPresent(t->renderer);
}

