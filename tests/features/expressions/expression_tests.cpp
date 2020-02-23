#define BOOST_TEST_MODULE cpp_code_provider_tests

#include "../../../src/features/declarations.h"
#include "../../../src/features/expressions.h"
#include "../../../src/features/functions.h"
#include "../../../src/features/statements.h"
#include "../../../src/features/types.h"
#include "../../../src/formatters/formatter_settings.h"
#include <boost/test/output_test_stream.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(expression_tests)

using namespace std;
using f = cpp::codeprovider::functions::function;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::statements;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::formatting;
using namespace cpp::codeprovider::utils;

BOOST_AUTO_TEST_CASE(binary_expression_tests)
{
	expression_type binary_expressions[] = {
		expression_type::addition,
		expression_type::subtraction,
		expression_type::multiplication,
		expression_type::division,
		expression_type::modulus,
		expression_type::assignment,
		expression_type::subscript,
		expression_type::and_exp,
		expression_type::or_exp,
		expression_type::member_access,
		expression_type::comma,
		expression_type::left_shift,
		expression_type::right_shift,
		expression_type::less,
		expression_type::greater,
		expression_type::less_equal,
		expression_type::greater_equal,
		expression_type::equal,
		expression_type::not_equal,
		expression_type::bit_and,
		expression_type::bit_or,
		expression_type::xor_exp,
		expression_type::add_assign,
		expression_type::subtract_assign,
		expression_type::multiply_assign,
		expression_type::divide_assign,
		expression_type::modulus_assign,
		expression_type::left_shift_assign,
		expression_type::right_shift_assign,
		expression_type::bit_and_assign,
		expression_type::bit_or_assign,
		expression_type::xor_assign,
		expression_type::member_access_by_pointer,
		expression_type::pointer_to_member_access,
		expression_type::pointer_to_member_access_by_pointer,
	};

	for (auto expr : binary_expressions)
	{
		auto e = make_unique<binary_expression>(expr, make_unique<primitive_expression>("1"), make_unique<primitive_expression>("2"));
		BOOST_TEST(e->type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression &>(e->left()).expr() == "1");
		BOOST_TEST(dynamic_cast<const primitive_expression &>(e->right()).expr() == "2");

		auto other = e->clone();

		boost::test_tools::output_test_stream stream;

		stream << *e;

		ostringstream sstr;
		sstr << e->type();

		if (e->type() == expression_type::subscript)
			BOOST_TEST(stream.str() == ("1[2]"));
		else
		{
			BOOST_TEST(stream.str() == ("1 " + sstr.str() + " 2"));
		}

		stream.str("");
		other->write(stream);

		if (e->type() == expression_type::subscript)
			BOOST_TEST(stream.str() == ("1[2]"));
		else
		{
			BOOST_TEST(stream.str() == ("1 " + sstr.str() + " 2"));
		}

		auto copy(*e);

		BOOST_TEST(e->type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression &>(e->left()).expr() == "1");
		BOOST_TEST(dynamic_cast<const primitive_expression &>(e->right()).expr() == "2");
		BOOST_TEST(copy.type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression &>(copy.left()).expr() == "1");
		BOOST_TEST(dynamic_cast<const primitive_expression &>(copy.right()).expr() == "2");

		auto copy2(*e);
		copy2 = *e;

		BOOST_TEST(e->type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression &>(e->left()).expr() == "1");
		BOOST_TEST(dynamic_cast<const primitive_expression &>(e->right()).expr() == "2");
		BOOST_TEST(copy2.type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression &>(copy2.left()).expr() == "1");
		BOOST_TEST(dynamic_cast<const primitive_expression &>(copy2.right()).expr() == "2");

		const auto &c_ref = copy;
		c_ref.clone();
		c_ref.left();
		c_ref.right();
		c_ref.type();
		c_ref.write(stream);
	}
}

namespace
{
void write_expression(ostringstream &os, unique_ptr<unary_expression> &e)
{
	switch (e->type())
	{
	case expression_type::parenthesis:
		os << "(" << e->expr() << ")";
		break;
	case expression_type::size_of:
		os << "sizeof(" << e->expr() << ")";
		break;
	case expression_type::decltype_exp:
		os << "decltype(" << e->expr() << ")";
		break;
	case expression_type::typeid_op:
		os << "typeid(" << e->expr() << ")";
		break;
	case expression_type::postfix_decrement:
		os << e->expr() << "--";
		break;
	case expression_type::postfix_increment:
		os << e->expr() << "++";
		break;
	case expression_type::pack_size_of:
		os << "sizeof...(" << e->expr() << ")";
		break;
	default:
		os << e->type() << e->expr();
		break;
	}
}
} // namespace

BOOST_AUTO_TEST_CASE(unary_expression_tests)
{
	expression_type unary_expressions[] = {
		expression_type::address_of,
		expression_type::complement,
		expression_type::decltype_exp,
		expression_type::delete_exp,
		expression_type::dereference,
		expression_type::method_ref,
		expression_type::postfix_decrement,
		expression_type::postfix_increment,
		expression_type::prefix_decrement,
		expression_type::prefix_increment,
		expression_type::throw_exp,
		expression_type::typeid_op,
		expression_type::parenthesis,
		expression_type::size_of,
		expression_type::pack_size_of,
	};

	for (auto expr : unary_expressions)
	{
		auto e = make_unique<unary_expression>(expr, make_unique<primitive_expression>("1"));
		BOOST_TEST(e->type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression &>(e->expr()).expr() == "1");

		auto other = e->clone();

		boost::test_tools::output_test_stream stream;

		ostringstream sstr;
		stream << *e;
		write_expression(sstr, e);

		BOOST_TEST(stream.str() == sstr.str());

		stream.str("");
		sstr.str("");
		other->write(stream);
		write_expression(sstr, e);

		BOOST_TEST(stream.str() == sstr.str());

		auto copy(*e);

		BOOST_TEST(e->type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression &>(e->expr()).expr() == "1");
		BOOST_TEST(copy.type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression &>(copy.expr()).expr() == "1");

		auto copy2(*e);
		copy2 = *e;

		BOOST_TEST(e->type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression &>(e->expr()).expr() == "1");
		BOOST_TEST(copy2.type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression &>(copy2.expr()).expr() == "1");

		const auto &c_ref = copy;
		c_ref.clone();
		c_ref.expr();
		c_ref.type();
		c_ref.write(stream);
	}
}

BOOST_AUTO_TEST_CASE(ternary_expression_tests)
{
	auto e = make_unique<ternary_expression>(make_unique<primitive_expression>("1"), make_unique<primitive_expression>("2"), make_unique<primitive_expression>("3"));
	BOOST_TEST(e->type() == expression_type::conditional);
	BOOST_TEST(dynamic_cast<const primitive_expression &>(e->condition()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression &>(e->left()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression &>(e->right()).expr() == "3");

	auto other = e->clone();

	boost::test_tools::output_test_stream stream;

	stream << *e;

	BOOST_TEST(stream.str() == "1 ? 2 : 3");

	stream.str("");
	other->write(stream);

	BOOST_TEST(stream.str() == "1 ? 2 : 3");

	ternary_expression copy(*e);

	BOOST_TEST(dynamic_cast<const primitive_expression &>(e->condition()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression &>(e->left()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression &>(e->right()).expr() == "3");
	BOOST_TEST(dynamic_cast<const primitive_expression &>(copy.condition()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression &>(copy.left()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression &>(copy.right()).expr() == "3");

	auto copy2(*e);
	copy2 = *e;

	BOOST_TEST(dynamic_cast<const primitive_expression &>(e->condition()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression &>(e->left()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression &>(e->right()).expr() == "3");
	BOOST_TEST(dynamic_cast<const primitive_expression &>(copy2.condition()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression &>(copy2.left()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression &>(copy2.right()).expr() == "3");

	const auto &c_ref = copy;
	c_ref.clone();
	c_ref.condition();
	c_ref.left();
	c_ref.right();
	c_ref.type();
	c_ref.write(stream);
}

BOOST_AUTO_TEST_CASE(lambda_expression_tests)
{
	auto f1 = make_unique<lambda_expression>();

	BOOST_TEST(f1->body().statements().size() == 0);
	BOOST_TEST(f1->parameters().size() == 0);
	BOOST_TEST(!f1->return_type().operator->());
	BOOST_TEST(f1->default_capture_mode() == capture_mode::none);
	BOOST_TEST(f1->captured_variables().size() == 0);
	BOOST_TEST(!f1->is_mutable());
	BOOST_TEST(!f1->is_no_except());
	BOOST_TEST(!f1->no_except_expr().operator->());

	boost::test_tools::output_test_stream stream;
	auto indent = formatter_settings::settings.get_indent_string();

	stream << *f1;
	BOOST_TEST(stream.str() == "[](){}");

	f1->is_no_except(true);
	f1->captured_variables().emplace_back(capture_mode::by_val, make_unique<unary_expression>(expression_type::variable_ref, make_unique<primitive_expression>("abc")));
	f1->body().statements().emplace_back(make_unique<expression_statement>(make_unique<unary_expression>(expression_type::prefix_increment, make_unique<primitive_expression>("abc"))));
	f1->parameters().emplace_back(make_unique<variable_declaration>(declarator_specifier(make_unique<primitive_type>("int"))));

	BOOST_TEST(f1->body().statements().size() == 1);
	BOOST_TEST(f1->parameters().size() == 1);
	BOOST_TEST(!f1->return_type().operator->());
	BOOST_TEST(f1->default_capture_mode() == capture_mode::none);
	BOOST_TEST(f1->captured_variables().size() == 1);

	f1->body();
	f1->parameters();
	f1->return_type();
	f1->default_capture_mode();
	f1->captured_variables();

	stream.str("");
	stream << *f1;
	BOOST_TEST(stream.str() == "[abc](int ) noexcept\n" + indent + "{\n" + indent + indent + "++abc;\n" + indent + "}\n");

	auto other = f1->clone();
	stream.str("");
	other->write(stream);
	BOOST_TEST(stream.str() == "[abc](int ) noexcept\n" + indent + "{\n" + indent + indent + "++abc;\n" + indent + "}\n");

	f1->default_capture_mode(capture_mode::by_ref);
	stream.str("");
	stream << *f1;
	BOOST_TEST(stream.str() == "[&, abc](int ) noexcept\n" + indent + "{\n" + indent + indent + "++abc;\n" + indent + "}\n");

	auto copy1(*f1);

	BOOST_TEST(copy1.body().statements().size() == 1);
	BOOST_TEST(copy1.parameters().size() == 1);
	BOOST_TEST(!copy1.return_type().operator->());
	BOOST_TEST(copy1.default_capture_mode() == capture_mode::by_ref);
	BOOST_TEST(copy1.captured_variables().size() == 1);
	BOOST_TEST(!copy1.is_mutable());
	BOOST_TEST(copy1.is_no_except());

	copy1.body();
	copy1.parameters();
	copy1.return_type();
	copy1.default_capture_mode();
	copy1.captured_variables();

	stream.str("");
	stream << copy1;
	BOOST_TEST(stream.str() == "[&, abc](int ) noexcept\n" + indent + "{\n" + indent + indent + "++abc;\n" + indent + "}\n");

	auto copy2(*f1);

	f1->no_except_expr(copyable_ptr<expression>(make_unique<primitive_expression>("abc")));
	f1->default_capture_mode(capture_mode::none);
	f1->captured_variables().emplace_back(capture_mode::by_val, make_unique<unary_expression>(expression_type::variable_ref, make_unique<primitive_expression>("def")));
	f1->body().statements().emplace_back(make_unique<expression_statement>(make_unique<unary_expression>(expression_type::prefix_increment, make_unique<primitive_expression>("def"))));
	f1->parameters().emplace_back(make_unique<variable_declaration>(declarator_specifier(make_unique<primitive_type>("int"))));

	stream.str("");
	stream << copy2;
	BOOST_TEST(stream.str() == "[&, abc](int ) noexcept\n" + indent + "{\n" + indent + indent + "++abc;\n" + indent + "}\n");

	copy2 = *f1;
	copy2.is_mutable(true);
	copy2.return_type(make_unique<primitive_type>("int"));

	BOOST_TEST(copy2.body().statements().size() == 2);
	BOOST_TEST(copy2.parameters().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_type &>(*copy2.return_type()).get_name() == "int");
	BOOST_TEST(copy2.default_capture_mode() == capture_mode::none);
	BOOST_TEST(copy2.captured_variables().size() == 2);
	BOOST_TEST(copy2.is_mutable());

	copy2.body();
	copy2.parameters();
	copy2.return_type();
	copy2.default_capture_mode();
	copy2.captured_variables();
	copy2.is_no_except(false);

	stream.str("");
	stream << copy2;
	BOOST_TEST(stream.str() == "[abc, def](int , int ) -> int mutable\n" + indent + "{\n" + indent + indent + "++abc;\n" + indent + indent + "++def;\n" + indent + "}\n");

	const auto &c_ref = copy1;
	c_ref.body();
	c_ref.parameters();
	c_ref.return_type();
	c_ref.default_capture_mode();
	c_ref.captured_variables();
	c_ref.is_mutable();
	c_ref.is_no_except();

	stream.str("");
	stream << c_ref;
	BOOST_TEST(stream.str() == "[&, abc](int ) noexcept\n" + indent + "{\n" + indent + indent + "++abc;\n" + indent + "}\n");
}

namespace
{
void write_fold_expression(ostringstream &sstr, unique_ptr<fold_expression> &e)
{
	switch (e->fold_type())
	{
	case expression_type::binary_fold:
		sstr << e->left() << e->type() << " ... " << e->type() << e->right();
		break;
	case expression_type::right_unary_fold:
		sstr << e->left() << e->type() << " ... ";
		break;
	case expression_type::left_unary_fold:
		sstr << " ... " << e->type() << e->right();
		break;
	}
}
} // namespace

BOOST_AUTO_TEST_CASE(fold_expression_tests)
{
	expression_type fold_expressions[] = {
		expression_type::binary_fold,
		expression_type::left_unary_fold,
		expression_type::right_unary_fold,
	};

	for (auto expr : fold_expressions)
	{
		auto e = make_unique<fold_expression>(expression_type::add_assign, expr, make_unique<primitive_expression>("a"), make_unique<primitive_expression>("b"));
		BOOST_TEST(e->fold_type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression &>(e->left()).expr() == "a");
		BOOST_TEST(dynamic_cast<const primitive_expression &>(e->right()).expr() == "b");

		auto other = e->clone();

		boost::test_tools::output_test_stream stream;

		ostringstream sstr;
		stream << *e;
		write_fold_expression(sstr, e);

		BOOST_TEST(stream.str() == sstr.str());

		stream.str("");
		sstr.str("");
		other->write(stream);
		write_fold_expression(sstr, e);

		BOOST_TEST(stream.str() == sstr.str());

		auto copy(*e);

		BOOST_TEST(e->fold_type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression &>(e->left()).expr() == "a");
		BOOST_TEST(dynamic_cast<const primitive_expression &>(e->right()).expr() == "b");
		BOOST_TEST(copy.fold_type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression &>(copy.left()).expr() == "a");
		BOOST_TEST(dynamic_cast<const primitive_expression &>(copy.right()).expr() == "b");

		auto copy2(*e);
		copy2 = *e;

		BOOST_TEST(e->fold_type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression &>(e->left()).expr() == "a");
		BOOST_TEST(dynamic_cast<const primitive_expression &>(e->right()).expr() == "b");
		BOOST_TEST(copy2.fold_type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression &>(copy2.left()).expr() == "a");
		BOOST_TEST(dynamic_cast<const primitive_expression &>(copy2.right()).expr() == "b");

		const auto &c_ref = copy;
		c_ref.clone();
		c_ref.left();
		c_ref.right();
		c_ref.type();
		c_ref.fold_type();
		c_ref.write(stream);
	}
}

template<typename T> void run_callable_tests(shared_ptr<T> c)
{
	auto r = make_unique<callable_reference_expression>(c);
}

BOOST_AUTO_TEST_CASE(callable_reference_expression_tests)
{
	auto udt = make_shared<user_defined_type>("udt");
	auto f1 = make_shared<f>("f1", udt);
	auto mf = make_shared<member_function>("mf", udt, udt);
	auto le = make_shared<lambda_expression>();

	run_callable_tests(f1);
	run_callable_tests(mf);
	run_callable_tests(le);
}

BOOST_AUTO_TEST_SUITE_END()