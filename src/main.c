#include <stdio.h>
#include <stdlib.h>

#include <bignum.h>

#include "units.h"
#include "query.h"

int main(int argc, char** argv) {
	conversion_query_t query = interpret_arguments(argc - 1, argv + 1);

	if (query.status == FORMAT_ERROR) {
		printf("wrong format :(\n");
		return -1;
	} else if (query.status == UNIT_ERROR) {
		printf("unsupported unit :(\n");
		return -1;
	}

	bignum_t* result = convert_units(query.number, query.unit_from, query.unit_to);

	bignum_t* one = bignum_create_from_string("1");
	bool input_plural = bignum_unsigned_compare(query.number, one) == BIGNUM_GT;
	bool result_plural = bignum_unsigned_compare(result, one) == BIGNUM_GT;

	bignum_cleanup(one);

	const char* name_from_unit = get_unit_name(query.unit_from, input_plural);
	const char* name_to_unit = get_unit_name(query.unit_to, result_plural);
	char* resultstr = bignum_to_string(result);
	printf("%s %s is %s %s\n", argv[1], name_from_unit, resultstr, name_to_unit);

	free(resultstr);
	bignum_cleanup(result);
	
	return 0;
}
