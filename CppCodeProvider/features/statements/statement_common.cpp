#include "common.h"

using namespace std;
using namespace cpp::codeprovider::statements;

statement::~statement()
{
}

ostream &cpp::codeprovider::statements::operator<<(ostream &os, const statement &expr)
{
	expr.write(os);

	return os;
}
