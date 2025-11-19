#include "utils.h"
#include <SDL3/SDL_log.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// false on failure.
int LoadImage(struct image_t* outFrame, const char* filepath) {
    if (!(outFrame || filepath)) {
        SDL_LogError(SDL_LOG_CATEGORY_ASSERT, "One of the arguments given to 'LoadImage' was null. (All arguments are required)");
        return -1;
    }
    outFrame->data = stbi_load(filepath, &outFrame->w, &outFrame->h, &outFrame->chans, 0);
    if (!outFrame->data) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load image %s", filepath);
        outFrame->data = NULL;
        return -2;
    }

    outFrame->surface = SDL_CreateSurfaceFrom(outFrame->w, outFrame->h, SDL_PIXELFORMAT_RGB24, outFrame->data, outFrame->w*(sizeof(char)*outFrame->chans));
    if (!outFrame->surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create surface for image %s\n%s", filepath, SDL_GetError());
        free(outFrame->data);
        outFrame->data = NULL;
        return -3;
    }

    return 0;
}

void FreeImage(struct image_t* image) {
    if (!image) return;
    SDL_DestroySurface(image->surface);
    image->surface = NULL;
    free(image->data);
    image->data = NULL;
    return;
}