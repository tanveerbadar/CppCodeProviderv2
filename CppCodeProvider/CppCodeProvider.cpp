#include "features\expressions.h"

using namespace std;
using namespace cpp::codeprovider::expressions;

int main()
{
	auto a1 = make_unique<primitive_expression>("1");
	auto e1 = binary_expression(expression_type::addition, move(a1), make_unique<primitive_expression>("2"));
	auto e2 = unary_expression(expression_type::prefix_increment, make_unique<primitive_expression>("a"));
	auto e3 = e1;
	auto e4 = ternary_expression(make_unique<primitive_expression>("a"), make_unique<primitive_expression>("2"), make_unique<primitive_expression>("3"));
	cout << e1 << " " << e2 << " " << e3 << " " << e4 << endl;

	primitive_expression copy(*a1);
	copy = *a1;

	char ch;

	cin >> ch;

	return 0;
}

