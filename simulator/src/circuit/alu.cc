void Build1BitAdder(
    Simulator* sim,
    Connector* a,
    Connector* b,
    Connector* c_in,
    Connector* s,
    Connector* c_out) {
  NandGate* g_0 = sim->AddComponent<NandGate>()
    ->SetIn(a, b)
    ->SetOut(sim->AddConnector());

  NandGate* g_1 = sim->AddComponent<NandGate>()
    ->SetIn(a, *g_0)
    ->SetOut(sim->AddConnector());

  NandGate* g_2 = sim->AddComponent<NandGate>()
    ->SetIn(b, *g_0)
    ->SetOut(sim->AddConnector());

  NandGate* g_3 = sim->AddComponent<NandGate>()
    ->SetIn(*g_1, *g_2)
    ->SetOut(sim->AddConnector());

  NandGate* g_4 = sim->AddComponent<NandGate>()
    ->SetIn(*g_3, c_in)
    ->SetOut(sim->AddConnector());

  NandGate* g_5 = sim->AddComponent<NandGate>()
    ->SetIn(*g_3, *g_4)
    ->SetOut(sim->AddConnector());

  NandGate* g_6 = sim->AddComponent<NandGate>()
    ->SetIn(*g_4, c_in)
    ->SetOut(sim->AddConnector());

  NandGate* g_7 = sim->AddComponent<NandGate>()
    ->SetIn(*g_5, *g_6)
    ->SetOut(s);

  NandGate* g_8 = sim->AddComponent<NandGate>()
    ->SetIn(*g_4, *g_0)
    ->SetOut(c_out);
}

EightBitAdder::EightBitAdder(
      Simulator* sim, std::string name,
      std::array<Connector*, 8> a, std::array<Connector*, 8> b, std::array<Connector*, 8> s,
      Connector* c_in, Connector* c_out) {
  this->name = name;
  this->a = a;
  this->b = b;
  this->s = s;
  this->c_in = c_in;
  this->c_out = c_out;

  Connector* current_c_in = NULL;
  Connector* current_c_out = c_in;
  for (int32_t i = 0; i < 8; i++) {
    current_c_in = current_c_out;
    if (i < 7) { current_c_out = sim->AddConnector(); }
    else       { current_c_out = c_out; }
    Build1BitAdder(sim, a[i], b[i], current_c_in, s[i], current_c_out);
  }
}

void EightBitAdder::UpdateUi() {
  ImGui::Begin(name.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize);

  ImGui::Text("A: ");
  for (int32_t i = 0; i < 8; i++) {
    ImGui::SameLine();
    a.at(i)->UpdateUi(true);
  }

  ImGui::Text("B: ");
  for (int32_t i = 0; i < 8; i++) {
    ImGui::SameLine();
    b[i]->UpdateUi(true);
  }

  ImGui::Text("Carry in: ");
  ImGui::SameLine();
  c_in->UpdateUi(true);

  ImGui::Text("Sum: ");
  for (int32_t i = 0; i < 8; i++) {
    ImGui::SameLine();
    s[i]->UpdateUi(false);
  }

  ImGui::Text("Carry out: ");
  ImGui::SameLine();
  c_out->UpdateUi(false);

  ImGui::End();
}
