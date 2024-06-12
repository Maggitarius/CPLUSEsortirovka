#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

class MergeSort {
public:
    void Merge(std::vector<int>& arr, int low, int mid, int high) {
        int n1 = mid - low + 1;
        int n2 = high - mid;

        std::vector<int> L(n1), R(n2);

        for (int i = 0; i < n1; ++i)
            L[i] = arr[low + i];
        for (int j = 0; j < n2; ++j)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = low;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    void Sort(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int mid = low + (high - low) / 2;
            Sort(arr, low, mid);
            Sort(arr, mid + 1, high);
            Merge(arr, low, mid, high);
        }
    }
};

int main() {
    setlocale(LC_ALL, "RUS");
    std::vector<int> arr(10);

    std::cout << "Введите 10 целых чисел:\n";
    for (int i = 0; i < 10; i++) {
        std::cin >> arr[i];
    }

    MergeSort mergeSort;
    std::thread mergeSortThread([&]() {
        mergeSort.Sort(arr, 0, arr.size() - 1);
        });

    mergeSortThread.join();

    std::cout << "Отсортированный массив:\n";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}