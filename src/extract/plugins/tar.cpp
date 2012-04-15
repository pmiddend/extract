#include <extract/is_runnable.hpp>
#include <extract/unlines.hpp>
#include <extract/plugins/tar.hpp>
#include <extract/process/call_safe.hpp>
#include <extract/process/exec.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem/operations.hpp>
#include <fcppt/config/external_end.hpp>


namespace
{
bool
is_prefix(
	fcppt::string const &_prefix,
	fcppt::string const &_str)
{
	return
		_str.compare(
			0,
			_prefix.size(),
			_prefix) == 0;
}
}

fcppt::string const extract::plugins::tar::command_name_(
	FCPPT_TEXT("tar"));

extract::plugins::tar::tar(
	extract::environment const &_env)
:
	base(
		fcppt::assign::make_container<mime_set>
			(FCPPT_TEXT("application/x-tar"))
			(FCPPT_TEXT("application/x-gzip"))
			(FCPPT_TEXT("fictional/targz"))
			(FCPPT_TEXT("fictional/tarxz"))
			(FCPPT_TEXT("fictional/tarbz2")),
		_env)
{
}

void
extract::plugins::tar::process(
	boost::filesystem::path const &_p,
	mime_type const &_m)
{
	process::argument_list args;
	args.push_back(
		command_name_);

	args.push_back(
		command_string(_m)+
		(environment().verbose() ? FCPPT_TEXT("v") : FCPPT_TEXT(""))+
		FCPPT_TEXT("xf"));

	if (environment().password())
		fcppt::io::cerr() << FCPPT_TEXT("You specified a password. tar doesn't support passwords, however.\n");

	if (environment().keep_broken())
		fcppt::io::cerr() << FCPPT_TEXT("You specified to keep broken files. tar doesn't support this, however.\n");

	args.push_back(
		_p.string());

	args.push_back(
		FCPPT_TEXT("-C"));

	boost::filesystem::path const real =
		real_target_path(_p,_m);

	args.push_back(
		real.string());

	if(
		boost::filesystem::exists(real) &&
		!boost::filesystem::is_directory(real))
		throw fcppt::exception(
			FCPPT_TEXT("Detected a tar bomb but directory")+
			real.string()+
			FCPPT_TEXT(" cannot be created"));

	if (!boost::filesystem::exists(real))
		boost::filesystem::create_directory(
			real);

	process::exec(
		args);
}

extract::file_sequence const
extract::plugins::tar::list(
	boost::filesystem::path const &_p,
	mime_type const &_m)
{
	process::output out =
		process::call_safe(
			fcppt::assign::make_container<process::argument_list>
				(command_name_)
				(command_string(_m)+FCPPT_TEXT("tf"))
				(_p.string()));

	// erase last newline
	out.out.erase(
		--out.out.end());

	return
		unlines(
			out.out);
}

bool
extract::plugins::tar::is_available()
{
	return
		is_runnable(
			command_name_);
}

fcppt::string const
extract::plugins::tar::command_string(
	mime_type const &_m)
{
	if (_m == FCPPT_TEXT("fictional/targz") || _m == FCPPT_TEXT("application/x-gzip"))
		return FCPPT_TEXT("z");
	if (_m == FCPPT_TEXT("fictional/tarbz2"))
		return FCPPT_TEXT("j");
	return FCPPT_TEXT("");
}
