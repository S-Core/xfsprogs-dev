# xfs_copy: copy/restore xfs filesystem to/from regular file
    
When copying to regular file, the length of the resulting file is equal to the size of the source filesystem. <br>
I added an option which store only the amount of space actually used in the source filesystem by the filesystem and the XFS log.

![](https://repository-images.githubusercontent.com/206241956/371a8c00-cff3-11e9-81f1-66098c314584)

## Usage
Copy xfs filesystem on /dev/sdd1 to regular file
as the amount used in filesystem.

```
$ xfs_copy -s /dev/sdd1 regular_file
```


Copy xfs filesystem to /dev/sdd1 from the regular file
which was copied using "xfs_copy -s"

```
$ xfs_copy -f regular_file /dev/sdd1
```
