/* splitting this off into a separate file because GCC throws an impossible */
/* to suppress warning for each file that these definitons are included in */

#define VERYSMALL 100 			/* testing purposes only */
#define SMALL 16384 			/* 2^14 */
#define MEDIUM  262144			/* 2^18 */
#define LARGE  4194304			/* 2^22 */
#define XLARGE   67108864		  /* 2^26 */

#define ARRAY_SIZE 0

/* now we can compile bsort-small, bsort-large, etc by passing arguments */
/* to gcc */
#ifdef VERYSMALL_SIZE
#define ARRAY_SIZE VERYSMALL
#endif
#ifdef SMALL_SIZE
#define ARRAY_SIZE SMALL
#endif
#ifdef MEDIUM_SIZE
#define ARRAY_SIZE MEDIUM
#endif
#ifdef LARGE_SIZE 
#define ARRAY_SIZE LARGE
#endif
#ifdef XLARGE_SIZE 
#define ARRAY_SIZE XLARGE
#endif

#if !ARRAY_SIZE
#error You need to pass an array size to the compiler
#endif
