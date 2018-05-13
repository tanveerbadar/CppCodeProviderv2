#include "expression_statement.h"

namespace cpp::codeprovider::statements
{
	using namespace std;
	using namespace expressions;

	expression_statement::expression_statement(unique_ptr<expression> e)
		: e1(move(e))
	{
	}

	expression_statement::expression_statement(const expression_statement& other)
		: expression_statement(other.e1->clone())
	{
	}

	void expression_statement::write(ostream& os) const
	{
		os << *e1 << ";" << endl;
	}

	unique_ptr<statement> expression_statement::clone() const
	{
		return make_unique<expression_statement>(*this);
	}
}