#ifndef EXTRACT_BOMB_DIRECTORY_HPP_HPP_INCLUDED
#define EXTRACT_BOMB_DIRECTORY_HPP_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/filesystem/path.hpp>

namespace extract
{
fcppt::string const
bomb_directory(
	fcppt::filesystem::path const &);
}

#endif
