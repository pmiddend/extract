#ifndef EXTRACT_PLUGINS_ZIP_HPP_HPP_INCLUDED
#define EXTRACT_PLUGINS_ZIP_HPP_HPP_INCLUDED

#include "base.hpp"

namespace extract
{
namespace plugins
{
class zip
:
	public base
{
public:
	explicit
	zip(
		extract::environment const &);
	
	void
	process(
		fcppt::filesystem::path const &);
};
}
}

#endif
