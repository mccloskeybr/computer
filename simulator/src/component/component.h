// NOTE: Components are individual logic units, like gates.
// They are composed to derive circuit flows.
// Components are essentially a graph, where edges are modeled by
// special components called Connectors.

enum SignalType {
  SignalType_Low,
  SignalType_High,
};

static int next_connector_id = 0;
class Connector {
 public:
  Connector();
  SignalType GetSignal();
  bool SetSignal(SignalType s);
  void AddConnection(class Component* component);
  const std::vector<class Component*>* GetConnections();
  void UpdateUi(class Simulator* sim);

 private:
  SignalType signal;
  std::vector<class Component*> connections;
  const int32_t id = next_connector_id++;
};

class Component {
 public:
  virtual ~Component() = default;
  virtual bool Process() = 0;
  virtual Connector* GetOut() = 0;
  operator Connector*() { return GetOut(); }
};

class Buffer : public Component {
 public:
  Buffer();
  Buffer* SetIn(Connector* i);
  Buffer* SetOut(Connector* o);
  Connector* GetOut() override;
  bool Process() override;

 private:
  Connector* in;
  Connector* out;
};

class TriStateBuffer : public Component {
 public:
  TriStateBuffer();
  TriStateBuffer* SetIn(Connector* i);
  TriStateBuffer* SetEnable(Connector* e);
  TriStateBuffer* SetOut(Connector* o);
  Connector* GetOut() override;
  bool Process() override;

 private:
  Connector* in;
  Connector* enable;
  Connector* out;
};

class NotGate : public Component {
 public:
  NotGate();
  NotGate* SetIn(Connector* i);
  NotGate* SetOut(Connector* o);
  Connector* GetOut() override;
  bool Process() override;

 private:
  Connector* in;
  Connector* out;
};

class NandGate : public Component {
 public:
  NandGate();
  NandGate* SetIn(Connector* i_0, Connector* i_1);
  NandGate* SetOut(Connector* o);
  Connector* GetOut() override;
  bool Process() override;

 private:
  Connector* in[2];
  Connector* out;
};

class Clock : public Component {
 public:
  Clock();
  Clock* SetOut(Connector* i);
  Clock* SetFrequencySeconds(float f);
  Connector* GetOut() override;
  bool Process() override;

 private:
  Connector* out;
  float freq_s;

  float time;
  uint64_t prev_time;
  uint64_t curr_time;
  float perf_freq;
};
