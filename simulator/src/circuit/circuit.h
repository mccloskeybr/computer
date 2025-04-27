// NOTE: circuits are collections of components.
// Bundled this way to make it easy to have customized UIs per
// grouping of components.

struct Circuit {
  virtual ~Circuit() = default;
  virtual void UpdateUi() = 0;
};

struct EightBitBus : public Circuit {
  EightBitBus(class Simulator* sim, std::string name);
  void UpdateUi() override;

  std::string name;
  std::array<Connector*, 8> bus;
};

struct ControlBoard : public Circuit {
  ControlBoard(class Simulator* sim, std::string name);
  void UpdateUi() override;

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
  EightBitAdder(
      class Simulator* sim, std::string name,
      std::array<Connector*, 8> a, std::array<Connector*, 8> b, std::array<Connector*, 8> s,
      Connector* c_in, Connector* c_out);
  void UpdateUi() override;

  std::string name;
  std::array<Connector*, 8> a;
  std::array<Connector*, 8> b;
  std::array<Connector*, 8> s;
  Connector* c_in;
  Connector* c_out;
};

struct EightBitRegister : public Circuit {
  EightBitRegister(
      class Simulator* sim, std::string name,
      std::array<Connector*, 8> d_in, std::array<Connector*, 8> d_out,
      Connector* clock, Connector* d_in_en, Connector* d_out_en);
  void UpdateUi() override;

  std::string name;
  std::array<Connector*, 8> d;
  Connector* clock;
  Connector* d_in_en;
  Connector* d_out_en;
};

void BuildComputer(class Simulator* sim);
