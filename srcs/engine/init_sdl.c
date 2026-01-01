#include "../../includes/header.h"

char *tmp_ctnr[] = {
    "111111111111111111111",
    "100000000000000000001",
    "100N00000000000000001",
    "100001000000001111001",
    "100000000000000000001",
    "100000011111001111101",
    "100N00000000000000001",
    "100N00000000000000001",
    "100N00000000000000001",
    "100N00000000000000001",
    "100N00000000000000001",
    "100N00000000000000001",
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
    t->n_spr = 5;
    t->spr = malloc(sizeof(t_sprite) * (t->n_spr + 1));
    if (!t->spr) {
        ft_puterror("Failed to allocate spr struct");
        return (false);
    }
    /*SDL_Rect dst = { w_x/2 - t->spr[0].srf->w/2, w_y/2 - t->spr[0].srf->h/2, t->spr[0].srf->w, t->spr[0].srf->h };
    SDL_RenderCopy(t->renderer, t->spr[0].txr, NULL, &dst);
    SDL_RenderPresent(t->renderer);

    SDL_Delay(3000);
    SDL_DestroyTexture(t->spr[0].txr);
    SDL_FreeSurface(t->spr[0].srf);*/
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


bool start_sdl(t_data *t) {
    t->window = NULL;
    t->width = 1280;
    t->height = 880;
    if (!create_window(t))
        return (false);
    t->renderer = NULL;
    if (!create_renderer(t))
        return (false);
    if (!create_sprites(t))
        return (false);
    t->player = malloc(sizeof(t_player) * 1);

    push_sprite_data(t, "wall_0.bmp", 0);
    push_sprite_data(t, "wall_1.bmp", 1);
    push_sprite_data(t, "player.bmp", 2);
    push_sprite_data(t, "wall_ray.bmp", 3);
    push_sprite_data(t, "weapon.bmp", 4);
    push_sprite_data(t, "cursor.bmp", 5);

    draw_grid(t, false);
    return (true);
}