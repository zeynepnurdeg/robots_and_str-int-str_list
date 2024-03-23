#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define INITIAL_SIZE 30

typedef struct {
	char name[INITIAL_SIZE];
	int year;
	char inventor[INITIAL_SIZE];
}info_t;

int readFromFile(info_t* arr) {
	FILE* inp;
	inp = fopen("robots.txt", "r");
	int i = 0, r, len;
	if (inp == NULL)
		printf("ERROR");
	else {
		while (fscanf(inp, " %[^0-9]%d %[^\n]", arr[i].name, &arr[i].year, arr[i].inventor) != EOF)
			i++;
		fclose(inp);

		for (r = 0; r < i; r++) {
			len = strlen(arr[r].name);
			arr[r].name[len - 1] = '\0';
		}
	}
	return (i);
}

void swap(info_t* x, info_t* y) {
	info_t temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void recBubbleSort(info_t* arr, int size) {
	int k, pass = 1, sorted = 1;
	for (k = 0; k < size; k++)
		if (strcmp(arr[k].name, arr[k + 1].name) > 0)
		{
			swap(&arr[k], &arr[k + 1]);
			sorted = 0;
		}
	if (!sorted)
		recBubbleSort(arr, size);
}

int recBinarySearch(info_t* arr, int top, int bottom, char* key) {
	int mid;
	if (top > bottom)
		return (-1);
	else
	{
		mid = (top + bottom) / 2;
		if (strcmp(arr[mid].name, key) == 0)
			return (mid);
		else if (strcmp(arr[mid].name, key) > 0)
			return (recBinarySearch(arr, top, mid - 1, key));
		else
			return (recBinarySearch(arr, mid + 1, bottom, key));
	}
}

void display(info_t* arr, int size) {
	int i, j;
	printf("Robot Name                         DATE     Inventor\n");
	printf("*********************************************************************************************\n");
	for (i = 0; i < size; i++) {
		printf(" %-25s       %6d     %-28s\n", arr[i].name, arr[i].year, arr[i].inventor);
	}
	printf("\n");
}

int main(void)
{
	info_t arr[INITIAL_SIZE];
	int size = readFromFile(arr);
	recBubbleSort(arr, size);
	display(arr, size);

	char key[INITIAL_SIZE];
	printf("Please enter a robot name to search : ");
	scanf(" %s", key);

	int index;
	index = recBinarySearch(arr, 0, size - 1, key);

	if (index != -1)
		printf("%s is the %d. number on the list\n", key, index + 1);
	else
		printf("%s is NOT on the list\n", key);

	return 0;
}