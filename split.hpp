#ifndef EXTRACT_SPLIT_HPP_HPP_INCLUDED
#define EXTRACT_SPLIT_HPP_HPP_INCLUDED

#include <boost/algorithm/string/split.hpp>
#include <vector>

namespace extract
{
template
<
	typename Input,
	typename Functor
>
std::vector<Input> const
split(
	Input const &in,
	Functor f)
{
	std::vector<Input> out;
	return
		boost::algorithm::split(
			out,
			in,
			f);
}
}

#endif
