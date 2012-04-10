#ifndef EXTRACT_PLUGINS_BASE_HPP_HPP_INCLUDED
#define EXTRACT_PLUGINS_BASE_HPP_HPP_INCLUDED

#include <extract/environment.hpp>
#include <extract/file_sequence.hpp>
#include <extract/plugins/mime_set.hpp>


namespace extract
{
namespace plugins
{
class base
{
public:
	explicit
	base(
		plugins::mime_set const &,
		extract::environment const &);

	plugins::mime_set const &
	mimes() const;

	extract::environment const &
	environment() const;

	virtual void
	process(
		boost::filesystem::path const &,
		extract::mime_type const &) = 0;

	virtual file_sequence const
	list(
		boost::filesystem::path const &,
		extract::mime_type const &) = 0;

	virtual
	~base();
protected:
	boost::filesystem::path const
	real_target_path(
		boost::filesystem::path const &,
		extract::mime_type const &);
private:
	plugins::mime_set const mimes_;
	extract::environment const &environment_;
};
}
}

#endif
