enum SignalType {
  SignalType_Low,
  SignalType_High,
};

struct Connector {
  SignalType signal;
  std::vector<class Component*> connections;
};

class Component {
 public:
  explicit Component();
  virtual ~Component() = default;
  virtual void Process() = 0;
  virtual Connector* GetOut() = 0;

 private:
  int32_t id;
};

class NotGate : public Component {
 public:
  explicit NotGate();
  void SetIn(Connector* i);
  void SetOut(Connector* o);
  Connector* GetOut() override;
  void Process() override;

 private:
  Connector* in;
  Connector* out;
};

class NandGate : public Component {
 public:
  explicit NandGate();
  void SetIn0(Connector* i);
  void SetIn1(Connector* i);
  void SetOut(Connector* o);
  Connector* GetOut() override;
  void Process() override;

 private:
  Connector* in[2];
  Connector* out;
};
