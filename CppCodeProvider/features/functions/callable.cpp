#include "callable.h"
#include "function.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../statements/try_statement.h"
#include "../types/template_parameters.h"

using namespace std;

namespace cpp::codeprovider::functions::internals
{
	using namespace std;
	using namespace types;
	using namespace declarations;
	using namespace templates;

	callable::callable(const string &n, unique_ptr<type> returns)
		: name(n), return_type(move(returns))
	{
	}
} // namespace cpp::codeprovider::functions::internals
