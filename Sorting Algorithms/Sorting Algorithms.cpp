#include <iostream>
#include <random>
#include <string>

void bubbleSort(int* arr, const int& N);
void selectionSort(int* arr, const int& N);
void insertionSort(int* arr, const int& N);
void quickSort(int* arr, const int& N);
void quickSort(int* arr, const int& N, const int& start, const int& end);
void printResults(const std::string& sortName, const int* arr, const int* sorted_arr, const int& N);

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 100);

    const int N = 20;
    int arr[N];
    int sorted_arr[N];
    for (int i = 0; i < N; i++)
        arr[i] = distr(gen);
    
    // Testing
    /*const int N = 8;
    int arr[N] = {1, 4, 3, 8, 7, 10, 5, 2};
    int sorted_arr[N];*/

    std::string algorithm_names[] = { "Bubble Sort", "Selection Sort", "Insertion Sort", "Quick Sort" };
    void (*algorithms[])(int* arr, const int& N) = {bubbleSort, selectionSort, insertionSort, quickSort};

    for (int sort_index = 0; sort_index < sizeof(algorithm_names) / sizeof(std::string); sort_index++) {
        memcpy(sorted_arr, arr, sizeof(arr));
        algorithms[sort_index](sorted_arr, N);
        printResults(algorithm_names[sort_index], arr, sorted_arr, N);
    }
}

void bubbleSort(int* arr, const int& N) {
    bool swap_occurred;
    for (int i = 1; i < N; i++) {
        swap_occurred = false;
        for (int j = 0; j < N - i; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swap_occurred = true;
            }
        }
        if (!swap_occurred)
            break;
    }
    return;
}

void selectionSort(int* arr, const int& N) {
    int min_index;
    for (int i = 0; i < N - 1; i++) {
        min_index = i;
        for (int j = i + 1; j < N; j++)
            if (arr[j] < arr[min_index])
                min_index = j;
        if (min_index != i)
            std::swap(arr[i], arr[min_index]);
    }
    return;
}


void insertionSort(int* arr, const int& N) {
    for (int i = 1; i < N; i++) {
        int j = i - 1;
        while (j > -1 && arr[j] > arr[j + 1]) {
            std::swap(arr[j], arr[j + 1]);
            j--;
        }
    }
    return;
}

void quickSort(int* arr, const int& N) {
    quickSort(arr, N, 0, N - 1);
}

void quickSort(int* arr, const int& N, const int& start, const int& end) {
    if (start >= end) return;
    int left = start;
    int right = end;
    int pivot = arr[(left + right) / 2];

    while (left <= right) {
        while (arr[left] < pivot) left++;
        while (arr[right] > pivot) right--;

        if (left <= right) {
            std::swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }

    quickSort(arr, N, 0, left - 1);
    quickSort(arr, N, left, end);
    
    return;
}


void printResults(const std::string& sortName, const int* arr, const int* sorted_arr, const int& N) {
    std::cout << "\t---------\t\t" << sortName << "\t\t---------\t\t" << std::endl;
    std::cout << "[ " << *arr << ", ";
    for (int i = 1; i < N - 1; i++)
        std::cout << arr[i] << ", ";
    std::cout << arr[N - 1] << " ]" << std::endl << std:: endl;

    std::cout << "[ " << *sorted_arr << ", ";
    for (int i = 1; i < N - 1; i++)
        std::cout << sorted_arr[i] << ", ";
    std::cout << sorted_arr[N - 1] << " ]" << std::endl << std::endl;
    return;
}