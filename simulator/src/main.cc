#define GLAD_GL_IMPLEMENTATION

#include <external/glad.h>
#include <external/SDL2/SDL_opengl.h>
#include <external/SDL2/SDL.h>

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include <imgui.cpp>
#include <imgui_tables.cpp>
#include <imgui_widgets.cpp>
#include <imgui_draw.cpp>
#include <imgui_demo.cpp>
#include <imgui_impl_opengl3.cpp>
#include <imgui_impl_sdl2.cpp>

#include <inttypes.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <string>
#include <deque>
#include <array>

#include <common/log.h>
#include <common/macros.h>

#include <component/component.h>
#include <circuit/circuit.h>
#include <simulator.h>

#include <component/buffer.cc>
#include <component/tri_state_buffer.cc>
#include <component/clock.cc>
#include <component/not_gate.cc>
#include <component/nand_gate.cc>
#include <component/connector.cc>
#include <circuit/alu.cc>
#include <circuit/bus.cc>
#include <circuit/register.cc>
#include <circuit/control.cc>
#include <circuit/computer.cc>
#include <simulator.cc>

static bool global_running;

void HandleEvents() {
  SDL_Event event = {};
  while (SDL_PollEvent(&event)) {
    ImGui_ImplSDL2_ProcessEvent(&event);
    switch (event.type) {
      case SDL_QUIT: {
        global_running = false;
      } break;
      default: break;
    }
  }
}

void GraphicsInit(SDL_Window** window, SDL_GLContext* gl_context) {
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  *window = SDL_CreateWindow(
      "Computer Simulator",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      1280, 720,
      SDL_WINDOW_OPENGL);
  *gl_context = SDL_GL_CreateContext(*window);

  int32_t version = gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);
  if (version == 0) {
    LOG_ERROR("Unable to load OpenGL!");
    UNREACHABLE();
  }

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_FRAMEBUFFER_SRGB);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glClearColor(0, 0, 0, 0);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // enable vsync
  SDL_GL_SetSwapInterval(1);

  LOG_INFO("Successfully initialized the graphics context.");
}

int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    LOG_ERROR("Unable to initialize SDL: %s", SDL_GetError());
    exit(1);
  }

  SDL_Window* window = NULL;
  SDL_GLContext gl_context;
  GraphicsInit(&window, &gl_context);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& imgui_io = ImGui::GetIO();
  imgui_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL3_Init();
  ImGui::StyleColorsDark();

  Simulator sim = {};
  BuildComputer(&sim);
  LOG_INFO("Successfully completed startup sequence.");

  global_running = true;
  while(global_running) {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    HandleEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    sim.UpdateSimulation();
    sim.UpdateUi();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
  SDL_Quit();

  return 0;
}
