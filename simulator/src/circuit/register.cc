void Build1BitRegister(
    Simulator* sim,
    Connector* clock,
    Connector* d_in_en,
    Connector* d_out_en,
    Connector* d_in,
    Connector* d,
    Connector* d_out) {
  // Control
  NandGate* g_0 = sim->AddComponent<NandGate>()
    ->SetIn(clock, d_in_en)
    ->SetOut(sim->AddConnector());

  NotGate* g_1 = sim->AddComponent<NotGate>()
    ->SetIn(*g_0)
    ->SetOut(sim->AddConnector());

  // D-latch 1
  NandGate* g_2 = sim->AddComponent<NandGate>()
    ->SetIn(*g_1, d_in)
    ->SetOut(sim->AddConnector());

  NotGate* g_3 = sim->AddComponent<NotGate>()
    ->SetIn(d_in)
    ->SetOut(sim->AddConnector());

  NandGate* g_4 = sim->AddComponent<NandGate>()
    ->SetIn(*g_3, *g_1)
    ->SetOut(sim->AddConnector());

  NandGate* g_5 = sim->AddComponent<NandGate>()
    ->SetOut(d);
  NandGate* g_6 = sim->AddComponent<NandGate>()
    ->SetOut(sim->AddConnector());
  g_5->SetIn(*g_2, *g_6);
  g_6->SetIn(*g_4, *g_5);

  // D-latch 2
  NandGate* g_7 = sim->AddComponent<NandGate>()
    ->SetIn(*g_0, *g_5)
    ->SetOut(sim->AddConnector());

  NotGate* g_8 = sim->AddComponent<NotGate>()
    ->SetIn(*g_5)
    ->SetOut(sim->AddConnector());

  NandGate* g_9 = sim->AddComponent<NandGate>()
    ->SetIn(*g_8, *g_0)
    ->SetOut(sim->AddConnector());

  NandGate* g_10 = sim->AddComponent<NandGate>()
    ->SetOut(sim->AddConnector());
  NandGate* g_11 = sim->AddComponent<NandGate>()
    ->SetOut(sim->AddConnector());
  g_10->SetIn(*g_7, *g_11);
  g_11->SetIn(*g_9, *g_10);

  // Output
  NotGate* g_12 = sim->AddComponent<NotGate>()
    ->SetIn(*g_11)
    ->SetOut(sim->AddConnector());

  TriStateBuffer* g_13 = sim->AddComponent<TriStateBuffer>()
    ->SetIn(*g_12)
    ->SetEnable(d_out_en)
    ->SetOut(d_out);
}

EightBitRegister::EightBitRegister(std::string name) {
  this->name = name;
}

EightBitRegister* EightBitRegister::SetDIn(std::array<Connector*, 8> d_in_) {
  this->d_in = d_in_;
  return this;
}

EightBitRegister* EightBitRegister::SetDOut(std::array<Connector*, 8> d_out_) {
  this->d_out = d_out_;
  return this;
}

EightBitRegister* EightBitRegister::SetClock(Connector* clock_) {
  this->clock = clock_;
  return this;
}

EightBitRegister* EightBitRegister::SetDInEnable(Connector* d_in_en_) {
  this->d_in_en = d_in_en_;
  return this;
}

EightBitRegister* EightBitRegister::SetDOutEnable(Connector* d_out_en_) {
  this->d_out_en = d_out_en_;
  return this;
}

EightBitRegister* EightBitRegister::Build(Simulator* sim) {
  for (int32_t i = 0; i < 8; i++) {
    this->d[i] = sim->AddConnector();
    Build1BitRegister(sim, clock, d_in_en, d_out_en, d_in[i], d[i], d_out[i]);
  }
  return this;
}

void EightBitRegister::UpdateUi(Simulator* sim) {
  ImGui::Begin(name.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize);

  ImGui::Text("Clock: ");
  ImGui::SameLine();
  clock->UpdateUi(sim);

  ImGui::SameLine();
  ImGui::Text("D in: ");
  ImGui::SameLine();
  d_in_en->UpdateUi(sim);

  ImGui::SameLine();
  ImGui::Text("D out: ");
  ImGui::SameLine();
  d_out_en->UpdateUi(sim);

  ImGui::Text("D: ");
  for (int32_t i = 0; i < 8; i++) {
    ImGui::SameLine();
    d[i]->UpdateUi(sim);
  }

  ImGui::End();
}
