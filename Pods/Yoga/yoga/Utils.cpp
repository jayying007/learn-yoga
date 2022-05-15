/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
#include "Utils.h"
#include <float.h>

using namespace facebook;

YGFlexDirection YGFlexDirectionCross(
    const YGFlexDirection flexDirection,
    const YGDirection direction) {
  return YGFlexDirectionIsColumn(flexDirection)
      ? YGResolveFlexDirection(YGFlexDirectionRow, direction)
      : YGFlexDirectionColumn;
}

float YGFloatMax(const float a, const float b) {
  if (!yoga::isUndefined(a) && !yoga::isUndefined(b)) {
    return fmaxf(a, b);
  }
  return yoga::isUndefined(a) ? b : a;
}

float YGFloatMin(const float a, const float b) {
  if (!yoga::isUndefined(a) && !yoga::isUndefined(b)) {
    return fminf(a, b);
  }

  return yoga::isUndefined(a) ? b : a;
}

bool YGValueEqual(const YGValue& a, const YGValue& b) {
  if (a.unit != b.unit) {
    return false;
  }

  if (a.unit == YGUnitUndefined ||
      (yoga::isUndefined(a.value) && yoga::isUndefined(b.value))) {
    return true;
  }

  return fabs(a.value - b.value) < 0.0001f;
}

bool YGFloatsEqual(const float a, const float b) {
  if (!yoga::isUndefined(a) && !yoga::isUndefined(b)) {
    return fabs(a - b) < 0.0001f;
  }
  return yoga::isUndefined(a) && yoga::isUndefined(b);
}

float YGFloatSanitize(const float val) {
  return yoga::isUndefined(val) ? 0 : val;
}

YGFloatOptional YGFloatOptionalMax(YGFloatOptional op1, YGFloatOptional op2) {
  if (op1 >= op2) {
    return op1;
  }
  if (op2 > op1) {
    return op2;
  }
  return op1.isUndefined() ? op2 : op1;
}


float YGNodeCalculateAvailableInnerDim(
    const YGNodeRef node,
    YGFlexDirection axis,
    float availableDim,
    float ownerDim) {
    
    YGFlexDirection direction = YGFlexDirectionIsRow(axis) ? YGFlexDirectionRow : YGFlexDirectionColumn;
    YGDimension dimension = YGFlexDirectionIsRow(axis) ? YGDimensionWidth : YGDimensionHeight;

    const float margin = node->getMarginForAxis(direction, ownerDim).unwrap();
    const float paddingAndBorder = node->getPaddingAndBorderForAxis(direction, ownerDim).unwrap();

    float availableInnerDim = availableDim - margin - paddingAndBorder;
    // Max dimension overrides predefined dimension value; Min dimension in turn
    // overrides both of the above
    if (!YGFloatIsUndefined(availableInnerDim)) {
        // We want to make sure our available height does not violate min and max
        // constraints
        const YGFloatOptional minDimensionOptional = YGResolveValue(node->getStyle().minDimensions[dimension], ownerDim);
        const float minInnerDim = minDimensionOptional.isUndefined()
            ? 0.0f
            : minDimensionOptional.unwrap() - paddingAndBorder;

        const YGFloatOptional maxDimensionOptional = YGResolveValue(node->getStyle().maxDimensions[dimension], ownerDim);
        const float maxInnerDim = maxDimensionOptional.isUndefined()
            ? FLT_MAX
            : maxDimensionOptional.unwrap() - paddingAndBorder;
    
        availableInnerDim = YGFloatMax(YGFloatMin(availableInnerDim, maxInnerDim), minInnerDim);
    }

    return availableInnerDim;
}
