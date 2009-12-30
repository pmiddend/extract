#include "zip.hpp"
#include "../process/exec.hpp"
#include <fcppt/assign/make_container.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>

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
	fcppt::filesystem::path const &_p)
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
