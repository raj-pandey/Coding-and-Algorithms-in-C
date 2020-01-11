#include <stdio.h>

#define SIZEOF(x)   (sizeof(x)/sizeof(x[0])) 

#if 0
#define ENTER    printf("Entering %s\n", __func__)
#define EXIT     printf("Exiting %s\n", __func__)
#else
#define ENTER    do{/*do nothing*/}while(0)
#define EXIT     do{/*do nothing*/}while(0)
#endif

/*
Sorting Algorithm types
*/
typedef enum {
    BUBBLESORT=0,
    SELSORT,
    INSERTIONSORT,
    MERGESORT,
	QUICKSORT
}sort_t;

/*
Function: display
Input Parameters:
    a:   Array to be printed
    sz:  Size of the Array
*/
void display(int *a, int sz){
    int i;
    
    ENTER;
    
    for(i=0; i<sz; ++i)
        printf("%d\t", a[i]);
    printf("\n");
    
    EXIT;
}

/*
Function: displaySorted helper
Input Parameters:
    a:    Array to be sorted
    sz:   Size of the Array
    type: Algorithm type
*/
void displaySorted(int *a, int sz, int type){
    ENTER;
    
    switch(type){
        case -1:
            printf("Unsorted array\n");
            display(a, sz);
            break;
        case 0:
            printf("Bubble Sort result\n");
            display(a, sz);
            break;
        case 1:
            printf("Selection Sort result\n");
            display(a, sz);
            break;
        case 2:
            printf("Insertion Sort result\n");
            display(a, sz);
            break;
        case 3:
            printf("Merge Sort result\n");
            display(a, sz);
            break;
        case 4:
            printf("Quick Sort result\n");
            display(a, sz);
            break;
        default:
            break;
    }
    
    EXIT;
    
    return;
}

/*
Function: bubbleSort Algorithm
Input Parameters:
	a:  Array to be sorted
	sz: Array size
Output Parameters:
	None
Worst Case: O(n2)
Best Case: O(1)
*/
void bubbleSort(int *a, int sz){
    int i,j,tmp;
    
    ENTER;
    
    for(i=0; i<sz-1; ++i){
        for(j=0; j<sz-i-1; ++j){
            if (a[j] > a[j+1]){
                tmp = a[j];
                a[j]=a[j+1];
                a[j+1]=tmp;
            }
        }
    }
    
    EXIT;
    
    return;
}

/*
Function: selSort Algorithm
Input Parameters:
	a:  Array to be sorted
	sz: Array size
Output Parameters:
	None
Worst Case: O(n2)
Best Case:  O(n2)
*/
void selSort(int *a, int sz){
    int i,j, min, tmp;
    i=j=min=0;
    
    ENTER;
    
    for(i=0; i<sz; ++i){
        min=i;
        for(j=i+1; j<sz; ++j){
            if(a[j]<a[min])
                min=j;
        }
        tmp=a[min];
        a[min]=a[i];
        a[i]=tmp;
    }

    EXIT;
    
    return;
}

/*
Function: insertionSort Algorithm
Input Parameters:
	a:  Array to be sorted
	sz: Array size
Output Parameters:
	None
Worst Case: O(n2)
Best Case:  O(n)
*/
void insertionSort(int *a, int sz){
    int i,j, min, tmp;
    
    ENTER;
    
    for(i=0; i<sz; ++i){
        min=i;
        for(j=i+1; j<sz; ++j){
            if(a[j]<a[min])
                min=j;
        }
        tmp=a[min];
        a[min]=a[i];
        a[i]=tmp;
    }
    
    EXIT;
    
    return;
}

/*
Function to merge left sub-array and right sub-array
Input Parameters:
	a:   Resulting Array
	lsz: Size of left sub-array
	lar: Left sub-array
	rsz: Size of right sub-array
	rar: Right sub-array
Output:
	None
*/
void merge(int *a, int lsz, int *lar, int rsz, int *rar){
    int i,j,k;i=j=k=0;
    
    ENTER;
    
    while(i < lsz && j < rsz){
        if (lar[i] <= rar[j]){
            a[k] = lar[i++];
        } else {
            a[k] = rar[j++];
        }
        k++;
    }
    
    while (i < lsz)
        a[k++] = lar[i++];
    
    while (j < rsz)
        a[k++] = rar[j++];
    
    EXIT;
    
    return;
} 

/*
Function: mergeSort Algorithm
Input Parameters:
	a:  Array to be sorted
	sz: Array size
Output Parameters:
	None
Worst Case: O(nlogn)
Best Case: Omega(nlogn)
*/
void mergeSort(int *a, int sz){
    int left, right, i,j;
    
    ENTER;
    
    if(sz < 2)
        return;
    left = sz/2; right=sz-left;
    
    int lar[left], rar[right];
    for(i=0; i<left; i++)
        lar[i] = a[i];
    
    for(j=0; j<right; j++)
        rar[j] = a[j+left];
    
    mergeSort(lar, left);
    mergeSort(rar, right);
    merge(a, left, lar, right, rar);
    
    EXIT;
    
    return;
}

/*
Function: swapptr
Input Parameters:
    a:     Array to be sorted
    lIdx:  Left array index;
    rIdx:  Right array index
*/
void swapptr(int *a, int lIdx, int rIdx)
{
	ENTER;
	
	int temp = a[lIdx];
	a[lIdx] = a[rIdx];
	a[rIdx] = temp;

    EXIT;
    
    return;
}

/*
Function: partition
Input Parameters:
    a:      Array to be sorted
    lIdx:   Left index
    rIdx:   Right index
    pivot:  Pivot
Output Parameters:
	leftptr: partition index
*/
int partition(int *a, int lIdx, int rIdx, int pivot)
{
	int leftptr = (lIdx -1);
	int rightptr = rIdx;

    ENTER;
    
	for(;;){
		while (a[++leftptr] < pivot){
		}
		
		while (rightptr > 0 && a[--rightptr] > pivot){
		}

		if (leftptr >= rightptr)
			break;
		else
			swapptr(a, leftptr, rightptr);
		
	}
	swapptr(a, leftptr, rIdx);

    EXIT;
    
	return leftptr;
}

/*
Function: quickSort Algorithm
Input Parameters:
	a:    Array to be sorted
	lIdx: Left index
	rIdx: Right index
Output Parameters:
	None
Worst Case: n2 (n is size of array)
Best Case: O(nlogn)
*/
void quickSort(int *a, int lIdx, int rIdx)
{
	ENTER;
	
	if (rIdx - lIdx <= 0)
		return;

	int pivot = a[rIdx], partIdx;

	partIdx = partition(a, lIdx, rIdx, pivot);

	quickSort(a, lIdx, partIdx - 1);
	quickSort(a, partIdx + 1, rIdx);
	
	EXIT;
	
	return;
}

/*
Function: Main application function to sort the array
*/
int main(int argc, char **argv)
{
    int a[] = {3,9,0,4,7,12,76,89,34};
    int sz=SIZEOF(a), algo_type;
    
    ENTER;
    
    displaySorted(a, sz, -1);
    
    for(;;){
        printf("Enter the sorting algo to sort the array\n");
		printf("0: BubbleSort\n");
		printf("1: SelectionSort\n");
		printf("2: InsertionSort\n");
		printf("3: MergeSort\n");
		printf("4: QuickSort\n");
        scanf("%d", &algo_type);
        
        if (algo_type < 0 ||  algo_type > 4)
            ;
        else
            break;
    }
    
    switch(algo_type){
        case 0:
            printf("Bubble sort\n");
            bubbleSort(a, sz);
            break;
        case 1:
            printf("Selection sort\n");
            selSort(a, sz);
            break;
        case 2:
            printf("Insertion sort\n");
            insertionSort(a, sz);
            break;
        case 3:
            printf("Merge sort\n");
            mergeSort(a, sz);
            break;
		case 4:
            printf("Quick sort\n");
            quickSort(a, 0, sz-1);
            break;
        default:
            printf("default case\n");
            break;
    }

    displaySorted(a, sz, algo_type);
    
    EXIT;
    
    return 0;
}
