#ifndef WRITE_HELPERS_HEADER
#define WRITE_HELPERS_HEADER

#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include "copyable_ptr.h"
#include "../features/forward_declarations.h"
#include "../features/internals/write_backlog_entry.h"

namespace cpp::codeprovider::utils
{
template <typename T>
void write_vector(std::ostream &os, const std::vector<utils::copyable_ptr<T>> &parameters)
{
	if (parameters.size() > 0)
	{
		if (parameters.size() > 1)
			for (auto i = 1; i < parameters.size() - 1; ++i)
			{
				parameters[i]->write_declaration(os);
				os << ", ";
			}
		parameters[parameters.size() - 1]->write_declaration(os);
		os << std::endl;
	}
}

template <typename T>
void write_vector(std::ostream &os, const std::vector<T> &parameters)
{
	if (parameters.size() > 0)
	{
		if (parameters.size() > 1)
			for (auto i = 1; i < parameters.size() - 1; ++i)
				os << parameters[i] << ", ";
		os << parameters[parameters.size() - 1] << std::endl;
	}
}

template <typename T>
void write_definitions(std::ostream &os, const std::vector<T> &entities)
{
	for (const auto &e : entities)
	{
		e.write_definition(os);
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

void write_members(const std::vector<std::pair<types::access_levels, utils::copyable_ptr<declarations::declaration>>> &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);

void write_definitions(const std::vector<functions::member_function> &functions, std::ostringstream &default_stream, std::ostringstream &private_stream, std::ostringstream &protected_stream, std::ostringstream &public_stream, std::vector<const cpp::codeprovider::internals::write_backlog_entry *> &write_backlog);

void write_declarations(const std::vector<functions::member_function> &functions, std::ostringstream &default_stream, std::ostringstream &private_stream, std::ostringstream &protected_stream, std::ostringstream &public_stream);
} // namespace cpp::codeprovider::utils

#endif