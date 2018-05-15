#include <algorithm>
#include "block_statement.h"
#include "..\..\formatters\formatter_settings.h"

namespace cpp::codeprovider::statements
{
	using namespace std;
	using namespace formatting;

	block_statement::block_statement()
	{
	}

	block_statement::block_statement(const block_statement & other)
	{
		for (auto& stmt : other.collection)
			collection.emplace_back(stmt->clone());
	}

	unique_ptr<statement> block_statement::clone() const
	{
		return make_unique<block_statement>(*this);
	}

	void block_statement::write(ostream& os) const
	{
		auto indent = formatter_settings::settings.get_indent_string();

		os << indent << "{" << endl;
		++formatter_settings::settings.indent_level;

		auto indent2 = formatter_settings::settings.get_indent_string();
		for (auto& stmt : collection)
		{
			os << indent2 << *stmt;
		}

		--formatter_settings::settings.indent_level;

		os << indent << "}" << endl;
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