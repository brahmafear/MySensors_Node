#ifndef __DEBUG_H
#define __DEBUG_H

#define ENABLE_DEBUG                                                                    // to include them in base sketch
#ifdef ENABLE_DEBUG
    #define DEBUG_MSG(...) Serial.print( __VA_ARGS__ )
#else
    #define DEBUG_MSG(...)
#endif

#endif
