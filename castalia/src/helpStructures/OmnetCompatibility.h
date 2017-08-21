//MACRO for compatibility with omnet++ 5.0
#if !defined( OMNETCOMPATIBILITY_H) && (OMNETPP_VERSION >= 0x0500)

    #define OMNETCOMPATIBILITY_H
    #include <stdio.h>
    #include "omnetpp.h"

    using namespace omnetpp;

    //void opp_error(const char *msgformat...);
    // In omnet 5.0, 'opp_error' has been removed so we redirect its output to the standard error function

    //create macro dispatcher to overload macros (functions)
    #define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(_,##__VA_ARGS__,5,4,3,2,1,0)
    #define VA_NUM_ARGS_IMPL(_,_1,_2,_3,_4,_5,N,...) N
    #define macro_dispatcher(func, ...) macro_dispatcher_(func, VA_NUM_ARGS(__VA_ARGS__))
    #define macro_dispatcher_(func, nargs) macro_dispatcher__(func, nargs)
    #define macro_dispatcher__(func, nargs) func ## nargs

    void errormsg(const char *format,...);

    //redefine functions for error messages
    #define opp_error(...) macro_dispatcher(opp_error, __VA_ARGS__)(__VA_ARGS__)
    #define opp_error1(m0)  errormsg(m0)
    #define opp_error2(m1,m2) errormsg(m1,m2)
    #define opp_error3(m1,m2,m3) errormsg(m1,m2,m3)
    #define opp_error4(m1,m2,m3,m4) errormsg(m1,m2,m3,m4)
    /**/

    //redefine functions for random number generators
    #define genk_intrand(a,b) omnetpp::intrand(getEnvir()->getRNG(a),b) //TODO: check the correctness of the random number generator
    #define genk_dblrand(a) dblrand(a)

    //std::string double2string(double d);
    //std::string double2string(omnetpp::SimTime t) {return t.str();}

#endif
