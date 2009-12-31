#include "rar.hpp"
#include "../process/exec.hpp"
#include "../process/call.hpp"
#include <fcppt/assign/make_container.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

fcppt::string const extract::plugins::rar::command_name_(
	FCPPT_TEXT("rar"));

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
	fcppt::filesystem::path const &_p,
	mime_type const &)
{
	process::argument_list args;
	args.push_back(
		command_name_);

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
	
	process::exec(
		args);
}

extract::file_sequence const
extract::plugins::rar::list(
	fcppt::filesystem::path const &_p,
	mime_type const &)
{
	file_sequence s;
	fcppt::string result = 
		process::call(
			fcppt::assign::make_container<process::argument_list>
				(command_name_)
				(FCPPT_TEXT("vb"))
				(_p.string()));
	result.erase(
		--result.end());
	boost::algorithm::split(
		s,
		result,
		boost::algorithm::is_any_of(
			FCPPT_TEXT("\n")));
	return s;
}
