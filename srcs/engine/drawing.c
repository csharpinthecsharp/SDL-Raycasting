#include "../../includes/header.h"

void draw_wall(t_data *t, int tex_index, double x, double y_top, double y_bot) {
    SDL_Rect src = { t->v->textureX, 0, 1, 64};
    SDL_Rect dst = { x , y_top, 1, y_bot - y_top };
    SDL_RenderCopy(t->renderer, t->spr[tex_index].txr, &src, &dst);
}

void draw_ray(t_data *t) {
    double colone_width = t->width/t->v->rayNb;
    double x = 0.0;
    double high = 0.0;
    double y_top = 0.0;
    double y_bot = 0.0;
    for (double i = 0; i < t->v->rayNb; i++) {
        x = i * colone_width;
        get_collision(t, t->v, i);
        high = (TILE_SIZE * t->height)/t->v->distance;
        y_top = (t->height - high) / 2;
        y_bot = y_top + high;

        draw_wall(t, t->v->sl_txr, x, y_top, y_bot);

        SDL_SetRenderDrawColor(t->renderer, 0, 255, 255, 255);
        SDL_RenderDrawLine(t->renderer, (int)x, (int)0, (int)x, (int)y_top);

        SDL_SetRenderDrawColor(t->renderer, 102, 51, 0, 255);
        SDL_RenderDrawLine(t->renderer, (int)x, (int)y_bot, (int)x, t->height);

        SDL_Rect gun = { (t->width/2 - 205) - t->spr[4].srf->w/2, (t->height - 350) - t->spr[4].srf->h/2, t->spr[4].srf->w * 7, t->spr[4].srf->h *7};
        SDL_RenderCopy(t->renderer, t->spr[4].txr, NULL, &gun);
        SDL_Rect cursor = { (t->width/2) - t->spr[5].srf->w/2, (t->height/2) - t->spr[5].srf->h/2, t->spr[5].srf->w, t->spr[5].srf->h};
        SDL_RenderCopy(t->renderer, t->spr[5].txr, NULL, &cursor);
    }
}

void draw_grid(t_data *t, bool update) {
    int x = TILE_SIZE;
    int y = TILE_SIZE;
    for (int i = 0; tmp_ctnr[i]; i++) {
        for (int j = 0; j < strlen(tmp_ctnr[i]); j++) {
            if (tmp_ctnr[i][j] == '1' || tmp_ctnr[i][j] == '2') {
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