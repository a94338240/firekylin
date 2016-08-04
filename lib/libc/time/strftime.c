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

#include <time.h>
static const char   sweekdays [7] [4] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};
static const char   weekdays [7] [10] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};
static const char   smonths [12] [4] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
static const char*  months [12] = {
    "January", "February", "March", "April", smonths[5-1], "June",
    "July", "August", "September", "October", "November", "December"
};
static const char   ampm [4] [3] = {
    "am", "pm",
    "AM", "PM"
};

static int  i2a ( char* dest,unsigned int x )
{
    int  div = 10;
    *dest++ = x/div + '0';
    *dest++ = x%div + '0';
    *dest++ = '\0';
    return 2;
}

size_t strftime(char *buf, size_t size, const char *fmt, struct tm *tmptr)
{
    char*         p = buf;
    const char*   src;
    unsigned int  no;
    char          tbuf [5];


    for ( ; *fmt != '\0'; fmt++ ) {
	if (*fmt == '%') {
	    if (*++fmt == '%') {
	        *p++ = '%';
	    }
	    else
again:
    	    switch (*fmt) {
//          case '%': *p++ = '%';  				 break;			// reduce size of jump table
            case 'n': *p++ = '\n'; 				 break;
            case 't': *p++ = '\t'; 				 break;
	    case 'O': case 'E': ++fmt; goto again;
            case 'c': src = "%b %a %d %k:%M:%S %Z %Y";        	 goto _strf;
            case 'r': src = "%I:%M:%S %p";                    	 goto _strf;
            case 'R': src = "%H:%M";      			 goto _strf;
            case 'x': src = "%b %a %d";   			 goto _strf;
            case 'X': src = "%k:%M:%S";   			 goto _strf;
            case 'D': src = "%m/%d/%y";   			 goto _strf;
            case 'T': src = "%H:%M:%S";
               _strf: p  += strftime (p, (size_t)(buf+size-p), src, tmptr); 	 break;
            case 'a': src = sweekdays [tmptr->tm_wday]; 		 goto _str;
            case 'A': src = weekdays  [tmptr->tm_wday]; 		 goto _str;
            case 'h':
            case 'b': src = smonths   [tmptr->tm_mon];  		 goto _str;
            case 'B': src = months    [tmptr->tm_mon];  		 goto _str;
            case 'p': src = ampm [tmptr->tm_hour > 12 ? 3 : 2]; goto _str;
            case 'P': src = ampm [tmptr->tm_hour > 12 ? 1 : 0]; goto _str;
            case 'C': no  = tmptr->tm_year/100 + 19; 		 goto _no;
            case 'd': no  = tmptr->tm_mday;          		 goto _no;
            case 'e': no  = tmptr->tm_mday;          		 goto _nos;
            case 'H': no  = tmptr->tm_hour;          		 goto _no;
            case 'I': no  = tmptr->tm_hour % 12;     		 goto _no;
            case 'j': no  = tmptr->tm_yday;          		 goto _no;
            case 'k': no  = tmptr->tm_hour;          		 goto _nos;
            case 'l': no  = tmptr->tm_hour % 12;     		 goto _nos;
            case 'm': no  = tmptr->tm_mon + 1;         		 goto _no;
            case 'M': no  = tmptr->tm_min;           		 goto _no;
            case 'S': no  = tmptr->tm_sec;           		 goto _no;
            case 'u': no  = tmptr->tm_wday ? tmptr->tm_wday : 7; 	 goto _no;
            case 'w': no  = tmptr->tm_wday;              		 goto _no;
	    case 'U': no  = (tmptr->tm_yday - tmptr->tm_wday + 7) / 7; goto _no;
	    case 'W': no  = (tmptr->tm_yday - (tmptr->tm_wday - 1 + 7) % 7 + 7) / 7; goto _no;
	    case 'Z':
#ifdef WANT_TZFILE_PARSER
		      tzset(); src = tzname[0];
#else
		      src = "[unknown timezone]";
#endif
		      goto _str;
            case 'Y': i2a ( tbuf+0, (unsigned int)(tmptr->tm_year / 100 + 19) );
		      i2a ( tbuf+2, (unsigned int)(tmptr->tm_year % 100) );
		      src = tbuf;
		      goto _str;
            case 'y': no  = tmptr->tm_year % 100; 			 goto _no;
                 _no: i2a ( tbuf, no );				 /* append number 'no' */
                      src = tbuf;
            	      goto _str;
                _nos: i2a ( tbuf, no );				 /* the same, but '0'->' ' */
            	      if (tbuf[0] == '0')
		          tbuf[0] = ' ';
		      src = tbuf;
		_str: while (*src  &&  p < buf+size)		 /* append string */
      	                  *p++ = *src++;
      	              break;
      	    };
        } else {
            *p++ = *fmt;
        }

        if (p >= buf+size)
            break;
    }

    *p = '\0';
    return p - buf;
}

