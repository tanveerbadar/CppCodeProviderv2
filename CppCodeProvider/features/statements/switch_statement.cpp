#include "switch_statement.h"
#include "..\..\formatters\formatter_settings.h"
#include "..\expressions\unary_expressions.h"

namespace cpp::codeprovider::statements
{
	using namespace std;
	using namespace expressions;
	using namespace formatting;

	case_statement::case_statement(bool)
		:statements(make_unique<block_statement>())
	{
	}

	case_statement::case_statement(unique_ptr<expression> l)
		: e(move(l)), statements(make_unique<block_statement>())
	{
	}

	case_statement::case_statement(const case_statement& other)
		: e(other.e ? other.e->clone() : make_unique<primitive_expression>("")), statements(make_unique<block_statement>(*other.statements))
	{
	}

	block_statement& case_statement::body() const
	{
		return *statements;
	}

	expression& case_statement::label() const
	{
		return *e;
	}

	bool case_statement::has_label() const
	{
		auto ptr = dynamic_cast<primitive_expression*>(e.get());
		return ptr && ptr->expr().size() > 0;
	}

	ostream& operator<<(ostream& os, const case_statement& c)
	{
		os << formatter_settings::settings.get_indent_string();
		if (c.has_label())
			os << "case " << c.label() << ":" << endl;
		else
			os << "default" << ":" << endl;

		++formatter_settings::settings.indent_level;
		os << c.body();
		--formatter_settings::settings.indent_level;

		return os;
	}

	switch_statement::switch_statement(unique_ptr<expression> c)
		:condition_exp(move(c))
	{
	}

	switch_statement::switch_statement(const switch_statement& other)
		: condition_exp(other.condition_exp->clone())
	{
		for (auto& stmt : other.collection)
			collection.emplace_back(stmt);
	}

	unique_ptr<statement> switch_statement::clone() const
	{
		return make_unique<switch_statement>(*this);
	}

	void switch_statement::write(ostream& os) const
	{
		auto indent = formatter_settings::settings.get_indent_string();

		if (comment.size() > 0)
			os << indent << "//" << comment << endl;

		os << indent << "switch(" << *condition_exp << ")" << endl;
		os << indent << "{" << endl;
		for (auto& c : collection)
		{
			os << c;
		}
		os << indent << "}" << endl;
	}

	const expression& switch_statement::condition() const
	{
		return *condition_exp;
	}

	switch_statement& switch_statement::condition(unique_ptr<expressions::expression> c)
	{
		condition_exp = move(c);
		return *this;
	}

	vector<case_statement>& switch_statement::cases()
	{
		return collection;
	}
}