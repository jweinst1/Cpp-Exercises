#ifndef CXX_TEST_H
#define CXX_TEST_H

/**
 * @file
 * Contains helper functions and macros for implementing a simple testing
 * framework.
 */

#include <iostream>
#include <string>

///////////////////////////////////////////////////////////////////////////////

namespace cxx_course {

//
// We can't use std::equal_to because it has only one template argument and we
// want to be able to have two for two almost-but-not-quite-the-same types,
// e.g., char const* and char*.
//

/**
 * Generic test for equality.
 *
 * @tparam T1 The first type.
 * @tparam T2 The second type.
 * @param i The first value.
 * @param j The second value.
 * @return Returns \c true only if \a i == \a j.
 */
template<typename T1,typename T2>
inline bool test_eq( T1 const &i, T2 const &j ) {
    return i == j;
}

/**
 * Specialization for <code>char const*</code>.
 */
template<typename T2>
inline bool test_eq( char const *s, T2 const &j ) {
    return test_eq( std::string( s ), j ); // wrap in std::string so == works
}

/**
 * Specialization for <code>char*</code>.
 *
 * @note This is needed in addition to the specialization for
 * <code>char const*</code> in order to make it work with non-const \c char
 * buffers:
 * @code
 *      char buf[64];
 *      // ...
 *      cout << (test_eq( buf, "foo" ) ? "PASS" : "FAIL") << '\n';
 * @endcode
 */
template<typename T2>
inline bool test_eq( char *s, T2 const &j ) {
    return test_eq( const_cast<char const*>( s ), j );
}

/**
 * Holds a test result for subsequent printing.
 *
 * @tparam ActualType The type of the actual test result.
 * @tparam ExpectedType The type of the expected test result.
 */
template<typename ActualType,typename ExpectedType>
struct test_result {
    typedef ActualType actual_type;
    typedef ExpectedType expected_type;

    /**
     * Constructs a %test_result.
     *
     * @param actual The actual value.
     * @param expected The expected value.
     * @param pass \c true only if the test passed.
     * @param line The line number of the test for printing if the test doesn't
     * pass.
     */
    test_result( actual_type const &actual, expected_type const &expected,
                 bool pass, int line ) :
        _actual( actual ),
        _expected( expected ),
        _pass( pass ),
        _line( line )
    {
    }

    actual_type const _actual;
    expected_type const _expected;
    bool const _pass;
    int const _line;
};

/**
 * Gets the printable version of \a v.
 *
 * @tparam T The type of \a v.
 * @param v The value to print.
 * @return Returns the printable version of \a v.
 */
template<typename T>
inline T const& print_value( T const &v ) {
    return v;
}

/**
 * Specialization for \c bool such that it prints either \c true or \c false
 * instead of either \c 1 or \c 0.
 */
inline char const* print_value( bool v ) {
    return v ? "true" : "false";
}

/**
 * Prints a test_result.
 *
 * @tparam ActualType The type of the actual result.
 * @tparam ExpectedType The type of the expected result.
 * @param o The ostream to print to.
 * @param r The test_result to print.
 * @return Returns \a o.
 */
template<typename ActualType,typename ExpectedType>
std::ostream& operator<<( std::ostream &o,
                          test_result<ActualType,ExpectedType> const &r ) {
    o << (r._pass ? "PASS" : "FAIL") << ": " << print_value( r._expected );
    if ( !r._pass )
        o << "; got: " << print_value( r._actual )
          << " (line: " << r._line << ')';
    return o;
}

/**
 * Helper function similar to \c std::make_pair() that makes a test_result
 * based on the argument types rather than having to specify the test_result
 * template parameters explicitly.
 *
 * @tparam ActualType The type of the actual test result.
 * @tparam ExpectedType The type of the expected test result.
 * @param actual The actual value.
 * @param expected The expected value.
 * @param pass \c true only if the test passed.
 * @param line The line number of the test for printing if the test doesn't
 * pass.
 */
template<typename ActualType,typename ExpectedType>
inline test_result<ActualType,ExpectedType>
make_test_result( ActualType const &actual, ExpectedType const &expected,
                  bool pass, int line ) {
    return test_result<ActualType,ExpectedType>( actual, expected, pass, line );
}

/**
 * Specialization for <code>char const*</code> / <code>char const*</code>.
 */
inline test_result<char const*,char const*>
make_test_result( char const *actual, char const *expected,
                  bool pass, int line ) {
    return test_result<char const*,char const*>( actual, expected, pass, line );
}

/**
 * Specialization for <code>char*</code> / <code>char const*</code>.
 */
inline test_result<char const*,char const*>
make_test_result( char *actual, char *expected, bool pass, int line ) {
    return test_result<char const*,char const*>( actual, expected, pass, line );
}

/**
 * Specialization for <code>char const*</code> / <code>char*</code>.
 */
inline test_result<char const*,char const*>
make_test_result( char const *actual, char *expected, bool pass, int line ) {
    return test_result<char const*,char const*>( actual, expected, pass, line );
}

/**
 * Specialization for <code>char*</code> / <code>char*</code>.
 */
inline test_result<char const*,char const*>
make_test_result( char *actual, char const *expected, bool pass, int line ) {
    return test_result<char const*,char const*>( actual, expected, pass, line );
}

} // namespace cxx_course

///////////////////////////////////////////////////////////////////////////////

#define TEST_BLOCK(...)                 do { __VA_ARGS__ } while (0)

/**
 * Test comparison helper macro that hides the verbose, ugly implementation.
 *
 * @note Temporaries are created so the expressions are evaluated exactly once.
 *
 * @hideinitializer
 */
#define TEST_COMP(TEST,ACTUAL,EXPECTED) TEST_BLOCK( \
    try {                                           \
        auto const &actual( ACTUAL );               \
        auto const &expected( EXPECTED );           \
        std::cout << cxx_course::make_test_result( actual, expected, cxx_course::test_ ## TEST( actual, expected ), __LINE__ ) << '\n'; \
    }                                               \
    catch ( ... ) {                                 \
        std::cout << "FAIL: caught unexpected exception (line: " << __LINE__ << ")\n"; \
    } )

#define TEST_EQUAL(ACTUAL,EXPECTED)     TEST_COMP( eq, ACTUAL, EXPECTED )
#define TEST_FALSE(EXPR)                TEST_COMP( eq, EXPR, false )
#define TEST_TRUE(EXPR)                 TEST_COMP( eq, EXPR, true )

/**
 * Tests that an expected exception was thrown.
 *
 * @hideinitializer
 */
#define TEST_EXCEPTION(EXPR,EXCEPTION) TEST_BLOCK(  \
    try {                                           \
        (void)(EXPR);                               \
        std::cout << "FAIL: expected " #EXCEPTION " (line: " << __LINE__ << ")\n"; \
    }                                               \
    catch ( EXCEPTION const& ) {                    \
        std::cout << "PASS: " #EXPR "\n";           \
    }                                               \
    catch ( ... ) {                                 \
        std::cout << "FAIL: caught unexpected exception (line: " << __LINE__ << ")\n"; \
    } )

///////////////////////////////////////////////////////////////////////////////
#endif /* CXX_TEST_H */
/* vim:set et sw=4 ts=4: */