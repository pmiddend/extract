#ifndef EXTRACT_DETERMINE_MIME_TYPE_HPP_HPP_INCLUDED
#define EXTRACT_DETERMINE_MIME_TYPE_HPP_HPP_INCLUDED

#include <extract/mime_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace extract
{
extract::mime_type const
determine_mime_type(
	boost::filesystem::path const &);
}

#endif
