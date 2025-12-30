#ifndef HEADER_H
#define HEADER_H

#define _n_spr 3

#include "../libft/libft.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <fcntl.h>

#define TILE_SIZE 130

extern char *tmp_ctnr[];

typedef struct s_sprite {
    int         id;
    const char  *path;
    SDL_Surface *srf;
    SDL_Texture *txr;
    SDL_Rect     dst;
} t_sprite;

typedef struct s_player {
    int x;
    int y;
} t_player;

typedef struct s_map {
    char **ctnr;
    int    len;

} t_map; 

typedef struct s_data {
    t_sprite        *spr;
    t_player        *player;
    int             n_spr;
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_Event       event;
    SDL_bool        quit;
} t_data;

bool is_a_valid_file(const char *path);
bool start_sdl(t_data *t);
void free_sdl(t_data *t);
void handle_key_movement(t_data *t);
void draw_grid(t_data *t, bool update);

#endif
