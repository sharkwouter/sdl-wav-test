#include <SDL.h>
#include <SDL_mixer.h>

#include "Square.hpp"

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER);

    SDL_Window *window = SDL_CreateWindow(
        "sdl-test-wav",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        480,
        272,
        SDL_WINDOW_SHOWN
    );
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    
    SDL_Event event;
    Square square(480/2-16, 272/2-16, 32);
    Mix_Chunk * sound_test = Mix_LoadWAV("test.wav");

    bool running = true;
    while (running) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_CONTROLLERDEVICEADDED:
                    if (SDL_IsGameController(event.cdevice.which)) {
                        SDL_GameControllerOpen(event.cdevice.which);
                    }
                    break;
                case SDL_CONTROLLERBUTTONDOWN:
                    switch (event.cbutton.button) {
                        case SDL_CONTROLLER_BUTTON_A:
                            Mix_PlayChannel(1, sound_test, SDL_FALSE);
                            break;
                        case SDL_CONTROLLER_BUTTON_START:
                            running = false;
                            break;
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_SPACE:
                            Mix_PlayChannel(1, sound_test, SDL_FALSE);
                            break;
                        case SDLK_ESCAPE:
                            running = false;
                            break;
                    }
                    break;
            }
        }

        square.Move();
        square.Draw(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeChunk(sound_test);
    Mix_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}