/*  This file is part of The Firekylin Operating System.
 *
 *  Copyright 2016 Liuxiaofeng
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef _LOCALE_H
#define _LOCALE_H

enum {
	LC_CTYPE,
	LC_NUMERIC,
	LC_TIME,
	LC_COLLATE,
	LC_MONETARY,
	LC_MESSAGES,
	LC_ALL,
	LC_PAPER,
	LC_NAME,
	LC_ADDRESS,
	LC_TELEPHONE,
	LC_MEASUREMENT,
	LC_IDENTIFICATION,
};

/* Structure giving information about numeric and monetary notation.  */
struct lconv {
	/* Numeric (non-monetary) information.  */
	char *decimal_point;
	char *thousands_sep;
	/* Each element is the number of digits in each group;
	 elements with higher indices are farther left.
	 An element with value CHAR_MAX means that no further grouping is done.
	 An element with value 0 means that the previous element is used
	 for all groups farther left.  */
	char *grouping;

	/* Monetary information.  */

	/* First three chars are a currency symbol from ISO 4217.
	 Fourth char is the separator.  Fifth char is '\0'.  */
	char *int_curr_symbol;
	char *currency_symbol; /* Local currency symbol.  */
	char *mon_decimal_point; /* Decimal point character.  */
	char *mon_thousands_sep; /* Thousands separator.  */
	char *mon_grouping; /* Like `grouping' element (above).  */
	char *positive_sign; /* Sign for positive values.  */
	char *negative_sign; /* Sign for negative values.  */
	char int_frac_digits; /* Int'l fractional digits.  */
	char frac_digits; /* Local fractional digits.  */
	/* 1 if currency_symbol precedes a positive value, 0 if succeeds.  */
	char p_cs_precedes;
	/* 1 iff a space separates currency_symbol from a positive value.  */
	char p_sep_by_space;
	/* 1 if currency_symbol precedes a negative value, 0 if succeeds.  */
	char n_cs_precedes;
	/* 1 iff a space separates currency_symbol from a negative value.  */
	char n_sep_by_space;
	/* Positive and negative sign positions:
	 0 Parentheses surround the quantity and currency_symbol.
	 1 The sign string precedes the quantity and currency_symbol.
	 2 The sign string follows the quantity and currency_symbol.
	 3 The sign string immediately precedes the currency_symbol.
	 4 The sign string immediately follows the currency_symbol.  */
	char p_sign_posn;
	char n_sign_posn;
	/* 1 if int_curr_symbol precedes a positive value, 0 if succeeds.  */
	char int_p_cs_precedes;
	/* 1 iff a space separates int_curr_symbol from a positive value.  */
	char int_p_sep_by_space;
	/* 1 if int_curr_symbol precedes a negative value, 0 if succeeds.  */
	char int_n_cs_precedes;
	/* 1 iff a space separates int_curr_symbol from a negative value.  */
	char int_n_sep_by_space;
	/* Positive and negative sign positions:
	 0 Parentheses surround the quantity and int_curr_symbol.
	 1 The sign string precedes the quantity and int_curr_symbol.
	 2 The sign string follows the quantity and int_curr_symbol.
	 3 The sign string immediately precedes the int_curr_symbol.
	 4 The sign string immediately follows the int_curr_symbol.  */
	char int_p_sign_posn;
	char int_n_sign_posn;
};

extern char *setlocale(int category, const char *locale);
extern struct lconv * localeconv(void);

#endif
