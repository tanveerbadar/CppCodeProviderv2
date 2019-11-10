#include "common.h"

using namespace std;
using namespace cpp::codeprovider::expressions;

expression::~expression()
{
}

ostream &cpp::codeprovider::expressions::operator<<(ostream &os, const expression &expr)
{
	expr.write(os);

	return os;
}
