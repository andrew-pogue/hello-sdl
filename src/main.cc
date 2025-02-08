#include <SDL3/SDL.h>
#include <iostream>
#include <cstdlib>

static bool play = false;
static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

bool open();
void close();
void error(const char *msg = nullptr);
void handle_event(const SDL_Event &event);
void update(double dt);
void draw();

int main(int argc, char *argv[]) {
    if (!open()) {
        close();
        return EXIT_FAILURE;
    }

    SDL_Event event;
    while (play) {
        while (SDL_PollEvent(&event)) handle_event(event);
        update(0.0);
        draw();
    }

    close();
    return EXIT_SUCCESS;
}

bool open() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        error("Could not initialize SDL!");
        return false;
    }
    window = SDL_CreateWindow("Hello SDL3", 800, 600, 0);
    if (!window) {
        error("Could not create window!");
        return false;
    }
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        error("Could not create renderer!");
        return false;
    }
    play = true;
    return true;
}

void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void error(const char *msg) {
    const char *error = SDL_GetError();
    if (msg) std::cerr << msg << '\n';
    if (error) std::cerr << "Error: " << SDL_GetError() << '\n';
}

void handle_event(const SDL_Event &event) {
    switch (event.type) {
        case SDL_EVENT_QUIT:
            play = false;
            break;
        case SDL_EVENT_KEY_DOWN:
            play = (event.key.key != SDLK_ESCAPE);
            break;
    }
}

void update(double dt) {
}

void draw() {
    SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
