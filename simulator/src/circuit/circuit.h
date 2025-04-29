// NOTE: circuits are collections of components.
// Bundled this way to make it easy to have customized UIs per
// grouping of components.

class Circuit {
 public:
  virtual ~Circuit() = default;
  virtual void UpdateUi(class Simulator* sim) = 0;
};

class EightBitBus : public Circuit {
 public:
  EightBitBus(std::string name);
  EightBitBus* Build(class Simulator* sim);
  void UpdateUi(class Simulator* sim) override;

  std::string name;
  std::array<Connector*, 8> bus;
};

class ControlBoard : public Circuit {
 public:
  ControlBoard(std::string name);
  ControlBoard* Build(class Simulator* sim);
  void UpdateUi(class Simulator* sim) override;

  std::string name;
  Connector* clock;
  Connector* a_bus_in;
  Connector* a_bus_out;
  Connector* b_bus_in;
  Connector* b_bus_out;
  Connector* s_bus_in;
  Connector* s_bus_out;
};

class EightBitAdder : public Circuit {
 public:
  explicit EightBitAdder(std::string name);
  EightBitAdder* SetA(std::array<Connector*, 8> a);
  EightBitAdder* SetB(std::array<Connector*, 8> b);
  EightBitAdder* SetS(std::array<Connector*, 8> s);
  EightBitAdder* SetCarryIn(Connector* a);
  EightBitAdder* SetCarryOut(Connector* a);
  EightBitAdder* Build(class Simulator* sim);
  void UpdateUi(class Simulator* sim) override;

  std::string name;
  std::array<Connector*, 8> a;
  std::array<Connector*, 8> b;
  std::array<Connector*, 8> s;
  Connector* c_in;
  Connector* c_out;
};

class EightBitRegister : public Circuit {
 public:
  explicit EightBitRegister(std::string name);
  EightBitRegister* SetDIn(std::array<Connector*, 8> d_in);
  EightBitRegister* SetDOut(std::array<Connector*, 8> d_out);
  EightBitRegister* SetClock(Connector* clock);
  EightBitRegister* SetDInEnable(Connector* d_in_en);
  EightBitRegister* SetDOutEnable(Connector* d_out_en);
  EightBitRegister* Build(class Simulator* sim);
  void UpdateUi(class Simulator* sim) override;

  std::string name;
  std::array<Connector*, 8> d;
  std::array<Connector*, 8> d_in;
  std::array<Connector*, 8> d_out;
  Connector* clock;
  Connector* d_in_en;
  Connector* d_out_en;
};
