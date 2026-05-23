#include <stdio.h>

void countSort(int arr[], int size);

int main(void){
    int arr[]={4,2,5,1,3};
    int size = sizeof(arr)/sizeof(int);
    printf("array unsorted: ");
    for(int i=0; i<size; i++){
        printf("%i ", arr[i]);
    }
    printf("\n");

    countSort(arr, size);

    printf("array sorted: ");
    for(int i=0; i<size; i++){
        printf("%i ", arr[i]);
    }
    printf("\n");

    return 0;
}

void countSort(int arr[], int size){
    int max = arr[0];
    for(int i=0; i<size; i++){
        if(arr[i]>max)
        max = arr[i];
    }

    int cntArr[max+1];
    int sizeCnt = sizeof(cntArr)/sizeof(int);
    //inicializa o array com zeros 
    for(int i=0; i<sizeCnt; i++){
        cntArr[i]=0;
    }

    for(int i=0; i<size; i++){
        cntArr[arr[i]]++;
    }
    for(int i=1; i<sizeCnt; i++){
        cntArr[i]=cntArr[i]+cntArr[i-1];
    }

    int ans[size];

    for(int i=size-1; i>=0; i--){
        ans[cntArr[arr[i]]-1]=arr[i];
        cntArr[arr[i]]--;
    }
    for(int i=0; i<size; i++){
        arr[i]=ans[i];
    }

}