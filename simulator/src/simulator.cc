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

Clock* Simulation::AddClock() {
  Clock* clock = new Clock();
  components.push_back(clock);
  return clock;
}

Buffer* Simulation::AddBuffer() {
  Buffer* buffer = new Buffer();
  components.push_back(buffer);
  return buffer;
}

TriStateBuffer* Simulation::AddTriStateBuffer() {
  TriStateBuffer* tri_state_buffer = new TriStateBuffer();
  components.push_back(tri_state_buffer);
  return tri_state_buffer;
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
      if (ImGui::RadioButton("##modifyable", connector->GetSignal() == SignalType_High)) {
        if (connector->GetSignal() == SignalType_High) {
          connector->SetSignal(SignalType_Low);
        } else {
          connector->SetSignal(SignalType_High);
        }
      }
    } else {
      ImGui::RadioButton("##non_modifyable", connector->GetSignal() == SignalType_High);
    }

    ImGui::PopID();
  }

  ImGui::End();
}

void Simulation::UpdateSimulation() {
  std::deque<Connector*> connector_queue = {connectors.begin(), connectors.end()};
  while (!connector_queue.empty()) {
    Connector* connector = connector_queue.front();
    connector_queue.pop_front();
    for (Component* component : *connector->GetConnections()) {
      if (component->Process()) {
        connector_queue.push_back(component->GetOut());
      }
    }
  }
}
