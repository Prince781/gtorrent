#include "lt_deps.hpp"

extern "C" {

#include "lt_filestorage.h"

file_storage *lt_file_storage_create(void) {
	return reinterpret_cast<file_storage*>(new libtorrent::file_storage());
}

}
