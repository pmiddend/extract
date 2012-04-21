#ifndef EXTRACT_FILE_SEQUENCE_HPP_HPP_INCLUDED
#define EXTRACT_FILE_SEQUENCE_HPP_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace extract
{
typedef
std::vector<boost::filesystem::path>
file_sequence;
}

#endif
