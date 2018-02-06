int raise (int signum)
{
  for(;;) ;
  return 0;
}

#ifndef COMPILER_HAS_MEMCPY
/*void *memcpy(void *dest, const void *src, size_t count) */
void *memcpy(void *dest, const void *src, unsigned int count)
{
  char *tmp = (char *) dest, *s = (char *) src;

  while (count--)
    *tmp++ = *s++;

  return dest;
}
#endif /* COMPILER_HAS_MEMCPY */
