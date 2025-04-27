void Build1BitAdder(
    Simulator* sim,
    Connector* a,
    Connector* b,
    Connector* c_in,
    Connector* s,
    Connector* c_out) {
  NandGate* g_0 = sim->AddNandGate();
  g_0->SetIn0(a);
  g_0->SetIn1(b);
  g_0->SetOut(sim->AddConnector());

  NandGate* g_1 = sim->AddNandGate();
  g_1->SetIn0(a);
  g_1->SetIn1(g_0->GetOut());
  g_1->SetOut(sim->AddConnector());

  NandGate* g_2 = sim->AddNandGate();
  g_2->SetIn0(b);
  g_2->SetIn1(g_0->GetOut());
  g_2->SetOut(sim->AddConnector());

  NandGate* g_3 = sim->AddNandGate();
  g_3->SetIn0(g_1->GetOut());
  g_3->SetIn1(g_2->GetOut());
  g_3->SetOut(sim->AddConnector());

  NandGate* g_4 = sim->AddNandGate();
  g_4->SetIn0(g_3->GetOut());
  g_4->SetIn1(c_in);
  g_4->SetOut(sim->AddConnector());

  NandGate* g_5 = sim->AddNandGate();
  g_5->SetIn0(g_3->GetOut());
  g_5->SetIn1(g_4->GetOut());
  g_5->SetOut(sim->AddConnector());

  NandGate* g_6 = sim->AddNandGate();
  g_6->SetIn0(g_4->GetOut());
  g_6->SetIn1(c_in);
  g_6->SetOut(sim->AddConnector());

  NandGate* g_7 = sim->AddNandGate();
  g_7->SetIn0(g_5->GetOut());
  g_7->SetIn1(g_6->GetOut());
  g_7->SetOut(s);

  NandGate* g_8 = sim->AddNandGate();
  g_8->SetIn0(g_4->GetOut());
  g_8->SetIn1(g_0->GetOut());
  g_8->SetOut(c_out);
}

EightBitAdder::EightBitAdder(Simulator* sim) {
  for (int32_t i = 0; i < 8; i++) {
    a[i] = sim->AddConnector();
    b[i] = sim->AddConnector();
    s[i] = sim->AddConnector();
  }
  c_in = sim->AddConnector();

  Connector* current_c_in = NULL;
  Connector* current_c_out = c_in;
  for (int32_t i = 0; i < 8; i++) {
    current_c_in = current_c_out;
    current_c_out = sim->AddConnector();
    Build1BitAdder(sim, a[i], b[i], current_c_in, s[i], current_c_out);
  }

  c_out = current_c_out;
}

void EightBitAdder::UpdateUi() {
  ImGui::Begin("Adder");

  ImGui::Text("A: ");
  for (int32_t i = 0; i < 8; i++) {
    ImGui::SameLine();
    a[i]->UpdateUi(true);
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
