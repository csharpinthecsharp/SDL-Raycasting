#include "../includes/header.h"
#include <SDL2/SDL_events.h>

int main(int ac, char **av) {
    t_data data;
    t_data *t;
    t = &data;
    if (ac != 2)
    {
        ft_puterror("Invalid selection!");
        return (1);
    }
    if (!is_a_valid_file(av[1]))
        return (1);
    if (!start_sdl(t))
        return (1);
    //https://zestedesavoir.com/tutoriels/1014/utiliser-la-sdl-en-langage-c/dessiner-dans-la-fenetre/
    // https://lodev.org/cgtutor/raycasting.html
    // https://lodev.org/cgtutor/raycasting2.html
    // https://lodev.org/cgtutor/raycasting3.html
}