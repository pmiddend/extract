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
		boost::filesystem::path const &,
		mime_type const &);

	file_sequence const
	list(
		boost::filesystem::path const &,
		mime_type const &);

	static bool
	is_available();
private:
	static fcppt::string const command_name_;
};
}
}

#endif
