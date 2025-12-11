#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <istream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

typedef std::uint64_t u64;
typedef std::uint32_t u32;
typedef std::int32_t i32;

struct Box {
  i32 x;
  i32 y;
  i32 z;

  i32 distance(const Box &other) const {
    if (&other == this) {
      return std::numeric_limits<i32>::max();
    }
    return std::abs(std::sqrt(std::pow((x - other.x), 2) +
                              std::pow((y - other.y), 2) +
                              std::pow((z - other.z), 2)));
  }
};

struct Adjacency {
  std::pair<u32, u32> boxes; // indexes in boxes vector
  i32 distance;
};

u32 get_root(std::vector<u32> &parents, u32 i) {
  auto p = parents[i];
  if (p == i) {
    return i;
  }

  parents[i] = get_root(parents, parents[i]);
  return parents[i];
}

void merge_nodes(std::vector<u32> &parents, u32 a, u32 b) {
  auto a_parent = get_root(parents, a);
  parents[a_parent] = get_root(parents, b);
}

void part1(std::vector<Adjacency> &adjacencies, std::vector<u32> &parents) {
  for (i32 i = 0; i < 1000; i++) {
    // we must connect these two:
    auto idx_1 = adjacencies.back().boxes.first;
    auto idx_2 = adjacencies.back().boxes.second;
    adjacencies.pop_back();
    std::printf("connect %2d and %2d - ", idx_1, idx_2);

    merge_nodes(parents, idx_1, idx_2);
    for (const auto a : parents) {
      std::printf("%2u ", a);
    }
    std::printf("\n");
  }
  for (const auto a : parents) {
    std::printf("%2u ", a);
  }
  std::printf("\n");

  std::vector<u32> counts(parents.size(), 0);
  for (u32 i = 0; i < parents.size(); i++) {
    auto root = get_root(parents, i);
    counts[root]++;
  }

  std::partial_sort(counts.begin(), counts.begin() + 3, counts.end(),
                    std::greater<u32>());
  u32 product = 1;
  for (u32 i = 0; i < 3; i++) {
    std::printf("%u ", counts[i]);
    product *= counts[i];
  }

  std::printf("\nResult is: %u\n", product);
}

void part2(std::vector<Adjacency> &adjacencies, std::vector<u32> &parents,
           std::vector<Box> &boxes) {
  u64 circuit_count{parents.size()};
  u32 idx_1, idx_2;
  while (circuit_count > 1 && !adjacencies.empty()) {
    // we must connect these two:
    idx_1 = adjacencies.back().boxes.first;
    idx_2 = adjacencies.back().boxes.second;
    adjacencies.pop_back();
    std::printf("connect %2d and %2d\n", idx_1, idx_2);

    if (get_root(parents, idx_1) == get_root(parents, idx_2)) {
      // skip, they're already connected
      continue;
    }

    merge_nodes(parents, idx_1, idx_2);
    circuit_count--;
  }
  auto last_1 = boxes[idx_1];
  auto last_2 = boxes[idx_2];

  std::printf("Result is %d * %d = %d\n", last_1.x, last_2.x,
              last_1.x * last_2.x);
}

int main() {
  // std::ifstream file("input_example.txt");
  std::ifstream file("input.txt");
  std::string line;
  std::vector<Box> boxes{};

  char delim;
  i32 x, y, z;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    iss >> x;
    iss >> delim;
    iss >> y;
    iss >> delim;
    iss >> z;
    boxes.emplace_back(Box{x, y, z});
  }

  std::vector<Adjacency> adjacencies{};
  adjacencies.reserve(boxes.size());

  for (u32 i = 0; i < boxes.size(); i++) {
    auto &box = boxes[i];
    std::printf("#%2d: %d %d %d\n", i, box.x, box.y, box.z);

    for (u32 j = i + 1; j < boxes.size(); j++) {
      auto &other = boxes[j];
      auto dist = box.distance(other);
      adjacencies.emplace_back(Adjacency{std::pair<u32, u32>{i, j}, dist});
    }
  }

  std::sort(adjacencies.begin(), adjacencies.end(),
            [](const Adjacency &a, const Adjacency &b) {
              return a.distance > b.distance;
            });

  std::vector<u32> parents{};
  parents.reserve(boxes.size());
  for (u32 i = 0; i < boxes.size(); i++) {
    parents.push_back(i);
  }

  // part1(adjacencies, parents);
  part2(adjacencies, parents, boxes);

  return 0;
}
