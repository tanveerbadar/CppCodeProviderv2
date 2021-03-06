#include "../../../src/features/declarations/variable_declaration.h"
#include "../../../src/features/declarations/variable_declaration_list.h"
#include "../../../src/features/expressions.h"
#include "../../../src/features/statements.h"
#include "../../../src/features/types.h"
#include "../../../src/formatters/formatter_settings.h"
#include "../../../src/utils/copyable_ptr.h"
#include <boost/test/output_test_stream.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(statement_tests)

using namespace std;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::statements;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::formatting;
using namespace cpp::codeprovider::utils;

BOOST_AUTO_TEST_CASE(expression_statement_tests)
{
	auto stmt = make_unique<expression_statement>(make_unique<primitive_expression>("1"));

	BOOST_TEST(dynamic_cast<const primitive_expression &>(stmt->expression()).expr() == "1");

	auto indent = formatter_settings::settings.get_indent_string();
	boost::test_tools::output_test_stream stream;

	stmt->expression();

	stmt->write(stream);
	BOOST_TEST(stream.str() == indent + "1;\n");

	auto other = stmt->clone();

	stream.str("");
	stream << *other;

	BOOST_TEST(stream.str() == indent + "1;\n");

	stream.str("");
	other->write(stream);

	BOOST_TEST(stream.str() == indent + "1;\n");

	auto copy(*stmt);

	BOOST_TEST(dynamic_cast<const primitive_expression &>(stmt->expression()).expr() == "1");

	auto copy2(*stmt);

	copy2 = *stmt;

	copy.clone();
	copy.expression();

	stream.str("");
	copy.write(stream);

	BOOST_TEST(stream.str() == indent + "1;\n");

	const auto &c_ref = copy;
	c_ref.clone();
	c_ref.expression();
	c_ref.write(stream);
}

BOOST_AUTO_TEST_CASE(block_statement_tests)
{
	block_statement block;

	BOOST_TEST(block.statements().size() == 0);

	auto indent = formatter_settings::settings.get_indent_string();
	boost::test_tools::output_test_stream output;

	output << block;

	BOOST_TEST(output.str() == indent + "{\n" + indent + "}\n");

	auto copy1(block);

	auto &body2 = block.statements();

	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body2.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	BOOST_TEST(block.statements().size() == 2);

	auto copy2(block);

	output.str("");
	output << copy2;

	BOOST_TEST(output.str() == indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(block.statements().size() == 2);

	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));

	copy2 = block;

	BOOST_TEST(copy2.statements().size() == 3);
	BOOST_TEST(block.statements().size() == 3);

	const auto &c_ref = copy1;
	c_ref.statements();

	output.str("");
	output << c_ref;

	BOOST_TEST(output.str() == indent + "{\n" + indent + "}\n");
}

BOOST_AUTO_TEST_CASE(for_loop_tests)
{
	auto stmt = make_unique<for_loop>();

	BOOST_TEST(stmt->statements().size() == 0);

	auto indent = formatter_settings::settings.get_indent_string();
	boost::test_tools::output_test_stream stream;

	stream << *stmt;

	BOOST_TEST(stream.str() == indent + "for( ;; )\n" + indent + "{\n" + indent + "}\n");

	auto copy1(*stmt);
	auto &body2 = stmt->statements();

	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body2.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	auto list = make_unique<variable_declaration_list>(declarator_specifier(make_unique<primitive_type>("int")));
	declarator i, j, k;
	i.name = "i";
	i.initializer_exp = copyable_ptr<expression>(make_unique<primitive_expression>("5"));
	j.name = "j";
	j.initializer_exp = copyable_ptr<expression>(make_unique<primitive_expression>("i"));
	k.name = "k";
	k.initializer_exp = copyable_ptr<expression>(make_unique<primitive_expression>("0"));
	list->declarations().push_back(i);
	list->declarations().push_back(j);
	list->declarations().push_back(k);

	BOOST_TEST(stmt->statements().size() == 2);
	BOOST_TEST(dynamic_cast<const variable_declaration_list &>(stmt->initializer()).declarations().empty());
	BOOST_TEST(dynamic_cast<const primitive_expression &>(stmt->condition()).expr() == "");
	BOOST_TEST(dynamic_cast<const primitive_expression &>(stmt->loop()).expr() == "");

	stmt->initializer(move(list));

	BOOST_TEST(dynamic_cast<const variable_declaration_list &>(stmt->initializer()).declarations().size() == 3);

	stmt->condition(make_unique<primitive_expression>("2"));

	BOOST_TEST(dynamic_cast<const primitive_expression &>(stmt->condition()).expr() == "2");

	stmt->loop(make_unique<primitive_expression>("3"));

	BOOST_TEST(dynamic_cast<const primitive_expression &>(stmt->loop()).expr() == "3");

	auto other = stmt->clone();

	stream.str("");
	stream << *other;

	BOOST_TEST(stream.str() == indent + "for( int i = 5, j = i, k = 0; 2; 3 )\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	stream.str("");
	other->write(stream);

	BOOST_TEST(stream.str() == indent + "for( int i = 5, j = i, k = 0; 2; 3 )\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	auto copy2(*stmt);
	BOOST_TEST(stmt->statements().size() == 2);
	BOOST_TEST(dynamic_cast<const variable_declaration_list &>(stmt->initializer()).declarations().size() == 3);
	BOOST_TEST(dynamic_cast<const primitive_expression &>(stmt->condition()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression &>(stmt->loop()).expr() == "3");
	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(dynamic_cast<const variable_declaration_list &>(stmt->initializer()).declarations().size() == 3);
	BOOST_TEST(dynamic_cast<const primitive_expression &>(copy2.condition()).expr() == "2");
	BOOST_TEST(dynamic_cast<const primitive_expression &>(copy2.loop()).expr() == "3");

	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	stmt->condition(make_unique<primitive_expression>("5"));
	stmt->loop(make_unique<primitive_expression>("6"));

	stream.str("");
	copy2.write(stream);

	BOOST_TEST(stream.str() == indent + "for( int i = 5, j = i, k = 0; 2; 3 )\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	stream.str("");
	stmt->write(stream);

	BOOST_TEST(stream.str() == indent + "for( int i = 5, j = i, k = 0; 5; 6 )\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + indent + "1;\n" + indent + "}\n");

	copy2 = *stmt;
	BOOST_TEST(stmt->statements().size() == 3);
	BOOST_TEST(dynamic_cast<const variable_declaration_list &>(stmt->initializer()).declarations().size() == 3);
	BOOST_TEST(dynamic_cast<const primitive_expression &>(stmt->condition()).expr() == "5");
	BOOST_TEST(dynamic_cast<const primitive_expression &>(stmt->loop()).expr() == "6");
	BOOST_TEST(copy2.statements().size() == 3);
	BOOST_TEST(dynamic_cast<const variable_declaration_list &>(stmt->initializer()).declarations().size() == 3);
	BOOST_TEST(dynamic_cast<const primitive_expression &>(copy2.condition()).expr() == "5");
	BOOST_TEST(dynamic_cast<const primitive_expression &>(copy2.loop()).expr() == "6");

	const auto &c_ref = copy1;
	c_ref.clone();
	c_ref.condition();
	c_ref.initializer();
	c_ref.loop();
	c_ref.statements();

	stream.str("");
	c_ref.write(stream);

	BOOST_TEST(stream.str() == indent + "for( ;; )\n" + indent + "{\n" + indent + "}\n");
}

BOOST_AUTO_TEST_CASE(while_loop_tests)
{
	auto stmt = make_unique<while_loop>(make_unique<primitive_expression>("1"));

	BOOST_TEST(stmt->statements().size() == 0);

	auto indent = formatter_settings::settings.get_indent_string();
	boost::test_tools::output_test_stream stream;

	stream << *stmt;

	BOOST_TEST(stream.str() == indent + "while( 1 )\n" + indent + "{\n" + indent + "}\n");

	auto copy1(*stmt);
	auto &body2 = stmt->statements();

	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body2.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	BOOST_TEST(stmt->statements().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression &>(stmt->condition()).expr() == "1");
	BOOST_TEST(stmt->style() == while_loop_style::while_loop);

	stream.str("");
	stream << *stmt;

	BOOST_TEST(stream.str() == indent + "while( 1 )\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	stmt->condition(make_unique<primitive_expression>("2"));

	BOOST_TEST(dynamic_cast<const primitive_expression &>(stmt->condition()).expr() == "2");

	stmt->style(while_loop_style::do_while_loop);

	BOOST_TEST(stmt->style() == while_loop_style::do_while_loop);

	auto other = stmt->clone();

	stream.str("");
	stream << *other;

	BOOST_TEST(stream.str() == indent + "do\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "while( 2 );\n");

	stream.str("");
	other->write(stream);

	BOOST_TEST(stream.str() == indent + "do\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "while( 2 );\n");

	auto copy2(*stmt);
	BOOST_TEST(stmt->statements().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression &>(stmt->condition()).expr() == "2");
	BOOST_TEST(stmt->style() == while_loop_style::do_while_loop);
	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression &>(copy2.condition()).expr() == "2");
	BOOST_TEST(copy2.style() == while_loop_style::do_while_loop);

	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	stmt->condition(make_unique<primitive_expression>("3"));
	copy2 = *stmt;

	BOOST_TEST(stmt->statements().size() == 3);
	BOOST_TEST(dynamic_cast<const primitive_expression &>(stmt->condition()).expr() == "3");
	BOOST_TEST(stmt->style() == while_loop_style::do_while_loop);
	BOOST_TEST(copy2.statements().size() == 3);
	BOOST_TEST(dynamic_cast<const primitive_expression &>(copy2.condition()).expr() == "3");
	BOOST_TEST(copy2.style() == while_loop_style::do_while_loop);

	const auto &c_ref = copy1;
	c_ref.clone();
	c_ref.condition();
	c_ref.statements();
	c_ref.style();

	stream.str("");
	c_ref.write(stream);

	BOOST_TEST(stream.str() == indent + "while( 1 )\n" + indent + "{\n" + indent + "}\n");
}

BOOST_AUTO_TEST_CASE(if_statement_tests)
{
	auto stmt = make_unique<if_statement>(make_unique<binary_expression>(expression_type::not_equal, make_unique<primitive_expression>("1"), make_unique<primitive_expression>("2")));

	BOOST_TEST(stmt->if_block().size() == 0);
	BOOST_TEST(dynamic_cast<const primitive_expression &>(dynamic_cast<const binary_expression &>(stmt->condition()).right()).expr() == "2");
	BOOST_TEST(stmt->else_block().size() == 0);
	BOOST_TEST(!stmt->is_constexpr());

	boost::test_tools::output_test_stream stream;
	auto indent = formatter_settings::settings.get_indent_string();

	stream << *stmt;

	BOOST_TEST(stream.str() == indent + "if(1 != 2)\n" + indent + "{\n" + indent + "}\n");

	auto &condition = stmt->condition();
	auto &body2 = stmt->if_block();

	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body2.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	auto &body4 = stmt->else_block();

	body4.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("3")));
	body4.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("4")));

	stmt->condition(make_unique<binary_expression>(expression_type::not_equal, make_unique<primitive_expression>("1"), make_unique<primitive_expression>("2")));

	BOOST_TEST(dynamic_cast<const primitive_expression &>(dynamic_cast<const binary_expression &>(stmt->condition()).right()).expr() == "2");
	BOOST_TEST(stmt->if_block().size() == 2);
	BOOST_TEST(stmt->else_block().size() == 2);

	stream.str("");
	stream << *stmt;

	BOOST_TEST(stream.str() == indent + "if(1 != 2)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "else\n" + indent + "{\n" + indent + indent + "3;\n" + indent + indent + "4;\n" + indent + "}\n");

	auto other = stmt->clone();

	stream.str("");
	stream << *other;

	BOOST_TEST(stream.str() == indent + "if(1 != 2)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "else\n" + indent + "{\n" + indent + indent + "3;\n" + indent + indent + "4;\n" + indent + "}\n");	other->write(stream);

	stmt->is_constexpr(true);

	auto copy2(*stmt);
	BOOST_TEST(dynamic_cast<const primitive_expression &>(dynamic_cast<const binary_expression &>(stmt->condition()).right()).expr() == "2");
	BOOST_TEST(stmt->if_block().size() == 2);
	BOOST_TEST(stmt->else_block().size() == 2);
	BOOST_TEST(copy2.if_block().size() == 2);
	BOOST_TEST(copy2.else_block().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression &>(dynamic_cast<const binary_expression &>(copy2.condition()).right()).expr() == "2");
	BOOST_TEST(copy2.is_constexpr());

	stream.str("");
	stream << copy2;

	BOOST_TEST(stream.str() == indent + "if constexpr (1 != 2)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "else\n" + indent + "{\n" + indent + indent + "3;\n" + indent + indent + "4;\n" + indent + "}\n");	other->write(stream);

	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("3")));
	body4.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("3")));
	stmt->condition(make_unique<binary_expression>(expression_type::not_equal, make_unique<primitive_expression>("1"), make_unique<primitive_expression>("3")));

	stream.str("");
	stream << copy2;

	BOOST_TEST(stream.str() == indent + "if constexpr (1 != 2)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "else\n" + indent + "{\n" + indent + indent + "3;\n" + indent + indent + "4;\n" + indent + "}\n");	other->write(stream);
	
	stream.str("");
	other->write(stream);

	BOOST_TEST(stream.str() == indent + "if(1 != 2)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "else\n" + indent + "{\n" + indent + indent + "3;\n" + indent + indent + "4;\n" + indent + "}\n");	other->write(stream);

	stmt->is_constexpr(false);
	copy2 = *stmt;
	BOOST_TEST(dynamic_cast<const primitive_expression &>(dynamic_cast<const binary_expression &>(stmt->condition()).right()).expr() == "3");
	BOOST_TEST(stmt->if_block().size() == 3);
	BOOST_TEST(stmt->else_block().size() == 3);
	BOOST_TEST(copy2.if_block().size() == 3);
	BOOST_TEST(copy2.else_block().size() == 3);
	BOOST_TEST(dynamic_cast<const primitive_expression &>(dynamic_cast<const binary_expression &>(copy2.condition()).right()).expr() == "3");
	BOOST_TEST(!copy2.is_constexpr());

	const auto &c_ref = copy2;
	c_ref.clone();
	c_ref.condition();
	c_ref.else_block();
	c_ref.if_block();
	c_ref.write(stream);
	c_ref.is_constexpr();

	stream.str("");
	stream << c_ref;

	BOOST_TEST(stream.str() == indent + "if(1 != 3)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + indent + "3;\n" + indent + "}\n" + indent + "else\n" + indent + "{\n" + indent + indent + "3;\n" + indent + indent + "4;\n" + indent + indent + "3;\n" + indent + "}\n");
}

BOOST_AUTO_TEST_CASE(catch_block_tests)
{
	catch_clause block;
	BOOST_TEST(block.statements().size() == 0);
	auto &var = block.variable();

	boost::test_tools::output_test_stream output;
	auto indent = formatter_settings::settings.get_indent_string();
	output << block;

	BOOST_TEST(output.str() == indent + "catch(...)\n" + indent + "{\n" + indent + "}\n" );

	auto copy1(block);

	output.str("");
	output << copy1;

	BOOST_TEST(output.str() == indent + "catch(...)\n" + indent + "{\n" + indent + "}\n" );

	auto &body2 = block.statements();

	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body2.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	BOOST_TEST(block.statements().size() == 2);

	output.str("");
	output << block;

	BOOST_TEST(output.str() == indent + "catch(...)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" );

	auto copy2(block);

	output.str("");
	output << copy2;

	BOOST_TEST(output.str() == indent + "catch(...)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" );

	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(block.statements().size() == 2);

	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	copy2 = block;

	output.str("");
	output << block;

	BOOST_TEST(output.str() == indent + "catch(...)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + indent + "1;\n" + indent + "}\n" );

	BOOST_TEST(copy2.statements().size() == 3);
	BOOST_TEST(block.statements().size() == 3);

	output.str("");
	output << copy2;

	BOOST_TEST(output.str() == indent + "catch(...)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + indent + "1;\n" + indent + "}\n" );

	const auto &c_ref = copy1;
	c_ref.statements();
	c_ref.variable();

	output.str("");
	output << c_ref;

	BOOST_TEST(output.str() == indent + "catch(...)\n" + indent + "{\n" + indent + "}\n" );

	auto type = make_unique<primitive_type>("int");
	auto var2 = make_unique<variable_declaration>(variable_declaration(declarator_specifier(move(type))));
	var2->var_declarator().name = "i";
	catch_clause catch2(move(var2));

	output.str("");
	output << catch2;

	BOOST_TEST(output.str() == indent + "catch(int i)\n" + indent + "{\n" + indent + "}\n" );
}

BOOST_AUTO_TEST_CASE(try_statement_tests)
{
	auto stmt = make_unique<try_statement>();

	BOOST_TEST(stmt->statements().size() == 0);
	BOOST_TEST(stmt->catch_clauses().size() == 0);

	boost::test_tools::output_test_stream stream;
	auto indent = formatter_settings::settings.get_indent_string();

	stream << *stmt;
	auto str = stream.str();

	BOOST_TEST(str == indent + "try\n" + indent + "{\n" + indent + "}\n");
	
	auto &body2 = stmt->statements();

	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body2.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	BOOST_TEST(stmt->statements().size() == 2);

	catch_clause block;
	auto &body3 = block.statements();
	body3.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body3.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	stmt->catch_clauses().push_back(block);

	BOOST_TEST(stmt->statements().size() == 2);
	BOOST_TEST(stmt->catch_clauses().size() == 1);

	stream.str("");
	stream << *stmt;
	str = stream.str();

	BOOST_TEST(str == indent + "try\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "catch(...)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	auto other = stmt->clone();

	stream << *other;

	stream.str("");
	stream << *other;
	str = stream.str();

	BOOST_TEST(str == indent + "try\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "catch(...)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	other->write(stream);

	stream.str("");
	stream << *other;
	str = stream.str();

	BOOST_TEST(str == indent + "try\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "catch(...)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	stream << *stmt;

	stream.str("");
	stream << *stmt;
	str = stream.str();

	BOOST_TEST(str == indent + "try\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "catch(...)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	auto copy1(*stmt);

	BOOST_TEST(copy1.statements().size() == 2);
	BOOST_TEST(copy1.catch_clauses().size() == 1);

	BOOST_TEST(stmt->statements().size() == 2);
	BOOST_TEST(stmt->catch_clauses().size() == 1);

	stream.str("");
	stream << copy1;
	str = stream.str();

	BOOST_TEST(str == indent + "try\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "catch(...)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	auto copy2(*stmt);

	stmt->catch_clauses().push_back(block);
	body2.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	stream.str("");
	stream << copy2;
	str = stream.str();

	BOOST_TEST(str == indent + "try\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "catch(...)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	copy2 = *stmt;

	stream.str("");
	stream << copy2;
	str = stream.str();

	BOOST_TEST(str == indent + "try\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "catch(...)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "catch(...)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	BOOST_TEST(copy2.statements().size() == 3);
	BOOST_TEST(stmt->statements().size() == 3);
	BOOST_TEST(copy2.catch_clauses().size() == 2);
	BOOST_TEST(stmt->catch_clauses().size() == 2);


	stream.str("");
	stream << copy2;
	str = stream.str();

	BOOST_TEST(str == indent + "try\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "catch(...)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "catch(...)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	const auto &c_ref = copy1;
	c_ref.catch_clauses();
	c_ref.clone();
	c_ref.statements();

	stream.str("");
	c_ref.write(stream);
	str = stream.str();

	BOOST_TEST(str == indent + "try\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "catch(...)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");
}

BOOST_AUTO_TEST_CASE(case_statement_tests)
{
	case_statement block(false);
	BOOST_TEST(block.statements().size() == 0);

	boost::test_tools::output_test_stream output;
	auto indent = formatter_settings::settings.get_indent_string();

	output << block;

	BOOST_TEST(output.str() == indent + "default:\n" + indent + "{\n" + indent + "}\n");

	auto &body2 = block.statements();
	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body2.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	BOOST_TEST(block.statements().size() == 2);

	auto &var = block.label();

	output.str("");
	output << block;

	BOOST_TEST(output.str() == indent + "default:\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	auto copy2(block);

	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(block.statements().size() == 2);

	output.str("");
	output << copy2;

	BOOST_TEST(output.str() == indent + "default:\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));

	output.str("");
	output << copy2;

	BOOST_TEST(output.str() == indent + "default:\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	copy2 = block;

	BOOST_TEST(copy2.statements().size() == 3);
	BOOST_TEST(block.statements().size() == 3);

	output.str("");
	output << copy2;

	BOOST_TEST(output.str() == indent + "default:\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + indent + "1;\n" + indent + "}\n");

	case_statement block2(make_unique<primitive_expression>("5"));
	auto &var2 = block2.label();
	BOOST_TEST(dynamic_cast<const primitive_expression &>(var2).expr() == "5");

	output.str("");
	output << block2;

	BOOST_TEST(output.str() == indent + "case 5:\n" + indent + "{\n" + indent + "}\n");

	auto copy3(block2);

	output.str("");
	output << copy3;

	BOOST_TEST(output.str() == indent + "case 5:\n" + indent + "{\n" + indent + "}\n");

	const auto &c_ref = copy2;
	c_ref.has_label();
	c_ref.label();
	c_ref.statements();

	output.str("");
	output << c_ref;

	BOOST_TEST(output.str() == indent + "default:\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + indent + "1;\n" + indent + "}\n");
}

BOOST_AUTO_TEST_CASE(switch_statement_tests)
{
	auto stmt = make_unique<switch_statement>(make_unique<primitive_expression>("5"));

	BOOST_TEST(stmt->cases().size() == 0);
	BOOST_TEST(dynamic_cast<const primitive_expression &>(stmt->condition()).expr() == "5");

	boost::test_tools::output_test_stream stream;
	auto indent = formatter_settings::settings.get_indent_string();

	stream << *stmt;

	BOOST_TEST(stream.str() == indent + "switch(5)\n" + indent + "{\n" + indent + "}\n");

	case_statement block(true);
	auto &body3 = block.statements();
	body3.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body3.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	stmt->cases().push_back(block);

	BOOST_TEST(stmt->cases().size() == 1);

	stream.str("");
	stream << *stmt;

	BOOST_TEST(stream.str() == indent + "switch(5)\n" + indent + "{\n" + indent + "default:\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "}\n");

	auto other = stmt->clone();

	stream.str("");
	stream << *other;

	BOOST_TEST(stream.str() == indent + "switch(5)\n" + indent + "{\n" + indent + "default:\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "}\n");

	stream.str("");
	other->write(stream);

	BOOST_TEST(stream.str() == indent + "switch(5)\n" + indent + "{\n" + indent + "default:\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "}\n");

	stream.str("");
	stream << *other;

	BOOST_TEST(stream.str() == indent + "switch(5)\n" + indent + "{\n" + indent + "default:\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "}\n");

	auto copy2(*stmt);

	BOOST_TEST(dynamic_cast<const primitive_expression &>(copy2.condition()).expr() == "5");
	BOOST_TEST(copy2.cases().size() == 1);
	BOOST_TEST(stmt->cases().size() == 1);

	stmt->cases().push_back(block);

	stream.str("");
	stream << copy2;

	BOOST_TEST(stream.str() == indent + "switch(5)\n" + indent + "{\n" + indent + "default:\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "}\n");

	copy2 = *stmt;

	stream.str("");
	stream << copy2;

	BOOST_TEST(stream.str() == indent + "switch(5)\n" + indent + "{\n" + indent + "default:\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "default:\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "}\n");

	BOOST_TEST(copy2.cases().size() == 2);
	BOOST_TEST(stmt->cases().size() == 2);
	BOOST_TEST(dynamic_cast<const primitive_expression &>(copy2.condition()).expr() == "5");

	stream.str("");
	stream << copy2;

	BOOST_TEST(stream.str() == indent + "switch(5)\n" + indent + "{\n" + indent + "default:\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "default:\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "}\n");

	const auto &c_ref = copy2;
	c_ref.cases();
	c_ref.condition();
	c_ref.clone();

	stream.str("");
	c_ref.write(stream);

	BOOST_TEST(stream.str() == indent + "switch(5)\n" + indent + "{\n" + indent + "default:\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "default:\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n" + indent + "}\n");
}

BOOST_AUTO_TEST_CASE(jump_statement_tests)
{
	jump_statement break_stmt(jump_type::break_jump);
	jump_statement continue_stmt(jump_type::continue_jump);
	jump_statement goto_stmt(jump_type::goto_jump, make_unique<primitive_expression>("label"));
	jump_statement return_stmt1(jump_type::return_jump);
	jump_statement return_stmt2(jump_type::return_jump, make_unique<primitive_expression>("5"));

	BOOST_TEST(break_stmt.type() == jump_type::break_jump);
	BOOST_TEST(continue_stmt.type() == jump_type::continue_jump);
	BOOST_TEST(goto_stmt.type() == jump_type::goto_jump);
	BOOST_TEST(return_stmt1.type() == jump_type::return_jump);

	boost::test_tools::output_test_stream output;
	auto indent = formatter_settings::settings.get_indent_string();

	output << break_stmt;
	BOOST_TEST(output.str() == indent + "break;\n");

	output.str("");
	output << continue_stmt;
	BOOST_TEST(output.str() == indent + "continue;\n");

	output.str("");
	output << goto_stmt;
	BOOST_TEST(output.str() == indent + "goto label;\n");

	output.str("");
	output << return_stmt1;
	BOOST_TEST(output.str() == indent + "return;\n");

	output.str("");
	output << return_stmt2;
	BOOST_TEST(output.str() == indent + "return 5;\n");

	auto copy1(break_stmt);
	auto copy2(continue_stmt);
	auto copy3(goto_stmt);
	auto copy4(return_stmt1);
	auto copy5(return_stmt2);

	BOOST_TEST(copy1.type() == jump_type::break_jump);
	BOOST_TEST(break_stmt.type() == jump_type::break_jump);
	BOOST_TEST(copy2.type() == jump_type::continue_jump);
	BOOST_TEST(continue_stmt.type() == jump_type::continue_jump);
	BOOST_TEST(copy3.type() == jump_type::goto_jump);
	BOOST_TEST(goto_stmt.type() == jump_type::goto_jump);
	BOOST_TEST(copy4.type() == jump_type::return_jump);
	BOOST_TEST(return_stmt1.type() == jump_type::return_jump);
	BOOST_TEST(copy5.type() == jump_type::return_jump);
	BOOST_TEST(return_stmt2.type() == jump_type::return_jump);

	output.str("");
	output << copy1;
	BOOST_TEST(output.str() == indent + "break;\n");

	output.str("");
	output << copy2;
	BOOST_TEST(output.str() == indent + "continue;\n");

	output.str("");
	output << copy3;
	BOOST_TEST(output.str() == indent + "goto label;\n");

	output.str("");
	output << copy4;
	BOOST_TEST(output.str() == indent + "return;\n");

	output.str("");
	output << copy5;
	BOOST_TEST(output.str() == indent + "return 5;\n");

	copy1 = continue_stmt;
	copy2 = break_stmt;
	copy5 = goto_stmt;
	copy3 = return_stmt1;
	copy4 = return_stmt2;

	BOOST_TEST(copy2.type() == jump_type::break_jump);
	BOOST_TEST(break_stmt.type() == jump_type::break_jump);
	BOOST_TEST(copy1.type() == jump_type::continue_jump);
	BOOST_TEST(continue_stmt.type() == jump_type::continue_jump);
	BOOST_TEST(copy5.type() == jump_type::goto_jump);
	BOOST_TEST(goto_stmt.type() == jump_type::goto_jump);
	BOOST_TEST(copy3.type() == jump_type::return_jump);
	BOOST_TEST(return_stmt1.type() == jump_type::return_jump);
	BOOST_TEST(copy4.type() == jump_type::return_jump);
	BOOST_TEST(return_stmt2.type() == jump_type::return_jump);

	output.str("");
	output << copy2;
	BOOST_TEST(output.str() == indent + "break;\n");

	output.str("");
	output << copy1;
	BOOST_TEST(output.str() == indent + "continue;\n");

	output.str("");
	output << copy5;
	BOOST_TEST(output.str() == indent + "goto label;\n");

	output.str("");
	output << copy3;
	BOOST_TEST(output.str() == indent + "return;\n");

	output.str("");
	output << copy4;
	BOOST_TEST(output.str() == indent + "return 5;\n");
}

BOOST_AUTO_TEST_CASE(ranged_for_loop_tests)
{
	auto var = make_unique<variable_declaration>(declarator_specifier(make_unique<primitive_type>("int")));
	var->var_declarator().name = "i";
	var->var_declarator().initializer_exp = copyable_ptr<expression>(make_unique<primitive_expression>("55"));
	auto stmt = make_unique<ranged_for_loop>(move(var));

	BOOST_TEST(stmt->statements().size() == 0);
	BOOST_TEST(dynamic_cast<const variable_declaration &>(stmt->initializer()).var_declarator().name == "i");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(*dynamic_cast<const variable_declaration &>(stmt->initializer()).var_declarator().initializer_exp).expr() == "55");

	boost::test_tools::output_test_stream stream;
	auto indent = formatter_settings::settings.get_indent_string();

	stream << *stmt;

	BOOST_TEST(stream.str() == indent + "for(int i : 55)\n" + indent + "{\n" + indent + "}\n");

	auto &body2 = stmt->statements();

	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));
	body2.emplace_back(make_unique<expression_statement>(make_unique<primitive_expression>("2")));

	BOOST_TEST(stmt->statements().size() == 2);

	stream.str("");
	stream << *stmt;

	BOOST_TEST(stream.str() == indent + "for(int i : 55)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	auto other = stmt->clone();

	stream.str("");
	stream << *other;

	BOOST_TEST(stream.str() == indent + "for(int i : 55)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	stream.str("");
	other->write(stream);
	BOOST_TEST(stream.str() == indent + "for(int i : 55)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	auto copy2(*stmt);
	BOOST_TEST(copy2.statements().size() == 2);
	BOOST_TEST(dynamic_cast<const variable_declaration &>(copy2.initializer()).var_declarator().name == "i");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(*dynamic_cast<const variable_declaration &>(copy2.initializer()).var_declarator().initializer_exp).expr() == "55");

	stream.str("");
	stream << copy2;
	BOOST_TEST(stream.str() == indent + "for(int i : 55)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + "}\n");

	body2.push_back(make_unique<expression_statement>(make_unique<primitive_expression>("1")));

	copy2 = *stmt;

	stream.str("");
	stream << copy2;
	BOOST_TEST(stream.str() == indent + "for(int i : 55)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + indent + "1;\n" + indent + "}\n");

	BOOST_TEST(stmt->statements().size() == 3);
	BOOST_TEST(copy2.statements().size() == 3);
	BOOST_TEST(dynamic_cast<const variable_declaration &>(copy2.initializer()).var_declarator().name == "i");
	BOOST_TEST(dynamic_cast<const primitive_expression&>(*dynamic_cast<const variable_declaration &>(copy2.initializer()).var_declarator().initializer_exp).expr() == "55");

	const auto &c_ref = copy2;
	c_ref.clone();
	c_ref.initializer();
	c_ref.statements();
	c_ref.write(stream);

	stream.str("");
	stream << copy2;
	BOOST_TEST(stream.str() == indent + "for(int i : 55)\n" + indent + "{\n" + indent + indent + "1;\n" + indent + indent + "2;\n" + indent + indent + "1;\n" + indent + "}\n");
}

BOOST_AUTO_TEST_SUITE_END()