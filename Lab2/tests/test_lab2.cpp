#include <iostream>
#include <cassert>
#include "../core/array.h"

using namespace std;

// Тестовые функции без задержек Sleep для быстрого тестирования
namespace TestArrayProcessor {
    void findMinMaxFast(int* arr, int size, int* minVal, int* maxVal) {
        if (size <= 0) return;

        *minVal = arr[0];
        *maxVal = arr[0];

        for (int i = 1; i < size; i++) {
            if (arr[i] < *minVal) *minVal = arr[i];
            if (arr[i] > *maxVal) *maxVal = arr[i];
        }
    }

    double calculateAverageFast(int* arr, int size) {
        if (size <= 0) return 0;

        double sum = 0;
        for (int i = 0; i < size; i++) {
            sum += arr[i];
        }
        return sum / size;
    }
}

// Тесты для поиска минимального и максимального элементов
void test_find_min_max() {

    // Test 1: Обычный массив
    int arr1[] = { 5, 2, 8, 1, 9 };
    int min1, max1;
    TestArrayProcessor::findMinMaxFast(arr1, 5, &min1, &max1);
    assert(min1 == 1);
    assert(max1 == 9);

    // Test 2: Отрицательные числа
    int arr2[] = { -5, -2, -8, -1, -9 };
    int min2, max2;
    TestArrayProcessor::findMinMaxFast(arr2, 5, &min2, &max2);
    assert(min2 == -9);
    assert(max2 == -1);

    // Test 3: Один элемент
    int arr3[] = { 42 };
    int min3, max3;
    TestArrayProcessor::findMinMaxFast(arr3, 1, &min3, &max3);
    assert(min3 == 42);
    assert(max3 == 42);

    cout << "find_min_max tests passed" << endl;
}

// Тесты для вычисления среднего арифметического
void test_calculate_average() {

    // Test 1: Обычный массив
    int arr1[] = { 1, 2, 3, 4, 5 };
    double avg1 = TestArrayProcessor::calculateAverageFast(arr1, 5);
    assert(avg1 == 3.0);

    // Test 2: Отрицательные числа
    int arr2[] = { -1, -2, -3, -4, -5 };
    double avg2 = TestArrayProcessor::calculateAverageFast(arr2, 5);
    assert(avg2 == -3.0);

    // Test 3: Дробный результат
    int arr3[] = { 1, 2, 3, 4 };
    double avg3 = TestArrayProcessor::calculateAverageFast(arr3, 4);
    assert(avg3 == 2.5);

    cout << "calculate_average tests passed" << endl;
}

// Тесты для замены min/max на среднее значение
void test_replace_min_max_with_average() {
   
    // Test 1: Обычный случай
    int arr1[] = { 1, 5, 3, 5, 1 };
    int min1, max1;
    double avg1;

    // Сначала вычисляем min, max и average
    TestArrayProcessor::findMinMaxFast(arr1, 5, &min1, &max1);
    avg1 = TestArrayProcessor::calculateAverageFast(arr1, 5);

    // Затем вызываем функцию с правильными параметрами
    ArrayProcessor::replaceMinMaxWithAverage(arr1, 5, min1, max1, avg1);

    // Проверяем результат
    assert(arr1[0] == 3);  // было 1 (min)
    assert(arr1[1] == 3);  // было 5 (max)
    assert(arr1[2] == 3);  // было 3 (остается)
    assert(arr1[3] == 3);  // было 5 (max)
    assert(arr1[4] == 3);  // было 1 (min)

    // Test 2: Все элементы одинаковые
    int arr2[] = { 4, 4, 4, 4 };
    int min2, max2;
    double avg2;

    TestArrayProcessor::findMinMaxFast(arr2, 4, &min2, &max2);
    avg2 = TestArrayProcessor::calculateAverageFast(arr2, 4);
    ArrayProcessor::replaceMinMaxWithAverage(arr2, 4, min2, max2, avg2);

    for (int i = 0; i < 4; i++) {
        assert(arr2[i] == 4);
    }

    // Test 3: Другой пример
    int arr3[] = { 2, 4, 6, 8 };
    int min3, max3;
    double avg3;

    TestArrayProcessor::findMinMaxFast(arr3, 4, &min3, &max3);
    avg3 = TestArrayProcessor::calculateAverageFast(arr3, 4);
    ArrayProcessor::replaceMinMaxWithAverage(arr3, 4, min3, max3, avg3);

    assert(arr3[0] == 5);  // было 2 (min)
    assert(arr3[1] == 4);  // остается
    assert(arr3[2] == 6);  // остается
    assert(arr3[3] == 5);  // было 8 (max)

    cout << "replace_min_max_with_average tests passed" << endl;
}

// Главная функция тестов
int main() {
    cout << "Starting tests for Lab2...\n" << endl;
  //  cout << "=========================================" << endl;

    test_find_min_max();
    test_calculate_average();
    test_replace_min_max_with_average();

    //cout << "=========================================" << endl;
    cout << "\nAll tests passed successfully" << endl;

    return 0;
}