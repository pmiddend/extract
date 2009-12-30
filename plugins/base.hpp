#ifndef EXTRACT_PLUGINS_BASE_HPP_HPP_INCLUDED
#define EXTRACT_PLUGINS_BASE_HPP_HPP_INCLUDED

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
		plugins::environment const &);
	
	mime_set const &
	mimes() const;

	plugins::environment const &
	environment() const;

	virtual void
	process(
		fcppt::filesystem::path const &) = 0;

	virtual
	~base();
private:
	mime_set const mimes_;
	plugins::environment const &environment_;
};
}
}

#endif
