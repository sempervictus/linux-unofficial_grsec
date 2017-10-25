#ifndef _SCST_BACKPORT_H_
#define _SCST_BACKPORT_H_

/*
 *  Copyright (C) 2015 -2016 SanDisk Corporation
 *
 *  Backports of functions introduced in recent kernel versions.
 *
 *  Please keep the functions in this file sorted according to the name of the
 *  header file in which these have been defined.
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation, version 2
 *  of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 */

#include <linux/blkdev.h>	/* struct request_queue */
#include <linux/scatterlist.h>	/* struct scatterlist */
#include <linux/slab.h>		/* kmalloc() */
#include <linux/version.h>
#include <linux/writeback.h>	/* sync_page_range() */
#include <scsi/scsi_cmnd.h>	/* struct scsi_cmnd */
#include <rdma/ib_verbs.h>

/* <asm-generic/barrier.h> */

#define smp_mb__after_atomic_inc smp_mb__after_atomic
#define smp_mb__after_clear_bit smp_mb__after_atomic
#define smp_mb__before_atomic_dec smp_mb__before_atomic
#define smp_mb__after_atomic_dec smp_mb__after_atomic

/* <asm-generic/fcntl.h> */

/* <linux/blkdev.h> */

/* <linux/compiler.h> */

/* <linux/cpumask.h> */

/* <linux/dlm.h> */

/* See also commit 0f8e0d9a317406612700426fad3efab0b7bbc467 */

/* <linux/fs.h> */

/* <linux/kernel.h> */

/*
 * See also commit 33ee3b2e2eb9. That commit was introduced in kernel v2.6.39
 * and later backported to kernel v2.6.38.4.
 */

/* <linux/kmod.h> */

/* <linux/kref.h> */

/* See also commit 2c935bc57221 */
#define kref_read(kref) (atomic_read(&(kref)->refcount))

/* <linux/kthread.h> */

/* See also commit 207205a2ba26 */

/* <linux/ktime.h> */

/* <linux/list.h> */

#ifndef __list_for_each
/* ToDo: cleanup when both are the same for all relevant kernels */
#define __list_for_each list_for_each
#endif

/*
 * Returns true if entry is in its list. Entry must be deleted from the
 * list by using list_del_init()!
 */
static inline bool list_entry_in_list(const struct list_head *entry)
{
	return !list_empty(entry);
}

/* <linux/lockdep.h> */

/* <linux/kernel.h> */

/* <linux/preempt.h> */

/* <linux/printk.h> */

/* <linux/ratelimit.h> */

/* <linux/rcupdate.h> */

/* See also commit b62730baea32 */

/* <rdma/ib_verbs.h> */
/* commit ed082d36 */
#ifndef ib_alloc_pd
static inline struct ib_pd *ib_alloc_pd_backport(struct ib_device *device)
{
	return ib_alloc_pd(device);
}
#define ib_alloc_pd(device, flags)				\
	({							\
		(void)(flags), ib_alloc_pd_backport(device);	\
	})
#endif

/* <linux/sched.h> */

/* <linux/scatterlist.h> */

/* <linux/slab.h> */

/* <linux/t10-pi.h> */

/* <linux/types.h> */

/* <linux/vmalloc.h> */

/* <linux/unaligned.h> */

/* <scsi/scsi_cmnd.h> */

#endif /* _SCST_BACKPORT_H_ */
