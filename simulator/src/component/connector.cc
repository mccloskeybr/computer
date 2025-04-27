Connector::Connector() {
  signal = SignalType_Low;
  connections = std::vector<Component*>();
}

SignalType Connector::GetSignal() {
  return signal;
}

bool Connector::SetSignal(SignalType s) {
  bool changed = (s != signal);
  signal = s;
  return changed;
}

void Connector::AddConnection(class Component* component) {
  connections.push_back(component);
}

const std::vector<class Component*>* Connector::GetConnections() {
  return &connections;
}

void Connector::UpdateUi(Simulator* sim) {
  ImGui::PushID(id);
  if (ImGui::RadioButton("##modifyable", (signal == SignalType_High))) {
    if (signal == SignalType_High) { signal = SignalType_Low;  }
    else                           { signal = SignalType_High; }
    sim->PushDirtyConnector(this);
  }
  ImGui::PopID();
}

