void Build1BitRegister(
    Simulator* sim,
    Connector* clock,
    Connector* d_in,
    Connector* d_out,
    Connector* d) {
  // Control
  NandGate* g_0 = sim->AddNandGate();
  g_0->SetIn0(clock);
  g_0->SetIn1(d_in);
  g_0->SetOut(sim->AddConnector());

  NotGate* g_1 = sim->AddNotGate();
  g_1->SetIn(g_0->GetOut());
  g_1->SetOut(sim->AddConnector());

  // D-latch 1
  NandGate* g_2 = sim->AddNandGate();
  g_2->SetIn0(g_1->GetOut());
  g_2->SetIn1(d);
  g_2->SetOut(sim->AddConnector());

  NotGate* g_3 = sim->AddNotGate();
  g_3->SetIn(d);
  g_3->SetOut(sim->AddConnector());

  NandGate* g_4 = sim->AddNandGate();
  g_4->SetIn0(g_3->GetOut());
  g_4->SetIn1(g_1->GetOut());
  g_4->SetOut(sim->AddConnector());

  NandGate* g_5 = sim->AddNandGate();
  g_5->SetOut(sim->AddConnector());
  NandGate* g_6 = sim->AddNandGate();
  g_6->SetOut(sim->AddConnector());
  g_5->SetIn0(g_2->GetOut());
  g_5->SetIn1(g_6->GetOut());
  g_6->SetIn0(g_4->GetOut());
  g_6->SetIn1(g_5->GetOut());

  // D-latch 2
  NandGate* g_7 = sim->AddNandGate();
  g_7->SetIn0(g_0->GetOut());
  g_7->SetIn1(g_5->GetOut());
  g_7->SetOut(sim->AddConnector());

  NotGate* g_8 = sim->AddNotGate();
  g_8->SetIn(g_5->GetOut());
  g_8->SetOut(sim->AddConnector());

  NandGate* g_9 = sim->AddNandGate();
  g_9->SetIn0(g_8->GetOut());
  g_9->SetIn1(g_0->GetOut());
  g_9->SetOut(sim->AddConnector());

  NandGate* g_10 = sim->AddNandGate();
  g_10->SetOut(sim->AddConnector());
  NandGate* g_11 = sim->AddNandGate();
  g_11->SetOut(sim->AddConnector());
  g_10->SetIn0(g_7->GetOut());
  g_10->SetIn1(g_11->GetOut());
  g_11->SetIn0(g_9->GetOut());
  g_11->SetIn1(g_10->GetOut());

  // Output
  NotGate* g_12 = sim->AddNotGate();
  g_12->SetIn(g_11->GetOut());
  g_12->SetOut(sim->AddConnector());

  TriStateBuffer* g_13 = sim->AddTriStateBuffer();
  g_13->SetIn(g_12->GetOut());
  g_13->SetEnable(d_out);
  g_13->SetOut(d);
}

EightBitRegister::EightBitRegister(Simulator* sim) {
  for (int32_t i = 0; i < 8; i++) {
    d[i] = sim->AddConnector();
  }
  clock = sim->AddConnector();
  d_in = sim->AddConnector();
  d_out = sim->AddConnector();

  for (int32_t i = 0; i < 8; i++) {
    Build1BitRegister(sim, clock, d_in, d_out, d[i]);
  }
}

void EightBitRegister::UpdateUi() {
  ImGui::Begin("Register");

  ImGui::Text("Clock: ");
  ImGui::SameLine();
  clock->UpdateUi(true);

  ImGui::Text("D in: ");
  ImGui::SameLine();
  d_in->UpdateUi(true);

  ImGui::Text("D out: ");
  ImGui::SameLine();
  d_out->UpdateUi(true);

  ImGui::Text("D: ");
  for (int32_t i = 0; i < 8; i++) {
    ImGui::SameLine();
    d[i]->UpdateUi(true);
  }

  ImGui::End();
}
