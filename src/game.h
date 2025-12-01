#ifndef SRC_GAME_H
#define SRC_GAME_H

#include <SDL3/SDL.h>
#include <stdbool.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int fps, fps_cap;
    float fps_avg;
    double deltaTime;
    bool show_debug_info;
    bool exit;
} game_t;



#endif /* SRC_GAME_H */