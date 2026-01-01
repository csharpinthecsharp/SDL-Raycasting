#include "../../includes/header.h"

void update_loop(t_data *t) {
    SDL_SetRenderDrawColor(t->renderer, 0,0,0,255);
    SDL_RenderClear(t->renderer);
    draw_ray(t);
    draw_grid(t, true);
    SDL_RenderPresent(t->renderer);
}

void draw_grid(t_data *t, bool update) {
    int x = TILE_SIZE;
    int y = TILE_SIZE;
    for (int i = 0; tmp_ctnr[i]; i++) {
        for (int j = 0; j < strlen(tmp_ctnr[i]); j++) {
            if (tmp_ctnr[i][j] == '1') {
                SDL_Rect dst = { x - t->spr[1].srf->w/2, y - t->spr[1].srf->h/2, t->spr[1].srf->w, t->spr[1].srf->h };
                SDL_RenderCopy(t->renderer, t->spr[1].txr, NULL, &dst);
                x += TILE_SIZE;
            }
            else if (tmp_ctnr[i][j] == '0') {
                SDL_Rect dst = { x - t->spr[0].srf->w/2, y - t->spr[0].srf->h/2, t->spr[0].srf->w, t->spr[0].srf->h };
                SDL_RenderCopy(t->renderer, t->spr[0].txr, NULL, &dst);
                x += TILE_SIZE;
            }
            else if (tmp_ctnr[i][j] == 'N') {
                if (update) {
                    SDL_Rect dst = { x - t->spr[0].srf->w/2, y - t->spr[0].srf->h/2, t->spr[0].srf->w, t->spr[0].srf->h };
                    SDL_RenderCopy(t->renderer, t->spr[0].txr, NULL, &dst);
                    x += TILE_SIZE;
                }
                else {
                    SDL_Rect dst = { x - t->spr[2].srf->w/2, y - t->spr[2].srf->h/2, t->spr[2].srf->w, t->spr[2].srf->h };
                    SDL_RenderCopy(t->renderer, t->spr[2].txr, NULL, &dst);
                    t->player->x = x;
                    t->player->y = y;
                    x += TILE_SIZE;
                }
            }
        }
        x = TILE_SIZE;
        y += TILE_SIZE;
    }
    if (update) {
        SDL_Rect dst = { t->player->x - t->spr[2].srf->w/2, t->player->y - t->spr[2].srf->h/2, t->spr[2].srf->w, t->spr[2].srf->h };
        SDL_RenderCopy(t->renderer, t->spr[2].txr, NULL, &dst);
    }
}