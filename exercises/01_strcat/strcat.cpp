#include "cxx_test.h"

#include <cstddef>                      /* for size_t */

////////// EXERCISE BELOW THIS LINE ///////////////////////////////////////////

/**
 * Concatenates \a src onto the end of \a dst.
 *
 * @param dst A pointer to the buffer to concatenate onto.  It must be large
 * enough to hold all additional characters plus a terminating null.
 * @param src The C string to copy from.
 * @return Returns \a dst.
 */
char* strcat( char *dst, char const *src ) {
    // TODO: Hint: do the strlen() exercise before this one.
    char * dstp = dst;
    while(*dstp) dstp++;
    while((*dstp++ = *src++));
    //new terminator for cstr
    *dstp = '\0';
    return dst;
}

////////// EXERCISE ABOVE THIS LINE ///////////////////////////////////////////

int main() {

    // Have a message buffer big enough to contain the concatenated string and
    // initialize it to be empty.
    char big_buf[64] = "";

    TEST_EQUAL( strcat( big_buf, "hello" ), "hello" );
    TEST_EQUAL( strcat( big_buf, ", world" ), "hello, world" );
    return 0;
}