#ifndef EXTRACT_BOMB_DIRECTORY_HPP_HPP_INCLUDED
#define EXTRACT_BOMB_DIRECTORY_HPP_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <boost/filesystem/path.hpp>

namespace extract
{
fcppt::string const
bomb_directory(
	boost::filesystem::path const &);
}

#endif
