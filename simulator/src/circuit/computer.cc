void BuildComputer(class Simulator* sim) {
  auto* control = sim->AddCircuit<ControlBoard>("Control");
  auto* d_bus = sim->AddCircuit<EightBitBus>("Bus");
  auto* adder_a_bus = sim->AddCircuit<EightBitBus>("Adder A Bus");
  auto* adder_b_bus = sim->AddCircuit<EightBitBus>("Adder B Bus");
  auto* adder_s_bus = sim->AddCircuit<EightBitBus>("Adder S Bus");

  auto* reg_a = sim->AddCircuit<EightBitRegister>(
      "Register A",
      d_bus->bus, adder_a_bus->bus,
      control->clock, control->a_bus_in, control->a_bus_out);
  auto* reg_b = sim->AddCircuit<EightBitRegister>(
      "Register B",
      d_bus->bus, adder_b_bus->bus,
      control->clock, control->b_bus_in, control->b_bus_out);
  auto* reg_s = sim->AddCircuit<EightBitRegister>(
      "Register S",
      adder_s_bus->bus, d_bus->bus,
      control->clock, control->s_bus_in, control->s_bus_out);

  auto* adder = sim->AddCircuit<EightBitAdder>(
      "Adder",
      adder_a_bus->bus, adder_b_bus->bus, adder_s_bus->bus,
      sim->AddConnector(), sim->AddConnector());
}
