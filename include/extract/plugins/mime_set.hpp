#ifndef EXTRACT_PLUGINS_MIME_SET_HPP_HPP_INCLUDED
#define EXTRACT_PLUGINS_MIME_SET_HPP_HPP_INCLUDED

#include <extract/mime_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <fcppt/config/external_end.hpp>


namespace extract
{
namespace plugins
{
typedef
std::set
<
	extract::mime_type
>
mime_set;
}
}

#endif
