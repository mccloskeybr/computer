EightBitBus::EightBitBus(std::string name) {
  this->name = name;
}

EightBitBus* EightBitBus::Build(Simulator* sim) {
  for (int32_t i = 0; i < 8; i++) {
    bus[i] = sim->AddConnector();
  }
  return this;
}

void EightBitBus::UpdateUi(Simulator* sim) {
  ImGui::Begin(name.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize);

  ImGui::Text("Bus: ");
  for (int32_t i = 0; i < 8; i++) {
    ImGui::SameLine();
    bus[i]->UpdateUi(sim);
  }

  ImGui::End();
}
