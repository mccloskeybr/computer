#include <bitset>
#include <format>
#include <string>
#include <vector>

#include <stdio.h>
#include <stdint.h>

enum ControlFlag : uint64_t {
  Y_IN     = 1 << 1,
  PC_INC   = 1 << 2,
  PC_IN    = 1 << 3,
  PC_OUT   = 1 << 4,
  DB_EN    = 1 << 5,
  OP_INC   = 1 << 6,
  OP_RESET = 1 << 7,
  MAX      = OP_RESET,
};

struct Instruction {
  const char* name;
  const uint8_t op_code;
  const std::vector<int64_t> micro_ops;
};

static const Instruction INSTRUCTIONS[] = {
  {
    // Load Y immediate
    .name = "LDY #",
    .op_code = 0xA0,
    .micro_ops = {
      PC_INC | OP_INC,                   // inc program counter
      PC_OUT | DB_EN | Y_IN | OP_INC,    // load next value in inst stream in Y
      PC_INC | OP_INC,                   // inc program counter
      PC_OUT | DB_EN | PC_IN | OP_RESET, // load next value in inst stream in program counter
    },
  },
};

int main(int argc, char** argv) {
  // NOTE: buffer_size encapsulates the entire data block for 1 EEPROM. The
  // AS6C62256 has 15 address lines, each stores 1 byte.
  size_t buffer_size = (1 << 16) - 1;
  char* buffer = (char*) malloc(buffer_size);

  // NOTE: each EEPROM can only output 1 byte / 8 control flags, but we want to
  // support more than 8 control flags. Therefore, break each control line into
  // distinct sets of 8 bits, 1 for each EEPROM.
  //
  // consider the following control line:
  //
  // 0000 0100 | 0000 0010 | 0000 0001
  // EEPROM_0 -> 0000 0100
  // EEPROM_1 -> 0000 0010
  // EEPROM_2 -> 0000 0001
  //
  // this allows us to feed the particular micro op as an address into all
  // EEPROMs (calculated as op_code + micro_op_index) and concatenate the
  // results together to build the final control line.
  int32_t set = 0;
  int64_t mask = 0;
  do {
    int32_t shift = 8 * set;
    mask = 0xff << shift;
    memset(buffer, 0, buffer_size);

    std::string file_name = std::format("inst_rom_{}.bin", set);
    FILE* file = fopen(file_name.c_str(), "wb+");
    if (file == NULL) { fprintf(stderr, "ERR: Cannot open file."); exit(1); }

    for (const Instruction& inst : INSTRUCTIONS) {
      fprintf(stdout, "%s: %s\n", file_name.c_str(), inst.name);
      for (int32_t i = 0; i < inst.micro_ops.size(); i++) {
        uint16_t address = ((uint16_t) (inst.op_code)) + i;
        uint8_t code = (uint8_t) ((inst.micro_ops[i] & mask) >> shift);
        fprintf(stdout, "%X: %s\n", address, std::bitset<8>(code).to_string().c_str());
        buffer[address] = code;
      }
    }

    fwrite(buffer, sizeof(char), buffer_size, file);
    fclose(file);

    set++;
  } while ((mask & MAX) == 0);
  return 0;
}
