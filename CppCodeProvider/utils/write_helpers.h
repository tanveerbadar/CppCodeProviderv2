#ifndef WRITE_HELPERS_HEADER
#define WRITE_HELPERS_HEADER

#pragma once

#include <iostream>
#include <vector>
#include <memory>

namespace cpp::codeprovider::utils
{
    template<typename T> void write_vector(std::ostream& os, const std::vector<std::unique_ptr<T>>& parameters)
    {
		if(parameters.size() > 0)
		{
			if (parameters.size() > 1)
				for (auto i = 1; i < parameters.size() - 1; ++i)
					os << *parameters[i] << ", ";
			os << *parameters[parameters.size() - 1] << endl;
		}
   }

    template<typename T> void write_vector(std::ostream& os, const std::vector<T>& parameters)
    {
		if(parameters.size() > 0)
		{
			if (parameters.size() > 1)
				for (auto i = 1; i < parameters.size() - 1; ++i)
					os << parameters[i] << ", ";
			os << parameters[parameters.size() - 1] << endl;
		}
   }
}

#endif