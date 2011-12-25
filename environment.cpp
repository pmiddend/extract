#include "environment.hpp"

extract::environment::environment(
	boost::program_options::options_description &_options,
	boost::program_options::variables_map &_vm)
:
	vm_(
		_vm)
{
	_options.add_options()
		(
			"password,p",
			boost::program_options::value<fcppt::string>(),
			"Set a password for the archive")
		(
			"keep-broken,k",
			boost::program_options::value<bool>()->zero_tokens()->default_value(
				false),
			"Keep partially extracted (broken) files")
		(
			"verbose,v",
			boost::program_options::value<bool>()->zero_tokens()->default_value(
				false),
			"Verbose output")
		(
			"target-dir,t",
			boost::program_options::value<fcppt::string>(),
			"The directory where to extract the stuff");
}

fcppt::optional<fcppt::string> const
extract::environment::password() const
{
	return
		vm_.count("password")
		?
			fcppt::optional<fcppt::string>(
				vm_["password"].as<fcppt::string>())
		:
			fcppt::optional<fcppt::string>();
}

bool
extract::environment::keep_broken() const
{
	return
		vm_["keep-broken"].as<bool>();
}

fcppt::optional<fcppt::filesystem::path> const
extract::environment::target_path() const
{
	return
		vm_.count("target-dir")
		?
			fcppt::optional<fcppt::filesystem::path>(
				fcppt::filesystem::path(
					vm_["target-dir"].as<fcppt::string>()))
		:
			fcppt::optional<fcppt::filesystem::path>();
}

bool
extract::environment::verbose() const
{
	return
		vm_["verbose"].as<bool>();
}
