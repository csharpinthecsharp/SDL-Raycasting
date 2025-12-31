#include "../../includes/header.h"
#define PI 3.1415926535
double pl_angle;
double fov = 60;
double nb_ray = 1000;
double speed = 0.8;
//https://www.youtube.com/watch?v=g8p7nAbDz6Y
// TODO LOOKING DIRECTION

double get_collision(t_data *t, double i) {
    double distance = 0;
    double dx;
    double dy;
    double rad = fov * PI / 180;
    double pas = rad/nb_ray;
    double angle = pl_angle - rad/2 + i * pas;

    dx = cos(angle);
    dy = sin(angle);
    t->player->px = t->player->x;
    t->player->py = t->player->y;
    while (1) {
        t->player->px += dx;
        t->player->py += dy;
        distance++;
        int map_x = (t->player->px - t->spr[2].srf->w/2) / TILE_SIZE;
        int map_y = (t->player->py - t->spr[2].srf->h/2) / TILE_SIZE;

        if (map_x < 0 || map_y < 0)
            break;
        if (tmp_ctnr[map_y][map_x] == '1')
            break;
    }
    return distance;
} 

void draw_ray(t_data *t) {
    double colone_width = 1280/nb_ray;
    double distance = 0;
    for (double i = 0; i < nb_ray; i++) {
        double x = i * colone_width;
        distance = get_collision(t, i);
        double high = (TILE_SIZE * 880)/distance;
        double y_top = (880 - high) / 2;
        double y_bot = y_top + high;
        SDL_SetRenderDrawColor(t->renderer, 0, 128, 0, 255);
        SDL_RenderDrawLine(t->renderer, (int)x, (int)y_top, (int)x, (int)y_bot); 
    }
}

void handle_key_movement(t_data *t) {

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_ESCAPE])
        t->quit = SDL_TRUE;
    if (state[SDL_SCANCODE_S]) {
        t->player->x -= cos(pl_angle) * speed;
        t->player->y -= sin(pl_angle) * speed;
    }
    if (state[SDL_SCANCODE_W]) {
        t->player->x += cos(pl_angle) * speed;
        t->player->y += sin(pl_angle) * speed;
    }
    if (state[SDL_SCANCODE_LEFT]) {
        pl_angle-=0.04;
        if (pl_angle < 0)
            pl_angle+=2*PI;
    }
    if (state[SDL_SCANCODE_RIGHT]){ 
        pl_angle+=0.04;
        if (pl_angle > 2*PI)
            pl_angle-=2*PI;
    }
    return ;
}
