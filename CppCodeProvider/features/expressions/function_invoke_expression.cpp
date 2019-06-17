#include "function_invoke_expression.h"
#include "../../utils/write_helpers.h"

using namespace std;
using namespace cpp::codeprovider::expressions;

unique_ptr<expression> function_invoke_expression::clone() const
{
    return make_unique<function_invoke_expression>(*this);
}

void function_invoke_expression::write(ostream& os) const
{
    target->write(os);

    if (arguments.size() > 0)
    {
        if (arguments.size() > 1)
            for (auto i = 1; i < arguments.size() - 1; ++i)
            {
                arguments[i]->write(os);
                os << ", ";
            }
        arguments[arguments.size() - 1]->write(os);
        os << std::endl;
    }
}