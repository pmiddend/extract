#include "call.hpp"
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/error/strerror.hpp>
#include <fcppt/assert.hpp>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/select.h>
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <cerrno>

fcppt::string const
extract::process::call(
	argument_list const &_args)
{
	FCPPT_ASSERT(
		!_args.empty());

	std::size_t const
		reading_end = 
			static_cast<std::size_t>(
				0),
		writing_end = 
			static_cast<std::size_t>(
				1);

	int out_pipe[2];
	int err_pipe[2];

	if (pipe(out_pipe) == -1 || pipe(err_pipe) == -1)
		throw 
			fcppt::exception(
				FCPPT_TEXT("one of the pipes failed"));
	
	pid_t const pid = 
		fork();

	if (pid == 0)
	{
		close(
			out_pipe[reading_end]);
		close(
			err_pipe[reading_end]);
		dup2(
			out_pipe[writing_end],
			STDOUT_FILENO);
		dup2(
			err_pipe[writing_end],
			STDERR_FILENO);
		close(
			out_pipe[writing_end]);
		close(
			err_pipe[writing_end]);
		
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

	close(
		out_pipe[writing_end]);
	close(
		err_pipe[writing_end]);

	fd_set master_fds;
	FD_ZERO(
		&master_fds);
	
	FD_SET(
		out_pipe[reading_end],
		&master_fds);

	FD_SET(
		err_pipe[reading_end],
		&master_fds);

	fcppt::string 
		output;
	int eof_count = 
		0;
	while (eof_count < 2)
	{
		fd_set read_fds = master_fds;

		int 
			maxfd = 
				std::max(
					out_pipe[reading_end],
					err_pipe[reading_end]),
			select_return = 
				select(
					maxfd+1,
					&read_fds,
					0,
					0,
					0);

		if (select_return == -1)
			throw 
				fcppt::exception(
					FCPPT_TEXT("select failed"));

		int const fds[2] = 
			{ 
				out_pipe[reading_end],
				err_pipe[reading_end] 
			};

		for (int i = 0; i < 2; ++i)
		{
			if (!FD_SET(fds[i],&read_fds))
				continue;

			ssize_t const buffer_size = 
				static_cast<ssize_t>(
					1024);

			char char_buffer[buffer_size];

			ssize_t const b = ::read(
				fds[i],
				char_buffer,
				static_cast<std::size_t>(
					buffer_size-1));
			
			if (b == static_cast<ssize_t>(0))
			{
				eof_count++;
				FD_CLR(
					fds[i],
					&master_fds);
				continue;
			}
			
			if (b == static_cast<ssize_t>(-1))
				throw 
					fcppt::exception(
						FCPPT_TEXT("read failed"));

			output.insert(
				output.end(),
				char_buffer,
				char_buffer + b);
		}
	}
	
	int status;
	waitpid(
		pid,
		(&status),
		0);
	
	return output;
}
