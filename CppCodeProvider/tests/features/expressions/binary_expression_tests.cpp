#define BOOST_TEST_MODULE binary_expression_tests
#include <boost/test/included/unit_test.hpp>
#include "..\..\..\features\expressions.h"

using namespace std;
using namespace cpp::codeprovider::primitives;

BOOST_AUTO_TEST_CASE(construction_test)
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
	}
}