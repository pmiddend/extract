#ifndef EXTRACT_PLUGIN_TYPES_HPP_HPP_INCLUDED
#define EXTRACT_PLUGIN_TYPES_HPP_HPP_INCLUDED

#include <extract/plugins/rar.hpp>
#include <extract/plugins/tar.hpp>
#include <extract/plugins/zip.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector.hpp>
#include <fcppt/config/external_end.hpp>


namespace extract
{
typedef
boost::mpl::vector3
<
	extract::plugins::tar,
	extract::plugins::rar,
	extract::plugins::zip
>
plugin_types;
}

#endif
