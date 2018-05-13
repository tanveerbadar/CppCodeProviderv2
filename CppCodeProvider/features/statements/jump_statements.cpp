#include "jump_statements.h"

namespace cpp::codeprovider::statements
{
	using namespace std;
	using namespace formatting;

	jump_statement::jump_statement(const jump_statement& other)
		:j_type(other.j_type), e1(other.e1->clone())
	{
	}

	unique_ptr<statement> jump_statement::clone() const
	{
		return make_unique<jump_statement>(*this);
	}

	void jump_statement::write(ostream& os) const
	{
		auto indent = formatter_settings::settings.get_indent_string();

		switch (j_type)
		{
		case jump_type::continue_jump:
			os << indent << "continue;" << endl;
			break;
		case jump_type::break_jump:
			os << indent << "break;" << endl;
			break;
		case jump_type::goto_jump:
			os << indent << "goto " << *e1 << endl;
			break;
		case jump_type::return_jump:
			os << indent << "return ";
			if (e1)
				os << *e1;
			os << ";" << endl;
			break;
		}
	}
}