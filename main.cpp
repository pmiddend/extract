#include "determine_mime_type.hpp"
#include "environment.hpp"
#include <fcppt/io/cout.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/io/cerr.hpp>
#include <boost/program_options.hpp>
#include <cstdlib>
#include <iostream>

int main(
	int const _argc,
	char *_argv[])
try
{
	boost::program_options::options_description options;
	boost::program_options::positional_options_description positional;
	boost::program_options::variables_map vm;

	extract::environment env(
		options,
		vm);

	options.add_options()
		(
			"help",
			"Produce help message")
		(
			"input-file",
			boost::program_options::value<fcppt::string>(),
			"File to extract");

	positional.add(
		"input-file",
		-1);

	boost::program_options::store(
		boost::program_options::command_line_parser(
			_argc,
			_argv)
				.options(
					options)
				.positional(
					positional)
				.run(),
		vm);
	
	boost::program_options::notify(
		vm);

	if (vm.count("help"))
	{
		std::cout << options << "\n";
		return EXIT_SUCCESS;
	}

	fcppt::io::cerr << "Finished parsing, got the following input file: " << vm["input-file"].as<fcppt::string>() << "\n";
}
catch (boost::program_options::multiple_occurrences const &e)
{
	fcppt::io::cerr << FCPPT_TEXT("Please specify only _one_ input file\n");
	return EXIT_FAILURE;
}
catch (fcppt::exception const &e)
{
	fcppt::io::cerr << FCPPT_TEXT("Caught an exception: ") << e.string() << FCPPT_TEXT("\n");
	return EXIT_FAILURE;
}
