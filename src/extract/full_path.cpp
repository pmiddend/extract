#include <extract/full_path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/exception.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/throw.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/filesystem/operations.hpp>
#include <cstdlib>
#include <vector>
#include <fcppt/config/external_end.hpp>


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

	for(part_sequence::const_iterator r = parts.begin(); r != parts.end(); ++r)
		if(
			boost::filesystem::exists(
				boost::filesystem::path(*r)/
				s))
			return
				fcppt::optional<boost::filesystem::path>(
					boost::filesystem::path(*r)/
						s);

	return
		fcppt::optional<boost::filesystem::path>();
}
