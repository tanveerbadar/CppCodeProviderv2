#include "common.h"

namespace cpp::codeprovider::expressions
{
	using namespace std;

	expression::~expression()
	{
	}

	ostream& operator <<(ostream& os, const expression& expr)
	{
		expr.write(os);

		return os;
	}
}