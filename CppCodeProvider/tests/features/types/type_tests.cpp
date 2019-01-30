#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "../../../features/expressions.h"
#include "../../../features/functions.h"
#include "../../../features/types.h"

using namespace std;
using namespace cpp::codeprovider::types;

BOOST_AUTO_TEST_SUITE(type_tests)

BOOST_AUTO_TEST_CASE(user_defined_type_tests)
{
    auto udt = make_unique<user_defined_type>("udt");

    auto copy(*udt);

    copy = *udt;
}

BOOST_AUTO_TEST_SUITE_END()