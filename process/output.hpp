#ifndef EXTRACT_PROCESS_OUTPUT_HPP_HPP_INCLUDED
#define EXTRACT_PROCESS_OUTPUT_HPP_HPP_INCLUDED

#include <fcppt/string.hpp>

namespace extract
{
namespace process
{
class output
{
public:
	fcppt::string out,err;
	int exit_code;
};
}
}

#endif
