#include "file_sequence_to_file_tree.hpp"
#include "split.hpp"
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

namespace
{
template
<
	typename T,
	typename Iterator,
	typename It2
>
Iterator const
find_child(
	Iterator it,
	It2 const end,
	T const &t)
{
	for (;it != end; ++it)
		if (it->value() == t)
			return it;
	return it;
}

void
analyze_part(
	extract::file_tree &_t,
	extract::file_sequence::const_reference r)
{
	extract::file_tree *t = 
		&_t;
	BOOST_FOREACH(
		fcppt::string const &p,
		extract::split(
			r,
			boost::algorithm::is_any_of(
				FCPPT_TEXT("/"))))
	{
		extract::file_tree::iterator i = 
			find_child(
				t->begin(),
				t->end(),
				p);

		if (i == t->end())
		{
			t->push_back(
				p);
			i = 
				--t->end();
		}

		t = &(*i);
	}
}
}

extract::file_tree const 
extract::file_sequence_to_file_tree(
	file_sequence const &_s,
	fcppt::string const &_root)
{
	file_tree t(
		_root);
	
	BOOST_FOREACH(
		file_sequence::const_reference r,
		_s)
		analyze_part(
			t,
			r);

	return t;
}
