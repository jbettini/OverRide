int main(int argc, const char **argv, const char **envp)
{
	int x;

	puts("***********************************");
	puts("* \t     -Level00 -\t\t  *");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &x);
	if (x == 5276)
	{
		puts("\nAuthenticated!");
		system("/bin/sh");
		return 0;
	}
	puts("\nInvalid Password!");
	return 1;
}