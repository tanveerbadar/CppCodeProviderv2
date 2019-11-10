#ifndef IF_DIRECTIVE_HEADER
#define IF_DIRECTIVE_HEADER

#pragma once

#include "common.h"
#include "../../utils/copyable_ptr.h"
#include <string>
#include <vector>

namespace cpp
{
namespace codeprovider
{
namespace preprocessor
{
typedef std::vector<utils::copyable_ptr<namespaces::namespace_scope_entity>> global_entity_list;

class if_directive : public preprocessor_directive
{
    bool is_ifndef;
    global_entity_list if_block, else_block;
    std::string macro;

public:
    if_directive(const std::string &, bool, const global_entity_list &);
    if_directive(const std::string &, bool, const global_entity_list &, const global_entity_list &);

    std::ostream &write_declaration(std::ostream &) const override;
    std::ostream &write_definition(std::ostream &) const override;
};
} // namespace preprocessor
} // namespace codeprovider
} // namespace cpp

#endif