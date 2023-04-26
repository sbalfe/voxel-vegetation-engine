//
// Created by shriller44 on 4/16/23.
//

#include "GUI.h"

GUI::GUI(int screen_width, int screen_height){

  // Initialize SDL Video
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Failed to initialize SDL video\n");
  }

  // Create main window
  window_ = SDL_CreateWindow(
      "SDL App",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      static_cast<int>(screen_width), static_cast<int>(screen_height),
      SDL_WINDOW_OPENGL);

  if (window_ == nullptr) {
    fprintf(stderr, "Failed to create main window\n");
    SDL_Quit();
  }

  // Initialize rendering context
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  /* create opengl context in SDL */
  context_ = SDL_GL_CreateContext(window_);

  if (context_ == nullptr) {
    fprintf(stderr, "Failed to create GL context\n");
    SDL_DestroyWindow(window_);
    SDL_Quit();
  }

  imgui_interface_ =  std::make_unique<Interface>(window_);

  SDL_GL_SetSwapInterval(1); // Use VSYNC
}

void GUI::Destroy(){
  SDL_GL_DeleteContext(context_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

[[nodiscard]] bool GUI::FlagSet(Interface::Flags flags) const { return imgui_interface_->FlagSet(flags);}

void GUI::ShowGUI(){ imgui_interface_->CoreGui(); }

void GUI::Init() const {
  ImGui_ImplSDL2_InitForOpenGL(window_, SDL_GL_GetCurrentContext());
}

void GUI::NewFrame() const {
  ImGui_ImplSDL2_NewFrame(window_);
}

void GUI::SwapWindow() const {
  SDL_GL_SwapWindow(window_);
}