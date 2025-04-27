Simulation::~Simulation() {
  for (Connector* connector : connectors) { delete connector; }
  for (Component* component : components) { delete component; }
}

Connector* Simulation::AddConnector() {
  Connector* connector = new Connector();
  connectors.push_back(connector);
  return connector;
}

Connector* Simulation::AddObservableConnector(std::string name, bool is_modifyable) {
  Connector* connector = AddConnector();
  observable_connectors.emplace_back(ObservableConnector{connector, name, is_modifyable});
  return connector;
}

NotGate* Simulation::AddNotGate() {
  NotGate* not_gate = new NotGate();
  components.push_back(not_gate);
  return not_gate;
}

NandGate* Simulation::AddNandGate() {
  NandGate* nand_gate = new NandGate();
  components.push_back(nand_gate);
  return nand_gate;
}

void Simulation::UpdateUi() {
  ImGui::Begin("test");

  for (int32_t i = 0; i < observable_connectors.size(); i++) {
    ImGui::PushID(i);

    ImGui::Text(observable_connectors[i].name.c_str());
    Connector* connector = observable_connectors[i].connector;
    if (observable_connectors[i].is_modifyable) {
      if (ImGui::RadioButton("##modifyable", connector->signal == SignalType_High)) {
        if (connector->signal == SignalType_High) {
          connector->signal = SignalType_Low;
        } else {
          connector->signal = SignalType_High;
        }
        Simulate(connector);
      }
    } else {
      ImGui::RadioButton("##non_modifyable", connector->signal == SignalType_High);
    }

    ImGui::PopID();
  }

  ImGui::End();
}

void Simulation::Simulate(Connector* connector) {
  std::deque<Connector*> connector_queue = {connector};
  while (!connector_queue.empty()) {
    Connector* connector = connector_queue.front();
    connector_queue.pop_front();
    for (Component* component : connector->connections) {
      component->Process();
      connector_queue.push_back(component->GetOut());
    }
  }
}

void BuildAdder(Simulation* sim) {
  Connector* a_in = sim->AddObservableConnector("a_in", true);
  Connector* b_in = sim->AddObservableConnector("b_in", true);
  Connector* c_in = sim->AddObservableConnector("c_in", true);

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
  g_7->SetOut(sim->AddObservableConnector("s_out", false));

  NandGate* g_8 = sim->AddNandGate();
  g_8->SetIn0(g_4->GetOut());
  g_8->SetIn1(g_0->GetOut());
  g_8->SetOut(sim->AddObservableConnector("c_out", false));
}
