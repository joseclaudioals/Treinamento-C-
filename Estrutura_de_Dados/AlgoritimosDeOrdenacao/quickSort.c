#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quickSort(int* arr, int start, int end);
int partition(int* arr, int start, int end);
void swap(int* a, int* b);

int main(void){
    int arr[] = {2, 4, 0, 1, 9, 3, 7, 5};
    srand(time(NULL));

    quickSort(arr, 0, (sizeof(arr)/sizeof(int))-1);

    for (int i =0; i< sizeof(arr)/sizeof(int); i++) {
        printf("%d - ", arr[i]);
    }

    return 0;
}

void quickSort(int* arr, int start, int end) {
    if (start>=end) return;

    int p = partition(arr, start, end);

    quickSort(arr, start, p-1);
    quickSort(arr, p+1, end);
}

int partition(int* arr, int start, int end) {

    int is = start + rand() % (end - start + 1);
    swap(&arr[is], &arr[end]);

    int p = arr[end];
    int i = start;
    for (int j = start; j<end; j++) {
        if (arr[j] <= p) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[end]);

    return i;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}