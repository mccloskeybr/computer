// NOTE: The Simulator is the main state holder for comprised circuits,
// and the driver of state changes through circuit graphs.

class Simulator {
 public:
  Simulator() = default;
  ~Simulator();

  Connector* AddConnector();
  template <class C>
  C* AddComponent();
  template <class C, typename... Args>
  C* AddCircuit(Args...);

  void UpdateUi();
  void UpdateSimulation();

 private:
  std::vector<Connector*> connectors;
  std::vector<Component*> components;
  std::vector<Circuit*> circuits;
};
