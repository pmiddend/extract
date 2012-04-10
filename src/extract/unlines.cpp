#include <extract/split.hpp>
#include <extract/unlines.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <fcppt/config/external_end.hpp>


std::vector<fcppt::string> const
extract::unlines(
	fcppt::string const &s)
{
	return
		split(
			s,
			boost::algorithm::is_any_of(
				FCPPT_TEXT("\n")));
}
