#include "cxx_test.h"

////////// EXERCISE BELOW THIS LINE ///////////////////////////////////////////

/**
 * Binary search the given array for the given value.
 *
 * A binary search works by taking a range of elements to check, say low-high,
 * and caclulating the midpoint, say mid; then:
 *
 *  + If v[mid] == the value you're looking for, you're done: return mid.
 *  + If v[mid] > the value you're looking for, reset high = mid - 1, calculate
 *    a new mid, and start again.
 *  + If v[mid] < the value you're looking for, reset low = mid + 1, calculate
 *    a new mid, and start again.
 *
 * If any any time high <= low, you've exhausted the range and it means that
 * the value you're looking for is not present.
 *
 * @param v The sorted array to search.
 * @param n The number of elements in \a v.
 * @param value The value to search for.
 * @return Returns the index of \a v having \a value if found or -1 if not
 * found.
 */
int binary_search( int const v[], int n, int value ) {
    int low_ind = 0;
    int high_ind = n-1;
    int mid = 0;
    while(low_ind <= high_ind){
        mid = (high_ind+low_ind)/2;
        if(v[mid] == value)
           return mid;
        else if(v[mid] > value)
           high_ind = mid - 1;
        else
           low_ind = mid + 1;
    }
    return -1;
}

////////// EXERCISE ABOVE THIS LINE ///////////////////////////////////////////

int v[] = {
     1, //  0
     3, //  1
     7, //  2
    15, //  3
    19, //  4
    27, //  5
    38, //  6
    42, //  7
    49, //  8
    50, //  9
    55, // 10
    63, // 11
    66, // 12
    67, // 13
    76, // 14
    98, // 15
};

int n = sizeof(v) / sizeof(v[0]);

int main() {
    TEST_EQUAL( binary_search( v, n,  -7 ), -1 );
    TEST_EQUAL( binary_search( v, n,   0 ), -1 );
    TEST_EQUAL( binary_search( v, n,   1 ),  0 );
    TEST_EQUAL( binary_search( v, n,   5 ), -1 );
    TEST_EQUAL( binary_search( v, n,  42 ),  7 );
    TEST_EQUAL( binary_search( v, n,  66 ), 12 );
    TEST_EQUAL( binary_search( v, n,  67 ), 13 );
    TEST_EQUAL( binary_search( v, n,  98 ), 15 );
    TEST_EQUAL( binary_search( v, n,  99 ), -1 );
    TEST_EQUAL( binary_search( v, n, 101 ), -1 );
    return 0;
}