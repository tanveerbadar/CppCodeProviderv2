#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "../../../src/features/declarations/variable_declaration.h"
#include "../../../src/features/expressions.h"
#include "../../../src/features/functions.h"
#include "../../../src/features/statements/try_statement.h"
#include "../../../src/features/types.h"
#include "../../../src/formatters/formatter_settings.h"

using namespace std;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::types::templates;
using namespace cpp::codeprovider::formatting;

BOOST_AUTO_TEST_SUITE(type_tests)

BOOST_AUTO_TEST_CASE(primitive_type_tests)
{
    auto p = make_unique<primitive_type>("int");

    boost::test_tools::output_test_stream stream;
	auto indent = formatter_settings::settings.get_indent_string();

    p->write_declaration(stream);

    BOOST_TEST(stream.str() == "int");

    stream.str("");
    p->write_definition(stream);

    BOOST_TEST(stream.str() == "int");

    auto other = p->clone();

    stream.str("");
    other->write_declaration(stream);

    BOOST_TEST(stream.str() == "int");

    stream.str("");
    other->write_definition(stream);

    BOOST_TEST(stream.str() == "int");

    auto copy(*p);

    stream.str("");
    copy.write_declaration(stream);

    BOOST_TEST(stream.str() == "int");

    stream.str("");
    copy.write_definition(stream);

    BOOST_TEST(stream.str() == "int");

    auto q = make_unique<primitive_type>("double");
    copy = *q;

    stream.str("");
    copy.write_declaration(stream);

    BOOST_TEST(stream.str() == "double");

    stream.str("");
    copy.write_definition(stream);

    BOOST_TEST(stream.str() == "double");

    const auto& c_ref = *p;
    c_ref.get_name();

    stream.str("");
    c_ref.write_declaration(stream);

    BOOST_TEST(stream.str() == "int");

    stream.str("");
    c_ref.write_definition(stream);

    BOOST_TEST(stream.str() == "int");
}

BOOST_AUTO_TEST_CASE(user_defined_type_tests)
{
    auto udt = make_shared<user_defined_type>("udt"), udt2 = make_shared<user_defined_type>("udt2");

    udt->container(udt2);

    udt2->template_parameters().emplace_back(make_unique<template_parameter>("T5"));

    BOOST_TEST(udt->bases().size() == 0);
    BOOST_TEST(udt->member_fields().size() == 0);
    BOOST_TEST(udt->member_functions().size() == 0);
    BOOST_TEST(udt->template_parameters().size() == 0);
    BOOST_TEST(udt->get_name() == "udt");

    udt->template_parameters().emplace_back(make_unique<template_parameter>("T1"));
    udt->template_parameters().emplace_back(make_unique<template_parameter>("T2"));
    udt->member_functions().emplace_back(string("mf"), make_shared<primitive_type>("int"), udt);
    udt->member_fields().emplace_back(make_pair(access_levels::public_access, make_unique<variable_declaration>(declarator_specifier(make_unique<primitive_type>("int")))));

    auto& mf = udt->member_functions()[0];

    mf.template_parameters().emplace_back(make_unique<template_parameter>("T3"));
    mf.template_parameters().emplace_back(make_unique<template_parameter>("T4"));

    boost::test_tools::output_test_stream stream;

    udt->write_declaration(stream);
    udt->write_definition(stream);

    auto output = stream.str();
    
    auto copy(*udt);

    BOOST_TEST(copy.bases().size() == 0);
    BOOST_TEST(copy.member_fields().size() == 1);
    BOOST_TEST(copy.member_functions().size() == 1);
    BOOST_TEST(copy.template_parameters().size() == 2);
    BOOST_TEST(copy.get_name() == "udt");

    copy.write_declaration(stream);
    copy.write_definition(stream);

    copy = *udt;

    BOOST_TEST(copy.bases().size() == 0);
    BOOST_TEST(copy.member_fields().size() == 1);
    BOOST_TEST(copy.member_functions().size() == 1);
    BOOST_TEST(copy.template_parameters().size() == 2);
    BOOST_TEST(copy.get_name() == "udt");

    copy.write_declaration(stream);
    copy.write_definition(stream);
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
    BOOST_TEST(e->template_parameters().size() == 0);
    BOOST_TEST(e->get_name() == "u");

    e->template_parameters().emplace_back(make_unique<template_parameter>("T"));
    e->member_fields().emplace_back(make_pair(access_levels::public_access, make_unique<variable_declaration>(declarator_specifier(make_unique<primitive_type>("int")))));

    BOOST_TEST(e->member_fields().size() == 1);
    BOOST_TEST(e->template_parameters().size() == 1);
    BOOST_TEST(e->get_name() == "u");

    boost::test_tools::output_test_stream stream;

    e->write_declaration(stream);
    e->write_definition(stream);

    auto copy(*e);

    BOOST_TEST(copy.member_fields().size() == 1);
    BOOST_TEST(copy.template_parameters().size() == 1);
    BOOST_TEST(copy.get_name() == "u");

    copy.write_declaration(stream);
    copy.write_definition(stream);

    e->template_parameters().emplace_back(make_unique<template_parameter>("U"));
    e->member_fields().emplace_back(make_pair(access_levels::public_access, make_unique<variable_declaration>(declarator_specifier(make_unique<primitive_type>("int")))));

    copy = *e;

    BOOST_TEST(copy.member_fields().size() == 2);
    BOOST_TEST(copy.template_parameters().size() == 2);
    BOOST_TEST(copy.get_name() == "u");

    copy.write_declaration(stream);
    copy.write_definition(stream);
}

BOOST_AUTO_TEST_CASE(template_parameter_tests)
{
    auto e = make_unique<template_parameter>("T");

    BOOST_TEST(e->get_name() == "T");
    BOOST_TEST(!e->is_parameter_pack());

    e->is_parameter_pack(true);

    auto copy(*e);

    BOOST_TEST(e->get_name() == "T");
    BOOST_TEST(e->is_parameter_pack());

    copy = *e;

    BOOST_TEST(e->get_name() == "T");
    BOOST_TEST(e->is_parameter_pack());

    e->is_parameter_pack(false);

    copy = *e;

    BOOST_TEST(e->get_name() == "T");
    BOOST_TEST(!e->is_parameter_pack());
}

BOOST_AUTO_TEST_CASE(template_template_parameter_tests)
{
    auto e = make_unique<template_template_parameter>("T", 5);

    BOOST_TEST(e->get_name() == "T");
    BOOST_TEST(!e->is_parameter_pack());

    e->is_parameter_pack(true);

    auto copy(*e);

    BOOST_TEST(e->get_name() == "T");
    BOOST_TEST(e->is_parameter_pack());

    copy = *e;

    BOOST_TEST(e->get_name() == "T");
    BOOST_TEST(e->is_parameter_pack());

    e->is_parameter_pack(false);

    copy = *e;

    BOOST_TEST(e->get_name() == "T");
    BOOST_TEST(!e->is_parameter_pack());
}

BOOST_AUTO_TEST_CASE(non_type_template_parameter_tests)
{
    auto e = make_unique<non_type_template_parameter>("int", "T");

    BOOST_TEST(e->get_name() == "int");
    BOOST_TEST(!e->is_parameter_pack());

    e->is_parameter_pack(true);

    auto copy(*e);

    BOOST_TEST(e->get_name() == "int");
    BOOST_TEST(e->is_parameter_pack());

    copy = *e;

    BOOST_TEST(e->get_name() == "int");
    BOOST_TEST(e->is_parameter_pack());

    e->is_parameter_pack(false);

    copy = *e;

    BOOST_TEST(e->get_name() == "int");
    BOOST_TEST(!e->is_parameter_pack());
}

BOOST_AUTO_TEST_SUITE_END()