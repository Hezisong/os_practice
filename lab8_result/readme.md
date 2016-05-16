参考了高博学长的做法，在kern/fs/file.c, kern/fs/sysfile.c, kern/fs/sfs/sfs_io.c, kern/fs/sfs/sfs_inode.c, kern/fs/devs/dev_disk0.c, kern/driver/ide.c中输出了调试信息，执行make qemu时得到如下调用顺序：

	sysfile_read
	file_read
	sfs_read
	sfs_io
	sfs_io_nolock
	sfs_rbuf
	sfs_rwblock_nolock
	disk0_io
	disk0_read_blks_nolock
	ide_read_secs