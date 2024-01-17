#include "units.h"

#include <stdlib.h>
#include <stdbool.h>

#include <bignum.h>

bignum_t* meters_to_meters(bignum_t* input, bool inverse) {
	(void) inverse;
	return bignum_copy(input);
}

const unit_t* METER = &(unit_t) {
	.unit_class = DISTANCE_UNIT,
	.conversion_function = &meters_to_meters,
	.keywords = {"meter", "meters", "m", NULL}
};

bignum_t* convert_centimeters(bignum_t* input, bool inverse) {
	bignum_t* factor = bignum_create_from_string("100");

	bignum_t* result;
	if (inverse) { // meters -> centimeters
		result = bignum_multiply(input, factor);
	} else { // centimeters -> meters
		result = bignum_divide(input, factor, PRECISION);
	}

	bignum_cleanup(factor);

	return result;
}

const unit_t* CENTIMETER = &(unit_t) {
	.unit_class = DISTANCE_UNIT,
	.conversion_function = &convert_centimeters,
	.keywords = {"centimeter", "centimeters", "cm", NULL}
};
