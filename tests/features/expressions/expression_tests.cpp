#define BOOST_TEST_MODULE cpp_code_provider_tests

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "../../../src/features/declarations.h"
#include "../../../src/features/expressions.h"
#include "../../../src/features/functions/callable.h"
#include "../../../src/features/statements.h"
#include "../../../src/features/types.h"

BOOST_AUTO_TEST_SUITE(expression_tests)

using namespace std;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::statements;
using namespace cpp::codeprovider::types;

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
		BOOST_TEST(dynamic_cast<const primitive_expression&>(e->left()).expr() == "1");
		BOOST_TEST(dynamic_cast<const primitive_expression&>(e->right()).expr() == "2");

		auto other = e->clone();

		boost::test_tools::output_test_stream stream;

		stream << *e;
		other->write(stream);

		auto copy(*e);

		BOOST_TEST(e->type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(e->left()).expr() == "1");
		BOOST_TEST(dynamic_cast<const primitive_expression&>(e->right()).expr() == "2");
		BOOST_TEST(copy.type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(copy.left()).expr() == "1");
		BOOST_TEST(dynamic_cast<const primitive_expression&>(copy.right()).expr() == "2");

		auto copy2(*e);
		copy2 = *e;

		BOOST_TEST(e->type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(e->left()).expr() == "1");
		BOOST_TEST(dynamic_cast<const primitive_expression&>(e->right()).expr() == "2");
		BOOST_TEST(copy2.type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.left()).expr() == "1");
		BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.right()).expr() == "2");

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
		expression_type::typeid_op,
	};

	for (auto expr : unary_expressions)
	{
		auto e = make_unique<unary_expression>(expr, make_unique<primitive_expression>("1"));
		BOOST_TEST(e->type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(e->expr()).expr() == "1");

		auto other = e->clone();

		boost::test_tools::output_test_stream stream;

		stream << *e;
		other->write(stream);

		auto copy(*e);

		BOOST_TEST(e->type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(e->expr()).expr() == "1");
		BOOST_TEST(copy.type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(copy.expr()).expr() == "1");

		auto copy2(*e);
		copy2 = *e;

		BOOST_TEST(e->type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(e->expr()).expr() == "1");
		BOOST_TEST(copy2.type() == expr);
		BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.expr()).expr() == "1");

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

	stream << *e;
	other->write(stream);

	ternary_expression copy(*e);

	BOOST_TEST(dynamic_cast<const primitive_expression&>(e->condition()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(e->left()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(e->right()).expr() == "3");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy.condition()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy.left()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy.right()).expr() == "3");

	auto copy2(*e);
	copy2 = *e;

	BOOST_TEST(dynamic_cast<const primitive_expression&>(e->condition()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(e->left()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(e->right()).expr() == "3");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.condition()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.left()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.right()).expr() == "3");

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

	boost::test_tools::output_test_stream stream;
	stream << *f1;

	auto other = f1->clone();
	other->write(stream);

	f1->default_capture_mode(capture_mode::by_ref);
	
	auto copy1(*f1);

	BOOST_TEST(copy1.body().statements().size() == 1);
	BOOST_TEST(copy1.parameters().size() == 1);
	BOOST_TEST(!copy1.return_type().operator->());
	BOOST_TEST(copy1.default_capture_mode() == capture_mode::by_ref);
	BOOST_TEST(copy1.captured_variables().size() == 1);

	copy1.body();
	copy1.parameters();
	copy1.return_type();
	copy1.default_capture_mode();
	copy1.captured_variables();

	stream << copy1;

	auto copy2(*f1);

	f1->default_capture_mode(capture_mode::none);
	f1->captured_variables().emplace_back(capture_mode::by_val, make_unique<unary_expression>(expression_type::variable_ref, make_unique<primitive_expression>("def")));
	f1->body().statements().emplace_back(make_unique<expression_statement>(make_unique<unary_expression>(expression_type::prefix_increment, make_unique<primitive_expression>("def"))));
	f1->parameters().emplace_back(make_unique<variable_declaration>(declarator_specifier(make_unique<primitive_type>("int"))));
	
	copy2 = *f1;

	BOOST_TEST(copy2.body().statements().size() == 2);
	BOOST_TEST(copy2.parameters().size() == 2);
	BOOST_TEST(!copy2.return_type().operator->());
	BOOST_TEST(copy2.default_capture_mode() == capture_mode::none);
	BOOST_TEST(copy2.captured_variables().size() == 2);

	copy2.body();
	copy2.parameters();
	copy2.return_type();
	copy2.default_capture_mode();
	copy2.captured_variables();

	stream << copy2;

	const auto& c_ref = copy1;
	c_ref.body();
	c_ref.parameters();
	c_ref.return_type();
	c_ref.default_capture_mode();
	c_ref.captured_variables();
}

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

		stream << *e;
		other->write(stream);

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

BOOST_AUTO_TEST_SUITE_END()