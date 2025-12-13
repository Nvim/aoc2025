#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <vector>

typedef std::uint64_t u64;
typedef std::uint32_t u32;
typedef std::int32_t i32;

struct Point {
  u64 x;
  u64 y;
  explicit Point(u64 x_in, u64 y_in) : x{x_in}, y{y_in} {}
};

u64 distance(const Point &a, const Point &b) {
  return static_cast<u64>(
      std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

struct Distance {
  std::pair<u64, u64> points;
  u64 distance;
  u64 area;
};

int main() {
  // std::ifstream file("input_example.txt");
  std::ifstream file("input.txt");
  std::string line;

  char delim;
  u64 x, y;

  std::vector<Point> points;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    iss >> x;
    iss >> delim;
    iss >> y;
    points.emplace_back(x, y);
  }

  std::for_each(points.begin(), points.end(),
                [](const Point &p) { std::printf("%lu - %lu\n", p.x, p.y); });

  std::vector<Distance> distances{};
  for (u64 i = 0; i < points.size(); i++) {
    for (u64 j = i + 1; j < points.size(); j++) {
      Point &a = points[i];
      Point &b = points[j];

      u64 height = b.y > a.y ? b.y - a.y : a.y - b.y;
      u64 width = b.x > a.x ? b.x - a.x : a.x - b.x;
      height++;
      width++;

      distances.push_back(
          {{i, j}, distance(points[i], points[j]), height * width});
    }
  }

  // clang-format off
  std::sort( distances.begin(), distances.end(), [](const auto &a, const auto &b) {
    return a.area < b.area; 
  });
  std::for_each(distances.end() - 10, distances.end(),
                [&points](const Distance &d) {
                  std::printf( "(%2lu, %2lu) - (%2lu, %2lu): %2lu -> %2lu\n",
                    points[d.points.first].x,
                    points[d.points.first].y,
                    points[d.points.second].x,
                    points[d.points.second].y,
                    d.distance, d.area);
                });
  // clang-format on
  return 0;
}
