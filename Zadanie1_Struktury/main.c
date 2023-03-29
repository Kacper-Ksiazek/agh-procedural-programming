#include <stdlib.h>
#include <stdio.h>
#include "IntArray.h"
#include "Utils.h"




int main() {
	IntArray tab = create(10);

	fill(&tab);
	printf("\nPrzed sortowaniem:\n");
	printIntArray(&tab);

	sort(&tab);

	printf("Po sortowaniem:\n");
	printIntArray(&tab);

	printf("\nSuma jest rowna: %d\n", sum(&tab));
	printf("Min: %d\nMax: %d", getMin(&tab), getMax(&tab));

	return 0;
}