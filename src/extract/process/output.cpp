#include <extract/process/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>


extract::process::output::output()
:
	standard_output_(),
	standard_error_(),
	exit_code_(
		EXIT_FAILURE)
{
}

fcppt::string &
extract::process::output::standard_output()
{
	return
		standard_output_;
}

fcppt::string const &
extract::process::output::standard_output() const
{
	return
		standard_output_;
}

fcppt::string &
extract::process::output::standard_error()
{
	return standard_error_;
}

fcppt::string const &
extract::process::output::standard_error() const
{
	return
		standard_error_;
}

int &
extract::process::output::exit_code()
{
	return
		exit_code_;
}

int const &
extract::process::output::exit_code() const
{
	return
		exit_code_;
}
