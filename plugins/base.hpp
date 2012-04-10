#ifndef EXTRACT_PLUGINS_BASE_HPP_HPP_INCLUDED
#define EXTRACT_PLUGINS_BASE_HPP_HPP_INCLUDED

#include "mime_set.hpp"
#include "../environment.hpp"
#include "../file_sequence.hpp"

namespace extract
{
namespace plugins
{
class base
{
public:
	explicit
	base(
		mime_set const &,
		extract::environment const &);

	mime_set const &
	mimes() const;

	extract::environment const &
	environment() const;

	virtual void
	process(
		boost::filesystem::path const &,
		mime_type const &) = 0;

	virtual file_sequence const
	list(
		boost::filesystem::path const &,
		mime_type const &) = 0;

	virtual
	~base();
protected:
	boost::filesystem::path const
	real_target_path(
		boost::filesystem::path const &,
		mime_type const &);
private:
	mime_set const mimes_;
	extract::environment const &environment_;
};
}
}

#endif
