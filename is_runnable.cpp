#include "is_runnable.hpp"
#include "full_path.hpp"
#include <boost/filesystem/path.hpp>
#include <fcppt/filesystem/is_executable.hpp>

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
