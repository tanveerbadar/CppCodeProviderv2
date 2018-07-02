#define BOOST_TEST_MODULE cpp_code_provider_tests

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "..\..\..\features\functions.h"
#include "..\..\..\features\declarations\variable_declaration.h"

using namespace std;

namespace cpp::codeprovider::types::templates
{
	class template_parameter
	{

	};
}

namespace cpp::codeprovider::types
{
	class type2
	{
	public:
		type2(const string& name)
		{
		}
	};
}

using f = cpp::codeprovider::functions::function;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::types;

BOOST_AUTO_TEST_CASE(function_tests)
{
	auto t = make_unique<type>();
	t->name = "t1";
	f f1("something", move(t));
}