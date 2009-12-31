#include "rar.hpp"
#include "../process/exec.hpp"
#include "../process/call.hpp"
#include "../file_sequence_to_file_tree.hpp"
#include "../bomb_directory.hpp"
#include <fcppt/assign/make_container.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/foreach.hpp>

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
	mime_type const &_m)
{
	process::argument_list args;
	args.push_back(
		command_name_);

	args.push_back(
		FCPPT_TEXT("x"));
	
	if (environment().password())
		args.push_back(
			FCPPT_TEXT("-p")+
			(*environment().password()));
	
	if (environment().keep_broken())
		args.push_back(
			FCPPT_TEXT("-kb"));
	
	args.push_back(
		_p.string());
	
	fcppt::filesystem::path target_path = 
		environment().target_path()
		?
			*environment().target_path()
		: 
			FCPPT_TEXT(".");
	
	if(
		file_sequence_to_file_tree(
			list(
				_p,
				_m),
			FCPPT_TEXT(".")).size() > 1)
	{
		target_path /= 
			bomb_directory(
				_p);
		fcppt::io::cerr << target_path.string() << "\n";
	}

	args.push_back(
		target_path.string()+FCPPT_TEXT("/")); // NOTE: There _has_ to be a trailing / so rar accepts it as a target directory
	
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
