#ifndef EXTRACT_FULL_PATH_HPP_HPP_INCLUDED
#define EXTRACT_FULL_PATH_HPP_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/filesystem/path.hpp>

namespace extract
{
fcppt::optional<fcppt::filesystem::path> const
full_path(
	fcppt::string const &);
}

#endif
