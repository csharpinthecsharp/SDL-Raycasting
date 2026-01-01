#include "../../includes/header.h"
double pl_angle;
double fov = 60;
double nb_ray = 300;
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
        distance += 1.0;
        int map_x = (t->player->px - t->spr[2].srf->w/2) / TILE_SIZE;
        int map_y = (t->player->py - t->spr[2].srf->h/2) / TILE_SIZE;

        if (map_x < 0 || map_y < 0)
            break;
        if (tmp_ctnr[map_y][map_x] == '1')
            break;
    }
    return (distance * cos(angle - pl_angle));
}

void draw_ray(t_data *t) {
    double colone_width = t->width/nb_ray;
    double distance = 0.0;
    double x = 0.0;
    double high = 0.0;
    double y_top = 0.0;
    double y_bot = 0.0;
    for (double i = 0; i < nb_ray; i++) {
        x = i * colone_width;
        distance = get_collision(t, i);
        high = (TILE_SIZE * t->height)/distance;
        y_top = (t->height - high) / 2;
        y_bot = y_top + high;

        SDL_SetRenderDrawColor(t->renderer, 255, 51, 51, 255);
        SDL_Rect dst = { (int)x, (int)y_top, 5, (int)y_bot - (int)y_top };
        SDL_RenderFillRect(t->renderer, &dst);

        SDL_SetRenderDrawColor(t->renderer, 0, 255, 255, 255);
        SDL_Rect top = { (int)x, 0, 5, y_top};
        SDL_RenderFillRect(t->renderer, &top);

        SDL_SetRenderDrawColor(t->renderer, 102, 51, 0, 255);
        SDL_Rect floor = { (int)x, y_bot, 5, t->height - y_bot};
        SDL_RenderFillRect(t->renderer, &floor);
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
