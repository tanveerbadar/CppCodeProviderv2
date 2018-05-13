#include "features\expressions.h"
#include "features\statements.h"

using namespace std;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::statements;

int main()
{
	auto a1 = make_unique<primitive_expression>("1");
	auto e1 = binary_expression(expression_type::addition, move(a1), make_unique<primitive_expression>("2"));
	auto e2 = unary_expression(expression_type::prefix_increment, make_unique<primitive_expression>("a"));
	auto e3 = e1;
	cout << e1 << " " << e2 << " " << e3 << endl;

	auto s1 = expression_statement(make_unique<primitive_expression>("a"));

	cout << s1;

	char ch;

	cin >> ch;

	return 0;
}

