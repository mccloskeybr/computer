// NOTE: circuits are collections of components.
// Bundled this way to make it easy to have customized UIs per
// grouping of components.

class Circuit {
 public:
  virtual ~Circuit() = default;
  virtual void UpdateUi() = 0;
};

class EightBitAdder : public Circuit {
 public:
  EightBitAdder(class Simulator* sim);
  void UpdateUi() override;

 private:
  Connector* a[8];
  Connector* b[8];
  Connector* s[8];
  Connector* c_in;
  Connector* c_out;
};

class EightBitRegister : public Circuit {
 public:
  EightBitRegister(class Simulator* sim);
  void UpdateUi() override;

 private:
  Connector* d[8];
  Connector* clock;
  Connector* d_in;
  Connector* d_out;
};
