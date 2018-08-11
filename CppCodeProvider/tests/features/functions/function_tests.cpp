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
		type(const string& n)
			:name(n)
		{
		}
		type(const type&) = default;

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
	f f1("something", make_unique<type>("t1"));

	BOOST_TEST(!f1.is_inline());
	BOOST_TEST(f1.body().statements().size() == 0);
	BOOST_TEST(f1.parameters().size() == 0);
	BOOST_TEST(f1.template_parameters().size() == 0);
	BOOST_TEST(f1.return_type().name == "t1");

	f1.body();
	f1.is_inline();
	f1.parameters();
	f1.return_type();
	f1.template_parameters();

	boost::test_tools::output_test_stream stream;

	stream << f1;

	auto copy1(f1);

	BOOST_TEST(!copy1.is_inline());
	BOOST_TEST(copy1.body().statements().size() == 0);
	BOOST_TEST(copy1.parameters().size() == 0);
	BOOST_TEST(copy1.template_parameters().size() == 0);
	BOOST_TEST(copy1.return_type().name == "t1");

	copy1.body();
	copy1.is_inline();
	copy1.parameters();
	copy1.return_type();
	copy1.template_parameters();

	stream << copy1;

	copy1 = f1;

	copy1.body();
	copy1.is_inline();
	copy1.parameters();
	copy1.return_type();
	copy1.template_parameters();

	stream << copy1;

	const auto& c_ref = copy1;
	c_ref.body();
	c_ref.is_inline();
	c_ref.parameters();
	c_ref.return_type();
	c_ref.template_parameters();
}