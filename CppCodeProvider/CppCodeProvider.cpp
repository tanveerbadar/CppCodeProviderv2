#include "features\expressions.h"
#include "features\statements.h"
#include "features\declarations.h"
#include "features\functions.h"


using namespace std;

namespace cpp::codeprovider::types
{
	namespace templates
	{
		class template_parameter
		{

		};
	}

	class type
	{
	public:
		std::string name;

		virtual std::unique_ptr<type> clone() const
		{
			return std::make_unique<type>(*this);
		}
	};

	class user_defined_type : public type
	{
	};
}

using namespace std;
using namespace cpp::codeprovider::expressions;
using namespace cpp::codeprovider::statements;
using namespace cpp::codeprovider::declarations;
using namespace cpp::codeprovider::types;
using namespace cpp::codeprovider::functions;

int main2()
{
	auto a1 = make_unique<primitive_expression>("1");
	auto e1 = make_unique<binary_expression>(expression_type::addition, make_unique<primitive_expression>(*a1), make_unique<primitive_expression>("2"));
	auto e2 = make_unique<unary_expression>(expression_type::prefix_increment, make_unique<primitive_expression>("a"));
	auto e3 = make_unique<binary_expression>(*e1);
	auto e4 = make_unique< ternary_expression>(make_unique<primitive_expression>("a"), make_unique<primitive_expression>("2"), make_unique<primitive_expression>("3"));
	cout << *e1 << " " << *e2 << " " << *e3 << " " << *e4 << endl;

	auto s1 = make_unique<expression_statement>(make_unique<primitive_expression>("a"));
	block_statement s2;

	auto& body = s2.statements();
	body.emplace_back(make_unique<expression_statement>(*s1));
	body.emplace_back(make_unique<expression_statement>(*s1));

	cout << *s1 << endl << s2 << endl;

	auto l1 = make_unique<for_loop>();

	(*l1).condition(make_unique<binary_expression>(*e1)).initializer(make_unique<binary_expression>(*e1)).loop(make_unique<binary_expression>(*e1));
	auto& body2 = l1->statements();
	body2.emplace_back(make_unique<expression_statement>(*s1));
	body2.emplace_back(make_unique<expression_statement>(*s1));

	cout << *l1;

	auto s3 = make_unique<switch_statement>(make_unique<binary_expression>(*e1));

	auto c = case_statement(make_unique<primitive_expression>(*a1));
	auto& body3 = c.statements();
	body3.emplace_back(make_unique<expression_statement>(*s1));
	body3.emplace_back(make_unique<expression_statement>(*s1));

	auto d = case_statement(true);
	auto& body4 = d.statements();
	body4.emplace_back(make_unique<expression_statement>(*s1));
	body4.emplace_back(make_unique<expression_statement>(*s1));

	auto& c_s = s3->cases();
	c_s.emplace_back(c);
	c_s.emplace_back(c);
	c_s.emplace_back(c);
	c_s.emplace_back(d);
	cout << *s3 << endl;

	auto s4 = make_unique<if_statement>(make_unique<binary_expression>(*e1));
	auto& if_block = s4->if_block();
	auto& else_block = s4->else_block();
	
	if_block.emplace_back(make_unique<expression_statement>(*s1));
	else_block.emplace_back(make_unique<expression_statement>(*s1));

	cout << *s4 << endl;

	auto s5 = make_unique<try_statement>();
	auto& try_body = s5->statements();
	try_body.emplace_back(make_unique<expression_statement>(*s1));
	try_body.emplace_back(make_unique<expression_statement>(*s1));
	try_body.emplace_back(make_unique<expression_statement>(*s1));

	catch_clause c2;
	auto& catch_body = c2.statements();
	catch_body.emplace_back(make_unique<expression_statement>(*s1));

	s5->catch_clauses().emplace_back(c2);
	s5->catch_clauses().emplace_back(c2);
	s5->catch_clauses().emplace_back(c2);
	s5->catch_clauses().emplace_back(c2);
	s5->catch_clauses().emplace_back(c2);
	s5->catch_clauses().emplace_back(c2);

	cout << *s5 << endl;

	auto t1 = make_unique<type>();
	t1->name = "int";
	auto v1 = make_unique<variable_declaration>(*t1);
	v1->declarator().name = "a";
	cout << *v1 << endl;

	auto v2 = make_unique<variable_declaration_list>(make_unique<type>());
	auto& variables = v2->declarations();
	auto lambda = []()
	{
		declarator decl;
		decl.name = "a";
		decl.is_rvalue_ref = true;
		decl.array_dimensions.push_back(5);
		decl.array_dimensions.push_back(3);
		decl.array_dimensions.push_back(2);
		decl.array_dimensions.push_back(4);
		decl.pointer_level = 3;
		return decl;
	};

	variables.push_back(lambda());
	variables.push_back(lambda());
	variables.push_back(lambda());
	variables.push_back(lambda());

	cout << *v2 << endl;

	function f1("func1", make_unique<type>(*t1));
	
	auto& body5 = f1.body().statements();
	body5.push_back(make_unique<expression_statement>(*s1));
	body5.push_back(make_unique<switch_statement>(*s3));
	body5.push_back(make_unique<if_statement>(*s4));

	cout << f1;

	member_function mf1("func2", make_unique<type>(*t1), user_defined_type());

	auto& body6 = mf1.body().statements();
	body6.push_back(make_unique<expression_statement>(*s1));
	body6.push_back(make_unique<switch_statement>(*s3));
	body6.push_back(make_unique<if_statement>(*s4));

	cout << mf1;

	primitive_expression copy(*a1);
	copy = *a1;

	char ch;
	cin >> ch;

	return 0;
}

