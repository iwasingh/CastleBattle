#ifndef LOGGER_H
#define LOGGER_H
#include <irrlicht.h>
using namespace irr;
#define LOGGER(tag, level, _Message)              \
  Logger::getLogger()->print(                     \
    static_cast<LOG_TYPE>(tag),                   \
    level,                                        \
    static_cast<core::stringc>(_Message)          \
  );
#ifndef DEBUG_OUTPUT
#define DEBUG_OUTPUT
#define DEBUG_OUTPUT_MASK 1
#endif
#define log(tag, level, _Message) if(level > DEBUG_OUTPUT_MASK) ; else LOGGER(tag,level,_Message)
enum LOG_TYPE{
  INFO,
  WARN,
  ERROR
};
/*
This class handles logs. In particulare the DEBUG_OUTPUT_MASK directive define the verbosity of the messages.
1 mean enable all couts that have level = 1 on their calls
2 mean enable all couts from 1 to 2 level
3 mean enable all couts from 1 to 3 level
ect.
For now there are 2 level. The last level 3 will also activate a visual debugging(you can move around the map)
*/
class Logger{
public:
  static int level;
  static Logger* getLogger();
  void print(LOG_TYPE type, int level, core::stringc str);
private:
  static Logger* logger;
  core::stringw label;
  void initLogger();
  Logger();
};
#endif
