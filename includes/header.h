#ifndef HEADER_H
#define HEADER_H

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
#include <math.h>

#define TILE_SIZE 16
#define PI 3.1415926535
#define FOV 60

extern char *tmp_ctnr[];

typedef struct s_sprite {
    int         id;
    const char  *path;
    SDL_Surface *srf;
    SDL_Texture *txr;
    SDL_Rect     dst;
} t_sprite;

typedef struct s_player {
    double x;
    double y;
    double px;
    double py;
} t_player;

typedef struct s_map {
    char **ctnr;
    int    len;
} t_map; 

typedef struct t_value {
    double plAngle;
    double speed;
    double textureX;
    double rayDirX;
    double rayDirY;
    double stepX;
    double stepY;
    double deltaX;
    double deltaY;
    double deltaDistX;
    double deltaDistY;
    double sideDistX;
    double sideDistY;
    double distance;
    double rayNb;
    int sl_txr;
} t_value;

typedef struct s_data {
    t_sprite        *spr;
    t_player        *player;
    t_value         *v;
    
    int             n_spr;
    int             width;
    int             height;

    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_Event       event;
    SDL_bool        quit;
} t_data;

void draw_ray(t_data *t);
bool start_sdl(t_data *t);
void free_sdl(t_data *t);
void handle_key_movement(t_data *t);
void update_loop(t_data *t);
void draw_wall(t_data *t, int tex_index, double x, double y_top, double y_bot);
void draw_grid(t_data *t, bool update);
void draw_ray(t_data *t);
void get_collision(t_data *t, t_value *v, double i);
#endif
