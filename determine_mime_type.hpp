#ifndef EXTRACT_DETERMINE_MIME_TYPE_HPP_HPP_INCLUDED
#define EXTRACT_DETERMINE_MIME_TYPE_HPP_HPP_INCLUDED

#include "mime_type.hpp"
#include <boost/filesystem/path.hpp>

namespace extract
{
mime_type const
determine_mime_type(
	boost::filesystem::path const &);
}

#endif
