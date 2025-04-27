Buffer::Buffer() {
  in = NULL;
  out = NULL;
}

bool Buffer::Process() {
  ASSERT(in != NULL);
  ASSERT(out != NULL);

  return out->SetSignal(in->GetSignal());
}

Buffer* Buffer::SetIn(Connector* i) {
  ASSERT(in == NULL);
  i->AddConnection(this);
  in = i;
  return this;
}

Buffer* Buffer::SetOut(Connector* o) {
  ASSERT(out == NULL);
  o->AddConnection(this);
  out = o;
  return this;
}

Connector* Buffer::GetOut() {
  ASSERT(out != NULL);
  return out;
}

