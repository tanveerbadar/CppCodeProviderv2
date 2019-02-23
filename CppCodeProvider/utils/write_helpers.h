#ifndef WRITE_HELPERS_HEADER
#define WRITE_HELPERS_HEADER

#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include "../features/forward_declarations.h"

namespace cpp::codeprovider::utils
{
    template<typename T> void write_vector(std::ostream& os, const std::vector<std::unique_ptr<T>>& parameters)
    {
		if(parameters.size() > 0)
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

    template<typename T> void write_vector(std::ostream& os, const std::vector<T>& parameters)
    {
		if(parameters.size() > 0)
		{
			if (parameters.size() > 1)
				for (auto i = 1; i < parameters.size() - 1; ++i)
					os << parameters[i] << ", ";
			os << parameters[parameters.size() - 1] << std::endl;
		}
   }

   template <typename T> void write_definitions(std::ostream &os, const std::vector<T> &entities)
   {
	   for (const auto &e : entities)
	   {
		   e.write_definition(os);
		   os << std::endl;
	   }
   }

   template <typename T> void write_declarations(std::ostream &os, const std::vector<T> &entities)
   {
	   for (const auto &e : entities)
	   {
		   e.write_declaration(os);
		   os << std::endl;
	   }
   }

   template <typename T> void write_definitions(std::ostream &os, const std::vector<std::unique_ptr<T>> &entities)
   {
	   for (const auto &e : entities)
	   {
		   e -> write_definition(os);
		   os << std::endl;
	   }
   }

   template <typename T> void write_declarations(std::ostream &os, const std::vector<std::unique_ptr<T>> &entities)
   {
	   for (const auto &e : entities)
	   {
		   e -> write_declaration(os);
		   os << std::endl;
	   }
   }

	 void write_members(const std::vector<std::pair<types::access_levels, std::unique_ptr<declarations::declaration>>> &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
 } // namespace cpp::codeprovider::utils

#endif