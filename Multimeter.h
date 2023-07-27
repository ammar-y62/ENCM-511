/* 
 * File:   Multimeter.h
 * Author: Ammar Elzeftawy, David Kim, Yaseen ElSherif
 *
 * Created on December 1, 2022, 9:20 PM
 */

#ifndef MULTIMETER_H
#define	MULTIMETER_H

#ifdef	__cplusplus
extern "C" {
#endif

void readMultimeter(void);
void __attribute((interrupt, no_auto_psv))_CNInterrupt(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MULTIMETER_H */