#ifndef BINARY_EXPRESSION_TYPE
#define BINARY_EXPRESSION_TYPE
#pragma once

namespace cpp::codeprovider::primitives
{
	enum class expression_type
	{
		/// <summary>
		/// Represents '+' operator in code.
		/// </summary>
		addition = 1,
		/// <summary>
		/// Represents '-' operator in code.
		/// </summary>
		subtraction,
		/// <summary>
		/// Represents '*' operator in code.
		/// </summary>
		multiplication,
		/// <summary>
		/// Represents '/' operator in code.
		/// </summary>
		division,
		/// <summary>
		/// Represents '%' operator in code.
		/// </summary>
		modulus,
		/// <summary>
		/// Represents '=' operator in code.
		/// </summary>
		assignment,
		/// <summary>
		/// Represents '[ ]' operator in code.
		/// </summary>
		subscript,
		/// <summary>
		/// Represents '&amp;&amp;' operator in code.
		/// </summary>
		and_exp,
		/// <summary>
		/// Represents '||' operator in code.
		/// </summary>
		or_exp,
		/// <summary>
		/// Represents '.' operator in code.
		/// </summary>
		member_access,
		/// <summary>
		/// Represents ',' operator in code.
		/// </summary>
		comma,
		/// <summary>
		/// Represents '&lt;&lt;' operator in code.
		/// </summary>
		left_shift,
		/// <summary>
		/// Represents '&gt;&gt;' operator in code.
		/// </summary>
		right_shift,
		/// <summary>
		/// Represents '&lt;' operator in code.
		/// </summary>
		less,
		/// <summary>
		/// Represents '&gt;' operator in code.
		/// </summary>
		greater,
		/// <summary>
		/// Represents '&lt;=' operator in code.
		/// </summary>
		less_equal,
		/// <summary>
		/// Represents '&gt;=' operator in code.
		/// </summary>
		greater_equal,
		/// <summary>
		/// Represents '==' operator in code.
		/// </summary>
		equal,
		/// <summary>
		/// Represents '!=' operator in code.
		/// </summary>
		not_equal,
		/// <summary>
		/// Represents '&amp;' operator in code.
		/// </summary>
		bit_and,
		/// <summary>
		/// Represents '|' operator in code.
		/// </summary>
		bit_or,
		/// <summary>
		/// Represents '^' operator in code.
		/// </summary>
		xor_exp,
		/// <summary>
		/// Represents '+=' operator in code.
		/// </summary>
		add_assign,
		/// <summary>
		/// Represents '-=' operator in code.
		/// </summary>
		subtract_assign,
		/// <summary>
		/// Represents '*=' operator in code.
		/// </summary>
		multiply_assign,
		/// <summary>
		/// Represents '/=' operator in code.
		/// </summary>
		divide_assign,
		/// <summary>
		/// Represents '%=' operator in code.
		/// </summary>
		modulus_assign,
		/// <summary>
		/// Represents '&lt;&lt;=' operator in code.
		/// </summary>
		left_shift_assign,
		/// <summary>
		/// Represents '&gt;&gt;=' operator in code.
		/// </summary>
		right_shift_assign,
		/// <summary>
		/// Represents '&amp;=' operator in code.
		/// </summary>
		bit_and_assign,
		/// <summary>
		/// Represents '|=' operator in code.
		/// </summary>
		bit_or_assign,
		/// <summary>
		/// Represents '^=' operator in code.
		/// </summary>
		xor_assign,
		/// <summary>
		/// Represents '++' operator in code.
		/// </summary>
		prefix_increment,
		/// <summary>
		/// Represents '--' operator in code.
		/// </summary>
		prefix_decrement,
		/// <summary>
		/// Represents '++' operator in code.
		/// </summary>
		postfix_increment,
		/// <summary>
		/// Represents '--' operator in code.
		/// </summary>
		postfix_decrement,
		/// <summary>
		/// Represents '+' operator in code.
		/// </summary>
		plus,
		/// <summary>
		/// Represents '-' operator in code.
		/// </summary>
		negate,
		/// <summary>
		/// Represents '!' operator in code.
		/// </summary>
		not_exp,
		/// <summary>
		/// Represents '~' operator in code.
		/// </summary>
		complement,
		/// <summary>
		/// Represents '*' operator in code.
		/// </summary>
		dereference,
		/// <summary>
		/// Represents '&amp;' operator in code.
		/// </summary>
		address_of,
		/// <summary>
		/// Represents 'sizeof( )' operator in code.
		/// </summary>
		size_of,
		/// <summary>
		/// Represents a static_cast&lt; &gt; in code.
		/// </summary>
		static_cast_exp,
		/// <summary>
		/// Represents a const_cast&lt; &gt; in code.
		/// </summary>
		const_cast_exp,
		/// <summary>
		/// Represents a reinterpret_cast&lt; &gt; in code.
		/// </summary>
		reinterpret_cast_exp,
		/// <summary>
		/// Represents a dynamic_cast&lt; &gt; in code.
		/// </summary>
		dynamic_cast_exp,
		/// <summary>
		/// Represents a ( [Type] )[expression] style cast in code.
		/// </summary>
		c_cast_exp,
		variable_ref,
		conditional,
		delete_exp,
		method_ref,
		new_exp,
		parenthesis,
		primitive,
		scope,
		throw_exp,
		decltype_exp,
	};

	std::ostream& operator <<(std::ostream& os, primitives::expression_type type);
}

#endif
