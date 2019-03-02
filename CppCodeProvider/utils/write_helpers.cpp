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

    void write_members(const vector<pair<access_levels, unique_ptr<declaration>>> &variables, ostringstream &default_stream, ostringstream &private_stream, ostringstream &protected_stream, ostringstream &public_stream)
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

    void write_declarations(const vector<member_function> &functions, ostringstream &default_stream, ostringstream &private_stream, ostringstream &protected_stream, ostringstream &public_streams)
    {
        for (const auto &mf : functions)
        {
            switch (mf.accessibility())
            {
            case access_levels::private_access:
                mf.write_declaration(private_stream);
                private_stream << endl;
                break;
            case access_levels::protected_access:
                mf.write_declaration(protected_stream);
                protected_stream << endl;
                break;
            case access_levels::public_access:
                mf.write_declaration(public_streams);
                public_streams << endl;
                break;
            default:
                mf.write_declaration(default_stream);
                default_stream << endl;
                break;
            }
        }
    }
} // namespace cpp::codeprovider::utils
