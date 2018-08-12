#include "common.h"

using namespace std;
using namespace cpp::codeprovider::types;

type::~type()
{
}

type::type(const std::string& n)
	:name(n)
{
}

string type::get_name() const
{
	return name;
}

namespace cpp::codeprovider::types
{
	ostream& operator<<(ostream& os, const type& t)
	{
		t.write(os);
		return os;
	}
}