Clock::Clock() {
  out = NULL;
  freq_s = 1;
  time = 0.0f;

  prev_time = SDL_GetPerformanceCounter();
  curr_time = prev_time;
  perf_freq = (float) SDL_GetPerformanceFrequency();
}

Clock* Clock::SetOut(Connector* o) {
  ASSERT(out == NULL);
  o->AddConnection(this);
  out = o;
  return this;
}

Clock* Clock::SetFrequencySeconds(float f) {
  freq_s = f;
  return this;
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
