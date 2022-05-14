/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
#pragma once

#include "YGMacros.h"

#ifdef __cplusplus
namespace facebook {
namespace yoga {
namespace enums {

template <typename T>
constexpr int count(); // can't use `= delete` due to a defect in clang < 3.9

namespace detail {
template <int... xs>
constexpr int n() {
  return sizeof...(xs);
}
} // namespace detail

} // namespace enums
} // namespace yoga
} // namespace facebook
#endif

#define YG_ENUM_DECL(NAME, ...)                               \
  typedef YG_ENUM_BEGIN(NAME){__VA_ARGS__} YG_ENUM_END(NAME); \
  WIN_EXPORT const char* NAME##ToString(NAME);

#ifdef __cplusplus
#define YG_ENUM_SEQ_DECL(NAME, ...)  \
  YG_ENUM_DECL(NAME, __VA_ARGS__)    \
  YG_EXTERN_C_END                    \
  namespace facebook {               \
  namespace yoga {                   \
  namespace enums {                  \
  template <>                        \
  constexpr int count<NAME>() {      \
    return detail::n<__VA_ARGS__>(); \
  }                                  \
  }                                  \
  }                                  \
  }                                  \
  YG_EXTERN_C_BEGIN
#else
#define YG_ENUM_SEQ_DECL YG_ENUM_DECL
#endif

YG_EXTERN_C_BEGIN

YG_ENUM_SEQ_DECL(
    YGAlign,
    YGAlignAuto,
    YGAlignFlexStart,
    YGAlignCenter,
    YGAlignFlexEnd,
    YGAlignStretch,
    YGAlignBaseline,
    YGAlignSpaceBetween,
    YGAlignSpaceAround);

YG_ENUM_SEQ_DECL(YGDimension, YGDimensionWidth, YGDimensionHeight)

YG_ENUM_SEQ_DECL(
    YGDirection,
    YGDirectionInherit,
    YGDirectionLTR,
    YGDirectionRTL)

YG_ENUM_SEQ_DECL(YGDisplay, YGDisplayFlex, YGDisplayNone)

YG_ENUM_SEQ_DECL(
    YGEdge,
    YGEdgeLeft,
    YGEdgeTop,
    YGEdgeRight,
    YGEdgeBottom,
    YGEdgeStart,
    YGEdgeEnd,
    YGEdgeHorizontal,
    YGEdgeVertical,
    YGEdgeAll)

YG_ENUM_SEQ_DECL(YGExperimentalFeature, YGExperimentalFeatureWebFlexBasis)

YG_ENUM_SEQ_DECL(
    YGFlexDirection,
    YGFlexDirectionColumn,
    YGFlexDirectionColumnReverse,
    YGFlexDirectionRow,
    YGFlexDirectionRowReverse)

YG_ENUM_SEQ_DECL(
    YGJustify,
    YGJustifyFlexStart,
    YGJustifyCenter,
    YGJustifyFlexEnd,
    YGJustifySpaceBetween,
    YGJustifySpaceAround,
    YGJustifySpaceEvenly)

YG_ENUM_SEQ_DECL(
    YGLogLevel,
    YGLogLevelError,
    YGLogLevelWarn,
    YGLogLevelInfo,
    YGLogLevelDebug,
    YGLogLevelVerbose,
    YGLogLevelFatal)

///      - YGMeasureModeUndefined: max content   最大内容     对齐最大的子元素，如果超过父元素，父元素跟着变大
///      - YGMeasureModeExactly: fill available  填充剩余空间  如果子元素小于父元素，将其拉伸
///      - YGMeasureModeAtMost: fit content      适应内容     对齐最大的子元素，但不会超过父元素大小
YG_ENUM_SEQ_DECL(
    YGMeasureMode,
    YGMeasureModeUndefined,
    YGMeasureModeExactly,
    YGMeasureModeAtMost)

YG_ENUM_SEQ_DECL(YGNodeType, YGNodeTypeDefault, YGNodeTypeText)

YG_ENUM_SEQ_DECL(
    YGOverflow,
    YGOverflowVisible,
    YGOverflowHidden,
    YGOverflowScroll)

YG_ENUM_SEQ_DECL(YGPositionType, YGPositionTypeRelative, YGPositionTypeAbsolute)

YG_ENUM_DECL(
    YGPrintOptions,
    YGPrintOptionsLayout = 1,
    YGPrintOptionsStyle = 2,
    YGPrintOptionsChildren = 4)

YG_ENUM_SEQ_DECL(
    YGUnit,
    YGUnitUndefined,
    YGUnitPoint,
    YGUnitPercent,
    YGUnitAuto)

YG_ENUM_SEQ_DECL(YGWrap, YGWrapNoWrap, YGWrapWrap, YGWrapWrapReverse)

YG_EXTERN_C_END

#undef YG_ENUM_DECL
#undef YG_ENUM_SEQ_DECL
