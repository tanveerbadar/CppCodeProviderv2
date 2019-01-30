#include "common.h"

using namespace std;

namespace cpp::codeprovider::declarations
{
	declaration::~declaration()
	{
	}

	ostream& operator<<(ostream& os, const declaration& decl)
	{
		decl.write(os);
		return os;
	}
}