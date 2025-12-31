#include "../../includes/header.h"
#define PI 3.1415926535

double pl_angle;
//https://www.youtube.com/watch?v=g8p7nAbDz6Y
// TODO LOOKING DIRECTION

void get_collision(t_data *t) {
    double distance = 0;
    double dx = cos(pl_angle);
    double dy = sin(pl_angle);
    t->player->px = t->player->x;
    t->player->py = t->player->y;
    while (distance < 2000) {
        t->player->px += dx;
        t->player->py += dy;
        distance+=1;
        int map_x = (t->player->px - t->spr[2].srf->w/2) / TILE_SIZE;
        int map_y = (t->player->py - t->spr[2].srf->h/2) / TILE_SIZE;
        if (map_x < 0 || map_y < 0)
            break;
        if (tmp_ctnr[map_y][map_x] == '1')
            break;
    }
} 

void temp_draw_line(t_data *t) {
    get_collision(t);
    SDL_SetRenderDrawColor(t->renderer, 0, 128, 0, 255);
    int p_x = t->player->x;
    int p_y = t->player->y;
    SDL_RenderDrawLine(t->renderer, p_x, p_y, t->player->px, t->player->py); 
}

void push_new_position(bool horizontal, bool incrementation, t_data *t) {
    if (horizontal) {
        if (incrementation)
            t->player->x += 10;
        else
            t->player->x -= 10;
    }
    else {
        if (incrementation)
            t->player->y += 10;
        else
            t->player->y -= 10;
    }
}

void handle_key_movement(t_data *t) {

    if (t->event.type != SDL_KEYDOWN)
        return;

    if (t->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        t->quit = SDL_TRUE;
    else if (t->event.key.keysym.scancode == SDL_SCANCODE_D)
        push_new_position(true, true, t);
    else if (t->event.key.keysym.scancode == SDL_SCANCODE_A)
        push_new_position(true, false, t);
    else if (t->event.key.keysym.scancode == SDL_SCANCODE_S)
        push_new_position(false, true, t);
    else if (t->event.key.keysym.scancode == SDL_SCANCODE_W)
        push_new_position(false, false, t);
    else if (t->event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
        pl_angle-=0.1;
        if (pl_angle < 0)
            pl_angle+=2*PI;
    }
    else if (t->event.key.keysym.scancode == SDL_SCANCODE_RIGHT){ 
        pl_angle+=0.1;
        if (pl_angle > 2*PI)
            pl_angle-=2*PI;
    }
    return ;
}
