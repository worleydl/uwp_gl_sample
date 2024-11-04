#include <Windows.h>

#include "glad/glad.h"
#include "SDL2/SDL.h"

// You can locally declare a SDL_main function or call to a DLL export (mingw works nice for this) 
int SDL_main(int argc, char* argv[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return -1;
    }

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "Sample Green Screen",      // Window title (not really used)
        SDL_WINDOWPOS_UNDEFINED,    // Window positions not used
        SDL_WINDOWPOS_UNDEFINED,
        640,                        // Width of framebuffer
        480,                        // Height of framebuffer
        SDL_WINDOW_OPENGL| SDL_WINDOW_FULLSCREEN_DESKTOP // Flags, need FULLSCREEN to stretch a lower res
    );

    if (!window) {
        SDL_Quit();
        return -1;
    }

    // Create OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_GL_MakeCurrent(window, glContext);

    // Load extensions after creating context
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
    
    SDL_Event event;
    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
        }

        // Set clear color to green
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // RGBA
        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

        // Swap buffers
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}

// Entry point into app (Note, SDL doesn't like being init from here you must call SDL_main)
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR argv, int argc)
{
    return SDL_WinRTRunApp(SDL_main, NULL);
}
