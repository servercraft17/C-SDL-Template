#include <SDL3/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

double deltaTime = 0.0f;
float avgfps = 0.0f;
int fps = 0;

int tick();
int render(SDL_Renderer* renderer);

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL, %s", SDL_GetError());
        return -1;
    }
    
    window = SDL_CreateWindow("IDK", 800, 600, 0);
    if (!window) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize window, %s", SDL_GetError());
        return -2;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize renderer, %s", SDL_GetError());
        return -3;
    }

    Uint64 nowTime = SDL_GetPerformanceCounter();
    Uint64 lastTime = 0;
    Uint64 startTicks = SDL_GetTicks();
    Uint64 lastTicks = 0;
    int frameCountTotal = 0;
    int frameCount = 0;

    bool running = true;
    while (running) {

        lastTime = nowTime;
        nowTime = SDL_GetPerformanceCounter();

        deltaTime = ((nowTime - lastTime)*1000 / (double)SDL_GetPerformanceFrequency() );

        // events
        for (SDL_Event ev; SDL_PollEvent(&ev);) {
            if (ev.type == SDL_EVENT_QUIT) running = false;
        }
        // logic / tick
        render(renderer);
        frameCountTotal++;
        frameCount++;

        avgfps = frameCountTotal / ((SDL_GetTicks() - startTicks) / 1000.f);

        Uint64 nowTicks = SDL_GetTicks();

        if (nowTicks - lastTicks >= 1000) {
            fps = frameCount;
            frameCount = 0;
            lastTicks = nowTicks;
        }

        SDL_Log("Dt: %f\nfps avg: %f\nfps: %d", deltaTime, avgfps, fps);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 64, 0, 175, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
    return 0;
}