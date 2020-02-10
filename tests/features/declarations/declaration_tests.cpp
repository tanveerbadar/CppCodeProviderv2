#include "../../../src/features/declarations.h"
#include "../../../src/features/expressions/primitive_expression.h"
#include "../../../src/features/types.h"
#include "../../../src/formatters/formatter_settings.h"
#include "../../../src/utils/copyable_ptr.h"
#include <boost/test/output_test_stream.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(declaration_tests)

using namespace std;

using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::formatting;
using namespace cpp::codeprovider::utils;

BOOST_AUTO_TEST_CASE(declarator_specifier_tests)
{
    auto t = make_shared<primitive_type>("int");
    declarator_specifier ds(t);

    BOOST_TEST(!ds.is_auto);
    BOOST_TEST(!ds.is_constant);
    BOOST_TEST(!ds.is_extern);
    BOOST_TEST(!ds.is_static);
    BOOST_TEST(!ds.is_volatile);
    BOOST_TEST(ds.get_type()->get_name() == "int");

    boost::test_tools::output_test_stream stream;
    auto indent = formatter_settings::settings.get_indent_string();

    stream << ds;
    BOOST_TEST(stream.str() == "int ");

    ds.is_volatile = ds.is_constant = ds.is_extern = ds.is_static = ds.is_auto = true;

    stream.str("");
    stream << ds;
    BOOST_TEST(stream.str() == "auto extern const volatile static int ");

    auto copy(ds);

    BOOST_TEST(copy.is_auto);
    BOOST_TEST(copy.is_constant);
    BOOST_TEST(copy.is_extern);
    BOOST_TEST(copy.is_static);
    BOOST_TEST(copy.is_volatile);
    BOOST_TEST(copy.get_type()->get_name() == "int");

    auto copy2(ds);

    copy2 = ds;

    BOOST_TEST(copy2.is_auto);
    BOOST_TEST(copy2.is_constant);
    BOOST_TEST(copy2.is_extern);
    BOOST_TEST(copy2.is_static);
    BOOST_TEST(copy2.is_volatile);
    BOOST_TEST(copy2.get_type()->get_name() == "int");
}

BOOST_AUTO_TEST_CASE(declarator_tests)
{
    declarator d;

    boost::test_tools::output_test_stream stream;
    auto indent = formatter_settings::settings.get_indent_string();

    stream << d;
    BOOST_TEST(stream.str() == "");

    auto copy(d);

    stream.str("");
    stream << copy;
    BOOST_TEST(stream.str() == "");

    d.name = "abc";
    copy = d;

    BOOST_TEST(copy.name == "abc");

    stream.str("");
    stream << copy;
    BOOST_TEST(stream.str() == "abc");

    d.is_constant = d.is_lvalue_ref = d.is_volatile = true;
    d.pointer_level = 5;
    d.array_dimensions.push_back(5);
    d.array_dimensions.push_back(3);
    d.initializer_exp = copyable_ptr<expression>(make_unique<primitive_expression>("nullptr"));

    stream.str("");
    stream << d;
    BOOST_TEST(stream.str() == "& const volatile *****abc[5][3] = nullptr");

    copy = d;

    BOOST_TEST(copy.is_constant);
    BOOST_TEST(copy.is_lvalue_ref);
    BOOST_TEST(copy.is_volatile);
    BOOST_TEST(copy.pointer_level == 5);
    BOOST_TEST(copy.array_dimensions.size() == 2);
    BOOST_TEST(copy.array_dimensions.at(0) == 5);
    BOOST_TEST(copy.array_dimensions.at(1) == 3);
    BOOST_TEST(dynamic_cast<const primitive_expression &>(*d.initializer_exp).expr() == "nullptr");

    copy.is_rvalue_ref = true;
    copy.is_lvalue_ref = false;

    stream.str("");
    stream << copy;
    BOOST_TEST(stream.str() == "&& const volatile *****abc[5][3] = nullptr");
}

BOOST_AUTO_TEST_CASE(variable_declaration_tests)
{
    auto t = make_shared<primitive_type>("double");
    declarator_specifier ds(t);
    ds.is_volatile = true;
    auto var = make_unique<variable_declaration>(ds);

    BOOST_TEST(var->specifier().get_type()->get_name() == "double");
    BOOST_TEST(var->var_declarator().name == "");

    var->var_declarator().name = "x";

    boost::test_tools::output_test_stream stream;
    auto indent = formatter_settings::settings.get_indent_string();

    var->write_declaration(stream);
    BOOST_TEST(stream.str() == "volatile double x");

    auto copy(*var);

    BOOST_TEST(copy.specifier().get_type()->get_name() == "double");
    BOOST_TEST(copy.var_declarator().name == "x");

    stream.str("");
    copy.write_declaration(stream);
    BOOST_TEST(stream.str() == "volatile double x");

    var->var_declarator().is_rvalue_ref = true;

    copy = *var;

    BOOST_TEST(copy.specifier().get_type()->get_name() == "double");
    BOOST_TEST(copy.var_declarator().name == "x");
    BOOST_TEST(copy.var_declarator().is_rvalue_ref);

    stream.str("");
    copy.write_declaration(stream);
    BOOST_TEST(stream.str() == "volatile double && x");

    const auto& c_ref = copy;
    c_ref.specifier();
    c_ref.clone();
    c_ref.var_declarator();

    stream.str("");
    c_ref.write_declaration(stream);
    BOOST_TEST(stream.str() == "volatile double && x");

    stream.str("");
    c_ref.write_definition(stream);
    BOOST_TEST(stream.str() == "volatile double && x");
}

BOOST_AUTO_TEST_CASE(variable_declaration_list_tests)
{
    auto t = make_shared<primitive_type>("double");
    declarator_specifier ds(t);
    ds.is_volatile = true;
    auto var = make_unique<variable_declaration_list>(ds);

    BOOST_TEST(var->specifier().get_type()->get_name() == "double");
    declarator i, j, k;
	i.name = "i";
	i.initializer_exp = copyable_ptr<expression>(make_unique<primitive_expression>("5"));
	j.name = "j";
	j.initializer_exp = copyable_ptr<expression>(make_unique<primitive_expression>("i"));
	k.name = "k";
	k.initializer_exp = copyable_ptr<expression>(make_unique<primitive_expression>("0"));
    var->declarations().push_back(i);
    var->declarations().push_back(j);
    var->declarations().push_back(k);

    boost::test_tools::output_test_stream stream;
    auto indent = formatter_settings::settings.get_indent_string();

    var->write_declaration(stream);
    BOOST_TEST(stream.str() == "volatile double i = 5, j = i, k = 0");

    auto copy(*var);

    BOOST_TEST(copy.specifier().get_type()->get_name() == "double");
    BOOST_TEST(copy.declarations().size() == 3);

    stream.str("");
    copy.write_declaration(stream);
    BOOST_TEST(stream.str() == "volatile double i = 5, j = i, k = 0");

    var->declarations().at(0).is_rvalue_ref = true;

    copy = *var;

    BOOST_TEST(copy.specifier().get_type()->get_name() == "double");
    BOOST_TEST(copy.declarations().size() == 3);
    BOOST_TEST(copy.declarations().at(0).is_rvalue_ref);

    stream.str("");
    copy.write_declaration(stream);
    BOOST_TEST(stream.str() == "volatile double && i = 5, j = i, k = 0");

    const auto& c_ref = copy;
    c_ref.specifier();
    c_ref.clone();
    c_ref.declarations();

    stream.str("");
    c_ref.write_declaration(stream);
    BOOST_TEST(stream.str() == "volatile double && i = 5, j = i, k = 0");

    stream.str("");
    c_ref.write_definition(stream);
    BOOST_TEST(stream.str() == "volatile double && i = 5, j = i, k = 0");
}

BOOST_AUTO_TEST_SUITE_END()