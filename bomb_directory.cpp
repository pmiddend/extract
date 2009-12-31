#include "bomb_directory.hpp"
#include <fcppt/text.hpp>

fcppt::string const
extract::bomb_directory(
	fcppt::filesystem::path const &_p)
{
	return 
		_p.filename().substr(
			0,
			_p.filename().find(
				FCPPT_TEXT('.')));
}
