NandGate::NandGate() {
  in[0] = NULL;
  in[1] = NULL;
  out = NULL;
}

void NandGate::SetIn0(Connector* i) {
  ASSERT(in[0] == NULL);
  i->AddConnection(this);
  in[0] = i;
}

void NandGate::SetIn1(Connector* i) {
  ASSERT(in[1] == NULL);
  i->AddConnection(this);
  in[1] = i;
}

void NandGate::SetOut(Connector* o) {
  ASSERT(out == NULL);
  o->AddConnection(this);
  out = o;
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
