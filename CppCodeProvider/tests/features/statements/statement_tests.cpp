#define BOOST_TEST_MODULE cpp_code_provider_tests

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "..\..\..\features\statements.h"
#include "..\..\..\features\expressions.h"
#include "..\..\..\features\declarations\variable_declaration.h"

BOOST_AUTO_TEST_SUITE(statement_tests)

using namespace std;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::statements;
using namespace cpp::codeprovider::declarations;

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

	const auto& c_ref = copy;
	c_ref.clone();
	c_ref.expression();
	c_ref.write(stream);
}

BOOST_AUTO_TEST_CASE(block_statement_tests)
{
	block_statement block;

	BOOST_TEST(block.statements().size() == 0);

	boost::test_tools::output_test_stream output;

	output << block;

	auto copy1(block);

	const auto& body1 = block.statements();
	auto& body2 = block.statements();
	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body2.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	BOOST_TEST(block.statements().size() == 2);

	auto copy2(block);

	output << copy2;

	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(block.statements().size() == 2);

	copy2 = block;

	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(block.statements().size() == 2);

	const auto& c_ref = copy1;
	c_ref.statements();
	output << c_ref;
}

BOOST_AUTO_TEST_CASE(for_loop_tests)
{
	auto stmt = make_unique<for_loop>();

	BOOST_TEST(stmt->statements().size() == 0);

	boost::test_tools::output_test_stream stream;

	stream << *stmt;

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

	stream << *other;
	other->write(stream);

	auto copy2(*stmt);
	BOOST_TEST(stmt->statements().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(stmt->initializer()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(stmt->condition()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(stmt->loop()).expr() == "3");
	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.initializer()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.condition()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.loop()).expr() == "3");

	copy2 = *stmt;
	BOOST_TEST(stmt->statements().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(stmt->initializer()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(stmt->condition()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(stmt->loop()).expr() == "3");
	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.initializer()).expr() == "1");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.condition()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.loop()).expr() == "3");

	const auto& c_ref = copy1;
	c_ref.clone();
	c_ref.condition();
	c_ref.initializer();
	c_ref.loop();
	c_ref.statements();
	c_ref.write(stream);
}

BOOST_AUTO_TEST_CASE(while_loop_tests)
{
	auto stmt = make_unique<while_loop>(make_unique<primitive_expression>("1"));

	BOOST_TEST(stmt->statements().size() == 0);

	boost::test_tools::output_test_stream stream;

	stream << *stmt;

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

	stream << *other;
	other->write(stream);

	auto copy2(*stmt);
	BOOST_TEST(stmt->statements().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(stmt->condition()).expr() == "2");
	BOOST_TEST(stmt->style() == while_loop_style::do_while_loop);
	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.condition()).expr() == "2");
	BOOST_TEST(copy2.style() == while_loop_style::do_while_loop);

	copy2 = *stmt;
	BOOST_TEST(stmt->statements().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(stmt->condition()).expr() == "2");
	BOOST_TEST(stmt->style() == while_loop_style::do_while_loop);
	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.condition()).expr() == "2");
	BOOST_TEST(copy2.style() == while_loop_style::do_while_loop);

	const auto& c_ref = copy1;
	c_ref.clone();
	c_ref.condition();
	c_ref.statements();
	c_ref.style();
	c_ref.write(stream);
}

BOOST_AUTO_TEST_CASE(if_statement_tests)
{
	auto stmt = make_unique<if_statement>(make_unique<binary_expression>(expression_type::not_equal, make_unique<primitive_expression>("1"), make_unique<primitive_expression>("2")));

	BOOST_TEST(stmt->if_block().size() == 0);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(dynamic_cast<const binary_expression&>(stmt->condition()).right()).expr() == "2");
	BOOST_TEST(stmt->else_block().size() == 0);

	auto& condition = stmt->condition();
	const auto& condition2 = stmt->condition();
	auto copy1(*stmt);
	const auto& body1 = stmt->if_block();
	auto& body2 = stmt->if_block();
	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body2.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	const auto& body3 = stmt->else_block();
	auto& body4 = stmt->else_block();
	body4.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("3")));
	body4.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("4")));

	stmt->condition(make_unique<binary_expression>(expression_type::not_equal, make_unique<primitive_expression>("1"), make_unique<primitive_expression>("2")));

	BOOST_TEST(dynamic_cast<const primitive_expression&>(dynamic_cast<const binary_expression&>(stmt->condition()).right()).expr() == "2");
	BOOST_TEST(stmt->if_block().size() == 2);
	BOOST_TEST(stmt->else_block().size() == 2);

	auto other = stmt->clone();

	boost::test_tools::output_test_stream stream;

	stream << *other;
	other->write(stream);

	auto copy2(*stmt);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(dynamic_cast<const binary_expression&>(stmt->condition()).right()).expr() == "2");
	BOOST_TEST(stmt->if_block().size() == 2);
	BOOST_TEST(stmt->else_block().size() == 2);
	BOOST_TEST(copy2.if_block().size() == 2);
	BOOST_TEST(copy2.else_block().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(dynamic_cast<const binary_expression&>(copy2.condition()).right()).expr() == "2");

	copy2 = *stmt;
	BOOST_TEST(dynamic_cast<const primitive_expression&>(dynamic_cast<const binary_expression&>(stmt->condition()).right()).expr() == "2");
	BOOST_TEST(stmt->if_block().size() == 2);
	BOOST_TEST(stmt->else_block().size() == 2);
	BOOST_TEST(copy2.if_block().size() == 2);
	BOOST_TEST(copy2.else_block().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(dynamic_cast<const binary_expression&>(copy2.condition()).right()).expr() == "2");

	const auto& c_ref = copy1;
	c_ref.clone();
	c_ref.condition();
	c_ref.else_block();
	c_ref.if_block();
	c_ref.write(stream);
}

BOOST_AUTO_TEST_CASE(catch_block_tests)
{
	catch_clause block;
	BOOST_TEST(block.statements().size() == 0);
	auto& var = block.variable();

	boost::test_tools::output_test_stream output;
	output << block;

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

	output << copy2;

	const auto& c_ref = copy1;
	c_ref.statements();
	c_ref.variable();

	output << c_ref;
}

BOOST_AUTO_TEST_CASE(try_statement_tests)
{
	auto stmt = make_unique<try_statement>();
	BOOST_TEST(stmt->statements().size() == 0);
	BOOST_TEST(stmt->catch_clauses().size() == 0);

	boost::test_tools::output_test_stream output;
	output << *stmt;

	auto copy1(*stmt);

	BOOST_TEST(copy1.statements().size() == 0);
	BOOST_TEST(copy1.catch_clauses().size() == 0);

	const auto& body1 = stmt->statements();
	auto& body2 = stmt->statements();

	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body2.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	BOOST_TEST(stmt->statements().size() == 2);

	catch_clause block;
	auto& body3 = block.statements();
	body3.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body3.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	stmt->catch_clauses().push_back(block);

	auto copy2(*stmt);

	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(stmt->statements().size() == 2);
	BOOST_TEST(copy2.catch_clauses().size() == 1);
	BOOST_TEST(stmt->catch_clauses().size() == 1);

	copy2 = *stmt;

	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(stmt->statements().size() == 2);
	BOOST_TEST(copy2.catch_clauses().size() == 1);
	BOOST_TEST(stmt->catch_clauses().size() == 1);

	output << copy2;

	const auto& c_ref = copy1;
	c_ref.catch_clauses();
	c_ref.clone();
	c_ref.statements();
	c_ref.write(output);
}

BOOST_AUTO_TEST_CASE(case_statement_tests)
{
	case_statement block(false);
	BOOST_TEST(block.statements().size() == 0);
	auto& var = block.label();

	boost::test_tools::output_test_stream output;
	output << block;

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

	output << copy2;

	case_statement block2(make_unique<primitive_expression>("5"));
	auto& var2 = block2.label();
	const auto& var3 = block2.label();
	BOOST_TEST(dynamic_cast<const primitive_expression&>(var2).expr() == "5");

	const auto& c_ref = copy1;
	c_ref.has_label();
	c_ref.label();
	c_ref.statements();
}

BOOST_AUTO_TEST_CASE(switch_statement_tests)
{
	auto stmt = make_unique<switch_statement>(make_unique<primitive_expression>("5"));
	BOOST_TEST(stmt->cases().size() == 0);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(stmt->condition()).expr() == "5");

	boost::test_tools::output_test_stream output;
	output << *stmt;

	auto copy1(*stmt);

	BOOST_TEST(copy1.cases().size() == 0);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy1.condition()).expr() == "5");

	case_statement block(true);
	auto& body3 = block.statements();
	body3.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body3.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	stmt->cases().push_back(block);

	auto copy2(*stmt);

	BOOST_TEST(copy2.cases().size() == 1);
	BOOST_TEST(stmt->cases().size() == 1);

	copy2 = *stmt;

	BOOST_TEST(copy2.cases().size() == 1);
	BOOST_TEST(stmt->cases().size() == 1);
	BOOST_TEST(dynamic_cast<const primitive_expression&>(copy2.condition()).expr() == "5");

	output << copy2;

	const auto& c_ref = copy1;
	c_ref.cases();
	c_ref.condition();
	c_ref.clone();
	c_ref.write(output);
}

BOOST_AUTO_TEST_CASE(jump_statement_tests)
{
	jump_statement break_stmt(jump_type::break_jump);
	jump_statement continue_stmt(jump_type::continue_jump);
	jump_statement goto_stmt(jump_type::goto_jump);
	jump_statement return_stmt1(jump_type::return_jump);
	jump_statement return_stmt2(jump_type::return_jump);

	BOOST_TEST(break_stmt.type() == jump_type::break_jump);
	BOOST_TEST(continue_stmt.type() == jump_type::continue_jump);
	BOOST_TEST(goto_stmt.type() == jump_type::goto_jump);
	BOOST_TEST(return_stmt1.type() == jump_type::return_jump);

	boost::test_tools::output_test_stream output;
	output << break_stmt;

	auto copy1(break_stmt);

	BOOST_TEST(copy1.type() == jump_type::break_jump);
	BOOST_TEST(break_stmt.type() == jump_type::break_jump);

	output << copy1;

	copy1 = break_stmt;

	BOOST_TEST(copy1.type() == jump_type::break_jump);
	BOOST_TEST(break_stmt.type() == jump_type::break_jump);
}


BOOST_AUTO_TEST_SUITE_END()