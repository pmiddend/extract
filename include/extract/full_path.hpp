#ifndef EXTRACT_FULL_PATH_HPP_HPP_INCLUDED
#define EXTRACT_FULL_PATH_HPP_HPP_INCLUDED

#include <fcppt/optional.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace extract
{
fcppt::optional<boost::filesystem::path> const
full_path(
	fcppt::string const &);
}

#endif
