#include <cstdlib>
#include <fcppt/container/array.hpp>
#include <extract/process/call.hpp>
#include <extract/process/exec.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/error/strerror.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <sys/epoll.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <algorithm>
#include <cerrno>
#include <cstddef>
#include <cstring>
#include <unistd.h>
#include <fcppt/config/external_end.hpp>


extract::process::output const
extract::process::call(
	argument_list const &_args)
{
	FCPPT_ASSERT_PRE(
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

		exec(
			_args);
	}

	close(
		out_pipe[writing_end]);
	close(
		err_pipe[writing_end]);

	int const epollfd =
		epoll_create(2);

	if(epollfd == -1)
		throw
			fcppt::exception(
				FCPPT_TEXT("epoll_create failed"));

	epoll_event new_event;
	new_event.events = EPOLLIN;
	new_event.data.fd = out_pipe[reading_end];

	if(epoll_ctl(epollfd,EPOLL_CTL_ADD,out_pipe[reading_end],&new_event) == -1)
		throw
			fcppt::exception(
				FCPPT_TEXT("epoll_ctl failed"));

	new_event.events = EPOLLIN;
	new_event.data.fd = err_pipe[reading_end];

	if(epoll_ctl(epollfd,EPOLL_CTL_ADD,err_pipe[reading_end],&new_event) == -1)
		throw
			fcppt::exception(
				FCPPT_TEXT("epoll_ctl failed"));

	process::output out;

	for(unsigned eof_count = 0u; eof_count < 2u;)
	{
		typedef
		fcppt::container::array
		<
			epoll_event,
			2
		>
		epoll_event_array;

		epoll_event_array events;

		int const retrieved_events =
			epoll_wait(
				epollfd,
				events.data(),
				2,
				-1);

		if(retrieved_events == -1)
			throw
				fcppt::exception(
					FCPPT_TEXT("epoll_wait failed"));


		for(std::size_t i = 0; i < static_cast<std::size_t>(retrieved_events); ++i)
		{
			int fd_index = events[i].data.fd == out_pipe[reading_end] ? 0 : 1;

			fcppt::string *outs[2] =
				{
					&out.standard_output(),
					&out.standard_error()
				};

			ssize_t const buffer_size =
				static_cast<ssize_t>(
					1024);

			char char_buffer[buffer_size];

			ssize_t const b = ::read(
				events[i].data.fd,
				char_buffer,
				static_cast<std::size_t>(
					buffer_size-1));

			if(b == 0)
			{
				eof_count++;
			}

			if(b == static_cast<ssize_t>(-1))
				throw
					fcppt::exception(
						FCPPT_TEXT("read failed"));

			outs[fd_index]->insert(
				outs[fd_index]->end(),
				char_buffer,
				char_buffer + b);
		}
	}

	waitpid(
		pid,
		(&out.exit_code()),
		0);

	return out;
}
