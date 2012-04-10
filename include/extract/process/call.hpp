#ifndef EXTRACT_PROCESS_CALL_HPP_HPP_INCLUDED
#define EXTRACT_PROCESS_CALL_HPP_HPP_INCLUDED

#include <extract/process/argument_list.hpp>
#include <extract/process/output.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace extract
{
namespace process
{
process::output const
call(
	process::argument_list const &);
}
}

#endif
