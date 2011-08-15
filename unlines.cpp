#include "unlines.hpp"
#include "split.hpp"
#include <fcppt/text.hpp>
#include <boost/algorithm/string/classification.hpp>

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
