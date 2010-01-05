#ifndef EXTRACT_PLUGIN_TYPES_HPP_HPP_INCLUDED
#define EXTRACT_PLUGIN_TYPES_HPP_HPP_INCLUDED

#include "plugins/rar.hpp"
#include "plugins/zip.hpp"
#include "plugins/tar.hpp"
#include <boost/mpl/vector.hpp>

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
