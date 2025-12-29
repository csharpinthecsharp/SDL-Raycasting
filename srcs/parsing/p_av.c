#include "../../includes/header.h"

bool try_open(const char *path) {
    int fd = -1;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (false);
    close(fd);
    return (true);
}

bool cmp_file_extension(const char *path) {
    if (ft_strncmp(path + ft_strlen(path) - 4, ".aaa", 4) != 0)
        return (false);
    return (true);

}

bool is_a_valid_file(const char *path) {
    if (!try_open(path)) {
        ft_puterror("Failed to open the file!");
        return (false);
    }
    ft_putgood("Successfully opened the file!");
    if (!cmp_file_extension(path)) {
        ft_puterror("File extension is wrong!");
        return (false);
    }
    ft_putgood("File extension is correct!");
    return (true);
}