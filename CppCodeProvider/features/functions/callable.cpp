#include "function.h"
#include "callable.h"
#include "..\declarations\declarator_specifier.h"
#include "..\declarations\variable_declaration.h"
#include "..\expressions\common.h"

using namespace std;

namespace cpp::codeprovider::types
{
	class type
	{
	public:
		type(const string& n)
			:name(n)
		{
		}
		type(const type&) = default;

		string name;
	};

	namespace templates
	{
		class template_parameter
		{

		};
	}
}

namespace cpp::codeprovider::functions::internals
{
	using namespace std;
	using namespace types;
	using namespace declarations;

	callable::callable(const string& n, unique_ptr<type> returns)
		: name(n), return_type(move(returns))
	{
	}

	callable::callable(const callable& other)
		: statements(other.statements), return_type(make_unique<type>(*other.return_type)), name(other.name), is_inline(other.is_inline)
	{
		for (auto& param : other.parameter_list)
			parameter_list.emplace_back(make_unique<variable_declaration>(*param));

		//for (auto& param : other.template_parameter_list)
		//	template_parameter_list.emplace_back(param);
	}
}
