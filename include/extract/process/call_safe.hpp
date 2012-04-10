#ifndef EXTRACT_PROCESS_CALL_SAFE_HPP_HPP_INCLUDED
#define EXTRACT_PROCESS_CALL_SAFE_HPP_HPP_INCLUDED

#include <extract/process/call.hpp>

namespace extract
{
namespace process
{
process::output const
call_safe(
	process::argument_list const &);
}
}

#endif
