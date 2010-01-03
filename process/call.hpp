#ifndef EXTRACT_PROCESS_CALL_HPP_HPP_INCLUDED
#define EXTRACT_PROCESS_CALL_HPP_HPP_INCLUDED

#include "output.hpp"
#include "argument_list.hpp"
#include <fcppt/string.hpp>
#include <utility>

namespace extract
{
namespace process
{
output const
call(
	argument_list const &);
}
}

#endif
