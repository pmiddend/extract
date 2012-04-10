#include "base.hpp"
#include "../file_sequence_to_file_tree.hpp"
#include "../bomb_directory.hpp"
#include <fcppt/text.hpp>
#include <boost/filesystem/operations.hpp>
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

boost::filesystem::path const
extract::plugins::base::real_target_path(
	boost::filesystem::path const &_p,
	mime_type const &_m)
{
	boost::filesystem::path target_path =
		environment().target_path()
		?
			*environment().target_path()
		:
			FCPPT_TEXT(".");

	file_tree tree(
		FCPPT_TEXT(".")
	);

	file_sequence_to_file_tree(
		tree,
		list(
			_p,
			_m));
	if(
		tree.size() > 1
	)
	{
		target_path /=
			bomb_directory(
				_p.filename());

		if (boost::filesystem::exists(target_path))
			throw fcppt::exception(
				FCPPT_TEXT("Detected an archive bomb but destination directory ")+target_path.string()+FCPPT_TEXT(" already exists"));
	}

	return
		target_path;
}
