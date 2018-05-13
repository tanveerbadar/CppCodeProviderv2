#include "features\expressions.h"
#include "features\statements.h"

using namespace std;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::statements;
using namespace cpp::codeprovider::formatting;

int main()
{
	auto fs = make_shared<formatter_settings>();
	auto a1 = make_unique<primitive_expression>("1");
	auto e1 = make_unique<binary_expression>(expression_type::addition, move(a1), make_unique<primitive_expression>("2"));
	auto e2 = make_unique<unary_expression>(expression_type::prefix_increment, make_unique<primitive_expression>("a"));
	auto e3 = e1->clone();
	cout << *e1 << " " << *e2 << " " << *e3 << endl;

	auto s1 = make_unique<expression_statement>(make_unique<primitive_expression>("a"));
	auto s2 = make_unique<block_statement>();

	auto& body = s2->statements();
	body.emplace_back(s1->clone());
	body.emplace_back(s1->clone());

	cout << *s1 << endl << *s2 << endl;

	auto l1 = make_unique<for_loop>();

	(*l1).condition(e1->clone()).initializer(e1->clone()).loop(e1->clone());
	auto& body2 = l1->loop_body().statements();
	body2.emplace_back(s1->clone());
	body2.emplace_back(s1->clone());

	cout << *l1;

	char ch;
	cin >> ch;

	return 0;
}

