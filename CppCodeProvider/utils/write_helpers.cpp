#include "write_helpers.h"
#include "../features/declarations/common.h"
#include "../features/functions/member_function.h"
#include "../features/types/access_levels.h"

using namespace std;

namespace cpp::codeprovider::utils
{
using namespace declarations;
using namespace functions;
using namespace types;

void write_members(const vector<pair<access_levels, copyable_ptr<declaration>>> &variables, ostringstream &default_stream, ostringstream &private_stream, ostringstream &protected_stream, ostringstream &public_stream)
{
    for (const auto &t : variables)
    {
        auto &[access, v] = t;

        switch (access)
        {
        case access_levels::private_access:
            v->write_declaration(private_stream);
            private_stream << endl;
            break;
        case access_levels::protected_access:
            v->write_declaration(protected_stream);
            protected_stream << endl;
            break;
        case access_levels::public_access:
            v->write_declaration(public_stream);
            public_stream << endl;
            break;
        default:
            v->write_declaration(default_stream);
            default_stream << endl;
            break;
        }
    }
}

void write_definition_helper(const member_function &mf, ostringstream &stream, vector<const cpp::codeprovider::internals::write_backlog_entry*> &write_backlog)
{
    if (!mf.is_abstract())
        mf.write_definition(stream);
    else
    {
        mf.write_declaration(stream);
        if (mf.body().statements().size())
            write_backlog.push_back(&mf);
    }
    stream << endl;
}

void write_definitions(const vector<member_function> &functions, ostringstream &default_stream, ostringstream &private_stream, ostringstream &protected_stream, ostringstream &public_stream, vector<const cpp::codeprovider::internals::write_backlog_entry *> &write_backlog)
{
    for (const auto &mf : functions)
    {
        switch (mf.accessibility())
        {
        case access_levels::private_access:
            write_definition_helper(mf, private_stream, write_backlog);
            break;
        case access_levels::protected_access:
            write_definition_helper(mf, protected_stream, write_backlog);
            break;
        case access_levels::public_access:
            write_definition_helper(mf, public_stream, write_backlog);
            break;
        default:
            write_definition_helper(mf, default_stream, write_backlog);
            break;
        }
    }
}

void write_declarations(const vector<member_function> &functions, ostringstream &default_stream, ostringstream &private_stream, ostringstream &protected_stream, ostringstream &public_stream)
{
    for (const auto &mf : functions)
    {
        switch (mf.accessibility())
        {
        case access_levels::private_access:
            if (mf.template_parameters().size())
                mf.write_definition(private_stream);
            else
                mf.write_declaration(private_stream);
            private_stream << endl;
            break;
        case access_levels::protected_access:
            if (mf.template_parameters().size())
                mf.write_definition(protected_stream);
            else
                mf.write_declaration(protected_stream);
            protected_stream << endl;
            break;
        case access_levels::public_access:
            if (mf.template_parameters().size())
                mf.write_definition(public_stream);
            else
                mf.write_declaration(protected_stream);
            public_stream << endl;
            break;
        default:
            if (mf.template_parameters().size())
                mf.write_definition(default_stream);
            else
                mf.write_declaration(protected_stream);
            default_stream << endl;
            break;
        }
    }
}
} // namespace cpp::codeprovider::utils
