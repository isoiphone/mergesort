#include <stdio.h>
#include <assert.h>
#include <vector>
#include <algorithm>

void merge(int *dst, int* src, int left, int right, int end) {
    int ledge = left;
    int redge = right;

    for (int i=left; i<end; ++i) {
        if (ledge < right && (redge >= end || src[ledge] <= src[redge])) {
            dst[i] = src[ledge];
            ledge++;
        } else {
            dst[i] = src[redge];
            redge++;
        }
    }
}

void mergeSort(int *dst, int *src, int len) {
    int* pdest=dst;
    int* psrc=src;
    
    for (int run = 1; run < len; run *= 2) {
        for (int i=0; i<len; i += 2*run) {
            merge(pdest, psrc, i, std::min(i+run, len), std::min(i+2*run, len));
        }
        
        int* ptmp = pdest;
        pdest = psrc;
        psrc = ptmp;
    }
}


void sortInPlace(int* arr, int len) {
    int* work = new int[len];
    mergeSort(work, arr, len);
    memcpy(arr, work, sizeof(int)*len);
    delete[] work;
}

bool isSorted(int* arr, int len) {
    for (int i=0; i<len; ++i) {
        printf("%d%s", arr[i], (i!=len-1) ? ", " : ".\n" );
    }
    
    for (int i=1; i<len; ++i) {
        if (arr[i] < arr[i-1])
            return false;
    }
    return true;
}


int main(int argc, const char * argv[]) {
    // some empty array
    int test1[] = {};
    int len1 = 0;
    
    sortInPlace(test1, len1);
    assert( isSorted(test1, len1) );
    
    // does our isSorted func work?
    int test2[] = {1,2};
    int len2 = 2;
    assert(test2[0] == 1);
    assert(test2[1] == 2);
    assert( isSorted(test2, len2) );

    int test3[] = {2,1};
    int len3 = 2;
    assert( !isSorted(test3, len3) );
    
    // already sorted data
    int test4[] = {1,2};
    int len4 = 2;
    sortInPlace(test4, len4);
    assert( isSorted(test4, len4) );
    assert(test4[0] == 1);
    assert(test4[1] == 2);
    
    // unsorted data
    int test5[] = {2,1};
    int len5 = 2;
    sortInPlace(test5, len5);
    assert( isSorted(test5, len5) );
    assert(test5[0] == 1);
    assert(test5[1] == 2);

    
    // unsorted data
    int test6[] = {2,1,3};
    int len6 = 3;
    sortInPlace(test6, len6);
    assert( isSorted(test6, len6) );
    assert(test6[0] == 1);
    assert(test6[1] == 2);
    assert(test6[2] == 3);
    
    // unsorted data
    int test7[] = {10,54,3,76,26,66,18,95,19,27,62,8,93,85,28,69,72,55,96,80,56,92,10,93,25,66,3,82,72,29,8,13,52,56,3,67,6,26,53,93,14,86,54,26,92,42,32,22,60,17,67,80,49,25,10,58,12,65,15,54,27,30,63,83,42,18,42,76,75,8,96,15,11,6,4,9,62,20,71,81,57,32,60,84,15,97,6,51,88,72,32,86,55,51,6,36,80,74,26,71};
    int len7 = 100;
    sortInPlace(test7, len7);
    assert( isSorted(test7, len7) );

    return 0;
}

