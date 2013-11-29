
static inline unsigned long long get_ticks()
{
	unsigned long long ret;
	__asm__ __volatile__ ("rdtsc" : "=A" (ret));
	return ret;
}B
