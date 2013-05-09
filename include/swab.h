#ifndef SWAB_H
#define SWAB_H

/* casts are necessary for constants, because we never know how for sure
 * how U/UL/ULL map to __u16, __u32, __u64. At least not in a portable way.
 */
#define ___swab16(x) \
({ \
	__u16 __x = (x); \
	((__u16)( \
		(((__u16)(__x) & (__u16)0x00ffU) << 8) | \
		(((__u16)(__x) & (__u16)0xff00U) >> 8) )); \
})

#define ___swab32(x) \
({ \
	__u32 __x = (x); \
	((__u32)( \
		(((__u32)(__x) & (__u32)0x000000ffUL) << 24) | \
		(((__u32)(__x) & (__u32)0x0000ff00UL) <<  8) | \
		(((__u32)(__x) & (__u32)0x00ff0000UL) >>  8) | \
		(((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); \
})

#define ___swab64(x) \
({ \
	__u64 __x = (x); \
	((__u64)( \
		(__u64)(((__u64)(__x) & (__u64)0x00000000000000ffULL) << 56) | \
		(__u64)(((__u64)(__x) & (__u64)0x000000000000ff00ULL) << 40) | \
		(__u64)(((__u64)(__x) & (__u64)0x0000000000ff0000ULL) << 24) | \
		(__u64)(((__u64)(__x) & (__u64)0x00000000ff000000ULL) <<  8) | \
		(__u64)(((__u64)(__x) & (__u64)0x000000ff00000000ULL) >>  8) | \
		(__u64)(((__u64)(__x) & (__u64)0x0000ff0000000000ULL) >> 24) | \
		(__u64)(((__u64)(__x) & (__u64)0x00ff000000000000ULL) >> 40) | \
		(__u64)(((__u64)(__x) & (__u64)0xff00000000000000ULL) >> 56) )); \
})

#define ___constant_swab16(x) \
	((__u16)( \
		(((__u16)(x) & (__u16)0x00ffU) << 8) | \
		(((__u16)(x) & (__u16)0xff00U) >> 8) ))
#define ___constant_swab32(x) \
	((__u32)( \
		(((__u32)(x) & (__u32)0x000000ffUL) << 24) | \
		(((__u32)(x) & (__u32)0x0000ff00UL) <<  8) | \
		(((__u32)(x) & (__u32)0x00ff0000UL) >>  8) | \
		(((__u32)(x) & (__u32)0xff000000UL) >> 24) ))
#define ___constant_swab64(x) \
	((__u64)( \
		(__u64)(((__u64)(x) & (__u64)0x00000000000000ffULL) << 56) | \
		(__u64)(((__u64)(x) & (__u64)0x000000000000ff00ULL) << 40) | \
		(__u64)(((__u64)(x) & (__u64)0x0000000000ff0000ULL) << 24) | \
		(__u64)(((__u64)(x) & (__u64)0x00000000ff000000ULL) <<  8) | \
		(__u64)(((__u64)(x) & (__u64)0x000000ff00000000ULL) >>  8) | \
		(__u64)(((__u64)(x) & (__u64)0x0000ff0000000000ULL) >> 24) | \
		(__u64)(((__u64)(x) & (__u64)0x00ff000000000000ULL) >> 40) | \
		(__u64)(((__u64)(x) & (__u64)0xff00000000000000ULL) >> 56) ))

/*
 * provide defaults when no architecture-specific optimization is detected
 */
#ifndef __arch__swab16
#  define __arch__swab16(x) ({ __u16 __tmp = (x) ; ___swab16(__tmp); })
#endif
#ifndef __arch__swab32
#  define __arch__swab32(x) ({ __u32 __tmp = (x) ; ___swab32(__tmp); })
#endif
#ifndef __arch__swab64
#  define __arch__swab64(x) ({ __u64 __tmp = (x) ; ___swab64(__tmp); })
#endif

#ifndef __arch__swab16p
#  define __arch__swab16p(x) __arch__swab16(*(x))
#endif
#ifndef __arch__swab32p
#  define __arch__swab32p(x) __arch__swab32(*(x))
#endif
#ifndef __arch__swab64p
#  define __arch__swab64p(x) __arch__swab64(*(x))
#endif

#ifndef __arch__swab16s
#  define __arch__swab16s(x) do { *(x) = __arch__swab16p((x)); } while (0)
#endif
#ifndef __arch__swab32s
#  define __arch__swab32s(x) do { *(x) = __arch__swab32p((x)); } while (0)
#endif
#ifndef __arch__swab64s
#  define __arch__swab64s(x) do { *(x) = __arch__swab64p((x)); } while (0)
#endif


/*
 * Allow constant folding
 */
#  define __swab16(x) \
(__builtin_constant_p((__u16)(x)) ? \
 ___swab16((x)) : \
 __fswab16((x)))
#  define __swab32(x) \
(__builtin_constant_p((__u32)(x)) ? \
 ___swab32((x)) : \
 __fswab32((x)))
#  define __swab64(x) \
(__builtin_constant_p((__u64)(x)) ? \
 ___swab64((x)) : \
 __fswab64((x)))


static __inline__ __u16 __fswab16(__u16 x)
{
	return (__extension__ __arch__swab16(x));
}
static __inline__ __u16 __swab16p(__u16 *x)
{
	return (__extension__ __arch__swab16p(x));
}
static __inline__ void __swab16s(__u16 *addr)
{
	(__extension__ ({__arch__swab16s(addr);}));
}

static __inline__ __u32 __fswab32(__u32 x)
{
	return (__extension__ __arch__swab32(x));
}
static __inline__ __u32 __swab32p(__u32 *x)
{
	return (__extension__ __arch__swab32p(x));
}
static __inline__ void __swab32s(__u32 *addr)
{
	(__extension__ ({__arch__swab32s(addr);}));
}

static __inline__ __u64 __fswab64(__u64 x)
{
#  ifdef __SWAB_64_THRU_32__
	__u32 h = x >> 32;
	__u32 l = x & ((1ULL<<32)-1);
	return (((__u64)__swab32(l)) << 32) | ((__u64)(__swab32(h)));
#  else
	return (__extension__ __arch__swab64(x));
#  endif
}
static __inline__ __u64 __swab64p(__u64 *x)
{
	return (__extension__ __arch__swab64p(x));
}
static __inline__ void __swab64s(__u64 *addr)
{
	(__extension__ ({__arch__swab64s(addr);}));
}

static inline __uint16_t get_unaligned_be16(void *p)
{
	__uint8_t *__p = p;
	return __p[0] << 8 | __p[1];
}

static inline __uint32_t get_unaligned_be32(void *p)
{
	__uint8_t *__p = p;
        return __p[0] << 24 | __p[1] << 16 | __p[2] << 8 | __p[3];
}

static inline __uint64_t get_unaligned_be64(void *p)
{
	return (__uint64_t)get_unaligned_be32(p) << 32 |
			   get_unaligned_be32(p + 4);
}

static inline void put_unaligned_be16(__uint16_t val, void *p)
{
	__uint8_t *__p = p;
	*__p++ = val >> 8;
	*__p++ = val;
}

static inline void put_unaligned_be32(__uint32_t val, void *p)
{
	__uint8_t *__p = p;
	put_unaligned_be16(val >> 16, __p);
	put_unaligned_be16(val, __p + 2);
}

static inline void put_unaligned_be64(__uint64_t val, void *p)
{
	put_unaligned_be32(val >> 32, p);
	put_unaligned_be32(val, p + 4);
}

#endif /* SWAB_H */
