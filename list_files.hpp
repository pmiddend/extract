#ifndef EXTRACT_LIST_FILES_HPP_HPP_INCLUDED
#define EXTRACT_LIST_FILES_HPP_HPP_INCLUDED

#include "plugins/base.hpp"
#include "mime_type.hpp"
#include <fcppt/filesystem/path.hpp>

namespace extract
{
void
list_files(
	plugins::base &,
	fcppt::filesystem::path const &,
	mime_type const &);
}

#endif
