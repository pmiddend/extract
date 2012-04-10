#include <extract/full_path.hpp>
#include <extract/is_runnable.hpp>
#include <fcppt/filesystem/is_executable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


bool
extract::is_runnable(
	fcppt::string const &r)
{
	fcppt::optional<boost::filesystem::path> const p =
		full_path(
			r);

	if (!p)
		return false;

	return
		fcppt::filesystem::is_executable(
			*p);
}
