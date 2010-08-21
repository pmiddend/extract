#include "bomb_directory.hpp"
#include <fcppt/text.hpp>

fcppt::string const
extract::bomb_directory(
	fcppt::filesystem::path const &_p)
{
	/*
	fcppt::string::size_type const p = 
		_p.filename().find(
			FCPPT_TEXT('.'));

	if (p == fcppt::string::npos)
		return 
			_p.filename()+FCPPT_TEXT(".dir");
			*/

	/*
	return 
		_p.filename().substr(
			0,
			);
			*/
	return 
		_p.filename().string()+FCPPT_TEXT(".dir");
}
