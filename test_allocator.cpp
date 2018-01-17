#define BOOST_TEST_MODULE ip_filter_test

#include <boost/test/unit_test.hpp>

#include "version.h"

BOOST_AUTO_TEST_CASE(version_test)
{
    BOOST_CHECK( version() > 0 );
}
