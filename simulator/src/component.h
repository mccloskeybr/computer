enum SignalType {
  SignalType_Low,
  SignalType_High,
};

class Connector {
 public:
  Connector();
  SignalType GetSignal();
  bool SetSignal(SignalType s);
  void AddConnection(class Component* component);
  const std::vector<class Component*>* GetConnections();

 private:
  SignalType signal;
  std::vector<class Component*> connections;
};

static int next_component_id = 0;
class Component {
 public:
  virtual ~Component() = default;
  virtual bool Process() = 0;
  virtual Connector* GetOut() = 0;

  const int32_t id = next_component_id++;
};

class Buffer : public Component {
 public:
  Buffer();
  void SetIn(Connector* i);
  void SetOut(Connector* o);
  Connector* GetOut() override;
  bool Process() override;

 private:
  Connector* in;
  Connector* out;
};

class TriStateBuffer : public Component {
 public:
  TriStateBuffer();
  void SetIn(Connector* i);
  void SetEnable(Connector* e);
  void SetOut(Connector* o);
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
  void SetIn(Connector* i);
  void SetOut(Connector* o);
  Connector* GetOut() override;
  bool Process() override;

 private:
  Connector* in;
  Connector* out;
};

class NandGate : public Component {
 public:
  NandGate();
  void SetIn0(Connector* i);
  void SetIn1(Connector* i);
  void SetOut(Connector* o);
  Connector* GetOut() override;
  bool Process() override;

 private:
  Connector* in[2];
  Connector* out;
};
