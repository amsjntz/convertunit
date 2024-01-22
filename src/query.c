#include <stdbool.h>
#include <stdlib.h>

#include "query.h"

typedef enum {START = 0, NUMBER = 1, UNIT1 = 2, FILLW_UNIT2 = 3, UNIT2 = 4, ERROR = 5} states_t;
typedef enum {I_NUMBER = 0, I_WORD = 1} inputs_t;

states_t next_state_lut[][2] = {
// INPUT:  num    word
		{NUMBER, ERROR},       // START
		{ ERROR, UNIT1},       // NUMBER
		{ ERROR, FILLW_UNIT2}, // UNIT1
		{ ERROR, UNIT2},       // FILLW_UNIT2
		{ ERROR, ERROR},       // UNIT2
		{ ERROR, ERROR}        // ERROR
};

bool is_number(char* in) {
	for (unsigned int i = 0; in[i] != '\0'; i++) {
		if (in[i] != '.' && (in[i] < '0' || in[i] > '9')) {
			return false;
		}
	}
	return true;
}

conversion_query_t interpret_arguments(unsigned int input_amount, char** inputs) {
	inputs_t tokens[input_amount];
	for (unsigned int i = 0; i < input_amount; i++) {
		if (is_number(inputs[i])) {
			tokens[i] = I_NUMBER;
		} else {
			tokens[i] = I_WORD;
		}
	}

	states_t current_state = START;
	for (unsigned int i = 0; i < input_amount; i++) {
		current_state = next_state_lut[current_state][tokens[i]];
	}

	conversion_query_t query;

	if (current_state == FILLW_UNIT2) {
		// input format matches <num> <unit> <unit>
		query.number = bignum_create_from_string(inputs[0]);
		query.unit_from = get_unit_by_keyword(inputs[1]);
		query.unit_to = get_unit_by_keyword(inputs[2]);
	} else if (current_state == UNIT2) {
		// input format matches <num> <unit> <fillword> <unit>
		query.number = bignum_create_from_string(inputs[0]);
		query.unit_from = get_unit_by_keyword(inputs[1]);
		query.unit_to = get_unit_by_keyword(inputs[3]);
	} else {
		// input format is invalid
		query.status = FORMAT_ERROR;
		return query;
	}

	if (query.unit_from == NULL || query.unit_to == NULL) {
		query.status = UNIT_ERROR;
	}

	return query;
}
