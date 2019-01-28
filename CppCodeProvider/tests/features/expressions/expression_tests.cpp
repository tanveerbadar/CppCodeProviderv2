#define BOOST_TEST_MODULE cpp_code_provider_tests

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "../../../features/declarations/variable_declaration.h"
#include "../../../features/expressions.h"
#include "../../../features/functions/callable.h"
#include "../../../features/types/common.h"
#include "../../../features/types/template_parameter.h"

BOOST_AUTO_TEST_SUITE(expression_tests)

using namespace std;
using namespace cpp::codeprovider::expressions;

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
	};

	for (auto expr : binary_expressions)
	{
		auto e = make_unique<binary_expression>(expr, make_unique<primitive_expression>("1"), make_unique<primitive_expression>("2"));
		BOOST_TEST(e->type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(e->left()).expr() == "1");
		BOOST_TEST(dynamic_cast<const primitive_expression&>(e->right()).expr() == "2");

		auto other = e->clone();

		boost::test_tools::output_test_stream stream;

		stream << *other;
		other->write(stream);

		binary_expression copy(*e);

		BOOST_TEST(e->type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(e->left()).expr() == "1");
		BOOST_TEST(dynamic_cast<const primitive_expression&>(e->right()).expr() == "2");
		BOOST_TEST(copy.type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(copy.left()).expr() == "1");
		BOOST_TEST(dynamic_cast<const primitive_expression&>(copy.right()).expr() == "2");

		copy = *e;

		BOOST_TEST(e->type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(e->left()).expr() == "1");
		BOOST_TEST(dynamic_cast<const primitive_expression&>(e->right()).expr() == "2");
		BOOST_TEST(copy.type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(copy.left()).expr() == "1");
		BOOST_TEST(dynamic_cast<const primitive_expression&>(copy.right()).expr() == "2");

		const auto& c_ref = copy;
		c_ref.clone();
		c_ref.left();
		c_ref.right();
		c_ref.type();
		c_ref.write(stream);
	}
}

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
	};

	for (auto expr : unary_expressions)
	{
		auto e = make_unique<unary_expression>(expr, make_unique<primitive_expression>("1"));
		BOOST_TEST(e->type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(e->expr()).expr() == "1");

		auto other = e->clone();

		boost::test_tools::output_test_stream stream;

		stream << *other;
		other->write(stream);

		unary_expression copy(*e);

		BOOST_TEST(e->type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(e->expr()).expr() == "1");
		BOOST_TEST(copy.type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(copy.expr()).expr() == "1");

		copy = *e;

		BOOST_TEST(e->type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(e->expr()).expr() == "1");
		BOOST_TEST(copy.type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(copy.expr()).expr() == "1");

		const auto& c_ref = copy;
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
	BOOST_TEST(dynamic_cast<const primitive_expression&>(e->condition()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(e->left()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(e->right()).expr() == "3");

	auto other = e->clone();

	boost::test_tools::output_test_stream stream;

	stream << *other;
	other->write(stream);

	ternary_expression copy(*e);

	BOOST_TEST(dynamic_cast<const primitive_expression&>(e->condition()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(e->left()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(e->right()).expr() == "3");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy.condition()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy.left()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy.right()).expr() == "3");

	copy = *e;

	BOOST_TEST(dynamic_cast<const primitive_expression&>(e->condition()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(e->left()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(e->right()).expr() == "3");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy.condition()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy.left()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy.right()).expr() == "3");

	const auto& c_ref = copy;
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

	f1->captured_variables().emplace_back(capture_mode::by_val, make_unique<unary_expression>(expression_type::variable_ref, make_unique<primitive_expression>("abc")));
	BOOST_TEST(f1->body().statements().size() == 0);
	BOOST_TEST(f1->parameters().size() == 0);
	BOOST_TEST(f1->return_type().get());
	BOOST_TEST(f1->default_capture_mode() == capture_mode::by_val);
	BOOST_TEST(f1->captured_variables().size() == 1);

	f1->body();
	f1->parameters();
	f1->return_type();
	f1->default_capture_mode();
	f1->captured_variables();

	boost::test_tools::output_test_stream stream;

	stream << *f1;

	auto copy1(*f1);

	BOOST_TEST(copy1.body().statements().size() == 0);
	BOOST_TEST(copy1.parameters().size() == 0);
	BOOST_TEST(copy1.return_type().get());
	BOOST_TEST(copy1.default_capture_mode() == capture_mode::by_val);
	BOOST_TEST(copy1.captured_variables().size() == 1);

	copy1.body();
	copy1.parameters();
	copy1.return_type();
	copy1.default_capture_mode();
	copy1.captured_variables();

	stream << copy1;

	copy1 = *f1;

	copy1.body();
	copy1.parameters();
	copy1.return_type();
	copy1.default_capture_mode();
	copy1.captured_variables();

	stream << copy1;

	const auto& c_ref = copy1;
	c_ref.body();
	c_ref.parameters();
	c_ref.return_type();
	c_ref.default_capture_mode();
	c_ref.captured_variables();
}

BOOST_AUTO_TEST_SUITE_END()