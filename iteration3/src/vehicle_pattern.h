/**
 * @file pattern.h
 * @copyright 2018 Ruoyun
 */

#ifndef SRC_VEHICLE_PATTERN_H_
#define SRC_VEHICLE_PATTERN_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);
/*******************************************************************************
 * Struct Definitions
 ******************************************************************************/
/**
 * @brief A simple representation of the position/orientation of an entity
 * within the Arena.
 *
 */
struct Pattern {
 public:
  bool positive{true};
  bool direct{true};
  /**
   * @brief Default constructor. Initialize coward pattern
   */
  Pattern() {}

  /**
   * @brief Constructor
   * @param positive_in True if the connection is positive, otherwise, negetive.
   * @param direct_in True if the connection is direct, otherwise, crossed.
   */
  Pattern(bool positive_in, bool direct_in) :
  positive(positive_in), direct(direct_in) {}
};

NAMESPACE_END(csci3081);

#endif  // SRC_VEHICLE_PATTERN_H_
