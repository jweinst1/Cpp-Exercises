#include "cxx_test.h"

#include <cstddef>                      /* for size_t */

////////// EXERCISE BELOW THIS LINE ///////////////////////////////////////////

/**
 * Determines the length of the given null-terminated C string.
 *
 * @param s A pointer to the null-terminated C string to determine the length
 * of.
 * @return Returns the number of characters in \a s.
 */
size_t strlen( char const *s ) {
    size_t len = 0;
    while(*s++) len++;
    return len;
}

////////// EXERCISE ABOVE THIS LINE ///////////////////////////////////////////

int main() {
    TEST_EQUAL( strlen( "" ), 0 );
    TEST_EQUAL( strlen( "1" ), 1 );
    TEST_EQUAL( strlen( "hello, world" ), 12 );
    return 0;
}