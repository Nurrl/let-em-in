#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	void *t;
	int curr;

	t = malloc(sizeof(*t));
	t = &1;
	curr = (int)t;
	printf("curr=%d\n", 1);
}
