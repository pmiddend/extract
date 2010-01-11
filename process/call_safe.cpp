#include "call_safe.hpp"
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/lexical_cast.hpp>

extract::process::output const
extract::process::call_safe(
	argument_list const &_l)
{
	extract::process::output const out = 
		call(
			_l);
	
	if (out.exit_code)
		throw fcppt::exception(
			FCPPT_TEXT("The program ")+
			_l[0]+
			FCPPT_TEXT(" failed with exit code ")+
			fcppt::lexical_cast<fcppt::string>(
				out.exit_code)+
			FCPPT_TEXT(" and had this to say about it: \n")+
			out.err);
	
	return out;
}
