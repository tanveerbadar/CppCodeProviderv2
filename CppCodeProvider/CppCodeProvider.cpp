#include "features\expressions.h"
#include "features\statements.h"

using namespace std;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::statements;

int main()
{
	auto a1 = make_unique<primitive_expression>("1");
	auto e1 = make_unique<binary_expression>(expression_type::addition, make_unique<primitive_expression>(*a1), make_unique<primitive_expression>("2"));
	auto e2 = make_unique<unary_expression>(expression_type::prefix_increment, make_unique<primitive_expression>("a"));
	auto e3 = make_unique<binary_expression>(*e1);
	auto e4 = make_unique< ternary_expression>(make_unique<primitive_expression>("a"), make_unique<primitive_expression>("2"), make_unique<primitive_expression>("3"));
	cout << *e1 << " " << *e2 << " " << *e3 << " " << *e4 << endl;

	auto s1 = make_unique<expression_statement>(make_unique<primitive_expression>("a"));
	auto s2 = make_unique<block_statement>();

	auto& body = s2->statements();
	body.emplace_back(make_unique<expression_statement>(*s1));
	body.emplace_back(make_unique<expression_statement>(*s1));

	cout << *s1 << endl << *s2 << endl;

	auto l1 = make_unique<for_loop>();

	(*l1).condition(make_unique<binary_expression>(*e1)).initializer(make_unique<binary_expression>(*e1)).loop(make_unique<binary_expression>(*e1));
	auto& body2 = l1->loop_body().statements();
	body2.emplace_back(make_unique<expression_statement>(*s1));
	body2.emplace_back(make_unique<expression_statement>(*s1));

	cout << *l1;

	auto s3 = make_unique<switch_statement>(make_unique<binary_expression>(*e1));

	auto c = case_statement(make_unique<primitive_expression>(*a1));
	auto& body3 = c.body().statements();
	body3.emplace_back(make_unique<expression_statement>(*s1));
	body3.emplace_back(make_unique<expression_statement>(*s1));

	auto d = case_statement(true);
	auto& body4 = d.body().statements();
	body4.emplace_back(make_unique<expression_statement>(*s1));
	body4.emplace_back(make_unique<expression_statement>(*s1));

	auto& c_s = s3->cases();
	c_s.emplace_back(c);
	c_s.emplace_back(c);
	c_s.emplace_back(c);
	c_s.emplace_back(d);
	cout << *s3 << endl;

	auto s4 = make_unique<if_statement>(make_unique<binary_expression>(*e1), make_unique<block_statement>(d.body()), make_unique<block_statement>(d.body()));

	cout << *s4 << endl;

	char ch;
	cin >> ch;

	return 0;
}

