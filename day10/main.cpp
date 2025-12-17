#include <cassert>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <vector>

typedef std::uint64_t u64;
typedef std::uint16_t u16;
typedef std::uint32_t u32;
typedef std::uint8_t u8;
typedef std::int32_t i32;

struct line_t {
  u16 desired_state{0};
  std::vector<u8> masks{};
};

void parse_line(line_t &out_line, std::string &line) {

  std::string desired;
  std::istringstream iss(line);

  iss >> desired;

  u16& d{out_line.desired_state};
  d = 0;
  for (u64 i = 1; desired[i] != ']'; i++) {
    switch (desired[i]) {
      break;
      case '.':
        d &= ~(1 << (i-1));
        break;
      case '#':
        d |= (1 << (i-1));
        break;
      default:
        printf("parse error\n");
        break;
    }
  }
  std::printf("desired: %s => %lb |", desired.c_str(), out_line.desired_state);

  std::string mask;
  iss >> mask;
  while (mask[0] != '{') {
    mask = mask.substr(1, mask.length()-2); 
    std::printf(" %s -", mask.c_str());
    iss >> mask;
  }
  std::printf("\n");
}

int main() {
  std::ifstream file("input_example.txt");
  std::string line;

  std::vector<line_t> lines;
  while (std::getline(file, line)) {
    line_t line_state;
    parse_line(line_state, line);
    lines.push_back(line_state);
  }

  // assert(lines[0].desired_state == 28);

  return 0;
}
