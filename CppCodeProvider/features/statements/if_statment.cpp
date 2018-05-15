#include "if_statement.h"
#include "..\expressions\common.h"

namespace cpp::codeprovider::statements
{
	using namespace std;
	using namespace expressions;

	if_statement::if_statement(unique_ptr<expression> c)
		:condition_exp(move(c))
	{
	}

	if_statement::if_statement(unique_ptr<expression> c, unique_ptr<block_statement> i)
		: condition_exp(move(c)), if_collection(move(i))
	{
	}

	if_statement::if_statement(unique_ptr<expression> c, unique_ptr<block_statement> i, unique_ptr<block_statement> e)
		: condition_exp(move(c)), if_collection(move(i)), else_collection(move(e))
	{
	}

	unique_ptr<statement> if_statement::clone() const
	{
		return make_unique<if_statement>(condition_exp->clone(), make_unique<block_statement>(*if_collection), make_unique<block_statement>(*else_collection));
	}

	void if_statement::write(ostream& os) const
	{
		os << "if( " << *condition_exp << " )" << endl;
		if (if_collection)
			os << *if_collection;
		if (else_collection)
		{
			os << "else" << endl;
			os << *else_collection;
		}
	}
}