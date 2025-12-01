#include <SDL3/SDL.h>
#include <stdio.h>

#include "game.h"

game_t game = {0};

void tick();
void render(SDL_Renderer* renderer);

int main() {
    game.exit = false;
    game.fps_cap = 144;
    game.show_debug_info = true;
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL, %s", SDL_GetError());
        return -1;
    }
    
    game.window = SDL_CreateWindow("IDK", 800, 600, 0);
    if (!game.window) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize window, %s", SDL_GetError());
        return -2;
    }

    game.renderer = SDL_CreateRenderer(game.window, NULL);
    if (!game.renderer) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize renderer, %s", SDL_GetError());
        return -3;
    }

    Uint64 nowTime = SDL_GetPerformanceCounter();
    Uint64 lastTime = 0;
    Uint64 startTicks = SDL_GetTicks();
    Uint64 lastTicks = 0;
    int frameCountTotal = 0;
    int frameCount = 0;

    while (!game.exit) {

        lastTime = nowTime;
        nowTime = SDL_GetPerformanceCounter();

        game.deltaTime = ((nowTime - lastTime)*1000 / (double)SDL_GetPerformanceFrequency() );

        // logic / tick
        Uint64 beginTime = SDL_GetPerformanceCounter();
        tick();
        render(game.renderer);
        frameCountTotal++;
        frameCount++;
        Uint64 endTime = SDL_GetPerformanceCounter();
        game.fps_avg = frameCountTotal / ((SDL_GetTicks() - startTicks) / 1000.f);


        Uint64 nowTicks = SDL_GetTicks();

        if (nowTicks - lastTicks >= 1000) {
            game.fps = frameCount;
            frameCount = 0;
            lastTicks = nowTicks;
        }

        
        float elapsedTime = (endTime - beginTime) / ((float) SDL_GetPerformanceFrequency() * 1000.0f);
        if (game.fps_cap != 0) SDL_Delay(floorf((1000.f / (float)game.fps_cap) - elapsedTime));
    }

    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);
    SDL_Quit();

    return 0;
}

void render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 64, 0, 175, 255);
    SDL_RenderClear(renderer);

    if (game.show_debug_info) {
        int x = 25;
        int y = 25;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        char dbg_S[256];
        sprintf(&dbg_S, "fps: %d", game.fps);
        SDL_RenderDebugText(renderer, x, y, dbg_S);
        y+=10;
        sprintf(&dbg_S, "avg: %f", game.fps_avg);
        SDL_RenderDebugText(renderer, x, y, dbg_S);
        y+=10;
        sprintf(&dbg_S, "dT: %f", game.deltaTime);
        SDL_RenderDebugText(renderer, x, y, dbg_S);
        y+=10;
    }

    SDL_RenderPresent(renderer);
}

void tick() {
    // events
    for (SDL_Event ev; SDL_PollEvent(&ev);) {
        if (ev.type == SDL_EVENT_QUIT) game.exit = true;
    }
    // logic
}