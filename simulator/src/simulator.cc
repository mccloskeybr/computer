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

template <class C>
C* Simulator::AddComponent() {
  C* component = new C();
  components.push_back(component);
  return component;
}

template <class C, typename... Args>
C* Simulator::AddCircuit(Args... args) {
  C* circuit = new C(this, args...);
  circuits.push_back(circuit);
  return circuit;
}

void Simulator::UpdateUi() {
  for (int32_t i = 0; i < circuits.size(); i++) {
    circuits[i]->UpdateUi();
  }
}

void Simulator::UpdateSimulation() {
  std::deque<Connector*> connector_queue = {};

  for (Component* component : components) {
    if (component->Process()) {
      connector_queue.push_back(component->GetOut());
    }
  }

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
