#include "user_defined_type.h"
#include "../functions/callable.h"
#include "template_parameter.h"
#include "../functions/member_function.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../../utils/write_helpers.h"
#include <sstream>

using namespace std;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::utils;

namespace
{
	void write_members(const vector<unique_ptr<tuple<access_levels, variable_declaration>>>& variables, ostringstream& default_stream, ostringstream& private_stream, ostringstream& protected_stream, ostringstream& public_streams)
	{
		for (const auto& t : variables)
		{
			auto& [access, v] = *t;
			switch (access)
			{
			case access_levels::private_access:
				private_stream << v << endl;
				break;
			case access_levels::protected_access:
				protected_stream << v << endl;
				break;
			case access_levels::public_access:
				public_streams << v << endl;
				break;
			default:
				default_stream << v << endl;
				break;
			}
		}
	}

	void write_members(const vector<unique_ptr<member_function>> &functions, ostringstream& default_stream, ostringstream& private_stream, ostringstream& protected_stream, ostringstream& public_streams)
	{
		for (const auto &mf : functions)
		{
			switch (mf->accessibility())
			{
			case access_levels::private_access:
				private_stream << *mf << endl;
				break;
			case access_levels::protected_access:
				protected_stream << *mf << endl;
				break;
			case access_levels::public_access:
				public_streams << *mf << endl;
				break;
			default:
				default_stream << *mf << endl;
				break;
			}
		}
	}
}

user_defined_type::user_defined_type(const string &name)
	: type(name)
{
}

user_defined_type::user_defined_type(const user_defined_type &other)
	: type(other)
{
}

vector<unique_ptr<member_function>> &user_defined_type::member_functions()
{
	return functions;
}

void user_defined_type::write(ostream &os) const
{
	os << (this->is_class ? "class " : "struct ") << get_name() << endl;
	write_vector(os, base_types);
	os << "{" << endl;
	ostringstream private_stream, protected_stream, public_stream;
	write_members(fields, this->is_class ? private_stream : public_stream, private_stream, protected_stream, public_stream);
	write_members(functions, this->is_class ? private_stream : public_stream, private_stream, protected_stream, public_stream);
	os << "private:" << endl;
	os << private_stream.str() << endl;
	os << "protected:" << endl;
	os << protected_stream.str() << endl;
	os << "public: " << endl;
	os << public_stream.str() << endl;
	os << "};" << endl << endl;
}

unique_ptr<type> user_defined_type::clone() const
{
	return make_unique<user_defined_type>(*this);
}
