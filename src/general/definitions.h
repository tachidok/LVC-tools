#ifndef DEFINITIONS_H
#define DEFINITIONS_H

namespace lvc_tools
{
 
#define LVC_TOOLS_WITH_DEBUG
#ifdef LVC_TOOLS_WITH_DEBUG
 // =======================================================================
 // Macros for debugging
 // =======================================================================
#define DEB(x) std::cerr<<"["<<#x<<"]:"<<x<<std::endl;
#define DEB2(x,y) std::cerr<<x<<" "<<y<<std::endl;
#define DEB3(x,y,z) std::cerr<<x<<" "<<y<<" "<<z<<std::endl;
#define DEB4(t,x,y,z) std::cerr<<t<<" "<<x<<" "<<y<<" "<<z<<std::endl;
#define DEB_TO_FILE(F,x) F<<"["<<#x<<"]:"<<x<<std::endl;
#define DEB_TO_FILE1(F,x) F<<x<<std::endl;
#define DEB_TO_FILE2(F,x,y) F<<x<<" "<<y<<std::endl;
#define DEB_TO_FILE3(F,x,y,z) F<<x<<" "<<y<<" "<<z<<std::endl;
#define DEB_TO_FILE4(F,t,x,y,z) F<<t<<" "<<x<<" "<<y<<" "<<z<<std::endl;
#endif // #ifdef LVC_TOOLS_WITH_DEBUG
 
 // =======================================================================
 // Macros to transform from degrees to radians and vice versa
 // =======================================================================
#define TO_RADIANS (M_PI/180.0)
#define TO_DEGREES (180.0/M_PI)

 // Error macro
 //#define ERROR_MESSAGE(error_message) std::cout << std::endl << "=======================================================================\nERROR\n=======================================================================\nError in file [" << LVC_TOOLS_EXCEPTION_LOCATION << "]\n in function " << LVC_TOOLS_CURRENT_FUNCTION << std::endl << std::endl << error_message << std::endl << std::endl; exit(-1);

 //#define ERROR_MESSAGE(error_message) std::cout << std::endl << "=======================================================================\nERROR\n=======================================================================\n"<<error_message<<std::endl << "=======================================================================\nERROR\n=======================================================================\n";

#define ERROR_MESSAGE(error_message) std::cout << std::endl << "=======================================================================\nERROR\n=======================================================================\n";
 
 // =======================================================================
 // The macros to deal with strings for error messages are taken from
 // oomph-lib
 // =======================================================================

 //Pre-processor magic for error reporting
 //Macro that converts argument to string
#define LVC_TOOLS_MAKE_STRING(x) #x

 //Macro wrapper to LVC_TOOLS_MAKE_STRING, required because calling
 //LVC_TOOLS_MAKE_STRING(__LINE__) directly returns __LINE__
 //i.e. the conversion of __LINE__ into a number must be performed before
 //its conversion into a string
#define LVC_TOOLS_TO_STRING(x) LVC_TOOLS_MAKE_STRING(x)

 //Combine the FILE and LINE built-in macros into a string that can
 //be used in error messages.
#define LVC_TOOLS_EXCEPTION_LOCATION __FILE__ ":" LVC_TOOLS_TO_STRING(__LINE__)

 // Get the current function name. All the mess is due to different
 // compilers naming the macro we need differently.
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
# define LVC_TOOLS_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__DMC__) && (__DMC__ >= 0x810)
# define LVC_TOOLS_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__FUNCSIG__)
# define LVC_TOOLS_CURRENT_FUNCTION __FUNCSIG__

#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
# define LVC_TOOLS_CURRENT_FUNCTION __FUNCTION__

#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
# define LVC_TOOLS_CURRENT_FUNCTION __FUNC__

#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
# define LVC_TOOLS_CURRENT_FUNCTION __func__

#else
# define LVC_TOOLS_CURRENT_FUNCTION "[Unknown function -- unrecognised compiler]"

#endif

}
 
#endif // #ifndef DEFINITIONS_H

