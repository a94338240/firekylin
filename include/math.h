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

#ifndef _MATH_H
#define _MATH_H

#define HUGE_VAL  \
  (((union { unsigned long long __ll; double __d; }) \
    { __ll: 0x7ff0000000000000ULL }).__d)
#define HUGE_VALF \
  (((union { unsigned int __i; float __f; })         \
    { __i: 0x7f800000UL }).__f)

#define M_E            2.7182818284590452354   /* e 		*/
#define M_LOG2E        1.4426950408889634074   /* log_2 e 	*/
#define M_LOG10E       0.43429448190325182765  /* log_10 e 	*/
#define M_LN2          0.69314718055994530942  /* log_e 2 	*/
#define M_LN10         2.30258509299404568402  /* log_e 10 	*/
#define M_PI           3.14159265358979323846  /* pi 		*/
#define M_PI_2         1.57079632679489661923  /* pi/2 		*/
#define M_PI_4         0.78539816339744830962  /* pi/4 		*/
#define M_1_PI         0.31830988618379067154  /* 1/pi 		*/
#define M_2_PI         0.63661977236758134308  /* 2/pi 		*/
#define M_2_SQRTPI     1.12837916709551257390  /* 2/sqrt(pi) 	*/
#define M_SQRT2        1.41421356237309504880  /* sqrt(2) 	*/
#define M_SQRT1_2      0.70710678118654752440  /* 1/sqrt(2) 	*/

#define M_El		2.7182818284590452353602874713526625L  /* e          */
#define M_LOG2El	1.4426950408889634073599246810018922L  /* log_2 e    */
#define M_LOG10El	0.4342944819032518276511289189166051L  /* log_10 e   */
#define M_LN2l		0.6931471805599453094172321214581766L  /* log_e 2    */
#define M_LN10l		2.3025850929940456840179914546843642L  /* log_e 10   */
#define M_PIl		3.1415926535897932384626433832795029L  /* pi         */
#define M_PI_2l		1.5707963267948966192313216916397514L  /* pi/2       */
#define M_PI_4l		0.7853981633974483096156608458198757L  /* pi/4       */
#define M_1_PIl		0.3183098861837906715377675267450287L  /* 1/pi       */
#define M_2_PIl		0.6366197723675813430755350534900574L  /* 2/pi       */
#define M_2_SQRTPIl	1.1283791670955125738961589031215452L  /* 2/sqrt(pi) */
#define M_SQRT2l	1.4142135623730950488016887242096981L  /* sqrt(2)    */
#define M_SQRT1_2l	0.7071067811865475244008443621048490L  /* 1/sqrt(2)  */

extern double sin(double x);
extern double cos(double x);
extern double tan(double x);
extern double asin(double x);
extern double acos(double x);
extern double atan(double x);
extern double atan2(double x, double y);
extern double exp(double x);
extern double pow(double x, double y);
extern double log(double x);
extern double log10(double x);
extern double sinh(double x);
extern double cosh(double x);
extern double tanh(double x);
extern double asinh(double x);
extern double acosh(double x);
extern double atanh(double x);
extern double sqrt(double x);
extern double hypot(double x, double y);
extern double fabs(double x);
extern double floor(double x);
extern double ceil(double x);
extern double fmod(double x, double m);
extern double ldexp(double x, int i);
extern double modf(double x, double *ipart);
extern double frexp(double x, int *exptr);

#endif
