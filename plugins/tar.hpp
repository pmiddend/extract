#ifndef EXTRACT_PLUGINS_TAR_HPP_HPP_INCLUDED
#define EXTRACT_PLUGINS_TAR_HPP_HPP_INCLUDED

#include "base.hpp"

namespace extract
{
namespace plugins
{
class tar
:
	public base
{
public:
	explicit
	tar(
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

	static fcppt::string const
	command_string(
		mime_type const &);
};
}
}

#endif
