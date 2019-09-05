## xfs_copy: copy/restore xfs filesystem to/from regular file
    
When copying to regular file, the length of the resulting file is equal to the size of the source filesystem. <br>
I added an option which store only the amount of space actually used in the source filesystem by the filesystem and the XFS log.
    
$ xfs_copy -s /dev/sdd1 regular_file <br> 
copy xfs filesystem on /dev/sdd1 to regular file
as the amount used in fs.
    
$ xfs_copy -f regular_file /dev/sdd1 <br> 
copy xfs filesystem to /dev/sdd1 from regular file
which was copied using "xfs_copy -s"

![](https://repository-images.githubusercontent.com/206241956/371a8c00-cff3-11e9-81f1-66098c314584)
