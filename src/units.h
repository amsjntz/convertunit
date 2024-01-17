#include <bignum.h>

#include <stdbool.h>

#define PRECISION 5

#define MAX_KEYWORD_AMOUNT 5

typedef enum {DISTANCE_UNIT, TEMPERATURE_UNIT} unit_class_t;

typedef struct {
	unit_class_t unit_class;

	// this function always has to convert the unit to an intermediate unit.
	// for distances this would be meter for example.
	// inverse defines conversion direction. for example:
	// function converts cm -> m when inverse = false
	// 			converts m  -> cm when inverse = true
	bignum_t* (*conversion_function)(bignum_t* input, bool inverse);

	// first element is unit name singular, second plural
	const char* keywords[MAX_KEYWORD_AMOUNT]; // last element has to be NULL
} unit_t;

const unit_t* get_unit_by_keyword(const char* keyword);

bignum_t* convert_units(bignum_t* input, const unit_t* from, const unit_t* to);
