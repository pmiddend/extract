#include <extract/determine_mime_type.hpp>
#include <extract/process/call.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/filesystem/extension.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <fcppt/config/external_end.hpp>


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

bool
is_suffix(
	fcppt::string const &_suffix,
	fcppt::string const &_str)
{
	return
		_str.compare(
			static_cast<fcppt::string::size_type>(
				_str.size() -
				_suffix.length()),
			_suffix.size(),
			_suffix) == 0;
}
}

extract::mime_type const
extract::determine_mime_type(
	boost::filesystem::path const &_p)
{
	process::output const out =
		process::call(
			fcppt::assign::make_container<process::argument_list>
				(process::argument(fcppt::string(FCPPT_TEXT("file"))))
				(process::argument(fcppt::string(FCPPT_TEXT("-ib"))))
				(process::argument(fcppt::filesystem::path_to_string(_p.string()))));

	if (!out.err.empty())
		throw
			fcppt::exception(
				FCPPT_TEXT("\"file\" returned an error: ")+
				out.err);

	fcppt::string::size_type newline_position =
		out.out.find(
			FCPPT_TEXT('\n'));

	if(
		newline_position != static_cast<fcppt::string::size_type>(out.out.size()-1))
		throw fcppt::exception(
			FCPPT_TEXT("Expected a single line of output from \"file\" command, got the following: ")+
			boost::algorithm::replace_all_copy(
				out.out,
				fcppt::string(
					FCPPT_TEXT("\n")),
				fcppt::string(
					FCPPT_TEXT("\\n"))));

	fcppt::string const first_line =
		out.out.substr(
			0,
			newline_position);

	std::pair<fcppt::string,fcppt::string> const mime_pair =
		::split(
			first_line,
			FCPPT_TEXT(';'));

	if (mime_pair.second.empty())
		throw fcppt::exception(
			FCPPT_TEXT("Expected output in the format \"<mime>; <charset>\" from file, got: ")+first_line);

	if (mime_pair.first == FCPPT_TEXT("application/octet-stream"))
	{
		fcppt::string const e =
			fcppt::filesystem::extension(
				_p);

		return
			extract::mime_type(
				FCPPT_TEXT("fictional/")+e);
	}

	if (mime_pair.first == FCPPT_TEXT("application/x-bzip2"))
		return
			extract::mime_type(
				is_suffix(
					FCPPT_TEXT(".tar.bz2"),
					_p.string())
				?
					fcppt::string(
						FCPPT_TEXT("fictional/tarbz2"))
				:
					mime_pair.first);

	if (mime_pair.first == FCPPT_TEXT("application/x-gzip"))
		return
			extract::mime_type(
				is_suffix(
					FCPPT_TEXT(".tar.gz"),
					_p.string())
				?
					fcppt::string(FCPPT_TEXT("fictional/targz"))
				:
					mime_pair.first);

	if (mime_pair.first == FCPPT_TEXT("application/x-xz"))
		return
			extract::mime_type(
				is_suffix(
					FCPPT_TEXT(".tar.xz"),
					_p.string())
				?
					FCPPT_TEXT("fictional/tarxz")
				:
					mime_pair.first);

	return
		extract::mime_type(
			mime_pair.first);
}
