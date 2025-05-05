void Build1BitRingCounter(
    Simulator* sim,
    Connector* clock,
    Connector* reset,
    Connector* d_in,
    Connector* d,
    Connector* d_out) {
  // D-latch 1

  NotGate* g_0 = sim->AddComponent<NotGate>()
    ->SetIn(d_in)
    ->SetOut(sim->AddConnector());

  NandGate* g_1 = sim->AddComponent<NandGate>()
    ->SetIn(d_in, clock)
    ->SetOut(sim->AddConnector());

  NandGate* g_2 = sim->AddComponent<NandGate>()
    ->SetIn(*g_0, clock)
    ->SetOut(sim->AddConnector());

  NandGate* g_3 = sim->AddComponent<NandGate>()
    ->SetOut(d);
  NandGate* g_4 = sim->AddComponent<NandGate>()
    ->SetOut(sim->AddConnector());
  g_3->SetIn(*g_1, *g_4);
  g_4->SetIn(*g_2, *g_3);

  // D-latch 2

  NotGate* clock_inv = sim->AddComponent<NotGate>()
    ->SetIn(clock)
    ->SetOut(sim->AddConnector());

  NotGate* g_5 = sim->AddComponent<NotGate>()
    ->SetIn(*g_3)
    ->SetOut(sim->AddConnector());

  NandGate* g_6 = sim->AddComponent<NandGate>()
    ->SetIn(*g_3, *clock_inv)
    ->SetOut(sim->AddConnector());

  NandGate* g_7 = sim->AddComponent<NandGate>()
    ->SetIn(*g_5, *clock_inv)
    ->SetOut(sim->AddConnector());

  NandGate* g_8 = sim->AddComponent<NandGate>()
    ->SetOut(d_out);
  NandGate* g_9 = sim->AddComponent<NandGate>()
    ->SetOut(sim->AddConnector());
  g_8->SetIn(*g_6, *g_9);
  g_9->SetIn(*g_7, *g_8);
}

EightBitRingCounter::EightBitRingCounter(std::string name) {
  this->name = name;
}

EightBitRingCounter* EightBitRingCounter::SetClock(Connector* clock_) {
  this->clock = clock_;
  return this;
}

EightBitRingCounter* EightBitRingCounter::SetReset(Connector* reset_) {
  this->reset = reset_;
  return this;
}

EightBitRingCounter* EightBitRingCounter::Build(Simulator* sim) {
  std::array<Connector*, 8> d_out = {};
  for (int32_t i = 0; i < 8; i++) {
    this->d[i] = sim->AddConnector();
    d_out[i] = sim->AddConnector();
  }
  for (int32_t i = 0; i < 8; i++) {
    Build1BitRingCounter(sim, clock, reset, d_out[(i + 7) % 8], d[i], d_out[i]);
  }
  return this;
}

void EightBitRingCounter::UpdateUi(Simulator* sim) {
  ImGui::Begin(name.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize);

  ImGui::Text("Clock: ");
  ImGui::SameLine();
  clock->UpdateUi(sim);

  ImGui::Text("D: ");
  for (int32_t i = 0; i < 8; i++) {
    ImGui::SameLine();
    d[i]->UpdateUi(sim);
  }

  ImGui::End();
}
