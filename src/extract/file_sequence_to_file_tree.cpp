#include <extract/file_sequence_to_file_tree.hpp>
#include <extract/split.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/tree/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <fcppt/config/external_end.hpp>


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

// - Split the given file name at the path delimiters.
// - Use the resulting sequence to traverse the file tree.
// - Add new leaf to tree.
void
analyze_part(
	extract::file_tree &_tree,
	boost::filesystem::path const &current_file)
{
	extract::file_tree *current_tree_node =
		&_tree;

	for(
		boost::filesystem::path::const_iterator current_path_part =
			current_file.begin();
		current_path_part != current_file.end();
		++current_path_part)
	{
		extract::file_tree::iterator found_tree_node =
			find_child(
				current_tree_node->begin(),
				current_tree_node->end(),
				*current_path_part);

		if(found_tree_node == current_tree_node->end())
		{
			current_tree_node->push_back(
				*current_path_part);

			// This is safe, we just pushed back to the tree.
			found_tree_node =
				boost::prior(
					current_tree_node->end());
		}

		current_tree_node = &(*found_tree_node);
	}
}
}

void
extract::file_sequence_to_file_tree(
	extract::file_sequence const &_s,
	extract::file_tree & _ret)
{
	for(
		file_sequence::const_iterator current_file =
			_s.begin();
		current_file != _s.end();
		++current_file)
		::analyze_part(
			_ret,
			*current_file);
}
