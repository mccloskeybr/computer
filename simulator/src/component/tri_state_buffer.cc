TriStateBuffer::TriStateBuffer() {
  in = NULL;
  enable = NULL;
  out = NULL;
}

bool TriStateBuffer::Process() {
  ASSERT(in != NULL);
  ASSERT(enable != NULL);
  ASSERT(out != NULL);

  if (enable->GetSignal() == SignalType_High) {
    return out->SetSignal(in->GetSignal());
  }
  return false;
}

void TriStateBuffer::SetIn(Connector* i) {
  ASSERT(in == NULL);
  i->AddConnection(this);
  in = i;
}

void TriStateBuffer::SetEnable(Connector* e) {
  ASSERT(enable == NULL);
  e->AddConnection(this);
  enable = e;
}

void TriStateBuffer::SetOut(Connector* o) {
  ASSERT(out == NULL);
  o->AddConnection(this);
  out = o;
}

Connector* TriStateBuffer::GetOut() {
  ASSERT(out != NULL);
  return out;
}

