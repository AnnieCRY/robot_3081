/**
 * @file entity_type.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef ITERATION1_SRC_ENTITY_TYPE_H_
#define ITERATION1_SRC_ENTITY_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

enum EntityType {
  kRobot, kObstacle, kBase, kEntity,
  kRightWall, kLeftWall, kTopWall, kBottomWall,
  kUndefined
};

NAMESPACE_END(csci3081);

#endif  // ITERATION1_SRC_ENTITY_TYPE_H_
