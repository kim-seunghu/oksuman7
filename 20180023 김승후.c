#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Text_info count_File(FILE*);
void reverse_case(FILE*);
int find_space(char *);

struct Text_info
{
	int cnt_Line;
	int cnt_Word;
	int cnt_Character;
};

int main(int argc, char *argv[])
{
	int cnt_Line = 0;
	int cnt_Word = 0;
	int cnt_Character = 0;

	FILE *fp = NULL;

	fp = fopen(argv[1], "r");

	if (fp == NULL)
	{
		printf("파일을 열 수 없습니다");
		exit(1);
	}
	else
	{
		struct Text_info abc = count_File(fp);



		printf("<Count Result>\n");
		int cnt_Line;
		printf("%-20s%5d\n", "Line count", abc.cnt_Line);
		printf("%-20s%5d\n", "Word count", abc.cnt_Word);
		printf("%-20s%5d\n", "Character count", abc.cnt_Character);
		fseek(fp, 0, SEEK_SET);
		printf("\n");
		reverse_case(fp);
		fclose(fp);
		
	}
}

struct Text_info count_File(FILE* fp)
{
	struct Text_info result;


	result.cnt_Line = 0;
	result.cnt_Word = 0;
	result.cnt_Character = 0;

	char temp[300];

	while (!feof(fp))
	{
		fgets(temp, 300, fp);
		result.cnt_Line++;
		result.cnt_Word += find_space(temp);
		result.cnt_Character += strlen(temp) - find_space(temp);
	}
	return result;
}

int find_space(char *str)
{
	int i = 0;
	int cnt = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' && str[i + 1] != ' ')
		{
			cnt++;
			i++;
		}
		else
			i++;
	}
	return cnt;
}

void reverse_case(FILE* fp)
{
	int i;
	int size;
	char temp[300];

	FILE* rev = NULL;
	rev = fopen("infile.rev", "w");
	if (rev == NULL)
	{
		printf("파일을 생성할 수 없습니다");
		exit(1);
	}

	while (!feof(fp))
	{
		fgets(temp, 300, fp);
		size = strlen(temp);

		for (i = 0; i < size; i++)
		{
			if (temp[i] >= 65 && temp[i] <= 90)
			{
				temp[i] += 32;
			}
			else if (temp[i] >= 97 && temp[i] <= 122)
			{
				temp[i] -= 32;
			}
			else
				continue;
		}
		fputs(temp, rev);
	}
	printf("File saved in infile.rev\n");
	fclose(rev);
}