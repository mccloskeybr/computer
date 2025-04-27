void BuildComputer(class Simulator* sim) {
  auto* control = sim->AddCircuit<ControlBoard>("Control")
    ->Build(sim);

  auto* d_bus = sim->AddCircuit<EightBitBus>("Bus")
    ->Build(sim);
  auto* adder_a_bus = sim->AddCircuit<EightBitBus>("Adder A Bus")
    ->Build(sim);
  auto* adder_b_bus = sim->AddCircuit<EightBitBus>("Adder B Bus")
    ->Build(sim);
  auto* adder_s_bus = sim->AddCircuit<EightBitBus>("Adder S Bus")
    ->Build(sim);

  auto* reg_a = sim->AddCircuit<EightBitRegister>("Register A")
    ->SetDIn(d_bus->bus)
    ->SetDOut(adder_a_bus->bus)
    ->SetClock(control->clock)
    ->SetDInEnable(control->a_bus_in)
    ->SetDOutEnable(control->a_bus_out)
    ->Build(sim);
  auto* reg_b = sim->AddCircuit<EightBitRegister>("Register B")
    ->SetDIn(d_bus->bus)
    ->SetDOut(adder_b_bus->bus)
    ->SetClock(control->clock)
    ->SetDInEnable(control->b_bus_in)
    ->SetDOutEnable(control->b_bus_out)
    ->Build(sim);
  auto* reg_s = sim->AddCircuit<EightBitRegister>("Register S")
    ->SetDIn(adder_s_bus->bus)
    ->SetDOut(d_bus->bus)
    ->SetClock(control->clock)
    ->SetDInEnable(control->s_bus_in)
    ->SetDOutEnable(control->s_bus_out)
    ->Build(sim);

  auto* adder = sim->AddCircuit<EightBitAdder>("Adder")
    ->SetA(adder_a_bus->bus)
    ->SetB(adder_b_bus->bus)
    ->SetS(adder_s_bus->bus)
    ->SetCarryIn(sim->AddConnector())
    ->SetCarryOut(sim->AddConnector())
    ->Build(sim);
}
