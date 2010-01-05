#include "determine_mime_type.hpp"
#include "environment.hpp"
#include "list_files.hpp"
#include "plugin_types.hpp"
#include <fcppt/io/cout.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/filesystem/exists.hpp>
#include <fcppt/filesystem/is_regular.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/mpl/for_each.hpp>
#include <fcppt/io/cerr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include <cstdlib>
#include <iostream>

namespace
{
typedef
boost::ptr_vector
<
	extract::plugins::base
>
plugin_sequence;

class plugin_adder
{
public:
	typedef void result_type;

	plugin_adder(
		plugin_sequence &_plugs,
		extract::environment &_env)
	:
		plugs_(
			_plugs),
		env_(
			_env)
	{
	}
	
	template<typename T>
	result_type
	operator()() const
	{
		if (T::is_available())
			plugs_.push_back(
				new T(
					env_));
	}
private:
	plugin_sequence &plugs_;
	extract::environment &env_;
};

}

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
			"list,l",
			boost::program_options::value<bool>()->zero_tokens()->default_value(
				false),
			"List contents instead of extracting the files")
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

	if (vm.count("help") || !vm.count("input-file"))
	{
		std::cout << options << "\n";
		return EXIT_SUCCESS;
	}

	fcppt::filesystem::path const p = 
		vm["input-file"].as<fcppt::string>();
	
	if (!fcppt::filesystem::exists(p))
	{
		fcppt::io::cerr << FCPPT_TEXT("The specified file \"") << p << FCPPT_TEXT("\" doesn't exist!\n");
		return EXIT_FAILURE;
	}

	if (!fcppt::filesystem::is_regular(p))
	{
		fcppt::io::cerr << FCPPT_TEXT("The specified file \"") << p << FCPPT_TEXT("\" is not a regular file!\n");
		return EXIT_FAILURE;
	}
	
	extract::mime_type const m = 
		extract::determine_mime_type(
			p);
	
	plugin_sequence plugs;

	fcppt::mpl::for_each<extract::plugin_types>(
		plugin_adder(
			plugs,
			env));
	
	plugin_sequence::iterator i = 
		plugs.end();
	for (i = plugs.begin(); i != plugs.end(); ++i)
		if (i->mimes().find(m) != i->mimes().end())
			break;
	
	if (i == plugs.end())
	{
		fcppt::io::cerr 
			<< FCPPT_TEXT("There was no matching extract plugin for file ") 
			<< p 
			<< FCPPT_TEXT(" which has mime type: ") 
			<< m
			<< FCPPT_TEXT("\n");
		return EXIT_FAILURE;
	}

	if (vm["list"].as<bool>())
		extract::list_files(
			*i,
			p,
			m);
	else
		i->process(
			p,
			m);
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
