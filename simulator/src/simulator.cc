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
  C* circuit = new C(args...);
  circuits.push_back(circuit);
  return circuit;
}

void Simulator::PushDirtyConnector(Connector* connector) {
  dirty_connectors.push_back(connector);
}

void Simulator::UpdateUi() {
  for (int32_t i = 0; i < circuits.size(); i++) {
    circuits[i]->UpdateUi(this);
  }
}

void Simulator::UpdateSimulation() {
  for (Component* component : components) {
    if (component->Process()) {
      PushDirtyConnector(component->GetOut());
    }
  }

  while (!dirty_connectors.empty()) {
    Connector* connector = dirty_connectors.front();
    dirty_connectors.pop_front();
    for (Component* component : *connector->GetConnections()) {
      if (component->Process()) {
        dirty_connectors.push_back(component->GetOut());
      }
    }
  }
}
