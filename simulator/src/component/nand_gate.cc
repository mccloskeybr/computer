NandGate::NandGate() {
  in[0] = NULL;
  in[1] = NULL;
  out = NULL;
}

NandGate* NandGate::SetIn(Connector* i_0, Connector* i_1) {
  ASSERT(in[0] == NULL);
  ASSERT(in[1] == NULL);
  i_0->AddConnection(this);
  i_1->AddConnection(this);
  in[0] = i_0;
  in[1] = i_1;
  return this;
}

NandGate* NandGate::SetOut(Connector* o) {
  ASSERT(out == NULL);
  o->AddConnection(this);
  out = o;
  return this;
}

Connector* NandGate::GetOut() {
  ASSERT(out != NULL);
  return out;
}

bool NandGate::Process() {
  ASSERT(in[0] != NULL);
  ASSERT(in[1] != NULL);
  ASSERT(out != NULL);

  if (in[0]->GetSignal() == SignalType_High &&
      in[1]->GetSignal() == SignalType_High) {
    return out->SetSignal(SignalType_Low);
  } else {
    return out->SetSignal(SignalType_High);
  }
}
