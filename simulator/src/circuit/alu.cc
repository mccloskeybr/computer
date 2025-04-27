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

EightBitAdder::EightBitAdder(std::string name) {
  this->name = name;
}

EightBitAdder* EightBitAdder::SetA(std::array<Connector*, 8> a_) {
  this->a = a_;
  return this;
}

EightBitAdder* EightBitAdder::SetB(std::array<Connector*, 8> b_) {
  this->b = b_;
  return this;
}

EightBitAdder* EightBitAdder::SetS(std::array<Connector*, 8> s_) {
  this->s = s_;
  return this;
}

EightBitAdder* EightBitAdder::SetCarryIn(Connector* c_in_) {
  this->c_in = c_in_;
  return this;
}

EightBitAdder* EightBitAdder::SetCarryOut(Connector* c_out_) {
  this->c_out = c_out_;
  return this;
}

EightBitAdder* EightBitAdder::Build(Simulator* sim) {
  Connector* current_c_in = NULL;
  Connector* current_c_out = c_in;
  for (int32_t i = 0; i < 8; i++) {
    current_c_in = current_c_out;
    if (i < 7) { current_c_out = sim->AddConnector(); }
    else       { current_c_out = c_out; }
    Build1BitAdder(sim, a[i], b[i], current_c_in, s[i], current_c_out);
  }
  return this;
}

void EightBitAdder::UpdateUi(Simulator* sim) {
  ImGui::Begin(name.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize);

  ImGui::Text("A: ");
  for (int32_t i = 0; i < 8; i++) {
    ImGui::SameLine();
    a[i]->UpdateUi(sim);
  }

  ImGui::Text("B: ");
  for (int32_t i = 0; i < 8; i++) {
    ImGui::SameLine();
    b[i]->UpdateUi(sim);
  }

  ImGui::Text("Carry in: ");
  ImGui::SameLine();
  c_in->UpdateUi(sim);

  ImGui::Text("Sum: ");
  for (int32_t i = 0; i < 8; i++) {
    ImGui::SameLine();
    s[i]->UpdateUi(sim);
  }

  ImGui::Text("Carry out: ");
  ImGui::SameLine();
  c_out->UpdateUi(sim);

  ImGui::End();
}
