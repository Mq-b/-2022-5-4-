int my_strlen1(char* ch)
{
	char* temp = ch;
	while (*temp != '\0')temp++;
	return temp - ch;
}
