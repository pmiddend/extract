#ifndef EXTRACT_PLUGINS_RAR_HPP_HPP_INCLUDED
#define EXTRACT_PLUGINS_RAR_HPP_HPP_INCLUDED

#include "base.hpp"

namespace extract
{
namespace plugins
{
class rar
:
	public base
{
public:
	explicit
	rar(
		extract::environment const &);
	
	void
	process(
		fcppt::filesystem::path const &);
};
}
}

#endif
