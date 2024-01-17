#include "units.h"

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

extern const unit_t* METER;
extern const unit_t* CENTIMETER;
extern const unit_t* FOOT;
extern const unit_t* INCH;

bool strcmp_ignorecase(const char* a, const char* b) {
	for (unsigned int j = 0; a[j] != '\0'; j++) {
		if (b[j] == '\0' || tolower(a[j]) != tolower(b[j])) {
			return false;
		}
	}
	return true;
}

bool keyword_matches(const char* keyword, const unit_t* unit) {
	for (unsigned int i = 0; unit->keywords[i] != NULL; i++) {
		if (strcmp_ignorecase(keyword, unit->keywords[i])) {
			return true;
		}
	}
	return false;
}

const unit_t* get_unit_by_keyword(const char* keyword) {
	const unit_t* units[] = {METER, CENTIMETER, FOOT, INCH, NULL};
	for (unsigned int i = 0; units[i] != NULL; i++) {
		if (keyword_matches(keyword, units[i])) {
			return units[i];
		}
	}
	return NULL;
}

bignum_t* convert_units(bignum_t* input, const unit_t* from, const unit_t* to) {
	if (from->unit_class != to->unit_class) {
		return NULL;
	}

	bignum_t* intermediate_unit = from->conversion_function(input, false);
	bignum_t* target_unit = to->conversion_function(intermediate_unit, true);

	bignum_cleanup(intermediate_unit);

	return target_unit;
}
