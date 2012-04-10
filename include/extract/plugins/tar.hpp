#ifndef EXTRACT_PLUGINS_TAR_HPP_HPP_INCLUDED
#define EXTRACT_PLUGINS_TAR_HPP_HPP_INCLUDED

#include <extract/environment.hpp>
#include <extract/plugins/base.hpp>

namespace extract
{
namespace plugins
{
class tar
:
	public plugins::base
{
public:
	explicit
	tar(
		extract::environment const &);

	void
	process(
		boost::filesystem::path const &,
		extract::mime_type const &);

	file_sequence const
	list(
		boost::filesystem::path const &,
		extract::mime_type const &);

	static bool
	is_available();
private:
	static fcppt::string const command_name_;

	static fcppt::string const
	command_string(
		mime_type const &);
};
}
}

#endif
