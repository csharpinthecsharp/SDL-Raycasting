#include "../includes/header.h"

int main(int ac, char **av) {
    t_data data;
    t_data *t;
    t = &data;
    if (ac != 1)
    {
        ft_puterror("./a!");
        return (1);
    }
    if (!start_sdl(t))
        return (1);

    t->quit = SDL_FALSE;
    while (!t->quit) {
        while (SDL_PollEvent(&t->event)) {
            if (t->event.type == SDL_QUIT)
                t->quit = SDL_TRUE;
        }
        handle_key_movement(t);
        update_loop(t);
        SDL_Delay(16);
    }
    free_sdl(t);
    //https://zestedesavoir.com/tutoriels/1014/utiliser-la-sdl-en-langage-c/dessiner-dans-la-fenetre/
    // https://lodev.org/cgtutor/raycasting.html
    // https://lodev.org/cgtutor/raycasting2.html
    // https://lodev.org/cgtutor/raycasting3.html
}