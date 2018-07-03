#define BOOST_TEST_MODULE cpp_code_provider_tests

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "..\..\..\features\functions.h"
#include "..\..\..\features\declarations\variable_declaration.h"

using namespace std;

namespace cpp::codeprovider::types
{
	class type
	{
	public:
		string name;
	};

	namespace templates
	{
		class template_parameter
		{

		};
	}
}

using f = cpp::codeprovider::functions::function;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::types;

BOOST_AUTO_TEST_CASE(function_tests)
{
	auto t = make_unique<type>();
	t->name = "t1";
	f f1("something", move(t));

	boost::test_tools::output_test_stream stream;

	stream << f1;

	auto copy1(f1);

	stream << copy1;

	copy1 = f1;

	stream << copy1;

	const auto& c_ref = copy1;
	c_ref.body();
	c_ref.is_inline();
	c_ref.parameters();
	c_ref.return_type();
	c_ref.template_parameters();
}