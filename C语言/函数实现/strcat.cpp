void my_strcat(char *ch1,char *ch2)//等价于strcat，把字符串2的值连接到字符串1
{
	int i = 0;
	while (ch1[i] != '\0')
	{
		i++;
	}
	int j = 0;
	while (ch2[j] !='\0')
	{
		ch1[i+j] = ch2[j];
		j++;
	}
}
