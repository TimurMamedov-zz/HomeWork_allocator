#define BOOST_TEST_MODULE allocator_test

#include <boost/test/unit_test.hpp>

#include "version.h"

BOOST_AUTO_TEST_SUITE(TestSuite1)

BOOST_AUTO_TEST_CASE(version_test)
{
    BOOST_CHECK( version() > 0 );
}

BOOST_AUTO_TEST_SUITE_END()