#ifndef EXTRACT_ENVIRONMENT_HPP_HPP_INCLUDED
#define EXTRACT_ENVIRONMENT_HPP_HPP_INCLUDED

#include <fcppt/optional.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/string.hpp>
#include <boost/program_options.hpp>

namespace extract
{
class environment
{
public:
	environment(
		boost::program_options::options_description &,
		boost::program_options::variables_map &);

	fcppt::optional<fcppt::string> const
	password() const;

	bool 
	keep_broken() const;

	fcppt::optional<fcppt::filesystem::path> const
	target_path() const;

	bool
	verbose() const;
private:
	boost::program_options::variables_map &vm_;
};
}

#endif
