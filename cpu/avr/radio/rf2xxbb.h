/*
 * rf2xxbb.h
 *
 *  Created on: Sep 24, 2012
 *      Author: smeshlink
 */

#ifndef RF2XXBB_H_
#define RF2XXBB_H_

#if RF212BB
#include "rf212bb.h"
#elif RF230BB
#include "rf230bb.h"
#else
#include "radio.h"
#endif

#endif /* RF2XXBB_H_ */
