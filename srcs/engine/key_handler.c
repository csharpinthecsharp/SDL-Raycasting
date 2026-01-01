#include "../../includes/header.h"
double pl_angle;
double fov = 60;
double nb_ray = 1500;
double speed = 0.8;
//https://www.youtube.com/watch?v=g8p7nAbDz6Y
// TODO LOOKING DIRECTION

double get_collision(t_data *t, double i)
{
    double angle;
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    int stepX;
    int stepY;
    int hit = 0;
    int side;

    double rad = fov * PI / 180.0;
    double pas = rad / nb_ray;
    angle = pl_angle - rad / 2.0 + i * pas;

    rayDirX = cos(angle);
    rayDirY = sin(angle);

    mapX = (int)(t->player->x / TILE_SIZE);
    mapY = (int)(t->player->y / TILE_SIZE);

    deltaDistX = fabs(TILE_SIZE / rayDirX);
    deltaDistY = fabs(TILE_SIZE / rayDirY);

    if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (t->player->x - mapX * TILE_SIZE) / fabs(rayDirX);
    }
    else {
        stepX = 1;
        sideDistX = ((mapX + 1) * TILE_SIZE - t->player->x) / fabs(rayDirX);
    }

    if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (t->player->y - mapY * TILE_SIZE) / fabs(rayDirY);
    }
    else {
        stepY = 1;
        sideDistY = ((mapY + 1) * TILE_SIZE - t->player->y) / fabs(rayDirY);
    }

    while (!hit) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }

        if (tmp_ctnr[mapY][mapX] == '1')
            hit = 1;
    }

    double dist;
    if (side == 0)
        dist = sideDistX - deltaDistX;
    else
        dist = sideDistY - deltaDistY;

    return dist * cos(angle - pl_angle);
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

        SDL_SetRenderDrawColor(t->renderer, 96, 96, 96, 255);
        SDL_RenderDrawLine(t->renderer, (int)x, (int)y_top, (int)x, (int)y_bot);

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

void handle_key_movement(t_data *t) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_ESCAPE])
        t->quit = SDL_TRUE;

    float dx = cos(pl_angle);
    float dy = sin(pl_angle);

    if (state[SDL_SCANCODE_W]) {
        t->player->x += dx * speed;
        t->player->y += dy * speed;
    }
    if (state[SDL_SCANCODE_S]) {
        t->player->x -= dx * speed;
        t->player->y -= dy * speed;
    }

    if (state[SDL_SCANCODE_A]) {
        t->player->x += dy * speed;
        t->player->y -= dx * speed;
    }
    if (state[SDL_SCANCODE_D]) {
        t->player->x -= dy * speed;
        t->player->y += dx * speed;
    }

    if (state[SDL_SCANCODE_LEFT]) { 
        pl_angle -= 0.04; 
        if (pl_angle < 0) pl_angle += 2*PI; 
    }
    if (state[SDL_SCANCODE_RIGHT]) { 
        pl_angle += 0.04; 
        if (pl_angle > 2*PI) pl_angle -= 2*PI; 
    }
}

