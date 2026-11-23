#include <cstdio>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl3.h"

static int RunDemo(SDL_Window* window, SDL_GLContext glContext)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui::GetIO().IniFilename = nullptr;

    if(!ImGui_ImplSDL3_InitForOpenGL(window, glContext))
    {
        std::fputs("Could not initialize the ImGui SDL3 backend.\n", stderr);
        ImGui::DestroyContext();
        return 1;
    }

    if (!ImGui_ImplOpenGL3_Init("#version 130")) 
    {
        std::fputs("Could not initialize the ImGui OpenGL backend.\n", stderr);
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
        return 1;
    }

    const SDL_WindowID windowId= SDL_GetWindowID(window);
    const bool hasVSync = SDL_GL_SetSwapInterval(1);
    bool running = true;

    while(running)
    {
        SDL_Event event{};
        while(SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);

            if (event.type == SDL_EVENT_QUIT ||
                (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
                 event.window.windowID == windowId))
            {
                running = false;
                break;
            }
        }

        if (!running) 
        {
            break;
        }

        int width = 0;
        int height = 0;
        if ((SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) ||
            !SDL_GetWindowSizeInPixels(window, &width, &height) ||
            width == 0 || height == 0)
        {
            SDL_Delay(10);
            continue;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::Render();
        glViewport(0, 0, width, height);
        glClearColor(0.12f, 0.14f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);

        if (!hasVSync) 
        {
            SDL_Delay(16);
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    return 0;
}

int main(int, char**)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) 
    {
        std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Window* window = SDL_CreateWindow(
        "DevCaddy", 1280, 800,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);

    if (!window) 
    {
        std::fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) 
    {
        std::fprintf(stderr, "SDL_GL_CreateContext failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    const int result = RunDemo(window, glContext);

    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return result;
}