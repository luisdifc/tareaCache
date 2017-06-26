#include <stdio.h>
#include <stdbool.h>

bool es_bisiesto (int year);

int main () {
	int year = 0;
	scanf ("%d", &year);

	if (es_bisiesto(year))
		printf("El año %d es bisiesto.\n", year);
	else 
		printf("El año %d NO es bisiesto.\n", year);
	return 0;
}

bool es_bisiesto (int year) {
	bool result = false;

	if ((year % 4 == 0 && year % 100 != 0) || (year %400 == 0))
		result = true;

	return result;
}
