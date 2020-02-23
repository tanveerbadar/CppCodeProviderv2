#include "callable_reference_expression.h"
#include "../functions/function.h"
#include "../functions/member_function.h"
#include "lambda_expression.h"

using namespace std;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::functions;

callable_reference_expression::callable_reference_expression(shared_ptr<function> f)
    : f_ref(f)
{
}

callable_reference_expression::callable_reference_expression(shared_ptr<member_function> mf)
    : mf_ref(mf)
{
}

callable_reference_expression::callable_reference_expression(shared_ptr<lambda_expression> le)
    : le_ref(le)
{
}

unique_ptr<expression> callable_reference_expression::clone() const
{
    return make_unique<callable_reference_expression>(*this);
}

void callable_reference_expression::write(ostream &os) const
{
    if (f_ref)
        os << f_ref->name();
    if (mf_ref)
        os << mf_ref->name();
    if (le_ref)
        os << *le_ref;
}
