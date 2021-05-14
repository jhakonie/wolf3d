#include "wx_parse_xpm.h"

t_u64	wx_parse_xpm_hash_key(const t_c8 *key, t_u32 size)
{
	t_u64		hash;
	t_u32		i;
	const t_c8	*p;

	p = key;
	hash = FNV_OFFSET;
	i = 0;
	while (i < size)
	{
		hash ^= (t_u64)(unsigned char)(*p);
		hash *= FNV_PRIME;
		i++;
		p++;
	}
	return (hash);
}
