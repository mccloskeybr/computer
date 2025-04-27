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

TriStateBuffer* TriStateBuffer::SetIn(Connector* i) {
  ASSERT(in == NULL);
  i->AddConnection(this);
  in = i;
  return this;
}

TriStateBuffer* TriStateBuffer::SetEnable(Connector* e) {
  ASSERT(enable == NULL);
  e->AddConnection(this);
  enable = e;
  return this;
}

TriStateBuffer* TriStateBuffer::SetOut(Connector* o) {
  ASSERT(out == NULL);
  o->AddConnection(this);
  out = o;
  return this;
}

Connector* TriStateBuffer::GetOut() {
  ASSERT(out != NULL);
  return out;
}

