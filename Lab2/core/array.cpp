#include "array.h"
#include <windows.h>

namespace ArrayProcessor {
    void findMinMax(int* arr, int size, int* minVal, int* maxVal) {
        if (size <= 0) return;
        
        *minVal = arr[0];
        *maxVal = arr[0];
        
        for (int i = 1; i < size; i++) {
            if (arr[i] < *minVal) {
                *minVal = arr[i];
            }
            if (arr[i] > *maxVal) {
                *maxVal = arr[i];
            }
            Sleep(MIN_MAX_SLEEP_MS);
        }
    }
    
    double calculateAverage(int* arr, int size) {
        if (size <= 0) return 0;
        
        double sum = 0;
        for (int i = 0; i < size; i++) {
            sum += arr[i];
            Sleep(AVERAGE_SLEEP_MS);
        }
        return sum / size;
    }
    
    void replaceMinMaxWithAverage(int* arr, int size, int minVal, int maxVal, double avg) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == minVal || arr[i] == maxVal) {
                arr[i] = static_cast<int>(avg);
            }
        }
    }
}