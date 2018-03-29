/**
 * @file pattern.h
 *
 */

#ifndef SRC_PATTERN_H_
#define SRC_PATTERN_H_

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
   *
   */
  Pattern(bool positive_in, bool direct_in) :
   positive(positive_in), direct(direct_in) {}
};

NAMESPACE_END(csci3081);

#endif  // SRC_pattern_H_
