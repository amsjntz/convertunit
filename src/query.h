#include <bignum.h>

#include "units.h"

typedef enum {OK, FORMAT_ERROR, UNIT_ERROR} query_status_t;

typedef struct {
	query_status_t status;

	const unit_t* unit_from;
	const unit_t* unit_to;

	bignum_t* number;
} conversion_query_t;

conversion_query_t interpret_arguments(unsigned int input_amount, char** inputs);
