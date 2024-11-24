#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>

bool isInCircle(double x, double y, double cx, double cy, double r) {
  return (pow(x - cx, 2) + pow(y - cy, 2)) <= r * r;
}

bool inIntersection(double x, double y, double cx1, double cy1, double r1, double cx2, double cy2, double r2, double cx3, double cy3, double r3) {
  return isInCircle(x, y, cx1, cy1, r1) &&
      isInCircle(x, y, cx2, cy2, r2) &&
      isInCircle(x, y, cx3, cy3, r3);
}

double monteCarlo(double cx1, double cy1, double r1, double cx2, double cy2, double r2, double cx3, double cy3, double r3, int num_points) {
  int count_inside = 0;

  double x_min = std::min(cx1 - r1, std::min(cx2 - r2, cx3 - r3));
  double y_min = std::min(cy1 - r1, std::min(cy2 - r2, cy3 - r3));
  double x_max = std::max(cx1 + r1, std::max(cx2 + r2, cx3 + r3));
  double y_max = std::max(cy1 + r1, std::max(cy2 + r2, cy3 + r3));
  double rect_area = (x_max - x_min) * (y_max - y_min);

  for (int i = 0; i < num_points; ++i) {
    double x = x_min + (x_max - x_min) * ((double)rand() / RAND_MAX);
    double y = y_min + (y_max - y_min) * ((double)rand() / RAND_MAX);

    if (inIntersection(x, y, cx1, cy1, r1, cx2, cy2, r2, cx3, cy3, r3)) {
      count_inside++;
    }
  }

  return rect_area * ((double)count_inside / num_points);
}

int main() {
  srand((unsigned)time(0));

  double cx1 = 1.0;
  double cy1 = 1.0;
  double r1 = 1.0;
  double cx2 = 1.5;
  double cy2 = 2.0;
  double r2 = std::sqrt(5) / 2.0;
  double cx3 = 2.0;
  double cy3 = 1.5;
  double r3 = std::sqrt(5) / 2.0;

  std::string filename = "results.csv";
  std::ofstream outputFile(filename, std::ios::app);
  if (!outputFile.is_open()) {
    std::cout << "Не удалось открыть файл: " << filename << std::endl;
    return 0;
  }

  for (size_t n = 100; n <= 100000; n += 500) {
    double area = monteCarlo(cx1, cy1, r1, cx2, cy2, r2, cx3, cy3, r3, n);
    std::cout << n << ";"<< area << std::endl;
    outputFile << n << ";" << area << "\n";
  }
  outputFile.close();

  return 0;
}
