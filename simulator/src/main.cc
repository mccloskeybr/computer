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

#include <common/log.h>
#include <common/macros.h>

#include <component.h>
#include <simulator.h>

#include <circuits.cc>
#include <component.cc>
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

  Simulation sim = {};

  /*
  Connector* c_in = sim.AddObservableConnector("c_in", true);
  Connector* a_0_in = sim.AddObservableConnector("a_0", true);
  Connector* a_1_in = sim.AddObservableConnector("a_1", true);
  Connector* a_2_in = sim.AddObservableConnector("a_2", true);
  Connector* a_3_in = sim.AddObservableConnector("a_3", true);
  Connector* b_0_in = sim.AddObservableConnector("b_0", true);
  Connector* b_1_in = sim.AddObservableConnector("b_1", true);
  Connector* b_2_in = sim.AddObservableConnector("b_2", true);
  Connector* b_3_in = sim.AddObservableConnector("b_3", true);
  Connector* s_0_out = sim.AddObservableConnector("s_0", false);
  Connector* s_1_out = sim.AddObservableConnector("s_1", false);
  Connector* s_2_out = sim.AddObservableConnector("s_2", false);
  Connector* s_3_out = sim.AddObservableConnector("s_3", false);
  Connector* c_out = sim.AddObservableConnector("c_out", false);
  Build4BitAdder(
      &sim,
      a_0_in, a_1_in, a_2_in, a_3_in,
      b_0_in, b_1_in, b_2_in, b_3_in,
      c_in,
      s_0_out, s_1_out, s_2_out, s_3_out,
      c_out);
  */

  Connector* clock = sim.AddObservableConnector("clock", true);
  Connector* d_in = sim.AddObservableConnector("d_in", true);
  Connector* d_out = sim.AddObservableConnector("d_out", true);
  Connector* d_0 = sim.AddObservableConnector("d_0", true);
  Connector* d_1 = sim.AddObservableConnector("d_1", true);
  Connector* d_2 = sim.AddObservableConnector("d_2", true);
  Connector* d_3 = sim.AddObservableConnector("d_3", true);
  Build4BitRegister(&sim, clock, d_in, d_out, d_0, d_1, d_2, d_3);

  LOG_INFO("Successfully completed startup sequence.");

  global_running = true;
  while(global_running) {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    HandleEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

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
