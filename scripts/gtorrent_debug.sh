# debug gTorrent using valgrind

function gtorrent_debug() {
	local options="--tool=memcheck --leak-check=yes"
	valgrind $options ./gTorrent $1 > valgrind_log.txt 2>&1
}

gtorrent_debug $1
