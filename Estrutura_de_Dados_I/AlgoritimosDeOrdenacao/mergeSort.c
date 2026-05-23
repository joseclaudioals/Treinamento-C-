#include <stdio.h>

void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

int main(void){
    int arr[]={4,2,5,1,3, 7, 3, 19, 27, 6};
    int size = sizeof(arr)/sizeof(int);
    printf("array unsorted: ");
    for(int i=0; i<size; i++){
        printf("%i ", arr[i]);
    }
    printf("\n");

    mergeSort(arr, 0, size-1);

    printf("array sorted: ");
    for(int i=0; i<size; i++){
        printf("%i ", arr[i]);
    }
    printf("\n");

    return 0;
}

void mergeSort(int arr[], int left, int right){
    if(left<right){
        //calcula o ponto medio
        int mid = left+(right-left)/2;
        //ordena metade da esquerda
        mergeSort(arr, left, mid);
        //ordena metade da direita
        mergeSort(arr, mid+1, right);

        //mescla ambas metades já ordenadas
        merge(arr, left, mid, right);
    }
}

void merge(int arr[], int left, int mid, int right){
    int i, j, k;
    int n1=mid-left+1;//tamanho do subarray esquerdo
    int n2=right-mid;//tamanho do subarray direito

    //cria arrays temporarios 
    int leftArr[n1], rightArr[n2];

    //copia os dados para os arrays temporarios
    for(i=0; i<n1; i++)
        leftArr[i]=arr[left+i];
    for(j=0; j<n2; j++)
        rightArr[j]=arr[mid+1+j];

    i=0;
    j=0;
    k=left;

    while(i<n1&&j<n2){
        if(leftArr[i]<=rightArr[j]){
            arr[k]=leftArr[i];
            i++;
        }
        else{
            arr[k]=rightArr[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        arr[k]=leftArr[i];
        i++;
        k++;
    }

    while(j<n2){
        arr[k]=rightArr[j];
        j++;
        k++;
    }

}