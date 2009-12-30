#include "determine_mime_type.hpp"
#include "process/call.hpp"
#include <fcppt/assign/make_container.hpp>
#include <fcppt/text.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/filesystem/extension.hpp>
#include <boost/algorithm/string/replace.hpp>

namespace
{
std::pair<fcppt::string,fcppt::string> const
split(
	fcppt::string const &s,
	fcppt::char_type const sep)
{
	std::pair<fcppt::string,fcppt::string> p;
	fcppt::string::size_type const sep_position = 
		s.find(
			sep);
	p.first = 
		s.substr(
			0,
			sep_position);
	
	if (sep_position != fcppt::string::npos)
		p.second = 
			s.substr(
				static_cast<fcppt::string::size_type>(
					sep_position + 1));

	return p;
}
}

extract::mime_type const
extract::determine_mime_type(
	fcppt::filesystem::path const &_p)
{
	fcppt::string const output =
		process::call(
			fcppt::assign::make_container<process::argument_list>
				(fcppt::string(FCPPT_TEXT("file")))
				(fcppt::string(FCPPT_TEXT("-ib")))
				(_p.string()));
	
	fcppt::string::size_type newline_position = 
		output.find(
			FCPPT_TEXT('\n'));
	
	if(
		newline_position != static_cast<fcppt::string::size_type>(output.size()-1))
		throw fcppt::exception(
			FCPPT_TEXT("Expected a single line of output from \"file\" command, got the following: ")+
			boost::algorithm::replace_all_copy(
				output,
				fcppt::string(
					FCPPT_TEXT("\n")),
				fcppt::string(
					FCPPT_TEXT("\\n"))));
	
	fcppt::string const first_line = 
		output.substr(
			0,
			newline_position);

	std::pair<fcppt::string,fcppt::string> const mime_pair = 
		split(
			first_line,
			FCPPT_TEXT(';'));
	
	if (mime_pair.second.empty())
		throw fcppt::exception(
			FCPPT_TEXT("Expected output in the format \"<mime>; <charset>\" from file, got: ")+first_line);

	if (mime_pair.first != FCPPT_TEXT("application/octet-stream"))
		return mime_pair.first;

	fcppt::string const e = 
		fcppt::filesystem::extension(
			_p);

	return e;
}
