#include "callable.h"
#include "function.h"
#include "../declarations/variable_declaration.h"
#include "../expressions/common.h"
#include "../statements/try_statement.h"
#include "../types/template_parameters.h"

using namespace std;

using namespace cpp::codeprovider::functions::internals;
using namespace cpp::codeprovider::types;

callable::callable(const string &n, shared_ptr<type> returns)
	: name(n), return_type(returns)
{
}
