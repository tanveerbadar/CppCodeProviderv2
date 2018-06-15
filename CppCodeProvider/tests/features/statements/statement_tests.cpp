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

	auto copy1(block);

	const auto& body1 = block.statements();
	auto& body2 = block.statements();
	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body2.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	BOOST_TEST(block.statements().size() == 2);

	auto copy2(block);

	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(block.statements().size() == 2);

	copy2 = block;

	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(block.statements().size() == 2);

	boost::test_tools::output_test_stream output;

	output << block;
}

BOOST_AUTO_TEST_CASE(for_loop_tests)
{
	auto stmt = make_unique<for_loop>();

	auto copy1(*stmt);
	const auto& body1 = stmt->statements();
	auto& body2 = stmt->statements();
	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body2.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	BOOST_TEST(stmt->statements().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(stmt->initializer()).expr() == "");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(stmt->condition()).expr() == "");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(stmt->loop()).expr() == "");

	stmt->initializer(make_unique<primitive_expression>("1"));

	BOOST_TEST(dynamic_cast<const primitive_expression&>(stmt->initializer()).expr() == "1");

	stmt->condition(make_unique<primitive_expression>("2"));

	BOOST_TEST(dynamic_cast<const primitive_expression&>(stmt->condition()).expr() == "2");

	stmt->loop(make_unique<primitive_expression>("3"));

	BOOST_TEST(dynamic_cast<const primitive_expression&>(stmt->loop()).expr() == "3");

	auto other = stmt->clone();

	boost::test_tools::output_test_stream stream;

	stream << *other;
	other->write(stream);

	auto copy2(*stmt);
	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.initializer()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.condition()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.loop()).expr() == "3");

	copy2 = *stmt;
	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.initializer()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.condition()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.loop()).expr() == "3");
}

BOOST_AUTO_TEST_CASE(while_loop_tests)
{
	auto stmt = make_unique<while_loop>(make_unique<primitive_expression>("1"));

	auto copy1(*stmt);
	const auto& body1 = stmt->statements();
	auto& body2 = stmt->statements();
	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body2.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	BOOST_TEST(stmt->statements().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(stmt->condition()).expr() == "1");
	BOOST_TEST(stmt->style() == while_loop_style::while_loop);

	stmt->condition(make_unique<primitive_expression>("2"));

	BOOST_TEST(dynamic_cast<const primitive_expression&>(stmt->condition()).expr() == "2");

	stmt->style(while_loop_style::do_while_loop);

	BOOST_TEST(stmt->style() == while_loop_style::do_while_loop);

	auto other = stmt->clone();

	boost::test_tools::output_test_stream stream;

	stream << *other;
	other->write(stream);

	auto copy2(*stmt);
	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.condition()).expr() == "2");
	BOOST_TEST(copy2.style() == while_loop_style::do_while_loop);

	copy2 = *stmt;
	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.condition()).expr() == "2");
	BOOST_TEST(copy2.style() == while_loop_style::do_while_loop);
}

BOOST_AUTO_TEST_SUITE_END()