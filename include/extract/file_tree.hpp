#ifndef EXTRACT_FILE_TREE_HPP_HPP_INCLUDED
#define EXTRACT_FILE_TREE_HPP_HPP_INCLUDED

#include <fcppt/container/tree/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace extract
{
typedef
fcppt::container::tree::object<boost::filesystem::path>
file_tree;
}

#endif
