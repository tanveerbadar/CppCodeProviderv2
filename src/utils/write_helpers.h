#ifndef WRITE_HELPERS_HEADER
#define WRITE_HELPERS_HEADER

#pragma once

#include "../features/forward_declarations.h"
#include "../features/internals/write_backlog_entry.h"
#include "copyable_ptr.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

namespace cpp
{
namespace codeprovider
{
namespace utils
{
template <typename T>
void write_vector(std::ostream &os, const std::vector<utils::copyable_ptr<T>> &parameters)
{
	if (parameters.size() > 0)
	{
		if (parameters.size() > 1)
			for (auto i = 0; i < parameters.size() - 1; ++i)
			{
				parameters[i]->write_declaration(os);
				os << ", ";
			}
		parameters[parameters.size() - 1]->write_declaration(os);
	}
}

template <typename T>
void write_vector(std::ostream &os, const std::vector<T> &parameters)
{
	if (parameters.size() > 0)
	{
		if (parameters.size() > 1)
			for (auto i = 0; i < parameters.size() - 1; ++i)
				os << parameters[i] << ", ";
		os << parameters[parameters.size() - 1];
	}
}

template<typename T> void write_definitions(std::ostream &os, const std::vector<T> &entities)
{
    for (const auto &mf : entities)
    {
        mf.write_definition(os);
        os << endl;
    }
}

template <typename T>
void write_definitions(std::ostream &os, const std::vector<copyable_ptr<T>> &entities)
{
	for (const auto &e : entities)
	{
		e->write_definition(os);
		os << std::endl;
	}
}

template <typename T>
void write_declarations(std::ostream &os, const std::vector<T> &entities)
{
	for (const auto &e : entities)
	{
		e->write_declaration(os);
		os << std::endl;
	}
}

void write_definition_helper(const cpp::codeprovider::functions::member_function &, std::ostringstream &, std::vector<const cpp::codeprovider::internals::write_backlog_entry *> &);

void write_members(const std::vector<std::pair<types::access_levels, utils::copyable_ptr<declarations::declaration>>> &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);

void write_definitions(const std::vector<functions::constructor> &functions, std::ostringstream &default_stream, std::ostringstream &private_stream, std::ostringstream &protected_stream, std::ostringstream &public_stream);

void write_definitions(const std::vector<functions::member_function> &functions, std::ostringstream &default_stream, std::ostringstream &private_stream, std::ostringstream &protected_stream, std::ostringstream &public_stream, std::vector<const cpp::codeprovider::internals::write_backlog_entry *> &write_backlog);

template<typename T>
void write_declarations(const std::vector<T> &functions, std::ostringstream &default_stream, std::ostringstream &private_stream, std::ostringstream &protected_stream, std::ostringstream &public_stream)
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

typedef std::vector<utils::copyable_ptr<types::templates::template_parameter>> template_parameter_list;

void write_template_parameters(std::ostream &, const template_parameter_list &);
} // namespace utils
} // namespace codeprovider
} // namespace cpp

#endif