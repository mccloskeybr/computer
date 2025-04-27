NotGate::NotGate() {
  in = NULL;
  out = NULL;
}

bool NotGate::Process() {
  ASSERT(in != NULL);
  ASSERT(out != NULL);

  switch (in->GetSignal()) {
    case SignalType_High: { return out->SetSignal(SignalType_Low); }
    case SignalType_Low:  { return out->SetSignal(SignalType_High); }
    default:              { UNREACHABLE(); return false; }
  }
}

NotGate* NotGate::SetIn(Connector* i) {
  ASSERT(in == NULL);
  i->AddConnection(this);
  in = i;
  return this;
}

NotGate* NotGate::SetOut(Connector* o) {
  ASSERT(out == NULL);
  o->AddConnection(this);
  out = o;
  return this;
}

Connector* NotGate::GetOut() {
  ASSERT(out != NULL);
  return out;
}

