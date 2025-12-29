#ifndef HEADER_H
#define HEADER_H

#define _n_spr 2

#include "../libft/libft.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>
#include <fcntl.h>

typedef struct s_sprite {
    int         id;
    const char  *path;
    SDL_Surface *srf;
    SDL_Texture *txr;
    SDL_Rect     dst;
} t_sprite;

typedef struct s_map {
    char **ctnr;
    int    len;

} t_map; 

typedef struct s_data {
    t_sprite        *spr;
    int             n_spr;
    SDL_Window      *window;
    SDL_Renderer    *renderer;
} t_data;

bool is_a_valid_file(const char *path);
bool start_sdl(t_data *t);
void free_sdl(t_data *t);

#endif
