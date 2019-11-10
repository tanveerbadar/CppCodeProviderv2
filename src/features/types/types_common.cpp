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