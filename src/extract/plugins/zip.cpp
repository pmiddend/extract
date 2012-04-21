#include <extract/is_runnable.hpp>
#include <extract/plugins/zip.hpp>
#include <extract/process/call_safe.hpp>
#include <extract/process/exec.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/extract_from_string_exn.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/foreach.hpp>
#include <boost/next_prior.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <fcppt/config/external_end.hpp>


namespace
{
typedef
std::pair
<
	fcppt::string::size_type,
	fcppt::string::size_type
>
index_pair;

index_pair const
extract_name(
	fcppt::string const first_line,
	fcppt::string const second_line)
{
	/*
		if (second_line.size() != first_line.size())
			throw fcppt::exception(
				FCPPT_TEXT("The first line of output should have the same number of characters as the second line, this is not the case: \"")+first_line+FCPPT_TEXT("\" vs. \"")+second_line+FCPPT_TEXT("\""));
				*/

		if (second_line.find_first_not_of(FCPPT_TEXT("- ")) != fcppt::string::npos)
			throw fcppt::exception(
				FCPPT_TEXT("The second line of output (specifying the column widths) should only contain '-' and ' ' characters. There were other characters, too: ")+second_line);

		if (second_line[0] != FCPPT_TEXT('-'))
			throw fcppt::exception(
				FCPPT_TEXT("The second line of output (specifying the column widths) should start with a '-', it doesn't, however: ")+second_line);

	index_pair name_column(
		fcppt::string::npos,
		fcppt::string::npos);

	for(
		fcppt::string::size_type i =
			static_cast<fcppt::string::size_type>(
				0);
		i < second_line.size();)
	{
		fcppt::string::size_type const
			space_begin =
				second_line.find(
					FCPPT_TEXT(' '),
					i);

		index_pair indices(
			i,
			space_begin == fcppt::string::npos
			?
				second_line.size()
			:
				space_begin);

		if(
			boost::algorithm::trim_copy(
				first_line.substr(
					indices.first,
					indices.second-indices.first)) ==
			FCPPT_TEXT("Name"))
		{
			name_column = indices;
			break;
		}

		if (space_begin == fcppt::string::npos)
			break;

		fcppt::string::size_type const
			space_end =
				second_line.find(
					FCPPT_TEXT('-'),
					space_begin);

		if (space_end == fcppt::string::npos)
			throw fcppt::exception(
				FCPPT_TEXT("The second line should contain a proper sequence of '-' and ' '. This is not the case: ")+second_line);

		i = space_end;
	}

	if (name_column.first == fcppt::string::npos || name_column.second == fcppt::string::npos)
		throw fcppt::exception(
			FCPPT_TEXT("Found no column containing \"Name\" in first line: ")+first_line);

	return
		name_column;
}
}

fcppt::string const extract::plugins::zip::command_name_(
	FCPPT_TEXT("unzip"));

extract::plugins::zip::zip(
	extract::environment const &_env)
:
	base(
		fcppt::assign::make_container<mime_set>
			(extract::mime_type(fcppt::string(FCPPT_TEXT("application/zip"))))
			(extract::mime_type(fcppt::string(FCPPT_TEXT("fictional/.zip")))),
		_env)
{

}

void
extract::plugins::zip::process(
	boost::filesystem::path const &_p,
	mime_type const &_m)
{
	process::argument_list args;
	args.push_back(
		process::argument(
			command_name_));

	if (environment().password())
	{
		args.push_back(
			process::argument(
				fcppt::string(
					FCPPT_TEXT("-P"))));
		args.push_back(
			process::argument(
				*environment().password()));
		fcppt::io::cerr() << FCPPT_TEXT("You specified a password. Zip doesn't support passwords, however.\n");
	}

	if (environment().keep_broken())
		fcppt::io::cerr() << FCPPT_TEXT("You specified to keep broken files. Zip doesn't support this, however.\n");

	if (!environment().verbose())
		args.push_back(
			process::argument(
				fcppt::string(
					FCPPT_TEXT("-qq"))));

	args.push_back(
		process::argument(
			_p.string()));

	args.push_back(
		process::argument(
			fcppt::string(
				FCPPT_TEXT("-d"))));

	args.push_back(
		process::argument(
			real_target_path(
				_p,
				_m).string()));

	process::exec(
		args);
}

extract::file_sequence const
extract::plugins::zip::list(
	boost::filesystem::path const &_p,
	mime_type const &)
{
	process::output const out =
		process::call_safe(
			fcppt::assign::make_container<process::argument_list>
				(process::argument(command_name_))
				(process::argument(fcppt::string(FCPPT_TEXT("-l"))))
				(process::argument(fcppt::string(FCPPT_TEXT("-q"))))
				(process::argument(_p.string())));

	if (!out.err.empty())
		throw fcppt::exception(
			FCPPT_TEXT("zip command got the following error: ")+
			out.err);

	fcppt::io::istringstream ss(
		out.out);

	fcppt::string first_line,second_line;

// Why is this here?
#if 0
	if(
		!std::getline(
			ss,
			first_line))
		throw fcppt::exception(
			FCPPT_TEXT("Expected at least three lines of output from unzip command, got only one: ")+
			first_line);
#endif

	if(
		!std::getline(
			ss,
			first_line))
		throw fcppt::exception(
			FCPPT_TEXT("Expected at least three lines of output from unzip command, got only two"));

	std::getline(
		ss,
		second_line);

	index_pair const name_column =
		extract_name(
			first_line,
			second_line);

	typedef
	std::vector<fcppt::string>
	string_sequence;

	string_sequence files;
	fcppt::string line;
	while(
		std::getline(
			ss,
			line))
		files.push_back(
			line.substr(
				name_column.first));

	if (boost::prior(files.end(),2)->find_first_not_of("-") != fcppt::string::npos)
		throw fcppt::exception(
			FCPPT_TEXT("Expected the second last line of \"unzip\" output to consist only of '-'. This is not the case, however: ")+
			(*boost::prior(files.end(),2))+
			FCPPT_TEXT(", last line was: ")+(*--files.end()));

	if(
		files.back().find(FCPPT_TEXT("file")) ==
			fcppt::string::npos ||
		files.back().find(FCPPT_TEXT("file")) ==
			static_cast<fcppt::string::size_type>(
				0))
		throw fcppt::exception(
			FCPPT_TEXT("Expected the last line of \"unzip\" output to be of the form \"<number> files\", this is not the case: ")+files.back());

	fcppt::extract_from_string_exn<fcppt::string::size_type>(
		files.back().substr(
			static_cast<fcppt::string::size_type>(
				0),
			static_cast<fcppt::string::size_type>(
				files.back().find("file")-1)));

	files.erase(
		boost::prior(
			files.end(),
			2),
		files.end());

	extract::file_sequence result;
	for(string_sequence::const_iterator it = files.begin(); it != files.end(); ++it)
		result.push_back(
			boost::filesystem::path(
				*it));
	return
		result;
}

bool
extract::plugins::zip::is_available()
{
	return
		is_runnable(
			command_name_);
}
