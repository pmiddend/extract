#ifndef EXTRACT_LIST_FILES_HPP_HPP_INCLUDED
#define EXTRACT_LIST_FILES_HPP_HPP_INCLUDED

#include <extract/mime_type.hpp>
#include <extract/plugins/base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace extract
{
void
list_files(
	plugins::base &,
	boost::filesystem::path const &,
	extract::mime_type const &);
}

#endif
