#include "cxx_test.h"

#include <cstddef>                      /* for size_t */

////////// EXERCISE BELOW THIS LINE ///////////////////////////////////////////

/**
 * Copies at most \a n characters from \a src to \a dst.
 *
 * @param dst A pointer to the buffer to receive the copy.  It must be large
 * enough to hold \a n characters of \a src plus a terminating null.
 * @param src The C string to copy from.
 * @param n The number of characters to copy.
 * @return Returns \a dst.
 */
char* strncpy( char *dst, char const *src, size_t n ) {
    //
    // As a starting point, here's the code for strcpy().  Modify it to copy at
    // most n characters.
    //
    // The way the real strncpy() works is:
    //
    //  + If the length of src < n, then dst is padded with null bytes until n
    //    is reached.
    //
    //  + If the length of src >= n, then dst is NOT null-terminated.  This
    //    means it's the caller's responsibillity to ensure dst is null-
    //    terminated.  This isn't the greatest, but that's the way the real
    //    strncpy() is.
    //
    char *const dst_orig = dst;
    while(n--) {
        //null byte padding
        if(!(*src) && n) *dst++ = '\0';
        else *dst++ = *src++;
    }
    return dst_orig;
}

////////// EXERCISE ABOVE THIS LINE ///////////////////////////////////////////

int main() {

    // Have a message buffer big enough to contain the concatenated string and
    // initialize it to be empty.
    char big_buf[64] = "";

    TEST_EQUAL( strncpy( big_buf, "hello", 4 ), "hell" );
    TEST_EQUAL( strncpy( big_buf, "brown", 1 ), "bell" );
    return 0;
}