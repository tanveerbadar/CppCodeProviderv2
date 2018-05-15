#ifndef FORMATTER_SETTINGS_HEADER
#define FORMATTER_SETTINGS_HEADER

#pragma once

#include <string>

namespace cpp::codeprovider::formatting
{
	struct formatter_settings
	{
		static formatter_settings settings;

		int indent_amount = 4;
		int indent_level = 1;
		char indent_char = ' ';

		std::string get_indent_string() const
		{
			return std::string(indent_level * indent_amount, indent_char);
		}
	};
}

#endif // !FORMATTER_SETTINGS_HEADER