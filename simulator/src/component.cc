Component::Component() {
  static int next_id = 0;
  id = next_id++;
}

NotGate::NotGate() {
  in = NULL;
  out = NULL;
}

void NotGate::Process() {
  switch (in->signal) {
    case SignalType_High: {
      out->signal = SignalType_Low;
      return;
    };
    case SignalType_Low: {
      out->signal = SignalType_High;
      return;
    };
    default: {
       UNREACHABLE();
       return;
    };
  }
}

void NotGate::SetIn(Connector* i) {
  ASSERT(in == NULL);
  i->connections.push_back(this);
  in = i;
}

void NotGate::SetOut(Connector* o) {
  ASSERT(out == NULL);
  out = o;
}

Connector* NotGate::GetOut() {
  ASSERT(out != NULL);
  return out;
}

NandGate::NandGate() {
  in[0] = NULL;
  in[1] = NULL;
  out = NULL;
}

void NandGate::SetIn0(Connector* i) {
  ASSERT(in[0] == NULL);
  i->connections.push_back(this);
  in[0] = i;
}

void NandGate::SetIn1(Connector* i) {
  ASSERT(in[1] == NULL);
  i->connections.push_back(this);
  in[1] = i;
}

void NandGate::SetOut(Connector* o) {
  ASSERT(out == NULL);
  out = o;
}

Connector* NandGate::GetOut() {
  ASSERT(out != NULL);
  return out;
}

void NandGate::Process() {
  if (in[0]->signal == SignalType_High &&
      in[1]->signal == SignalType_High) {
    out->signal = SignalType_Low;
  } else {
    out->signal = SignalType_High;
  }
}
