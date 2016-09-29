#ifndef SIMPLE_LOGGER
#define SIMPLE_LOGGER

/**
 * @file SimpleLogger.h
 * @author Florian Hagenauer
 * @date: 2016-06-20
 * A simple logging framework for simple logging with three levels (DEBUG, INFO, WARN).
 * Prints: [LEVEL][simTime][module/filename:line] Message
 */

#include <omnetpp.h>

#define DEBUG(x) if(debug) {std::cout << "[DBG][" << simTime().trunc(SIMTIME_US) << "][" << __FILE__ << ":" << __LINE__ << "] "; std::cout << x << std::endl;}
#define DEBUG_ID(x) if(debug) {std::cout << "[DBG][" << simTime().trunc(SIMTIME_US) << "][" << getId() << "][" << getFullPath() << ":" << __LINE__ << "] "; std::cout << x << std::endl;}

#define INFO(x) if(infoLogging || debug) {std::cout << "[INF][" << simTime().trunc(SIMTIME_US) << "][" << __FILE__ << ":" << __LINE__ << "] "; std::cout << x << std::endl;}
#define INFO_ID(x) if(infoLogging || debug) {std::cout << "[INF][" << simTime().trunc(SIMTIME_US) << "][" << getId() << "][" << getFullPath() << ":" << __LINE__ << "] "; std::cout << x << std::endl;}

#define WARN(x) {std::cout << "[WAR][" << simTime().trunc(SIMTIME_US) << "][" << __FILE__ << ":" << __LINE__ << "] "; std::cout << x << std::endl;}
#define WARN_ID(x) {std::cout << "[WAR][" << simTime().trunc(SIMTIME_US) << "][" << getId() << "][" << getFullPath() << ":" << __LINE__ << "] "; std::cout << x << std::endl;}

#endif
