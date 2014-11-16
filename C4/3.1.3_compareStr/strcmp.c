int strCmp(const char *str1, const char *str2)
{
	while (*str1 != '\0') {
		if (*str1 != *str2)
			return *str1 > *str2 ? 1 : -1;
		str1++;
		str2++;
	}
	return *str2 == '\0' ? 0 : -1;
}
