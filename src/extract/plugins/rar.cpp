#include <extract/is_runnable.hpp>
#include <extract/unlines.hpp>
#include <extract/plugins/rar.hpp>
#include <extract/process/call_safe.hpp>
#include <extract/process/exec.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/foreach.hpp>
#include <boost/next_prior.hpp>
#include <fcppt/config/external_end.hpp>


extract::plugins::rar::rar(
	extract::environment const &_env)
:
	base(
		fcppt::assign::make_container<plugins::mime_set>
			(extract::mime_type(fcppt::string(FCPPT_TEXT("application/x-rar"))))
			(extract::mime_type(fcppt::string(FCPPT_TEXT("fictional/.rar")))),
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
	boost::filesystem::path const &_p,
	mime_type const &_m)
{
	process::argument_list args;
	args.push_back(
		process::argument(
			command_name_));

	args.push_back(
		process::argument(
			fcppt::string(
				FCPPT_TEXT("x"))));

	/*
	args.push_back(
		FCPPT_TEXT("-p-"));
		*/

	if (environment().password())
		args.push_back(
			process::argument(
				FCPPT_TEXT("-p")+
				(*environment().password())));

	if (environment().keep_broken())
		args.push_back(
			process::argument(
				fcppt::string(
				FCPPT_TEXT("-kb"))));

	if (!environment().verbose())
		args.push_back(
			process::argument(
				fcppt::string(
					FCPPT_TEXT("-idc"))));

	args.push_back(
		process::argument(
			_p.string()));

	args.push_back(
		process::argument(
			real_target_path(_p,_m).string()+FCPPT_TEXT("/"))); // NOTE: There _has_ to be a trailing / so rar accepts it as a target directory

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
	boost::filesystem::path const &_p,
	mime_type const &)
{
	process::argument_list args;
	args.push_back(
		process::argument(
			command_name_));
	args.push_back(
		process::argument(
			fcppt::string(
				FCPPT_TEXT("vb"))));
	if (environment().password())
		args.push_back(
			process::argument(
				FCPPT_TEXT("-p")+
				(*environment().password())));
	args.push_back(
		process::argument(
			_p.string()));

	process::output out =
		process::call_safe(
			args);
	if (!out.standard_error().empty())
		throw fcppt::exception(
			FCPPT_TEXT("The error stream contains the following (unexpected) data: ")+
			out.standard_error());
	// Why do we do that?
	if(!out.standard_output().empty())
		out.standard_output().erase(
			boost::prior(
				out.standard_output().end()));

	typedef
	std::vector<fcppt::string>
	line_sequence;

	line_sequence const lines(
		extract::unlines(
			out.standard_output()));

	extract::file_sequence result;
	for(line_sequence::const_iterator it = lines.begin(); it != lines.end(); ++it)
		result.push_back(
			boost::filesystem::path(
				*it));
	return
		result;
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
