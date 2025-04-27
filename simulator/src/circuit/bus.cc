EightBitBus::EightBitBus(Simulator* sim, std::string name) {
  this->name = name;
  for (int32_t i = 0; i < 8; i++) {
    bus[i] = sim->AddConnector();
  }
}

void EightBitBus::UpdateUi() {
  ImGui::Begin(name.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize);

  ImGui::Text("Bus: ");
  for (int32_t i = 0; i < 8; i++) {
    ImGui::SameLine();
    bus[i]->UpdateUi(true);
  }

  ImGui::End();
}
