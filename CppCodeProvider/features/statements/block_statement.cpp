#include "block_statement.h"
#include "../../formatters/formatter_settings.h"

using namespace std;
using namespace cpp::codeprovider::statements;
using namespace cpp::codeprovider::formatting;

block_statement::block_statement(const block_statement &other)
{
	for (auto &stmt : other.collection)
		collection.emplace_back(stmt->clone());
}

block_statement &block_statement::operator=(const block_statement &other)
{
	if (this != &other)
	{
		statement_list temp;

		for (auto &stmt : other.collection)
			temp.emplace_back(stmt->clone());

		collection = move(temp);
	}

	return *this;
}

ostream &cpp::codeprovider::statements::operator<<(ostream &os, const block_statement &block)
{
	block.write_declaration(os);
	return os;
}

statement_list &block_statement::statements()
{
	return collection;
}

const statement_list &block_statement::statements() const
{
	return collection;
}

ostream &block_statement::write_declaration(ostream &os) const
{
	auto indent = formatter_settings::settings.get_indent_string();

	os << indent << "{" << endl;
	++formatter_settings::settings.indent_level;

	auto indent2 = formatter_settings::settings.get_indent_string();
	for (auto &stmt : collection)
	{
		os << indent2 << *stmt;
	}

	--formatter_settings::settings.indent_level;

	os << indent << "}" << endl;

	return os;
}

ostream &block_statement::write_definition(ostream &os) const
{
	return write_declaration(os);
}
