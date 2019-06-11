#ifndef TYPES_COMMON_HEADER
#define TYPES_COMMON_HEADER

#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace cpp
{
namespace codeprovider
{
namespace types
{
class type
{
	std::string name;

protected:
	type(const std::string &);

public:
	std::string get_name() const;
	virtual std::ostream &write_forward_declaration(std::ostream &) const = 0;
	virtual std::ostream &write_declaration(std::ostream &) const = 0;
	virtual std::ostream &write_definition(std::ostream &) const = 0;
	virtual std::unique_ptr<type> clone() const = 0;
	virtual ~type() = 0;
};
} // namespace types
} // namespace codeprovider
} // namespace cpp

#endif // ! TYPES_COMMON_HEADER
