#include <extract/process/exec.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/error/strerror.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cerrno>
#include <cstddef>
#include <cstring>
#include <unistd.h>
#include <fcppt/config/external_end.hpp>


void
extract::process::exec(
	argument_list const &_args)
{
	char **newargv =
		new char*[
			static_cast<std::size_t>(
				_args.size()+1)];
	for(
		std::size_t i =
			static_cast<std::size_t>(0);
		i < _args.size();
		++i)
	{
		newargv[i] =
			new char[
				static_cast<std::size_t>(
					_args[i].size()+1)];
		std::strcpy(
			newargv[i],
			_args[i].c_str());
	}
	newargv[
		static_cast<std::size_t>(
			_args.size())] = 0;

	execvp(
		_args.begin()->c_str(),
		newargv);

	throw
		fcppt::exception(
			fcppt::string(
				FCPPT_TEXT("execvp failed: "))+
			fcppt::error::strerror(
				errno));
}
