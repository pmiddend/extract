#ifndef EXTRACT_PLUGINS_RAR_HPP_HPP_INCLUDED
#define EXTRACT_PLUGINS_RAR_HPP_HPP_INCLUDED

#include <extract/environment.hpp>
#include <extract/plugins/base.hpp>
#include <fcppt/string.hpp>


namespace extract
{
namespace plugins
{
class rar
:
	public plugins::base
{
public:
	explicit
	rar(
		extract::environment const &);

	void
	process(
		boost::filesystem::path const &,
		extract::mime_type const &);

	extract::file_sequence const
	list(
		boost::filesystem::path const &,
		extract::mime_type const &);

	static bool
	is_available();
private:
	fcppt::string command_name_;
};
}
}

#endif
