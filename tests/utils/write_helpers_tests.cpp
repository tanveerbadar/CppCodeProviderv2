#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "../../src/utils/write_helpers.h"
#include "../../src/features/types/template_parameters.h"

using namespace std;
using namespace cpp::codeprovider::utils;
using namespace cpp::codeprovider::types::templates;

BOOST_AUTO_TEST_SUITE(write_helper_tests)

BOOST_AUTO_TEST_CASE(write_vector_1_tests)
{
    vector<copyable_ptr<template_parameter>> params{make_unique<template_parameter>("T1"), make_unique<template_parameter>("T2")};

    boost::test_tools::output_test_stream stream;

    write_vector(stream, params);

    auto str = stream.str();

    BOOST_TEST(str == "typename T1, typename T2");
}

BOOST_AUTO_TEST_CASE(write_vector_2_tests)
{
    vector<string> params{"T1", "T2"};

    boost::test_tools::output_test_stream stream;

    write_vector(stream, params);

    auto str = stream.str();

    BOOST_TEST(str == "T1, T2");
}

BOOST_AUTO_TEST_SUITE_END()
