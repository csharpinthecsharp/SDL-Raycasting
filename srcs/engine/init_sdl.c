#include "../../includes/header.h"

char *tmp_ctnr[] = {
    "111111111111111111111",
    "100000000000000000001",
    "100N00000000000000001",
    "122222220000002222001",
    "100000020000000000001",
    "100000022222002222201",
    "100N00020000000020001",
    "100N00020000000020001",
    "100N00000000000020001",
    "100N00000000022220001",
    "100N00000000000000001",
    "100N00002222200000001",
    "100N00000000000000001",
    "111111111111111111111",
    NULL
};


static bool create_window(t_data *t) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        ft_puterror("Failed to init SDL!");
        return (false);
    }
    ft_putgood("Successfully init SDL!");
    t->window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, t->width, t->height, SDL_WINDOW_SHOWN);
    if (!t->window)
    {
        ft_puterror("Failed to create the SDL window!");
        return (false);    
    }
    return (true);
}

static bool create_renderer(t_data *t) {
    t->renderer = SDL_CreateRenderer(t->window, -1, SDL_RENDERER_ACCELERATED);
    if (!t->renderer)
    {
        ft_puterror("Failed to create the SDL renderer!");
        return (false);
    }
    return (true);
}

static bool create_sprites(t_data *t) {
    t->n_spr = 6;
    t->spr = malloc(sizeof(t_sprite) * (t->n_spr + 1));
    if (!t->spr) {
        ft_puterror("Failed to allocate spr struct");
        return (false);
    }
    return (true);
}

bool push_sprite_data(t_data *t, const char *path, int index) {
    t->spr[index].id = index;
    t->spr[index].path = path;
    t->spr[index].srf = SDL_LoadBMP(path);
    if (!t->spr[index].srf)
        return (false);
    t->spr[index].txr = SDL_CreateTextureFromSurface(t->renderer, t->spr[index].srf);
    if (!t->spr[0].srf)
        return (false);
    return (true);
}

void init_value(t_value *v) {
    v->speed = 0.8;
    v->plAngle = 0.0;
    v->textureX = 0.0;
    v->rayDirX = 0.0;
    v->rayDirY = 0.0;
    v->stepX = 0.0;
    v->stepY = 0.0;
    v->deltaX = 0.0;
    v->deltaY = 0.0;
    v->deltaDistX = 0.0;
    v->deltaDistY = 0.0;
    v->sideDistX = 0.0;
    v->sideDistY = 0.0;
    v->distance = 0.0;
    v->rayNb = 1300;
    v->sl_txr = 3;
}

bool start_sdl(t_data *t) {
    t->window = NULL;
    t->width = 1280;
    t->height = 880;
    t->player = malloc(sizeof(t_player) * 1);
    t->v = malloc(sizeof(t_value) * 1);
    init_value(t->v);
    if (!create_window(t))
        return (false);
    t->renderer = NULL;
    if (!create_renderer(t))
        return (false);
    if (!create_sprites(t))
        return (false);

    push_sprite_data(t, "wall_0.bmp", 0);
    push_sprite_data(t, "wall_1.bmp", 1);
    push_sprite_data(t, "player.bmp", 2);
    push_sprite_data(t, "wall_ray_0.bmp", 3);
    push_sprite_data(t, "weapon.bmp", 4);
    push_sprite_data(t, "cursor.bmp", 5);
    push_sprite_data(t, "wall_ray_1.bmp", 6);

    draw_grid(t, false);
    return (true);
}