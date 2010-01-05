#include "base.hpp"
#include "../file_sequence_to_file_tree.hpp"
#include "../bomb_directory.hpp"
#include <fcppt/text.hpp>
#include <fcppt/filesystem/exists.hpp>
#include <fcppt/exception.hpp>

extract::plugins::base::base(
	mime_set const &_mimes,
	extract::environment const &_environment)
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

extract::environment const &
extract::plugins::base::environment() const
{
	return environment_;
}

extract::plugins::base::~base()
{
}

fcppt::filesystem::path const
extract::plugins::base::real_target_path(
	fcppt::filesystem::path const &_p,
	mime_type const &_m)
{
	fcppt::filesystem::path target_path = 
		environment().target_path()
		?
			*environment().target_path()
		: 
			FCPPT_TEXT(".");
	
	if(
		file_sequence_to_file_tree(
			list(
				_p,
				_m),
			FCPPT_TEXT(".")).size() > 1)
	{
		target_path /= 
			bomb_directory(
				_p.filename());

		if (fcppt::filesystem::exists(target_path))
			throw fcppt::exception(
				FCPPT_TEXT("Detected an archive bomb but destination directory ")+target_path.string()+FCPPT_TEXT(" already exists"));
	}

	return 
		target_path;
}
