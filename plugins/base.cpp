#include "base.hpp"

extract::plugins::base::base(
	mime_set const &_mimes,
	plugins::environment const &_environment)
:
	mimes_(
		_mimes),
	environment_(
		_environment)
{
}
	
extract::plugins::mime_set const &
extract::plugins::base::mimes() const
{
	return mimes_;
}

extract::plugins::environment const &
extract::plugins::base::environment() const
{
	return environment_;
}

extract::plugins::base::~base()
{
}
