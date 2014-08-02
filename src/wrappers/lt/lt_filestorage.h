#ifndef LT_FILESTORAGE_H
#define LT_FILESTORAGE_H

struct file_storage;	// libtorrent::file_storage
typedef struct file_storage file_storage;

/* @lt_file_storage_create(): create a file_storage object */
file_storage	*lt_file_storage_create		(void);

#endif
