#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <printf.h>
#include <set>
#include <sstream>
#include <string>
#include <vector>

typedef std::uint64_t u64;
typedef std::uint32_t u32;
typedef float f32;

std::set<u64> invalids{};

u32 num_digits(u64 num) {
  u32 digits = 1;
  while (num > 9) {
    num /= 10;
    digits++;
  }
  return digits;
}

bool is_symetric(std::string num) {

  auto len = num.length();
  if (len % 2 != 0) {
    return 0;
  }

  u64 chunk_sz = len / 2;
  auto chunk1 = num.substr(0, chunk_sz);
  auto chunk2 = num.substr(chunk_sz, num.npos);
  if (chunk1 == chunk2) {
    // printf("%s\n", num.c_str());
    // return std::stoul(num);
    return true;
  }

  return 0;
}

std::vector<std::string> tokenize(std::string &in, const std::string &delim) {
  std::vector<std::string> tokens;
  size_t pos = 0;
  std::string token;
  while ((pos = in.find(delim)) != std::string::npos) {
    token = in.substr(0, pos);
    tokens.push_back(token);
    in.erase(0, pos + delim.length());
  }
  tokens.push_back(in);

  return tokens;
}

void get_symetry_count(u64 begin, u64 end) {
  u64 count = 0;
  for (u64 i = begin; i <= end; i++) {
    if(is_symetric(std::to_string(i))) {
      invalids.emplace(i);
    }
  }
  // return count;
}

int main() {
  std::ifstream file("input2.txt");
  std::string line;
  if (!std::getline(file, line)) {
    return -1;
  }
  u32 count = 0;

  auto ranges = tokenize(line, ",");
  for (auto &str : ranges) {
    auto range = tokenize(str, "-");
    u64 begin = std::stoul(range[0].c_str());
    u64 end = std::stoul(range[1].c_str());

    // count += get_symetry_count(begin, end);
    get_symetry_count(begin, end);
    // printf("%lu-%lu,", begin, end);
  }
  for (auto elem : invalids) {
    count += elem;
  }

  file.close();

  printf("%d\n", count);
  return 0;
}

// int main() {
//   std::ifstream file("input2.txt");
//   std::string line;
//   if (!std::getline(file, line)) {
//     return -1;
//   }
//   u32 count = 0;
//
//   std::istringstream iss(line);
//   u64 range_start, range_end;
//   char delim;
//
//   while (!iss.eof()) {
//     iss >> range_start;
//     iss >> delim;
//     iss >> range_end;
//
//     // printf("%lu %c %lu\n", range_start, delim, range_end);
//     for (u64 i = range_start; i < range_end; i++) {
//       count += is_symetric_fast(i);    
//     }
//
//     iss >> delim;
//   }
//
//   printf("%d\n", count);
//   return 0;
// }
