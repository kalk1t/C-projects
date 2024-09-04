#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <io.h>


#pragma warning(disable:4996 6031)

struct World
{
	char name[100];
	char capital[100];
	char religion[100];
	char language[100];
	int space;
	int population;
};

int Countries_List(fname);
int Country_Search(fname);
int Country_Registration(fname);





int main(int argc, char* argv[])
{
	char fname[1024] = "Database";
	int OBJ;
	if (argc > 1)
		strcpy(fname, argv[1]);

	printf("Country DATABASE\n\n");
	printf("DB name :%s \n",fname); //db 
	A:
	printf("1-Registration\n"
		"2-Search\n"
		"3-List\n"
	"0-exit\n");
	scanf("%d", &OBJ);
	switch (OBJ)
	{
	case 1:
	{
		Country_Registration(fname);
	}
	break;
	case 2:
	{
		Country_Search(fname);
	}
	break;
	case 3:
	{
		Countries_List(fname);
	}
	break;
	case 0:
	{
		exit(0);
	}
	}
	char fname_1[100] = "";
	printf("\n\nADD New country\n\n\n");
		goto A;
	
		return 0;
}


int Country_Registration(fname)
{
	int CNTR = 0;
	struct World a;

	printf("\n\n\tCountry Registration: \n\n");
	printf("Country:");
	scanf("%s", a.name);

	printf("Capital:");
	scanf("%s", a.capital);

	printf("Religion:");
	scanf("%s", a.religion);

	printf("Language:");
	scanf("%s", a.language);

	printf("Space(km2):");
	scanf("%d", &a.space);

	printf("Population:");
	scanf("%d", &a.population);

	CNTR = open(fname, O_WRONLY | O_APPEND | O_CREAT, S_IWRITE);
	if (CNTR > 0)
	{
		write(CNTR, &a, sizeof(struct World));
		printf("\n%s %s %s %s %d %d", a.name,
			a.capital,
			a.religion,
			a.language,
			a.space,
			a.population);
		close(CNTR);
	}
	else
	{
		perror("open");
		return 0;
	}
}

//------

int Country_Search(fname)
{
	char Holder[1024] = "";
	int k = 0;
	printf("Search by: 1-Capital,2-Space,3-Religion,4-Language,5-Population,6-Any\n");
	scanf("\n%d", &k);

	printf("Searching Object :\n");
	scanf("\n%s", Holder);
	int SRCH;
	SRCH = open(fname, O_RDONLY, S_IREAD);
	if (SRCH > 0)
	{
		struct World a;
		while (eof(SRCH) == 0)
		{
			memset(&a, 0, sizeof(struct World));
			read(SRCH, &a, sizeof(struct World));

			switch (k)
			{
			case 1:
			{
				if (strstr(a.capital, Holder))
				{
					printf("\n%s %s %s %s %d %d", a.name,
						a.capital,
						a.religion,
						a.language,
						a.space,
						a.population);
				}

			}
			break;
			case 2:
			{
				int x = atoi(Holder);
				if (a.space == x)
				{
					printf("\n%s %s %s %s %d %d ", a.name,
						a.capital,
						a.religion,
						a.language,
						a.space,
						a.population);
				}

			}
			break;

			case 3:
			{
				if (strstr(a.religion, Holder))
				{
					printf("\n%s %s %s %s %d %d", a.name,
						a.capital,
						a.religion,
						a.language,
						a.space,
						a.population);
				}

			}
			break;
			case 4:
			{
				if (strstr(a.language, Holder))
				{
					printf("\n%s %s %s %s %d %d", a.name,
						a.capital,
						a.religion,
						a.language,
						a.space,
						a.population);
				}

			}
			break;
			case 5:
			{
				int x = atoi(Holder);
				if (a.population == x)
				{
					printf("\n%s %s %s %s %d %d", a.name,
						a.capital,
						a.religion,
						a.language,
						a.space,
						a.population);
				}

			}
			break;
			case 6:
			{
				int x = atoi;
				if (strstr(a.name, Holder) || a.space || a.population == x)
				{
					printf("\n%s %s %s %s %d %d", a.name,
						a.capital,
						a.religion,
						a.language,
						a.space,
						a.population);
				}
			}
			break;
			}



		}

		close(SRCH);

	}
	perror("\nOpen");
	return 0;
}

//----

int Countries_List(fname)
{
	int LIST = open(fname, O_RDONLY, S_IREAD);
	if (LIST > 0)
	{
		struct World a;
		while (eof(LIST) == 0)
		{
			read(LIST, &a, sizeof(struct World));
			printf("\n%s %s %s %s %d %d", a.name,
				a.capital,
				a.religion,
				a.language,
				a.space,
				a.population);


		}
		close(LIST);
	}
	else
	{
		perror("open");
		return 0;

	}



}
