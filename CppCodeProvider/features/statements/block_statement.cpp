#include "block_statement.h"
#include "../../formatters/formatter_settings.h"

namespace cpp::codeprovider::statements
{
	using namespace std;
	using namespace formatting;

	block_statement::block_statement(const block_statement & other)
	{
		for (auto& stmt : other.collection)
			collection.emplace_back(stmt->clone());
	}

	block_statement& block_statement::operator=(const block_statement& other)
	{
		if (this != &other)
		{
			vector<unique_ptr<statement>> temp;

			for (auto& stmt : other.collection)
				temp.emplace_back(stmt->clone());

			collection = move(temp);
		}

		return *this;
	}

	ostream& operator<<(ostream& os, const block_statement& block)
	{
		auto indent = formatter_settings::settings.get_indent_string();

		os << indent << "{" << endl;
		++formatter_settings::settings.indent_level;

		auto indent2 = formatter_settings::settings.get_indent_string();
		for (auto& stmt : block.statements())
		{
			os << indent2 << *stmt;
		}

		--formatter_settings::settings.indent_level;

		os << indent << "}" << endl;

		return os;
	}

	vector<unique_ptr<statement>>& block_statement::statements()
	{
		return collection;
	}

	const vector<unique_ptr<statement>>& block_statement::statements() const
	{
		return collection;
	}
}