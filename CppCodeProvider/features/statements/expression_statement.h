#ifndef EXPRESSION_STATEMENT_HEADER
#define EXPRESSION_STATEMENT_HEADER

#pragma once
#include "common.h"

namespace cpp::codeprovider::statements
{
	class expression;

	class expression_statement
	{
		std::unique_ptr<expression> e1;
	public:
		expression_statement(std::unique_ptr<expression>);
	};
}

#endif // !EXPRESSION_STATEMENT_HEADER
