#include <stdio.h>

void selectionSort(int arr[], int size);

int main(void){
    int arr[]={4,2,5,1,3};
    int size = sizeof(arr)/sizeof(int);
    printf("array unsorted: ");
    for(int i=0; i<size; i++){
        printf("%i ", arr[i]);
    }
    printf("\n");

    selectionSort(arr, size);

    printf("array sorted: ");
    for(int i=0; i<size; i++){
        printf("%i ", arr[i]);
    }
    printf("\n");

    return 0;
}

void selectionSort(int arr[], int size){
    for(int i=0; i<size-1; i++){
        int lowIndex = i;
        for(int j=i+1; j<size; j++){
            if(arr[j]<arr[lowIndex])
                lowIndex=j;
        }
        int temp = arr[i];
        arr[i]=arr[lowIndex];
        arr[lowIndex]=temp;
    }
}