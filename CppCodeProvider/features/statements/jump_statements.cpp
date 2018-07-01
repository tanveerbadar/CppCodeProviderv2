#include "jump_statements.h"
#include "..\expressions\common.h"
#include "..\..\formatters\formatter_settings.h"

namespace cpp::codeprovider::statements
{
	using namespace std;
	using namespace formatting;

	jump_statement::jump_statement(jump_type t)
		:j_type(t)
	{
	}

	jump_statement::jump_statement(const jump_statement& other)
		:j_type(other.j_type), e1(other.e1->clone())
	{
	}

	jump_type jump_statement::type() const
	{
		return j_type;
	}

	unique_ptr<statement> jump_statement::clone() const
	{
		return make_unique<jump_statement>(*this);
	}

	void jump_statement::write(ostream& os) const
	{
		auto indent = formatter_settings::settings.get_indent_string();
		if (comment.size() > 0)
			os << indent << "//" << comment << endl;

		os << indent;
		switch (j_type)
		{
		case jump_type::continue_jump:
			os << "continue;" << endl;
			break;
		case jump_type::break_jump:
			os << "break;" << endl;
			break;
		case jump_type::goto_jump:
			os << "goto " << *e1 << endl;
			break;
		case jump_type::return_jump:
			os << "return ";
			if (e1)
				os << *e1;
			os << ";" << endl;
			break;
		}
	}
}