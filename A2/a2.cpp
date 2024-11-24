#include <vector>
#include "ArrayGenerator.h"
#include "SortTester.h"

void merge(std::vector<int>& arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  std::vector<int> L(n1), R(n2);

  for (int i = 0; i < n1; ++i)
    L[i] = arr[left + i];
  for (int j = 0; j < n2; ++j)
    R[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k++] = L[i++];
    } else {
      arr[k++] = R[j++];
    }
  }

  while (i < n1) arr[k++] = L[i++];
  while (j < n2) arr[k++] = R[j++];
}

void mergeSort(std::vector<int>& arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}


void insertionSort(std::vector<int>& arr, int left, int right) {
  for (int i = left + 1; i <= right; ++i) {
    int key = arr[i];
    int j = i - 1;
    while (j >= left && arr[j] > key) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = key;
  }
}

void hybridMergeSort(std::vector<int>& arr, int left, int right, int threshold) {
  if (right - left + 1 <= threshold) {
    insertionSort(arr, left, right);
    return;
  }

  if (left < right) {
    int mid = left + (right - left) / 2;
    hybridMergeSort(arr, left, mid, threshold);
    hybridMergeSort(arr, mid + 1, right, threshold);
    merge(arr, left, mid, right);
  }
}

void standardMergeSortWrapper(std::vector<int>& arr) {
  mergeSort(arr, 0, arr.size() - 1);
}

void hybridMergeSortWrapper(std::vector<int>& arr, int threshold) {
  hybridMergeSort(arr, 0, arr.size() - 1, threshold);
}

int main() {
  ArrayGenerator generator;
  SortTester tester;

  // Задаем размеры тестируемых массивов
  std::vector<size_t> sizes;
  for (size_t i = 500; i <= 10000; i += 100) {
    sizes.push_back(i);
  }

  // Тестируем стандартный MERGE SORT
  tester.testAndSaveResults(standardMergeSortWrapper, generator, sizes, "results.csv", "random");
  tester.testAndSaveResults(standardMergeSortWrapper, generator, sizes, "results.csv", "reversed");
  tester.testAndSaveResults(standardMergeSortWrapper, generator, sizes, "results.csv", "nearly_sorted");

  // Тестируем гибридный MERGE SORT с threshold = 15
  int threshold = 15;
  auto hybridSortLambda = [threshold](std::vector<int>& arr) {
    hybridMergeSort(arr, 0, arr.size() - 1, threshold);
  };

  tester.testAndSaveResults(hybridSortLambda, generator, sizes, "results.csv", "random");
  tester.testAndSaveResults(hybridSortLambda, generator, sizes, "results.csv", "reversed");
  tester.testAndSaveResults(hybridSortLambda, generator, sizes, "results.csv", "nearly_sorted");

  return 0;
}
