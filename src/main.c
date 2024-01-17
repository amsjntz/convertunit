#include <stdio.h>
#include <stdlib.h>

#include <bignum.h>

#include "units.h"

int main(int argc, char** argv) {
	bignum_t* input = bignum_create_from_string(argv[1]);

	const unit_t* from_unit = get_unit_by_keyword(argv[2]);
	const unit_t* to_unit = get_unit_by_keyword(argv[3]);

	printf("%s -> %s\n", from_unit->keywords[0], to_unit->keywords[0]);

	bignum_t* result = convert_units(input, from_unit, to_unit);

	char* resultstr = bignum_to_string(result);
	printf("%s\n", resultstr);

	free(resultstr);
	bignum_cleanup(result);
	
	return 0;
}
