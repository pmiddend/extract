#ifndef EXTRACT_PROCESS_OUTPUT_HPP_HPP_INCLUDED
#define EXTRACT_PROCESS_OUTPUT_HPP_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/preprocessor/const.hpp>

namespace extract
{
namespace process
{
class output
{
public:
	output();

	fcppt::string &
	standard_output()
	FCPPT_PP_CONST;

	fcppt::string const &
	standard_output() const
	FCPPT_PP_CONST;

	fcppt::string &
	standard_error()
	FCPPT_PP_CONST;

	fcppt::string const &
	standard_error() const
	FCPPT_PP_CONST;

	int &
	exit_code()
	FCPPT_PP_CONST;

	int const &
	exit_code() const
	FCPPT_PP_CONST;
private:
	fcppt::string standard_output_;
	fcppt::string standard_error_;
	int exit_code_;
};
}
}

#endif
