#ifndef P3_BLOCK__ARRAYGENERATOR_H_
#define P3_BLOCK__ARRAYGENERATOR_H_

#include <vector>
#include <algorithm>
#include <random>

class ArrayGenerator {
 public:
  ArrayGenerator() {
    std::random_device rd;
    rng.seed(rd());
  }

  std::vector<int> generateRandomArray(size_t size, int minValue = 0, int maxValue = 6000) {
    std::uniform_int_distribution<int> dist(minValue, maxValue);
    std::vector<int> array(size);
    for (auto& val : array) {
      val = dist(rng);
    }
    return array;
  }

  std::vector<int> generateReversedArray(size_t size) {
    std::vector<int> array(size);
    for (size_t i = 0; i < size; ++i) {
      array[i] = size - i;
    }
    return array;
  }

  std::vector<int> generateNearlySortedArray(size_t size, int swaps = 10) {
    std::vector<int> array(size);
    for (size_t i = 0; i < size; ++i) {
      array[i] = i;
    }

    for (int i = 0; i < swaps; ++i) {
      size_t idx1 = rng() % size;
      size_t idx2 = rng() % size;
      std::swap(array[idx1], array[idx2]);
    }

    return array;
  }

 private:
  std::mt19937 rng;
};

#endif //P3_BLOCK__ARRAYGENERATOR_H_