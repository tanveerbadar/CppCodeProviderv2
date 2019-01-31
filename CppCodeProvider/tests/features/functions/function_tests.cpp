#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "../../../features/declarations/variable_declaration.h"
#include "../../../features/expressions.h"
#include "../../../features/functions.h"
#include "../../../features/statements/try_statement.h"
#include "../../../features/types.h"

using namespace std;

using f = cpp::codeprovider::functions::function;
using namespace cpp::codeprovider::functions;
using namespace cpp::codeprovider::types;

BOOST_AUTO_TEST_CASE(function_tests)
{
	f f1("something", make_unique<primitive_type>("int"));

	BOOST_TEST(!f1.is_inline());
	BOOST_TEST(!f1.is_static());
	BOOST_TEST(!f1.is_constexpr());
	BOOST_TEST(f1.body().statements().size() == 0);
	BOOST_TEST(f1.parameters().size() == 0);
	BOOST_TEST(f1.template_parameters().size() == 0);
	BOOST_TEST(f1.return_type().get_name() == "int");

	f1.is_inline(true);
	f1.is_static(true);
	f1.is_constexpr(true);

	f1.body();
	f1.is_inline();
	f1.is_static();
	f1.parameters();
	f1.return_type();
	f1.template_parameters();
	f1.is_constexpr();

	boost::test_tools::output_test_stream stream;

	stream << f1;

	auto copy1(f1);

	BOOST_TEST(copy1.is_inline());
	BOOST_TEST(copy1.is_static());
	BOOST_TEST(copy1.is_constexpr());
	BOOST_TEST(copy1.body().statements().size() == 0);
	BOOST_TEST(copy1.parameters().size() == 0);
	BOOST_TEST(copy1.template_parameters().size() == 0);
	BOOST_TEST(copy1.return_type().get_name() == "int");

	copy1.body();
	copy1.is_inline();
	copy1.is_static();
	copy1.parameters();
	copy1.return_type();
	copy1.template_parameters();
	copy1.is_constexpr();

	stream << copy1;

	copy1 = f1;

	BOOST_TEST(copy1.is_inline());
	BOOST_TEST(copy1.is_static());
	BOOST_TEST(copy1.is_constexpr());
	BOOST_TEST(copy1.body().statements().size() == 0);
	BOOST_TEST(copy1.parameters().size() == 0);
	BOOST_TEST(copy1.template_parameters().size() == 0);
	BOOST_TEST(copy1.return_type().get_name() == "int");

	copy1.body();
	copy1.is_inline();
	copy1.is_static();
	copy1.parameters();
	copy1.return_type();
	copy1.template_parameters();
	copy1.is_constexpr();

	stream << copy1;

	const auto& c_ref = copy1;
	c_ref.body();
	c_ref.is_inline();
	c_ref.is_static();
	c_ref.parameters();
	c_ref.return_type();
	c_ref.template_parameters();
	c_ref.is_constexpr();
}

BOOST_AUTO_TEST_CASE(member_function_tests)
{
	auto udt = make_shared<user_defined_type>("udt");
	member_function f1("something", make_unique<primitive_type>("int"), *udt);

	BOOST_TEST(!f1.is_inline());
	BOOST_TEST(!f1.is_static());
	BOOST_TEST(!f1.is_constexpr());
	BOOST_TEST(!f1.is_virtual());
	BOOST_TEST(!f1.is_abstract());
	BOOST_TEST(!f1.is_constant());
	BOOST_TEST(!f1.is_volatile());
	BOOST_TEST(!f1.is_override());
	BOOST_TEST(f1.body().statements().size() == 0);
	BOOST_TEST(f1.parameters().size() == 0);
	BOOST_TEST(f1.template_parameters().size() == 0);
	BOOST_TEST(f1.return_type().get_name() == "int");

	f1.is_inline(true);
	f1.is_static(true);
	f1.is_constexpr(true);
	f1.is_virtual(true);
	f1.is_abstract(true);
	f1.is_constant(true);
	f1.is_volatile(true);
	f1.is_override(true);

	f1.body();
	f1.is_inline();
	f1.is_static();
	f1.parameters();
	f1.return_type();
	f1.template_parameters();
	f1.is_constexpr();
	f1.is_virtual();
	f1.is_abstract();
	f1.is_constant();
	f1.is_volatile();
	f1.is_override();

	boost::test_tools::output_test_stream stream;

	stream << f1;

	auto copy1(f1);

	BOOST_TEST(copy1.is_inline());
	BOOST_TEST(copy1.is_static());
	BOOST_TEST(copy1.is_constexpr());
	BOOST_TEST(copy1.is_virtual());
	BOOST_TEST(copy1.is_abstract());
	BOOST_TEST(copy1.is_constant());
	BOOST_TEST(copy1.is_volatile());
	BOOST_TEST(copy1.is_override());
	BOOST_TEST(copy1.body().statements().size() == 0);
	BOOST_TEST(copy1.parameters().size() == 0);
	BOOST_TEST(copy1.template_parameters().size() == 0);
	BOOST_TEST(copy1.return_type().get_name() == "int");

	copy1.body();
	copy1.is_inline();
	copy1.is_static();
	copy1.parameters();
	copy1.return_type();
	copy1.template_parameters();
	copy1.is_constexpr();

	stream << copy1;

	copy1 = f1;

	BOOST_TEST(copy1.is_inline());
	BOOST_TEST(copy1.is_static());
	BOOST_TEST(copy1.is_constexpr());
	BOOST_TEST(copy1.is_virtual());
	BOOST_TEST(copy1.is_abstract());
	BOOST_TEST(copy1.is_constant());
	BOOST_TEST(copy1.is_volatile());
	BOOST_TEST(copy1.is_override());
	BOOST_TEST(copy1.body().statements().size() == 0);
	BOOST_TEST(copy1.parameters().size() == 0);
	BOOST_TEST(copy1.template_parameters().size() == 0);
	BOOST_TEST(copy1.return_type().get_name() == "int");

	copy1.body();
	copy1.is_inline();
	copy1.is_static();
	copy1.parameters();
	copy1.return_type();
	copy1.template_parameters();
	copy1.is_constexpr();

	stream << copy1;

	const auto& c_ref = copy1;
	c_ref.body();
	c_ref.is_inline();
	c_ref.is_static();
	c_ref.parameters();
	c_ref.return_type();
	c_ref.template_parameters();
	c_ref.is_constexpr();
}