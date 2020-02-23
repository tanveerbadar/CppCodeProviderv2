#include "../../../src/features/declarations.h"
#include "../../../src/features/expressions.h"
#include "../../../src/features/functions.h"
#include "../../../src/features/statements.h"
#include "../../../src/features/types.h"
#include "../../../src/formatters/formatter_settings.h"
#include <boost/test/output_test_stream.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(function_tests)

using namespace std;

using f = cpp::codeprovider::functions::function;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::statements;
using namespace cpp::codeprovider::types::templates;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::formatting;
using namespace cpp::codeprovider::utils;

BOOST_AUTO_TEST_CASE(function_tests)
{
	f f1("something", make_shared<primitive_type>("int"));

	BOOST_TEST(!f1.is_inline());
	BOOST_TEST(!f1.is_static());
	BOOST_TEST(!f1.is_constexpr());
	BOOST_TEST(!f1.has_try_block());
	BOOST_TEST(!f1.has_trailing_return_type());
	BOOST_TEST(!f1.is_var_arg());
	BOOST_TEST(!f1.is_no_except());
	BOOST_TEST(f1.body().statements().size() == 0);
	BOOST_TEST(f1.parameters().size() == 0);
	BOOST_TEST(f1.template_parameters().size() == 0);
	BOOST_TEST(f1.return_type()->get_name() == "int");
	BOOST_TEST(f1.catch_blocks().size() == 0);
	BOOST_TEST(!f1.no_except_expr().operator->());
	BOOST_TEST(f1.name() == "something");

	boost::test_tools::output_test_stream stream;
	auto indent = formatter_settings::settings.get_indent_string();

	f1.write_declaration(stream);
	BOOST_TEST(stream.str() == "int something();\n");

	stream.str("");
	f1.write_definition(stream);
	BOOST_TEST(stream.str() == "int something()\n" + indent + "{\n" + indent + "}\n");

	catch_clause block;

	f1.is_inline(true);
	f1.is_static(true);
	f1.is_constexpr(true);
	f1.has_try_block(true);
	f1.has_trailing_return_type(true);
	f1.is_var_arg(true);
	f1.is_no_except(true);
	f1.body().statements().emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));
	f1.template_parameters().emplace_back(make_unique<template_parameter>("T"));
	f1.catch_blocks().push_back(block);
	f1.parameters().emplace_back(make_unique<variable_declaration>(declarator_specifier(make_unique<primitive_type>("int"))));
	f1.name("abcd");

	BOOST_TEST(f1.name() == "abcd");

	stream.str("");
	f1.write_declaration(stream);
	BOOST_TEST(stream.str() == "template<typename T> constexpr inline static auto abcd(int , ...) noexcept -> int;\n");

	stream.str("");
	f1.write_definition(stream);
	BOOST_TEST(stream.str() == "template<typename T> constexpr inline static auto abcd(int , ...) noexcept -> int\n" + indent + "try\n" + indent + "{\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "catch(...)\n" + indent + "{\n" + indent + "}\n");

	auto copy1(f1);

	BOOST_TEST(copy1.is_inline());
	BOOST_TEST(copy1.is_static());
	BOOST_TEST(copy1.is_constexpr());
	BOOST_TEST(copy1.has_try_block());
	BOOST_TEST(copy1.has_trailing_return_type());
	BOOST_TEST(copy1.is_var_arg());
	BOOST_TEST(copy1.is_no_except());
	BOOST_TEST(copy1.body().statements().size() == 1);
	BOOST_TEST(copy1.parameters().size() == 1);
	BOOST_TEST(copy1.template_parameters().size() == 1);
	BOOST_TEST(copy1.return_type()->get_name() == "int");
	BOOST_TEST(copy1.catch_blocks().size() == 1);
	BOOST_TEST(copy1.name() == "abcd");

	stream.str("");
	copy1.write_declaration(stream);
	BOOST_TEST(stream.str() == "template<typename T> constexpr inline static auto abcd(int , ...) noexcept -> int;\n");

	stream.str("");
	copy1.write_definition(stream);
	BOOST_TEST(stream.str() == "template<typename T> constexpr inline static auto abcd(int , ...) noexcept -> int\n" + indent + "try\n" + indent + "{\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "catch(...)\n" + indent + "{\n" + indent + "}\n");

	f1.is_inline(false);
	f1.is_static(false);
	f1.is_constexpr(false);
	f1.has_try_block(false);
	f1.has_trailing_return_type(false);
	f1.is_var_arg(false);
	f1.no_except_expr(copyable_ptr<expression>(make_unique<primitive_expression>("abc")));
	f1.body().statements().emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	f1.template_parameters().emplace_back(make_unique<template_parameter>("U"));
	f1.catch_blocks().push_back(block);
	f1.parameters().emplace_back(make_unique<variable_declaration>(declarator_specifier(make_unique<primitive_type>("T"))));
	f1.name("something");

	stream.str("");
	f1.write_declaration(stream);
	BOOST_TEST(stream.str() == "template<typename T, typename U> int something(int , T ) noexcept(abc);\n");

	stream.str("");
	f1.write_definition(stream);
	BOOST_TEST(stream.str() == "template<typename T, typename U> int something(int , T ) noexcept(abc)\n" + indent + "{\n" + indent + indent + "2;\n" + indent + indent + "1;\n" + indent + "}\n");

	copy1 = f1;

	BOOST_TEST(!copy1.is_inline());
	BOOST_TEST(!copy1.is_static());
	BOOST_TEST(!copy1.is_constexpr());
	BOOST_TEST(!copy1.has_try_block());
	BOOST_TEST(copy1.is_no_except());
	BOOST_TEST(dynamic_cast<const primitive_expression &>(*copy1.no_except_expr()).expr() == "abc");
	BOOST_TEST(copy1.body().statements().size() == 2);
	BOOST_TEST(copy1.parameters().size() == 2);
	BOOST_TEST(copy1.template_parameters().size() == 2);
	BOOST_TEST(copy1.return_type()->get_name() == "int");
	BOOST_TEST(copy1.catch_blocks().size() == 2);
	BOOST_TEST(copy1.name() == "something");

	copy1.is_no_except(false);

	stream.str("");
	copy1.write_declaration(stream);
	BOOST_TEST(stream.str() == "template<typename T, typename U> int something(int , T );\n");

	stream.str("");
	copy1.write_definition(stream);
	BOOST_TEST(stream.str() == "template<typename T, typename U> int something(int , T )\n" + indent + "{\n" + indent + indent + "2;\n" + indent + indent + "1;\n" + indent + "}\n");

	const auto &c_ref = copy1;
	c_ref.body();
	c_ref.is_inline();
	c_ref.is_static();
	c_ref.parameters();
	c_ref.return_type();
	c_ref.template_parameters();
	c_ref.is_constexpr();
	c_ref.has_trailing_return_type();
	c_ref.is_var_arg();
	c_ref.is_no_except();
	c_ref.name();

	stream.str("");
	c_ref.write_declaration(stream);
	BOOST_TEST(stream.str() == "template<typename T, typename U> int something(int , T );\n");

	stream.str("");
	c_ref.write_definition(stream);
	BOOST_TEST(stream.str() == "template<typename T, typename U> int something(int , T )\n" + indent + "{\n" + indent + indent + "2;\n" + indent + indent + "1;\n" + indent + "}\n");
}

BOOST_AUTO_TEST_CASE(member_function_tests)
{
	auto udt = make_shared<user_defined_type>("udt");
	member_function f1("something", make_shared<primitive_type>("int"), udt);

	BOOST_TEST(!f1.is_inline());
	BOOST_TEST(!f1.is_static());
	BOOST_TEST(!f1.is_constexpr());
	BOOST_TEST(!f1.is_virtual());
	BOOST_TEST(!f1.is_abstract());
	BOOST_TEST(!f1.is_constant());
	BOOST_TEST(!f1.is_volatile());
	BOOST_TEST(!f1.is_override());
	BOOST_TEST(!f1.is_final());
	BOOST_TEST(!f1.has_try_block());
	BOOST_TEST(!f1.has_trailing_return_type());
	BOOST_TEST(!f1.is_var_arg());
	BOOST_TEST(!f1.is_no_except());
	BOOST_TEST(f1.body().statements().size() == 0);
	BOOST_TEST(f1.parameters().size() == 0);
	BOOST_TEST(f1.template_parameters().size() == 0);
	BOOST_TEST(f1.return_type()->get_name() == "int");
	BOOST_TEST(f1.catch_blocks().size() == 0);
	BOOST_TEST(!f1.no_except_expr().operator->());
	BOOST_TEST(f1.name() == "something");

	boost::test_tools::output_test_stream stream;
	auto indent = formatter_settings::settings.get_indent_string();

	f1.write_declaration(stream);
	BOOST_TEST(stream.str() == "int something();\n");

	stream.str("");
	f1.write_definition(stream);
	BOOST_TEST(stream.str() == "int udt::something()\n" + indent + "{\n" + indent + "}\n");

	catch_clause block;
	f1.is_inline(true);
	f1.is_static(true);
	f1.is_constexpr(true);
	f1.is_virtual(true);
	f1.is_abstract(true);
	f1.is_constant(true);
	f1.is_volatile(true);
	f1.is_override(true);
	f1.is_final(true);
	f1.has_try_block(true);
	f1.has_trailing_return_type(true);
	f1.is_var_arg(true);
	f1.is_no_except(true);
	f1.body().statements().emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));
	f1.template_parameters().emplace_back(make_unique<template_parameter>("T"));
	f1.catch_blocks().push_back(block);
	f1.parameters().emplace_back(make_unique<variable_declaration>(declarator_specifier(make_unique<primitive_type>("int"))));
	f1.name("abcd");

	BOOST_TEST(f1.name() == "abcd");

	stream.str("");
	f1.write_declaration(stream);
	BOOST_TEST(stream.str() == "template<typename T> constexpr inline static virtual auto abcd(int , ...) const volatile override final noexcept = 0 -> int;\n");

	stream.str("");
	f1.write_definition(stream);
	BOOST_TEST(stream.str() == "template<typename T> constexpr inline static virtual auto udt::abcd(int , ...) const volatile override noexcept -> int\n" + indent + "try\n" + indent + "{\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "catch(...)\n" + indent + "{\n" + indent + "}\n");

	auto copy1(f1);

	BOOST_TEST(copy1.is_inline());
	BOOST_TEST(copy1.is_static());
	BOOST_TEST(copy1.is_constexpr());
	BOOST_TEST(copy1.is_virtual());
	BOOST_TEST(copy1.is_abstract());
	BOOST_TEST(copy1.is_constant());
	BOOST_TEST(copy1.is_volatile());
	BOOST_TEST(copy1.is_override());
	BOOST_TEST(copy1.is_final());
	BOOST_TEST(copy1.has_try_block());
	BOOST_TEST(copy1.has_trailing_return_type());
	BOOST_TEST(copy1.is_var_arg());
	BOOST_TEST(copy1.is_no_except());
	BOOST_TEST(copy1.body().statements().size() == 1);
	BOOST_TEST(copy1.parameters().size() == 1);
	BOOST_TEST(copy1.template_parameters().size() == 1);
	BOOST_TEST(copy1.return_type()->get_name() == "int");
	BOOST_TEST(copy1.catch_blocks().size() == 1);
	BOOST_TEST(copy1.name() == "abcd");

	stream.str("");
	copy1.write_declaration(stream);
	BOOST_TEST(stream.str() == "template<typename T> constexpr inline static virtual auto abcd(int , ...) const volatile override final noexcept = 0 -> int;\n");

	stream.str("");
	copy1.write_definition(stream);
	BOOST_TEST(stream.str() == "template<typename T> constexpr inline static virtual auto udt::abcd(int , ...) const volatile override noexcept -> int\n" + indent + "try\n" + indent + "{\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "catch(...)\n" + indent + "{\n" + indent + "}\n");

	f1.is_inline(false);
	f1.is_static(false);
	f1.is_constexpr(false);
	f1.is_virtual(false);
	f1.is_abstract(false);
	f1.is_constant(false);
	f1.is_volatile(false);
	f1.is_override(false);
	f1.is_final(false);
	f1.has_try_block(false);
	f1.has_trailing_return_type(false);
	f1.is_var_arg(false);
	f1.no_except_expr(copyable_ptr<expression>(make_unique<primitive_expression>("abc")));
	f1.body().statements().emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	f1.template_parameters().emplace_back(make_unique<template_parameter>("U"));
	f1.catch_blocks().push_back(block);
	f1.parameters().emplace_back(make_unique<variable_declaration>(declarator_specifier(make_unique<primitive_type>("T"))));
	f1.name("something");

	stream.str("");
	f1.write_declaration(stream);
	BOOST_TEST(stream.str() == "template<typename T, typename U> int something(int , T ) noexcept(abc);\n");

	stream.str("");
	f1.write_definition(stream);
	BOOST_TEST(stream.str() == "template<typename T, typename U> int udt::something(int , T ) noexcept(abc)\n" + indent + "{\n" + indent + indent + "2;\n" + indent + indent + "1;\n" + indent + "}\n");

	copy1 = f1;

	BOOST_TEST(!copy1.is_inline());
	BOOST_TEST(!copy1.is_static());
	BOOST_TEST(!copy1.is_constexpr());
	BOOST_TEST(!copy1.is_virtual());
	BOOST_TEST(!copy1.is_abstract());
	BOOST_TEST(!copy1.is_constant());
	BOOST_TEST(!copy1.is_volatile());
	BOOST_TEST(!copy1.is_override());
	BOOST_TEST(!copy1.is_final());
	BOOST_TEST(!copy1.has_try_block());
	BOOST_TEST(!copy1.has_trailing_return_type());
	BOOST_TEST(!copy1.is_var_arg());
	BOOST_TEST(copy1.is_no_except());
	BOOST_TEST(dynamic_cast<const primitive_expression &>(*copy1.no_except_expr()).expr() == "abc");
	BOOST_TEST(copy1.body().statements().size() == 2);
	BOOST_TEST(copy1.parameters().size() == 2);
	BOOST_TEST(copy1.template_parameters().size() == 2);
	BOOST_TEST(copy1.return_type()->get_name() == "int");
	BOOST_TEST(copy1.catch_blocks().size() == 2);
	BOOST_TEST(copy1.name() == "something");

	copy1.is_no_except(false);

	stream.str("");
	copy1.write_declaration(stream);
	BOOST_TEST(stream.str() == "template<typename T, typename U> int something(int , T );\n");

	stream.str("");
	copy1.write_definition(stream);
	BOOST_TEST(stream.str() == "template<typename T, typename U> int udt::something(int , T )\n" + indent + "{\n" + indent + indent + "2;\n" + indent + indent + "1;\n" + indent + "}\n");

	const auto &c_ref = copy1;
	c_ref.body();
	c_ref.is_inline();
	c_ref.is_static();
	c_ref.is_constexpr();
	c_ref.is_virtual();
	c_ref.is_abstract();
	c_ref.is_constant();
	c_ref.is_volatile();
	c_ref.is_override();
	c_ref.is_final();
	c_ref.has_try_block();
	c_ref.parameters();
	c_ref.return_type();
	c_ref.template_parameters();
	c_ref.catch_blocks();
	c_ref.has_trailing_return_type();
	c_ref.is_var_arg();
	c_ref.is_no_except();
	c_ref.name();

	stream.str("");
	c_ref.write_declaration(stream);
	BOOST_TEST(stream.str() == "template<typename T, typename U> int something(int , T );\n");

	stream.str("");
	c_ref.write_definition(stream);
	BOOST_TEST(stream.str() == "template<typename T, typename U> int udt::something(int , T )\n" + indent + "{\n" + indent + indent + "2;\n" + indent + indent + "1;\n" + indent + "}\n");
}

BOOST_AUTO_TEST_CASE(constructor_tests)
{
	auto udt = make_shared<user_defined_type>("udt");
	constructor f1(udt);

	BOOST_TEST(!f1.is_inline());
	BOOST_TEST(!f1.is_constexpr());
	BOOST_TEST(!f1.has_try_block());
	BOOST_TEST(!f1.is_no_except());
	BOOST_TEST(f1.body().statements().size() == 0);
	BOOST_TEST(f1.parameters().size() == 0);
	BOOST_TEST(f1.template_parameters().size() == 0);
	BOOST_TEST(f1.catch_blocks().size() == 0);
	BOOST_TEST(!f1.no_except_expr().operator->());

	boost::test_tools::output_test_stream stream;
	auto indent = formatter_settings::settings.get_indent_string();

	f1.write_declaration(stream);
	BOOST_TEST(stream.str() == "udt();\n");

	stream.str("");
	f1.write_definition(stream);
	BOOST_TEST(stream.str() == "udt::udt()\n" + indent + "{\n" + indent + "}\n");

	catch_clause block;
	f1.is_inline(true);
	f1.is_constexpr(true);
	f1.has_try_block(true);
	f1.is_no_except(true);
	f1.body().statements().emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));
	f1.template_parameters().emplace_back(make_unique<template_parameter>("T"));
	f1.catch_blocks().push_back(block);
	f1.parameters().emplace_back(make_unique<variable_declaration>(declarator_specifier(make_unique<primitive_type>("int"))));
	f1.initializers().emplace_back("abc", make_unique<primitive_expression>("5"));

	stream.str("");
	f1.write_declaration(stream);
	BOOST_TEST(stream.str() == "template<typename T> constexpr inline udt(int ) noexcept;\n");

	stream.str("");
	f1.write_definition(stream);
	BOOST_TEST(stream.str() == "template<typename T> constexpr inline udt::udt(int ) noexcept\n" + indent + "try\n" + indent + indent + ": abc(5)\n" + indent + "{\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "catch(...)\n" + indent + "{\n" + indent + "}\n");

	auto copy1(f1);

	BOOST_TEST(copy1.is_inline());
	BOOST_TEST(copy1.is_constexpr());
	BOOST_TEST(copy1.has_try_block());
	BOOST_TEST(copy1.is_no_except());
	BOOST_TEST(copy1.body().statements().size() == 1);
	BOOST_TEST(copy1.parameters().size() == 1);
	BOOST_TEST(copy1.template_parameters().size() == 1);
	BOOST_TEST(copy1.catch_blocks().size() == 1);
	BOOST_TEST(copy1.initializers().size() == 1);

	stream.str("");
	copy1.write_declaration(stream);
	BOOST_TEST(stream.str() == "template<typename T> constexpr inline udt(int ) noexcept;\n");

	stream.str("");
	copy1.write_definition(stream);
	BOOST_TEST(stream.str() == "template<typename T> constexpr inline udt::udt(int ) noexcept\n" + indent + "try\n" + indent + indent + ": abc(5)\n" + indent + "{\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "catch(...)\n" + indent + "{\n" + indent + "}\n");

	f1.is_inline(false);
	f1.is_constexpr(false);
	f1.has_try_block(false);
	f1.no_except_expr(copyable_ptr<expression>(make_unique<primitive_expression>("abc")));
	f1.body().statements().emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	f1.template_parameters().emplace_back(make_unique<template_parameter>("U"));
	f1.catch_blocks().push_back(block);
	f1.parameters().emplace_back(make_unique<variable_declaration>(declarator_specifier(make_unique<primitive_type>("T"))));
	f1.initializers().emplace_back("x", make_unique<primitive_expression>("nullptr"));

	stream.str("");
	f1.write_declaration(stream);
	BOOST_TEST(stream.str() == "template<typename T, typename U> udt(int , T ) noexcept(abc);\n");

	stream.str("");
	f1.write_definition(stream);
	BOOST_TEST(stream.str() == "template<typename T, typename U> udt::udt(int , T ) noexcept(abc)\n" + indent + indent + ": abc(5), x(nullptr)\n" + indent + "{\n" + indent + indent + "2;\n" + indent + indent + "1;\n" + indent + "}\n");

	copy1 = f1;

	BOOST_TEST(!copy1.is_inline());
	BOOST_TEST(!copy1.is_constexpr());
	BOOST_TEST(!copy1.has_try_block());
	BOOST_TEST(copy1.is_no_except());
	BOOST_TEST(dynamic_cast<const primitive_expression &>(*copy1.no_except_expr()).expr() == "abc");
	BOOST_TEST(copy1.body().statements().size() == 2);
	BOOST_TEST(copy1.parameters().size() == 2);
	BOOST_TEST(copy1.template_parameters().size() == 2);
	BOOST_TEST(copy1.catch_blocks().size() == 2);
	BOOST_TEST(copy1.initializers().size() == 2);

	copy1.is_no_except(false);

	stream.str("");
	copy1.write_declaration(stream);
	BOOST_TEST(stream.str() == "template<typename T, typename U> udt(int , T );\n");

	stream.str("");
	copy1.write_definition(stream);
	BOOST_TEST(stream.str() == "template<typename T, typename U> udt::udt(int , T )\n" + indent + indent + ": abc(5), x(nullptr)\n" + indent + "{\n" + indent + indent + "2;\n" + indent + indent + "1;\n" + indent + "}\n");

	const auto &c_ref = copy1;
	c_ref.body();
	c_ref.is_inline();
	c_ref.is_constexpr();
	c_ref.has_try_block();
	c_ref.parameters();
	c_ref.template_parameters();
	c_ref.catch_blocks();
	c_ref.is_no_except();

	stream.str("");
	c_ref.write_declaration(stream);
	BOOST_TEST(stream.str() == "template<typename T, typename U> udt(int , T );\n");

	stream.str("");
	c_ref.write_definition(stream);
	BOOST_TEST(stream.str() == "template<typename T, typename U> udt::udt(int , T )\n" + indent + indent + ": abc(5), x(nullptr)\n" + indent + "{\n" + indent + indent + "2;\n" + indent + indent + "1;\n" + indent + "}\n");
}

BOOST_AUTO_TEST_SUITE_END()