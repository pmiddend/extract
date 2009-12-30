#include "rar.hpp"
#include "../process/exec.hpp"
#include <fcppt/assign/make_container.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>

extract::plugins::rar::rar(
	extract::environment const &_env)
:
	base(
		fcppt::assign::make_container<mime_set>
			(fcppt::string(FCPPT_TEXT("application/x-rar"))),
		_env)
{
	
}

void
extract::plugins::rar::process(
	fcppt::filesystem::path const &_p)
{
	process::argument_list args;
	args.push_back(
		FCPPT_TEXT("rar"));

	args.push_back(
		FCPPT_TEXT("e"));
	
	if (environment().password())
		args.push_back(
			FCPPT_TEXT("-p")+
			(*environment().password()));
	
	if (environment().keep_broken())
		args.push_back(
			FCPPT_TEXT("-kb"));
	
	args.push_back(
		_p.string());
	
	if (environment().target_path())
		args.push_back(
			environment().target_path()->string());
	
	/*
	fcppt::io::cerr << "Executing the following command:\n";
	for (process::argument_list::const_iterator i = args.begin(); i != args.end(); ++i)
		fcppt::io::cerr << *i << "\n";
		*/
	
	process::exec(
		args);
}
