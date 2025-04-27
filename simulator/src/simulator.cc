Simulator::~Simulator() {
  for (Connector* connector : connectors) { delete connector; }
  for (Component* component : components) { delete component; }
  for (Circuit* circuit : circuits) { delete circuit; }
}

Connector* Simulator::AddConnector() {
  Connector* connector = new Connector();
  connectors.push_back(connector);
  return connector;
}

Clock* Simulator::AddClock() {
  Clock* clock = new Clock();
  components.push_back(clock);
  return clock;
}

Buffer* Simulator::AddBuffer() {
  Buffer* buffer = new Buffer();
  components.push_back(buffer);
  return buffer;
}

TriStateBuffer* Simulator::AddTriStateBuffer() {
  TriStateBuffer* tri_state_buffer = new TriStateBuffer();
  components.push_back(tri_state_buffer);
  return tri_state_buffer;
}

NotGate* Simulator::AddNotGate() {
  NotGate* not_gate = new NotGate();
  components.push_back(not_gate);
  return not_gate;
}

NandGate* Simulator::AddNandGate() {
  NandGate* nand_gate = new NandGate();
  components.push_back(nand_gate);
  return nand_gate;
}

void Simulator::AddCircuit(Circuit* circuit) {
  circuits.push_back(circuit);
}

void Simulator::UpdateUi() {
  for (int32_t i = 0; i < circuits.size(); i++) {
    circuits[i]->UpdateUi();
  }
}

void Simulator::UpdateSimulation() {
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
