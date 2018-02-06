#ifndef APP_H
#define APP_H

EE_INT32 CallMyTaskTrustedService( EE_INT32 arg );
EE_INT32 CallMyIsrTrustedService( EE_INT32 arg );

void signal_error( int e );

#endif /* APP_H */
