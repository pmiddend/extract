#include "full_path.hpp"
#include <fcppt/assert/exception.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/throw.hpp>
#include <fcppt/text.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/foreach.hpp>
#include <vector>
#include <cstdlib>

fcppt::optional<boost::filesystem::path> const
extract::full_path(
	fcppt::string const &s)
{
	FCPPT_ASSERT_PRE(
		!s.empty());

	char const *path_raw =
		std::getenv("PATH");

	FCPPT_ASSERT_THROW(
		path_raw,
		fcppt::assert_::exception
	);

	fcppt::string path(
		path_raw);

	typedef
	std::vector<fcppt::string>
	part_sequence;

	part_sequence parts;
	boost::algorithm::split(
		parts,
		path,
		boost::algorithm::is_any_of(
			FCPPT_TEXT(":")));

	BOOST_FOREACH(
		part_sequence::const_reference r,
		parts)
		if(
			boost::filesystem::exists(
				boost::filesystem::path(r)/
				s))
			return
				fcppt::optional<boost::filesystem::path>(
					boost::filesystem::path(r)/
						s);

	return
		fcppt::optional<boost::filesystem::path>();
}
