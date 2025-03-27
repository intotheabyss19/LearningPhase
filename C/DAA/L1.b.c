#include <stdio.h>

struct Pair {
    int min;
    int max;
};

struct Pair findMinMax(int arr[], int low, int high) {
    struct Pair result, left, right;
    int mid;
    if (low == high) {
        result.max = arr[low];
        result.min = arr[low];
        return result;
    }
    if (high == low + 1) {
        if (arr[low] > arr[high]) {
            result.max = arr[low];
            result.min = arr[high];
        } else {
            result.max = arr[high];
            result.min = arr[low];
        }
        return result;
    }
    mid = low + (high - low) / 2;
    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high);
    if (left.min < right.min)
        result.min = left.min;
    else
        result.min = right.min;
    if (left.max > right.max)
        result.max = left.max;
    else
        result.max = right.max;
    return result;
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d elements:\n", n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    struct Pair result = findMinMax(arr, 0, n-1);
    printf("Minimum element: %d\n", result.min);
    printf("Maximum element: %d\n", result.max);
    return 0;
}
