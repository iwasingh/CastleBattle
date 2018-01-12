#ifndef LOGGER_H
#define LOGGER_H
#include <irrlicht.h>
#include <bullethelper.h>
using namespace irr;
/** Logger class expansion */
#define LOGGER(tag, level, _Message)              \
  Logger::getLogger()->print(                     \
    static_cast<LOG_TYPE>(tag),                   \
    level,                                        \
    static_cast<core::stringc>(_Message)          \
  );
#ifndef DEBUG_OUTPUT_MASK
  #define DEBUG_OUTPUT_MASK 0
#endif
/** Log a message. There is a bitwise AND with the DEBUG_OUTPUT_MASK */
#define log(tag, level, _Message) if(level & DEBUG_OUTPUT_MASK) LOGGER(tag,level,_Message) else;
#define log1(_Message) log(INFO,1, _Message)
#define log1p(_Message, parameter) log1(static_cast<core::stringc>(_Message) + core::stringc(parameter))
#define log2p(_Message, parameter) log2(static_cast<core::stringc>(_Message) + core::stringc(parameter))
#define log2(_Message) log(INFO,2, _Message)
#define logVector(level, _Message, vector)                                              \
  log(INFO, level,                                                                      \
    static_cast<core::stringc>(_Message)+                                               \
    static_cast<core::stringc>(vectorToString(static_cast<core::vector3df>(vector)))    \
  );


enum LOG_TYPE{ /*!< LOG_TYPE i think is useless. For now there are only INFO outputs. Maybe a name of the class who call the cout is better */
  INFO,
  WARN,
  ERROR
};
/** This singleton class handles logs and debugging. In particular the DEBUG_OUTPUT_MASK directive define the verbosity of the messages.
 DEBUG_OUTPUT_MASK 1 mean enable all couts that have level = 1 on their calls
 DEBUG_OUTPUT_MASK 2 mean enable all couts that have level = 2 on their calls
 DEBUG_OUTPUT_MASK 3 mean enable all tracing and debugging
For now there are 2 level. The level 2 will also activate a visual debugging(you can move around the map)
*/
class Logger{
public:
  // static int level;
  /** Return the instance  */
  static Logger* getLogger();
  /** Print message
  * @param type LOG_TYPE
  * @param level int
  * @param str stringc string to print
  * @see: ::Logger
  */
  void print(LOG_TYPE type, int level, core::stringc str);
private:
    /** Self instance  */
  static Logger* logger;
  /** Init singleton logger */
  void initLogger();
  /** Default constructor. Not used */
  Logger();
};
#endif
