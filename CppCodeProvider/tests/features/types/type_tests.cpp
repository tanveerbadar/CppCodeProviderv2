#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "../../../features/declarations/variable_declaration.h"
#include "../../../features/expressions.h"
#include "../../../features/functions.h"
#include "../../../features/statements/try_statement.h"
#include "../../../features/types.h"

using namespace std;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::types;

BOOST_AUTO_TEST_SUITE(type_tests)

BOOST_AUTO_TEST_CASE(user_defined_type_tests)
{
    auto udt = make_unique<user_defined_type>("udt");

    BOOST_TEST(udt->bases().size() == 0);
    BOOST_TEST(udt->member_fields().size() == 0);
    BOOST_TEST(udt->member_functions().size() == 0);
    BOOST_TEST(udt->template_parameters().size() == 0);
    BOOST_TEST(udt->get_name() == "udt");

    udt->member_functions().emplace_back(string("mf"), make_unique<primitive_type>("int"), *udt);
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

    e->enumerators().emplace_back(make_pair("e1", make_unique<primitive_expression>("5")));

    auto copy(*e);

    BOOST_TEST(copy.enumerators().size() == 1);
    BOOST_TEST(copy.get_name() == "e");
    BOOST_TEST(!copy.is_scoped_enum());

    copy = *e;

    BOOST_TEST(copy.enumerators().size() == 1);
    BOOST_TEST(copy.get_name() == "e");
    BOOST_TEST(!copy.is_scoped_enum());
}

BOOST_AUTO_TEST_SUITE_END()