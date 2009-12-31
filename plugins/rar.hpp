#ifndef EXTRACT_PLUGINS_RAR_HPP_HPP_INCLUDED
#define EXTRACT_PLUGINS_RAR_HPP_HPP_INCLUDED

#include "base.hpp"
#include <fcppt/string.hpp>

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
		fcppt::filesystem::path const &,
		mime_type const &);

	file_sequence const
	list(
		fcppt::filesystem::path const &,
		mime_type const &);
private:
	static fcppt::string const command_name_;
};
}
}

#endif
