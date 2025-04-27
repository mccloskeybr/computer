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

Buffer::Buffer() {
  in = NULL;
  out = NULL;
}

bool Buffer::Process() {
  ASSERT(in != NULL);
  ASSERT(out != NULL);

  return out->SetSignal(in->GetSignal());
}

void Buffer::SetIn(Connector* i) {
  ASSERT(in == NULL);
  i->AddConnection(this);
  in = i;
}

void Buffer::SetOut(Connector* o) {
  ASSERT(out == NULL);
  o->AddConnection(this);
  out = o;
}

Connector* Buffer::GetOut() {
  ASSERT(out != NULL);
  return out;
}

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

void NotGate::SetIn(Connector* i) {
  ASSERT(in == NULL);
  i->AddConnection(this);
  in = i;
}

void NotGate::SetOut(Connector* o) {
  ASSERT(out == NULL);
  o->AddConnection(this);
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


Clock::Clock() {
  out = NULL;
  freq_s = 1;
  time = 0.0f;

  prev_time = SDL_GetPerformanceCounter();
  curr_time = prev_time;
  perf_freq = (float) SDL_GetPerformanceFrequency();
}

void Clock::SetOut(Connector* o) {
  ASSERT(out == NULL);
  o->AddConnection(this);
  out = o;
}

void Clock::SetFrequencySeconds(float f) {
  freq_s = f;
}

Connector* Clock::GetOut() {
  ASSERT(out != NULL);
  return out;
}

bool Clock::Process() {
  ASSERT(out != NULL);

  // NOTE: freq_s == 0 --> manual clock.
  // semantically the same as having no clock at all but whatever.
  if (freq_s == 0) { return false; }

  curr_time = SDL_GetPerformanceCounter();
  float dt_s = (((float) (curr_time - prev_time)) / perf_freq);
  prev_time = curr_time;
  time += dt_s;
  if (time < 1.0f / freq_s) { return false; }

  time -= 1.0f / freq_s;
  if (out->GetSignal() == SignalType_High) {
    return out->SetSignal(SignalType_Low);
  } else {
    return out->SetSignal(SignalType_High);
  }
}
