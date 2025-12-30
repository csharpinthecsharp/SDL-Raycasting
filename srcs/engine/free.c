#include "../../includes/header.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

void free_sdl(t_data *t) {
    if (t->renderer)
        SDL_DestroyRenderer(t->renderer);
    if (t->window)
        SDL_DestroyWindow(t->window);
    if (t->spr[0].txr)
        SDL_DestroyTexture(t->spr[0].txr);
    if (t->spr[0].srf)
        SDL_FreeSurface(t->spr[0].srf);
    if (t->spr[1].txr)
        SDL_DestroyTexture(t->spr[1].txr);
    if (t->spr[1].srf)
        SDL_FreeSurface(t->spr[1].srf);
    SDL_Quit();
    return ;
}