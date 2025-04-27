ControlBoard::ControlBoard(Simulator* sim, std::string name) {
  this->name = name;

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
}

void ControlBoard::UpdateUi() {
  ImGui::Begin(name.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize);

  ImGui::Text("Clock: ");
  ImGui::SameLine();
  clock->UpdateUi(true);

  ImGui::Text("A in: ");
  ImGui::SameLine();
  a_bus_in->UpdateUi(true);

  ImGui::Text("A out: ");
  ImGui::SameLine();
  a_bus_out->UpdateUi(true);

  ImGui::Text("B in: ");
  ImGui::SameLine();
  b_bus_in->UpdateUi(true);

  ImGui::Text("B out: ");
  ImGui::SameLine();
  b_bus_out->UpdateUi(true);

  ImGui::Text("S in: ");
  ImGui::SameLine();
  s_bus_in->UpdateUi(true);

  ImGui::Text("S out: ");
  ImGui::SameLine();
  s_bus_out->UpdateUi(true);

  ImGui::End();
}
