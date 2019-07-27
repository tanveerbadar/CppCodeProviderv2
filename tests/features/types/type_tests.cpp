#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "../../../src/features/declarations/variable_declaration.h"
#include "../../../src/features/expressions.h"
#include "../../../src/features/functions.h"
#include "../../../src/features/statements/try_statement.h"
#include "../../../src/features/types.h"

using namespace std;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::types::templates;

BOOST_AUTO_TEST_SUITE(type_tests)

BOOST_AUTO_TEST_CASE(user_defined_type_tests)
{
    auto udt = make_shared<user_defined_type>("udt");

    BOOST_TEST(udt->bases().size() == 0);
    BOOST_TEST(udt->member_fields().size() == 0);
    BOOST_TEST(udt->member_functions().size() == 0);
    BOOST_TEST(udt->template_parameters().size() == 0);
    BOOST_TEST(udt->get_name() == "udt");

    udt->member_functions().emplace_back(string("mf"), make_shared<primitive_type>("int"), udt);
    udt->member_fields().emplace_back(make_pair(access_levels::public_access, make_unique<variable_declaration>(declarator_specifier(make_unique<primitive_type>("int")))));

    auto copy(*udt);

    BOOST_TEST(copy.bases().size() == 0);
    BOOST_TEST(copy.member_fields().size() == 1);
    BOOST_TEST(copy.member_functions().size() == 1);
    BOOST_TEST(copy.template_parameters().size() == 0);
    BOOST_TEST(copy.get_name() == "udt");

    copy = *udt;

    BOOST_TEST(copy.bases().size() == 0);
    BOOST_TEST(copy.member_fields().size() == 1);
    BOOST_TEST(copy.member_functions().size() == 1);
    BOOST_TEST(copy.template_parameters().size() == 0);
    BOOST_TEST(copy.get_name() == "udt");
}

BOOST_AUTO_TEST_CASE(enumeration_tests)
{
    auto e = make_unique<enumeration>("e");

    BOOST_TEST(e->enumerators().size() == 0);
    BOOST_TEST(e->get_name() == "e");
    BOOST_TEST(!e->is_scoped_enum());

    e->enumerators().emplace_back(make_pair(access_levels::public_access, make_unique<variable_declaration>(declarator_specifier(make_unique<primitive_type>("int")))));

    auto copy(*e);

    BOOST_TEST(copy.enumerators().size() == 1);
    BOOST_TEST(copy.get_name() == "e");
    BOOST_TEST(!copy.is_scoped_enum());

    copy = *e;

    BOOST_TEST(copy.enumerators().size() == 1);
    BOOST_TEST(copy.get_name() == "e");
    BOOST_TEST(!copy.is_scoped_enum());
}

BOOST_AUTO_TEST_CASE(union_tests)
{
    auto e = make_shared<union_type>("u");

    BOOST_TEST(e->member_fields().size() == 0);
    BOOST_TEST(e->member_functions().size() == 0);
    BOOST_TEST(e->template_parameters().size() == 0);
    BOOST_TEST(e->get_name() == "u");

    e->template_parameters().emplace_back(make_unique<template_parameter>("T"));
    e->member_functions().emplace_back(string("mf"), make_shared<primitive_type>("int"), e);
    e->member_fields().emplace_back(make_pair(access_levels::public_access, make_unique<variable_declaration>(declarator_specifier(make_unique<primitive_type>("int")))));

    BOOST_TEST(e->member_fields().size() == 1);
    BOOST_TEST(e->member_functions().size() == 1);
    BOOST_TEST(e->template_parameters().size() == 1);
    BOOST_TEST(e->get_name() == "u");

    boost::test_tools::output_test_stream stream;

    e->write_declaration(stream);
    e->write_definition(stream);

    auto copy(*e);

    BOOST_TEST(copy.member_fields().size() == 1);
    BOOST_TEST(copy.member_functions().size() == 1);
    BOOST_TEST(copy.template_parameters().size() == 1);
    BOOST_TEST(copy.get_name() == "u");

    copy.write_declaration(stream);
    copy.write_definition(stream);

    e->template_parameters().emplace_back(make_unique<template_parameter>("U"));
    e->member_functions().emplace_back(string("mf2"), make_shared<primitive_type>("int"), e);
    e->member_fields().emplace_back(make_pair(access_levels::public_access, make_unique<variable_declaration>(declarator_specifier(make_unique<primitive_type>("int")))));

    copy = *e;

    BOOST_TEST(copy.member_fields().size() == 2);
    BOOST_TEST(copy.member_functions().size() == 2);
    BOOST_TEST(copy.template_parameters().size() == 2);
    BOOST_TEST(copy.get_name() == "u");

    copy.write_declaration(stream);
    copy.write_definition(stream);
}

BOOST_AUTO_TEST_SUITE_END()