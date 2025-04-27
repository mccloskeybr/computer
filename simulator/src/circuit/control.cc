ControlBoard::ControlBoard(std::string name) {
  this->name = name;
}

ControlBoard* ControlBoard::Build(Simulator* sim) {
  this->clock = sim->AddConnector();
  sim->AddComponent<Clock>()
    ->SetFrequencySeconds(1.0f)
    ->SetOut(clock);

  this->a_bus_in = sim->AddConnector();
  this->a_bus_out = sim->AddConnector();
  this->b_bus_in = sim->AddConnector();
  this->b_bus_out = sim->AddConnector();
  this->s_bus_in = sim->AddConnector();
  this->s_bus_out = sim->AddConnector();

  return this;
}

void ControlBoard::UpdateUi(Simulator* sim) {
  ImGui::Begin(name.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize);

  ImGui::Text("Clock: ");
  ImGui::SameLine();
  clock->UpdateUi(sim);

  ImGui::Text("A in: ");
  ImGui::SameLine();
  a_bus_in->UpdateUi(sim);

  ImGui::Text("A out: ");
  ImGui::SameLine();
  a_bus_out->UpdateUi(sim);

  ImGui::Text("B in: ");
  ImGui::SameLine();
  b_bus_in->UpdateUi(sim);

  ImGui::Text("B out: ");
  ImGui::SameLine();
  b_bus_out->UpdateUi(sim);

  ImGui::Text("S in: ");
  ImGui::SameLine();
  s_bus_in->UpdateUi(sim);

  ImGui::Text("S out: ");
  ImGui::SameLine();
  s_bus_out->UpdateUi(sim);

  ImGui::End();
}
