#ifndef EXTRACT_PLUGINS_BASE_HPP_HPP_INCLUDED
#define EXTRACT_PLUGINS_BASE_HPP_HPP_INCLUDED

#include "mime_set.hpp"
#include "../environment.hpp"

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
		fcppt::filesystem::path const &) = 0;

	virtual
	~base();
private:
	mime_set const mimes_;
	extract::environment const &environment_;
};
}
}

#endif
