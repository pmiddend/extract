#include "list_files.hpp"
#include "file_tree.hpp"
#include "file_sequence_to_file_tree.hpp"
#include <fcppt/io/cout.hpp>
#include <fcppt/text.hpp>

namespace
{
template<typename C,typename Stream>
void
output(
	Stream &s,
	C const &c,
	unsigned const indent)
{
	s
		<<
			fcppt::string(
				indent,
				FCPPT_TEXT('\t'))
		<<
			c.value()
		<<
			FCPPT_TEXT("\n");

	for(typename C::const_iterator i = c.begin(); i != c.end(); ++i)
		output(
			s,
			*i,
			static_cast<unsigned>(
				indent+1));
}
}

void
extract::list_files(
	plugins::base &_b,
	fcppt::filesystem::path const &_p,
	mime_type const &_m)
{
	file_tree tree(
		_p.string());

	file_sequence_to_file_tree(
		tree,
		_b.list(
			_p,
			_m));

	output(
		fcppt::io::cout,
		tree,
		0u);
}
