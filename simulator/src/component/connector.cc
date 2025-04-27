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

void Connector::UpdateUi(bool is_modifyable) {
  ImGui::PushID(id);
  if (is_modifyable) {
    if (ImGui::RadioButton("##modifyable", (signal == SignalType_High))) {
      if (signal == SignalType_High) { signal = SignalType_Low;  }
      else                           { signal = SignalType_High; }
    }
  } else {
    ImGui::RadioButton("##non_modifyable", (signal == SignalType_High));
  }
  ImGui::PopID();
}

