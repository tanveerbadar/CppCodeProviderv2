#include "define_directive.h"
#include "../../utils/write_helpers.h"

using namespace std;
using namespace cpp::codeprovider::preprocessor;

define_directive::define_directive(const string &n)
    : name(n)
{
}

define_directive::define_directive(const string &n, const string &b)
    : name(n), body(b)
{
}

define_directive::define_directive(const string &n, const vector<string> &p, const string &b)
    : name(n), body(b), parameters(p)
{
}

ostream &define_directive::write_definition(ostream &os) const
{
    return write_declaration(os);
}

ostream &define_directive::write_declaration(ostream &os) const
{
    os << "#define " << name;

    if (!parameters.empty())
    {
        os << '(';
        utils::write_vector(os, parameters);
        os << ") ";
    }

    os << body;

    return os;
}