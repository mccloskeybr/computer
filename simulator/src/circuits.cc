void Build1BitAdder(
    Simulation* sim,
    Connector* a_in,
    Connector* b_in,
    Connector* c_in,
    Connector* s_out,
    Connector* c_out) {
  NandGate* g_0 = sim->AddNandGate();
  g_0->SetIn0(a_in);
  g_0->SetIn1(b_in);
  g_0->SetOut(sim->AddConnector());

  NandGate* g_1 = sim->AddNandGate();
  g_1->SetIn0(a_in);
  g_1->SetIn1(g_0->GetOut());
  g_1->SetOut(sim->AddConnector());

  NandGate* g_2 = sim->AddNandGate();
  g_2->SetIn0(b_in);
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
  g_7->SetOut(s_out);

  NandGate* g_8 = sim->AddNandGate();
  g_8->SetIn0(g_4->GetOut());
  g_8->SetIn1(g_0->GetOut());
  g_8->SetOut(c_out);
}

void Build4BitAdder(
    Simulation* sim,
    Connector* a_0_in, Connector* a_1_in, Connector* a_2_in, Connector* a_3_in,
    Connector* b_0_in, Connector* b_1_in, Connector* b_2_in, Connector* b_3_in,
    Connector* c_in,
    Connector* s_0_out, Connector* s_1_out, Connector* s_2_out, Connector* s_3_out,
    Connector* c_out) {
  Connector* c_0_out = sim->AddConnector();
  Build1BitAdder(sim, a_0_in, b_0_in, c_in, s_0_out, c_0_out);
  Connector* c_1_out = sim->AddConnector();
  Build1BitAdder(sim, a_1_in, b_1_in, c_0_out, s_1_out, c_1_out);
  Connector* c_2_out = sim->AddConnector();
  Build1BitAdder(sim, a_2_in, b_2_in, c_1_out, s_2_out, c_2_out);
  Connector* c_3_out = c_out;
  Build1BitAdder(sim, a_3_in, b_3_in, c_2_out, s_3_out, c_3_out);
}

void Build1BitRegister(
    Simulation* sim,
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

void Build4BitRegister(
    Simulation* sim,
    Connector* clock,
    Connector* d_in,
    Connector* d_out,
    Connector* d_0,
    Connector* d_1,
    Connector* d_2,
    Connector* d_3) {
  Build1BitRegister(sim, clock, d_in, d_out, d_0);
  Build1BitRegister(sim, clock, d_in, d_out, d_1);
  Build1BitRegister(sim, clock, d_in, d_out, d_2);
  Build1BitRegister(sim, clock, d_in, d_out, d_3);
}
