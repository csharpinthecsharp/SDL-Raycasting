#include "../../includes/header.h"
//https://www.youtube.com/watch?v=g8p7nAbDz6Y
// TODO LOOKING DIRECTION

void get_collision(t_data *t, t_value *v, double i)
{
    double angle;
    int mapX;
    int mapY;
    double hitx;
    double hity;
    int hit = 0;
    int side;

    double rad = FOV * PI / 180.0;
    double pas = rad / v->rayNb;
    angle = v->plAngle - rad / 2.0 + i * pas;

    v->rayDirX = cos(angle);
    v->rayDirY = sin(angle);

    mapX = (int)(t->player->x / TILE_SIZE);
    mapY = (int)(t->player->y / TILE_SIZE);

    v->deltaDistX = fabs(TILE_SIZE / v->rayDirX);
    v->deltaDistY = fabs(TILE_SIZE / v->rayDirY);

    if (v->rayDirX < 0) {
        v->stepX = -1;
        v->sideDistX = (t->player->x - mapX * TILE_SIZE) / fabs(v->rayDirX);
    }
    else {
        v->stepX = 1;
        v->sideDistX = ((mapX + 1) * TILE_SIZE - t->player->x) / fabs(v->rayDirX);
    }

    if (v->rayDirY < 0) {
        v->stepY = -1;
        v->sideDistY = (t->player->y - mapY * TILE_SIZE) / fabs(v->rayDirY);
    }
    else {
        v->stepY = 1;
        v->sideDistY = ((mapY + 1) * TILE_SIZE - t->player->y) / fabs(v->rayDirY);
    }

    while (!hit) {
        if (v->sideDistX < v->sideDistY) {
            v->sideDistX += v->deltaDistX;
            mapX += v->stepX;
            side = 0;
        }
        else {
            v->sideDistY += v->deltaDistY;
            mapY += v->stepY;
            side = 1;
        }

        if (tmp_ctnr[mapY][mapX] == '1') {
            v->sl_txr = 3;
            hit = 1;
        }
        else if (tmp_ctnr[mapY][mapX] == '2') {
            v->sl_txr = 6;
            hit = 1;
        }
    }

    if (side == 0) {
        v->distance = v->sideDistX - v->deltaDistX;
        hity = t->player->y + v->distance * v->rayDirY;
        v->textureX = (fmod(hity, TILE_SIZE) / TILE_SIZE) * 64;
    } else {
        v->distance = v->sideDistY - v->deltaDistY;
        hitx = t->player->x + v->distance * v->rayDirX;
        v->textureX = (fmod(hitx, TILE_SIZE) / TILE_SIZE) * 64;
    }


    v->distance = v->distance * cos(angle - v->plAngle);
}

void handle_key_movement(t_data *t) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_ESCAPE])
        t->quit = SDL_TRUE;

    float dx = cos(t->v->plAngle);
    float dy = sin(t->v->plAngle);

    if (state[SDL_SCANCODE_W]) {
        t->player->x += dx * t->v->speed;
        t->player->y += dy * t->v->speed;
    }
    if (state[SDL_SCANCODE_S]) {
        t->player->x -= dx * t->v->speed;
        t->player->y -= dy * t->v->speed;
    }

    if (state[SDL_SCANCODE_A]) {
        t->player->x += dy * t->v->speed;
        t->player->y -= dx * t->v->speed;
    }
    if (state[SDL_SCANCODE_D]) {
        t->player->x -= dy * t->v->speed;
        t->player->y += dx * t->v->speed;
    }

    if (state[SDL_SCANCODE_LEFT]) { 
        t->v->plAngle -= 0.04; 
        if (t->v->plAngle < 0) t->v->plAngle += 2*PI; 
    }
    if (state[SDL_SCANCODE_RIGHT]) { 
        t->v->plAngle += 0.04; 
        if (t->v->plAngle > 2*PI) t->v->plAngle -= 2*PI; 
    }
}

