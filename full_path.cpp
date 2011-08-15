#include "full_path.hpp"
#include <fcppt/assert.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/filesystem/exists.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/foreach.hpp>
#include <vector>
#include <cstdlib>

fcppt::optional<fcppt::filesystem::path> const
extract::full_path(
	fcppt::string const &s)
{
	FCPPT_ASSERT(
		!s.empty());

	char const *path_raw =
		std::getenv("PATH");

	FCPPT_ASSERT(
		path_raw);

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
			fcppt::filesystem::exists(
				fcppt::filesystem::path(r)/
				s))
			return
				fcppt::filesystem::path(r)/
					s;

	return
		fcppt::optional<fcppt::filesystem::path>();
}
