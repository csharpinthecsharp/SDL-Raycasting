#include "../../includes/header.h"

// TODO LOOKING DIRECTION
void temp_draw_line(t_data *t) {
    SDL_SetRenderDrawColor(t->renderer, 0, 128, 0, 255);
    int p_x = t->player->x/2;
    int p_y = t->player->y/2;
    int distance = TILE_SIZE * 2;
    int angle = 360;
    SDL_RenderDrawLine(t->renderer, p_x, p_y, p_x + distance, p_y - angle); 
    SDL_RenderDrawLine(t->renderer, p_x, p_y, p_x - distance, p_y - angle); 
}

bool is_collision(int x, int y) {
    y -= TILE_SIZE;
    x -= TILE_SIZE;
    printf("Player x: %d\n", x/TILE_SIZE);
    printf("Player y: %d\n", y/TILE_SIZE);
    if (tmp_ctnr[y/TILE_SIZE][x/TILE_SIZE] == '1')
        return (true);
    return (false);
}

void push_new_position(bool horizontal, bool incrementation, t_data *t) {
    if (horizontal) {
        if (incrementation) {
            if (!is_collision(t->player->x + TILE_SIZE, t->player->y)) {t->player->x += TILE_SIZE;} else return;
        }
        else {
            if (!is_collision(t->player->x - TILE_SIZE, t->player->y)) {t->player->x -= TILE_SIZE;} else return;
    }
    }
    else {
        if (incrementation) {
            if (!is_collision(t->player->x, t->player->y + TILE_SIZE)) {t->player->y += TILE_SIZE;} else return;
        }
        else {
            if (!is_collision(t->player->x, t->player->y - TILE_SIZE)) {t->player->y -= TILE_SIZE;} else return;
        }
    }
    SDL_RenderClear(t->renderer);
    draw_grid(t, true);
    temp_draw_line(t);
    SDL_RenderPresent(t->renderer);
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
    
    return ;
}
