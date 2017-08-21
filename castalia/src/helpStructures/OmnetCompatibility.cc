
#include "omnetpp.h"

#include "OmnetCompatibility.h"

//redefinition of functions for compatibility
#define VSNPRINTF(buffer, buflen, formatarg) \
    VSNPRINTF2(buffer, buflen, formatarg, formatarg)

#define VSNPRINTF2(buffer, buflen, lastarg, format) \
    va_list va; \
    va_start(va, lastarg); \
    vsnprintf(buffer, buflen, format, va); \
    buffer[buflen-1] = '\0'; \
    va_end(va);

#define BUFLEN 512
void errormsg(const char *fmt...)
{
    char buf[BUFLEN];
    VSNPRINTF(buf, BUFLEN, fmt);
    throw omnetpp::cRuntimeError(omnetpp::OppErrorCode::E_USER, buf);
}
