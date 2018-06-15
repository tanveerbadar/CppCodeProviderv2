#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "..\..\..\features\statements.h"
#include "..\..\..\features\expressions.h"

BOOST_AUTO_TEST_SUITE(statement_tests)

using namespace std;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::statements;

BOOST_AUTO_TEST_CASE(expression_statement_tests)
{
	auto stmt = make_unique<expression_statement>(make_unique<primitive_expression>("1"));

	BOOST_TEST(dynamic_cast<const primitive_expression&>(stmt->expression()).expr() == "1");

	auto other = stmt->clone();

	boost::test_tools::output_test_stream stream;

	stream << *other;
	other->write(stream);

	expression_statement copy(*stmt);

	copy = *stmt;
}

BOOST_AUTO_TEST_CASE(block_statement_tests)
{
	block_statement block;

	const auto& body1 = block.statements();
	auto& body2 = block.statements();
	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body2.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));

	BOOST_TEST(block.statements().size() == 2);

	block_statement copy(block);

	BOOST_TEST(copy.statements().size() == 2);
	BOOST_TEST(block.statements().size() == 2);

	copy = block;

	BOOST_TEST(copy.statements().size() == 2);
	BOOST_TEST(block.statements().size() == 2);

	boost::test_tools::output_test_stream output;

	output << block;
}

BOOST_AUTO_TEST_SUITE_END()