void my_strncpy(char* dest, const char* str, size_t n)
{
	while ((*dest++ = *str++) && --n);
}
