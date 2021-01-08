#include <stdio.h>

int main()
{
	int tab[5];
	int i;
	int temp;

	tab[0] = 2;
	tab[1] = 1;
	tab[2] = 5;
	tab[3] = 9;
	tab[4] = 8;


	i = 0;
	while (i < 5)
	{
		if (tab[i + 1] > tab[i])
		{
			temp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = temp;
			i = -1;
		}
		i++;
	}

	i = 0;
	while (tab[i++] < 5)
		printf("tab[i]: %d", tab[i]);
	return (0);
}