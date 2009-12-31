#ifndef EXTRACT_FILE_SEQUENCE_TO_FILE_TREE_HPP_HPP_INCLUDED
#define EXTRACT_FILE_SEQUENCE_TO_FILE_TREE_HPP_HPP_INCLUDED

#include "file_sequence.hpp"
#include "file_tree.hpp"

namespace extract
{
file_tree const 
file_sequence_to_file_tree(
	file_sequence const &,
	fcppt::string const &root);
}

#endif
