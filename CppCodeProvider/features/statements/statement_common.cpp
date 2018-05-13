#include "common.h"

namespace cpp::codeprovider::formatting
{
	formatter_settings formatter_settings::settings;
}

namespace cpp::codeprovider::statements
{
	using namespace std;

	statement::~statement()
	{
	}

	ostream& operator <<(ostream& os, const statement& expr)
	{
		expr.write(os);

		return os;
	}
}