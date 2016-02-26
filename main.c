#include "./ft_ls.h"

int main(int argc, const char *argv[])
{
	DIR *rep = NULL;
	struct dirent *fichierlu = NULL;

	if ((rep = opendir("./")) == NULL)
	{
		perror("Error ");
		return(EXIT_FAILURE);
	}
	while((fichierlu = readdir(rep)) != NULL)
	{
		ft_putstr(fichierlu->d_name);
		RC;
	}

	if (closedir(rep) == -1)
	{
		perror("Error ");
		return(EXIT_FAILURE);
	}
	return 0;
}