#include "units.h"

#include <stdlib.h>
#include <stdbool.h>

#include <bignum.h>

bignum_t* convert_feet(bignum_t* input, bool inverse) {
	bignum_t* divisor = bignum_create_from_string("3.280839895013");

	bignum_t* result;
	if (inverse) { // meter -> feet
		result = bignum_multiply(input, divisor);
	} else { // feet -> meter
		result = bignum_divide(input, divisor, PRECISION);
	}

	bignum_cleanup(divisor);

	return result;
}

const unit_t* FOOT = &(unit_t) {
	.unit_class = DISTANCE_UNIT,
	.conversion_function = &convert_feet,
	.keywords = {"foot", "feet", "ft", NULL}
};

bignum_t* convert_inches(bignum_t* input, bool inverse) {
	bignum_t* divisor = bignum_create_from_string("0.0254");

	bignum_t* result;
	if (inverse) { // meters -> inches
		result = bignum_divide(input, divisor, PRECISION);
	} else { // inches -> meters
		result = bignum_multiply(input, divisor);
	}

	bignum_cleanup(divisor);

	return result;
}

const unit_t* INCH = &(unit_t) {
	.unit_class = DISTANCE_UNIT,
	.conversion_function = &convert_inches,
	.keywords = {"inch", "inches", "in", NULL}
};
