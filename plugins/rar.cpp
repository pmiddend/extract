#include "rar.hpp"
#include "../process/exec.hpp"
#include "../process/call_safe.hpp"
#include "../unlines.hpp"
#include "../is_runnable.hpp"
#include <fcppt/assign/make_container.hpp>
#include <fcppt/text.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/io/cerr.hpp>
#include <boost/foreach.hpp>

extract::plugins::rar::rar(
	extract::environment const &_env)
:
	base(
		fcppt::assign::make_container<mime_set>
			(FCPPT_TEXT("application/x-rar"))
			(FCPPT_TEXT("fictional/.rar")),
		_env),
	command_name_(
		is_runnable(FCPPT_TEXT("unrar"))
		?
			FCPPT_TEXT("unrar")
		:
			FCPPT_TEXT("rar"))
{
}

void
extract::plugins::rar::process(
	fcppt::filesystem::path const &_p,
	mime_type const &_m)
{
	process::argument_list args;
	args.push_back(
		command_name_);

	args.push_back(
		FCPPT_TEXT("x"));

	/*
	args.push_back(
		FCPPT_TEXT("-p-"));
		*/

	if (environment().password())
		args.push_back(
			FCPPT_TEXT("-p")+
			(*environment().password()));

	if (environment().keep_broken())
		args.push_back(
			FCPPT_TEXT("-kb"));

	if (!environment().verbose())
		args.push_back(
			FCPPT_TEXT("-idc"));

	args.push_back(
		_p.string());

	args.push_back(
		real_target_path(_p,_m).string()+FCPPT_TEXT("/")); // NOTE: There _has_ to be a trailing / so rar accepts it as a target directory

	/*
	fcppt::io::cerr << "executing the following command:";
	BOOST_FOREACH(fcppt::string const &s,args)
		fcppt::io::cerr << s << "\n";
		*/

	process::exec(
		args);
}

extract::file_sequence const
extract::plugins::rar::list(
	fcppt::filesystem::path const &_p,
	mime_type const &)
{
	process::argument_list args;
	args.push_back(
		command_name_);
	args.push_back(
		FCPPT_TEXT("vb"));
	if (environment().password())
		args.push_back(
			FCPPT_TEXT("-p")+
			(*environment().password()));
	args.push_back(
		_p.string());

	process::output out =
		process::call_safe(
			args);
	if (!out.err.empty())
		throw fcppt::exception(
			FCPPT_TEXT("The error stream contains the following (unexpected) data: ")+
			out.err);
	out.out.erase(
		--out.out.end());
	return
		unlines(
			out.out);
}

bool
extract::plugins::rar::is_available()
{
	return
		is_runnable(
			FCPPT_TEXT("unrar")) ||
		is_runnable(
			FCPPT_TEXT("rar"));
}
