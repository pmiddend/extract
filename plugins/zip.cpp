#include "zip.hpp"
#include "../process/exec.hpp"
#include "../process/call.hpp"
#include <fcppt/assign/make_container.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/text.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/io/cerr.hpp>

fcppt::string const extract::plugins::zip::command_name_(
	FCPPT_TEXT("unzip"));

extract::plugins::zip::zip(
	extract::environment const &_env)
:
	base(
		fcppt::assign::make_container<mime_set>
			(fcppt::string(FCPPT_TEXT("application/zip"))),
		_env)
{
	
}

void
extract::plugins::zip::process(
	fcppt::filesystem::path const &_p,
	mime_type const &)
{
	process::argument_list args;
	args.push_back(
		FCPPT_TEXT("unzip"));

	if (environment().password())
		fcppt::io::cerr << FCPPT_TEXT("You specified a password. Zip doesn't support passwords, however.\n");
	
	if (environment().keep_broken())
		fcppt::io::cerr << FCPPT_TEXT("You specified to keep broken files. Zip doesn't support this, however.\n");
	
	args.push_back(
		_p.string());
	
	if (environment().target_path())
	{
		args.push_back(
			FCPPT_TEXT("-d"));

		args.push_back(
			environment().target_path()->string());
	}
	
	/*
	fcppt::io::cerr << "Executing the following command:\n";
	for (process::argument_list::const_iterator i = args.begin(); i != args.end(); ++i)
		fcppt::io::cerr << *i << "\n";
		*/
	
	process::exec(
		args);
}

extract::file_sequence const
extract::plugins::zip::list(
	fcppt::filesystem::path const &,
	mime_type const &)
{
	return file_sequence();
}

#if 0
void
extract::plugins::zip::bomb(
	fcppt::filesystem::path const &_p)
{
	fcppt::string const output = 
		process::call(
			fcppt::assign::make_container<process::argument_list>
				(FCPPT_TEXT("unzip"))
				(FCPPT_TEXT("-l"))
				(_p.string()));
	
	fcppt::io::istringstream ss(
		output);
	
	fcppt::string line;
	std::getline(
		ss,
		line);
	
	if (ss.eof())
		throw fcppt::exception(
			FCPPT_TEXT("Expected two lines of \"dummy text\" from \"unzip\" command, got just one line"));

	std::getline(
		ss,
		line);
	
	if (ss.eof())
		throw fcppt::exception(
			FCPPT_TEXT("Expected two lines of \"dummy text\" from \"unzip\" command, got two lines, then nothing"));
	
	
}
#endif
