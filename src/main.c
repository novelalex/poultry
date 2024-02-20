#include "poultry.c"
#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 600

int scc(int code);
void *scp(void *ptr);


void CKN_render(uint32_t * pixels) {

    poultry_fill(pixels, WIDTH, HEIGHT, 0xFF000044);

}

//static uint32_t pixels[WIDTH * HEIGHT];
int main(int argc, char **argv) {
    scc(SDL_Init(SDL_INIT_VIDEO));

    SDL_Window *window = scp(SDL_CreateWindow(
        "Poultry Window",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WIDTH, HEIGHT,
        SDL_WINDOW_RESIZABLE));

    SDL_Renderer *const renderer = scp(SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

    scc(SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT));

    SDL_Texture * screen_texture = scp(SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING,
    WIDTH, HEIGHT));
    uint32_t *pixels = malloc(WIDTH * HEIGHT * sizeof(uint32_t));

    int quit = 0;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: {
                quit = 1;
                break;
            } break;
            }
        }

        scc(SDL_SetRenderDrawColor(renderer, 0, 0, 0,255));
        scc(SDL_RenderClear(renderer));

        CKN_render(pixels);


        SDL_UpdateTexture(screen_texture, NULL, pixels, WIDTH * 4);
        SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    free(pixels);
    SDL_DestroyWindow(scp(window));
    SDL_Quit();

    return 0;
}


int scc(int code) {
    if (code < 0) {
        fprintf(stderr, "SDL error: %s\n", SDL_GetError());
        exit(1);
    }
    return code;
}

void *scp(void *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "SDL error: %s\n", SDL_GetError());
        exit(1);
    }
    return ptr;
}

