#ifndef P3_BLOCK__SORTTESTER_H_
#define P3_BLOCK__SORTTESTER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <functional>
#include <string>

class SortTester {
 public:
  template<typename SortFunc>
  long long measureExecutionTime(SortFunc sortFunc, std::vector<int>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arr);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  }

  template<typename SortFunc>
  void testAndSaveResults(
      SortFunc sortFunc,
      ArrayGenerator& generator,
      const std::vector<size_t>& sizes,
      const std::string& filename,
      const std::string& testType
  ) {
    std::ofstream outputFile(filename, std::ios::app);
    if (!outputFile.is_open()) {
      std::cerr << "Не удалось открыть файл: " << filename << std::endl;
      return;
    }

    for (size_t size : sizes) {
      std::vector<int> array;

      if (testType == "random") {
        array = generator.generateRandomArray(size);
      } else if (testType == "reversed") {
        array = generator.generateReversedArray(size);
      } else if (testType == "nearly_sorted") {
        array = generator.generateNearlySortedArray(size);
      } else {
        std::cerr << "Неверный тип теста: " << testType << std::endl;
        continue;
      }

      long long time = measureExecutionTime(sortFunc, array);

      outputFile << size << ";" << time << ";" << testType << "\n";
    }

    outputFile.close();
  }
};


#endif //P3_BLOCK__SORTTESTER_H_
