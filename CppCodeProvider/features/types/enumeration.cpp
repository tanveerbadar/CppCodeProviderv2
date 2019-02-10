#include "enumeration.h"
#include "../expressions/common.h"

using namespace std;

namespace cpp::codeprovider::types
{
    using namespace expressions;

    enumeration::enumeration(const string &e)
        : type(e)
    {
    }

    enumeration::enumeration(const enumeration& other)
        : type(other)
    {
        for(auto& p : other.members)
            members.emplace_back(make_pair(p.first, p.second->clone()));
    }

    enumeration& enumeration::operator=(const enumeration& other)
    {
        if(this != &other)
        {
            type::operator=(other);
            members.empty();
            for (auto &p : other.members)
                members.emplace_back(make_pair(p.first, p.second->clone()));
        }

        return *this;
    }

    enumerator_list &enumeration::enumerators()
    {
        return members;
    }

    const enumerator_list &enumeration::enumerators() const
    {
        return members;
    }

    bool enumeration::is_scoped_enum() const
    {
        return is_scoped;
    }

    enumeration &enumeration::is_scoped_enum(bool flag)
    {
        is_scoped = flag;
        return *this;
    }

    unique_ptr<type> enumeration::clone() const
    {
        return make_unique<enumeration>(*this);
    }

    ostream& enumeration::write_declaration(ostream& os) const
    {
        os << (is_scoped ? "enum class " : "enum ");
        os << get_name();
        os << ";" << endl;

        return os;
    }

    ostream &enumeration::write_definition(ostream &os) const
    {
        os << (is_scoped ? "enum class " : "enum ");
        os << get_name();
        os << "{" << endl;

        for(auto& e : members)
        {
            os << e.first;
            if(e.second)
                os << " = " << *e.second;
            os << ", " << endl;
        }

        os << "};" << endl;

        return os;
    }
} // namespace cpp::codeprovider::types