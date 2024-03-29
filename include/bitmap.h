// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2018 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#ifndef LIBFROG_BITMAP_H_
#define LIBFROG_BITMAP_H_

struct bitmap {
	pthread_mutex_t		bt_lock;
	struct avl64tree_desc	*bt_tree;
};

bool bitmap_init(struct bitmap **bmap);
void bitmap_free(struct bitmap **bmap);
bool bitmap_set(struct bitmap *bmap, uint64_t start, uint64_t length);
bool bitmap_iterate(struct bitmap *bmap,
		bool (*fn)(uint64_t, uint64_t, void *), void *arg);
bool bitmap_test(struct bitmap *bmap, uint64_t start,
		uint64_t len);
bool bitmap_empty(struct bitmap *bmap);
void bitmap_dump(struct bitmap *bmap);

#endif /* LIBFROG_BITMAP_H_ */
