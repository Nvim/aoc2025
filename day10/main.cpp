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
  std::vector<u32> masks{};
  u32 num_bytes{0};

  void print() {
    std::printf("[%b] ", desired_state);
    for (auto m : masks) {
      std::printf("(%b) ", m);
    }
    std::printf(" -- %u bytes\n", num_bytes);
  }
};

void parse_line(line_t &out_line, std::string &line) {
  std::string desired;
  std::istringstream iss(line);

  { // parse [.#.#] thing
    iss >> desired;

    u16 &d{out_line.desired_state};
    d = 0;
    out_line.num_bytes = desired.length() - 2; // remove brackets
    for (u64 i = 1; desired[i] != ']'; i++) {
      switch (desired[i]) {
        break;
      case '.':
        d &= ~(1 << (out_line.num_bytes - i));
        break;
      case '#':
        d |= (1 << (out_line.num_bytes - i));
        break;
      default:
        printf("parse error\n");
        break;
      }
    }
  }

  { // parse button combinations
    std::string mask_str;
    iss >> mask_str;
    while (mask_str[0] != '{') {
      mask_str = mask_str.substr(1, mask_str.length() - 2);
      std::istringstream mask_stream(mask_str);
      std::string number;
      u32 mask_value{0};
      while (std::getline(mask_stream, number, ',')) {
        u32 t;
        std::stringstream(number) >> t;
        mask_value |= (1 << (out_line.num_bytes - t - 1));
      }
      out_line.masks.push_back(mask_value);
      iss >> mask_str;
    }
  }
}

bool try_combination(line_t &line, std::vector<u32> &&buttons) {

  u32 m{0};
  for (auto button_idx : buttons) {
    m ^= line.masks[button_idx];
  }
  std::printf("want: %b, got %b\n", line.desired_state, m);
  return m == line.desired_state;
}

int main() {
  std::ifstream file("input_example.txt");
  std::string line;

  std::vector<line_t> lines;
  while (std::getline(file, line)) {
    line_t line_state;
    parse_line(line_state, line);
    std::printf("%s\n", line.c_str());
    line_state.print();
    std::printf("\n");
    lines.push_back(line_state);
  }

  // who needs testsuites
  using vec = std::vector<u32>;
  std::printf("0: %d\n", try_combination(lines[0], vec{1}));
  std::printf("0: %d\n", try_combination(lines[0], vec{1, 3, 5}));
  std::printf("1: %d\n", try_combination(lines[0], vec{0, 1, 2}));
  std::printf("0: %d\n", try_combination(lines[0], vec{0, 2, 3, 4}));
  std::printf("1: %d\n", try_combination(lines[0], vec{0, 2, 3, 4, 5}));

  // bruteforce time :)

  return 0;
}
