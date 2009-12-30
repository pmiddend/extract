#ifndef EXTRACT_DETERMINE_MIME_TYPE_HPP_HPP_INCLUDED
#define EXTRACT_DETERMINE_MIME_TYPE_HPP_HPP_INCLUDED

#include "mime_type.hpp"
#include <fcppt/filesystem/path.hpp>

namespace extract
{
mime_type const
determine_mime_type(
	fcppt::filesystem::path const &);
}

#endif
