struct ObservableConnector {
  Connector* connector;
  std::string name;
  bool is_modifyable;
};

class Simulation {
 public:
  Simulation() = default;
  ~Simulation();
  Connector* AddObservableConnector(std::string name, bool is_modifyable);
  Connector* AddConnector();

  Clock* AddClock();
  Buffer* AddBuffer();
  TriStateBuffer* AddTriStateBuffer();
  NotGate* AddNotGate();
  NandGate* AddNandGate();

  void UpdateUi();
  void UpdateSimulation();

 private:
  std::vector<ObservableConnector> observable_connectors;
  std::vector<Connector*> connectors;
  std::vector<Component*> components;
};
