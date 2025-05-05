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
#include <circuit/ring_counter.cc>
#include <computer.cc>
#include <simulator.cc>

static bool global_running = true;
int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) { UNREACHABLE(); }
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_Window* window = SDL_CreateWindow(
      "Computer Simulator",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      1280, 720,
      SDL_WINDOW_OPENGL);
  SDL_GLContext gl_context = SDL_GL_CreateContext(window);

  int32_t version = gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);
  if (version == 0) { UNREACHABLE(); }
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_FRAMEBUFFER_SRGB);
  SDL_GL_SetSwapInterval(1); // enable vsync

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& imgui_io = ImGui::GetIO();
  imgui_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL3_Init();
  ImGui::StyleColorsDark();

  LOG_INFO("Successfully completed startup sequence.");

  Simulator sim = {};
  BuildComputer(&sim);
  while(global_running) {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    SDL_Event event = {};
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT) { global_running = false; }
    }

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
