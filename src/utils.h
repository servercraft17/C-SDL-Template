#ifndef UTILS_H
#define UTILS_H

#include <SDL3/SDL.h>

struct image_t {
    unsigned char* data;
    SDL_Surface* surface;
    int w, h, chans;
};
typedef struct image_t Image;

#endif/* UTILS_H */
