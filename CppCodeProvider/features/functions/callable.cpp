#include "function.h"
#include "callable.h"
#include "..\declarations\declarator_specifier.h"
#include "..\declarations\variable_declaration.h"

namespace cpp::codeprovider::types::templates
{
	class template_parameter
	{

	};
}

namespace cpp::codeprovider::functions::internals
{
	using namespace std;
	using namespace types;

	callable::callable(const string& n, unique_ptr<type> returns)
		: name(n), return_type(move(returns))
	{
	}
}
