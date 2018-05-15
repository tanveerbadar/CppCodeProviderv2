#include <iostream>
#include "expression_types.h"

namespace cpp::codeprovider::expressions
{
	using namespace std;

	ostream& operator<<(ostream& os, expression_type type)
	{
		switch (type)
		{
		case expression_type::addition:
			os << "+";
			break;
		case expression_type::subtraction:
			os << "-";
			break;
		case expression_type::multiplication:
			os << "*";
			break;
		case expression_type::division:
			os << "/";
			break;
		case expression_type::modulus:
			os << "%";
			break;
		case expression_type::assignment:
			os << "=";
			break;
		case expression_type::and_exp:
			os << "&&";
			break;
		case expression_type::or_exp:
			os << "||";
			break;
		case expression_type::comma:
			os << ",";
			break;
		case expression_type::left_shift:
			os << "<<";
			break;
		case expression_type::right_shift:
			os << ">>";
			break;
		case expression_type::less:
			os << "<";
			break;
		case expression_type::greater:
			os << ">";
			break;
		case expression_type::less_equal:
			os << "<=";
			break;
		case expression_type::greater_equal:
			os << ">=";
			break;
		case expression_type::equal:
			os << "==";
			break;
		case expression_type::not_equal:
			os << "!=";
			break;
		case expression_type::bit_and:
			os << "&";
			break;
		case expression_type::bit_or:
			os << "|";
			break;
		case expression_type::xor_exp:
			os << "^";
			break;
		case expression_type::add_assign:
			os << "+=";
			break;
		case expression_type::subtract_assign:
			os << "-=";
			break;
		case expression_type::multiply_assign:
			os << "*=";
			break;
		case expression_type::divide_assign:
			os << "/=";
			break;
		case expression_type::modulus_assign:
			os << "%=";
			break;
		case expression_type::left_shift_assign:
			os << "<<=";
			break;
		case expression_type::right_shift_assign:
			os << ">>=";
			break;
		case expression_type::bit_and_assign:
			os << "&=";
			break;
		case expression_type::bit_or_assign:
			os << "|=";
			break;
		case expression_type::xor_assign:
			os << "^=";
			break;
		case expression_type::prefix_increment:
		case expression_type::postfix_increment:
			os << "++";
			break;
		case expression_type::prefix_decrement:
		case expression_type::postfix_decrement:
			os << "--";
			break;
		case expression_type::address_of:
			os << "&";
			break;
		case expression_type::negate:
			os << "-";
			break;
		case expression_type::plus:
			os << "+";
			break;
		case expression_type::throw_exp:
			os << "throw ";
			break;
		case expression_type::complement:
			os << "~";
			break;
		case expression_type::not_exp:
			os << "!";
			break;
		}
		return os;
	}
}