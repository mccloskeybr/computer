# Instruction ROM generator

Translating op codes into actual control lines requires complicated logic to
support. While experimenting with the CPU design, this leads to a high risk in
making expensive decisions early that take a while to correct later. For
example, what if we want to add a new control flag between existing control
flags? What if we want to change the micro ops associated with a particular
instruction? If done manually, this may take a while to get right.

This is solved by using EEPROMs as an op code --> control line map.
Conceptually, EEPROMs are presented a 15 bit value as input and provide an 8
bit value as output. Therefore, we can pass the opcode (8 bits for a 6502)
as well as the running micro op index (can use the remaining 7 bits, although
I'm only planning on having a max of 16 micro ops per instruction) as an input,
and the output can be what control lines should be enabled for a particular
instruction's micro op. We can support an arbitrary amount of control lines
by having different EEPROMs control different sets of the control line --
EEPROM outputs are concatenated together to determine the final line.

This strategy facilitates fast experimentation with different micro ops for
each instruction. This also allows us to experiment with different ISAs, as
the EEPROMs handle the entire instruction decode logic for the CPU.

This directory contains the code to fill the instruction decode EEPROMs with
the logic required to perform this operation.
