#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "..\..\..\features\functions.h"
#include "..\..\..\features\declarations\variable_declaration.h"
#include "..\..\..\features\types.h"

using namespace std;

using f = cpp::codeprovider::functions::function;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::types;

BOOST_AUTO_TEST_CASE(function_tests)
{
	f f1("something", make_unique<primitive_type>("int"));

	BOOST_TEST(!f1.is_inline());
	BOOST_TEST(f1.body().statements().size() == 0);
	BOOST_TEST(f1.parameters().size() == 0);
	BOOST_TEST(f1.template_parameters().size() == 0);
	BOOST_TEST(f1.return_type().get_name() == "int");

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
	BOOST_TEST(copy1.return_type().get_name() == "int");

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