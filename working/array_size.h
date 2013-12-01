/* splitting this off into a separate file because GCC throws an impossible */
/* to suppress warning for each file that these definitons are included in */


/* now we can compile bsort-small, bsort-large, etc by passing arguments */
/* to gcc */
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
