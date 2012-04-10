#ifndef EXTRACT_BOMB_DIRECTORY_HPP_HPP_INCLUDED
#define EXTRACT_BOMB_DIRECTORY_HPP_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace extract
{
fcppt::string const
bomb_directory(
	boost::filesystem::path const &);
}

#endif
