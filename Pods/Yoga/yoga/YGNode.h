/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
#pragma once
#include <stdio.h>
#include "YGConfig.h"
#include "YGLayout.h"
#include "YGStyle.h"
#include "Yoga-internal.h"

struct YGNode {
  using BaselineWithContextFn = float (*)(YGNode*, float, float, void*);
  using PrintWithContextFn = void (*)(YGNode*, void*);

private:
  void* context_ = nullptr;
  bool hasNewLayout_ : 1;
  bool isReferenceBaseline_ : 1;
  bool isDirty_ : 1;
  YGNodeType nodeType_ : 1;
  bool baselineUsesContext_ : 1;
  bool printUsesContext_ : 1;
  union {
    YGMeasureFunc noContext;
  } measure_ = {nullptr};
  union {
    YGBaselineFunc noContext;
    BaselineWithContextFn withContext;
  } baseline_ = {nullptr};
  union {
    YGPrintFunc noContext;
    PrintWithContextFn withContext;
  } print_ = {nullptr};
  YGDirtiedFunc dirtied_ = nullptr;
  YGStyle style_ = {};
  YGLayout layout_ = {};
  uint32_t lineIndex_ = 0;
  YGNodeRef owner_ = nullptr;
  YGVector children_ = {};
  YGConfigRef config_ = nullptr;
  std::array<YGValue, 2> resolvedDimensions_ = {
      {YGValueUndefined, YGValueUndefined}};

  YGFloatOptional relativePosition(
      const YGFlexDirection axis,
      const float axisSize) const;

  void setMeasureFunc(decltype(measure_));
  void setBaselineFunc(decltype(baseline_));

  // DANGER DANGER DANGER!
  // If the the node assigned to has children, we'd either have to deallocate
  // them (potentially incorrect) or ignore them (danger of leaks). Only ever
  // use this after checking that there are no children.
  // DO NOT CHANGE THE VISIBILITY OF THIS METHOD!
  YGNode& operator=(YGNode&&) = default;

public:
  YGNode()
      : hasNewLayout_{true},
        isReferenceBaseline_{false},
        isDirty_{false},
        nodeType_{YGNodeTypeDefault},
        baselineUsesContext_{false},
        printUsesContext_{false} {}
  ~YGNode() = default; // cleanup of owner/children relationships in YGNodeFree
  explicit YGNode(const YGConfigRef newConfig) : config_(newConfig){};

  YGNode(YGNode&&);

  // Does not expose true value semantics, as children are not cloned eagerly.
  // Should we remove this?
  YGNode(const YGNode& node) = default;

  // assignment means potential leaks of existing children, or alternatively
  // freeing unowned memory, double free, or freeing stack memory.
  YGNode& operator=(const YGNode&) = delete;

  // Getters
  void* getContext() const {
    return context_;
  }

  void print(void*);

  bool getHasNewLayout() const {
    return hasNewLayout_;
  }

  YGNodeType getNodeType() const {
    return nodeType_;
  }

  bool hasMeasureFunc() const noexcept {
    return measure_.noContext != nullptr;
  }

  YGSize measure(float, YGMeasureMode, float, YGMeasureMode);

  bool hasBaselineFunc() const noexcept {
    return baseline_.noContext != nullptr;
  }

  float baseline(float width, float height, void* layoutContext);

  YGDirtiedFunc getDirtied() const {
    return dirtied_;
  }

  // For Performance reasons passing as reference.
  YGStyle& getStyle() {
    return style_;
  }

  const YGStyle& getStyle() const {
    return style_;
  }

  // For Performance reasons passing as reference.
  YGLayout& getLayout() {
    return layout_;
  }

  const YGLayout& getLayout() const {
    return layout_;
  }

  uint32_t getLineIndex() const {
    return lineIndex_;
  }

  bool isReferenceBaseline() {
    return isReferenceBaseline_;
  }

  // returns the YGNodeRef that owns this YGNode. An owner is used to identify
  // the YogaTree that a YGNode belongs to. This method will return the parent
  // of the YGNode when a YGNode only belongs to one YogaTree or nullptr when
  // the YGNode is shared between two or more YogaTrees.
  YGNodeRef getOwner() const {
    return owner_;
  }

  // Deprecated, use getOwner() instead.
  YGNodeRef getParent() const {
    return getOwner();
  }

  const YGVector& getChildren() const {
    return children_;
  }

  // Applies a callback to all children, after cloning them if they are not
  // owned.
  template <typename T>
  void iterChildrenAfterCloningIfNeeded(T callback) {
    int i = 0;
    for (YGNodeRef& child : children_) {
      if (child->getOwner() != this) {
        child = config_->cloneNode(child, this, i);
        child->setOwner(this);
      }
      i += 1;

      callback(child);
    }
  }

  YGNodeRef getChild(uint32_t index) const {
    return children_.at(index);
  }

  YGConfigRef getConfig() const {
    return config_;
  }

  bool isDirty() const {
    return isDirty_;
  }

  std::array<YGValue, 2> getResolvedDimensions() const {
    return resolvedDimensions_;
  }

  YGValue getResolvedDimension(int index) const {
    return resolvedDimensions_[index];
  }

  // Methods related to positions, margin, padding and border
  YGFloatOptional getLeadingPosition(
      const YGFlexDirection axis,
      const float axisSize) const;
  bool isLeadingPositionDefined(const YGFlexDirection axis) const;
  bool isTrailingPosDefined(const YGFlexDirection axis) const;
  YGFloatOptional getTrailingPosition(
      const YGFlexDirection axis,
      const float axisSize) const;
  YGFloatOptional getLeadingMargin(
      const YGFlexDirection axis,
      const float widthSize) const;
  YGFloatOptional getTrailingMargin(
      const YGFlexDirection axis,
      const float widthSize) const;
  float getLeadingBorder(const YGFlexDirection flexDirection) const;
  float getTrailingBorder(const YGFlexDirection flexDirection) const;
  YGFloatOptional getLeadingPadding(
      const YGFlexDirection axis,
      const float widthSize) const;
  YGFloatOptional getTrailingPadding(
      const YGFlexDirection axis,
      const float widthSize) const;
  YGFloatOptional getLeadingPaddingAndBorder(
      const YGFlexDirection axis,
      const float widthSize) const;
  YGFloatOptional getTrailingPaddingAndBorder(
      const YGFlexDirection axis,
      const float widthSize) const;
  YGFloatOptional getMarginForAxis(
      const YGFlexDirection axis,
      const float widthSize) const;
    YGFloatOptional getPaddingAndBorderForAxis(const YGFlexDirection axis, const float widthSize) const;
  // Setters

  void setContext(void* context) {
    context_ = context;
  }

  void setPrintFunc(YGPrintFunc printFunc) {
    print_.noContext = printFunc;
    printUsesContext_ = false;
  }
  void setPrintFunc(PrintWithContextFn printFunc) {
    print_.withContext = printFunc;
    printUsesContext_ = true;
  }
  void setPrintFunc(std::nullptr_t) {
    setPrintFunc(YGPrintFunc{nullptr});
  }

  void setHasNewLayout(bool hasNewLayout) {
    hasNewLayout_ = hasNewLayout;
  }

  void setNodeType(YGNodeType nodeType) {
    nodeType_ = nodeType;
  }

  void setStyleFlexDirection(YGFlexDirection direction) {
    style_.flexDirection = direction;
  }

  void setStyleAlignContent(YGAlign alignContent) {
    style_.alignContent = alignContent;
  }

  void setMeasureFunc(YGMeasureFunc measureFunc);
  void setMeasureFunc(std::nullptr_t) {
    return setMeasureFunc(YGMeasureFunc{nullptr});
  }

  void setBaselineFunc(YGBaselineFunc baseLineFunc) {
    baselineUsesContext_ = false;
    baseline_.noContext = baseLineFunc;
  }
  void setBaselineFunc(BaselineWithContextFn baseLineFunc) {
    baselineUsesContext_ = true;
    baseline_.withContext = baseLineFunc;
  }
  void setBaselineFunc(std::nullptr_t) {
    return setBaselineFunc(YGBaselineFunc{nullptr});
  }

  void setDirtiedFunc(YGDirtiedFunc dirtiedFunc) {
    dirtied_ = dirtiedFunc;
  }

  void setStyle(const YGStyle& style) {
    style_ = style;
  }

  void setLayout(const YGLayout& layout) {
    layout_ = layout;
  }

  void setLineIndex(uint32_t lineIndex) {
    lineIndex_ = lineIndex;
  }

  void setIsReferenceBaseline(bool isReferenceBaseline) {
    isReferenceBaseline_ = isReferenceBaseline;
  }

  void setOwner(YGNodeRef owner) {
    owner_ = owner;
  }

  void setChildren(const YGVector& children) {
    children_ = children;
  }

  // TODO: rvalue override for setChildren

  void setConfig(YGConfigRef config) {
    config_ = config;
  }

  void setDirty(bool isDirty);
  void setLayoutLastOwnerDirection(YGDirection direction);
  void setLayoutComputedFlexBasis(const YGFloatOptional computedFlexBasis);
  void setLayoutComputedFlexBasisGeneration(
      uint32_t computedFlexBasisGeneration);
  void setLayoutMeasuredDimension(float measuredDimension, int index);
  void setLayoutHadOverflow(bool hadOverflow);
  void setLayoutDimension(float dimension, int index);
  void setLayoutDirection(YGDirection direction);
  void setLayoutMargin(float margin, int index);
  void setLayoutBorder(float border, int index);
  void setLayoutPadding(float padding, int index);
  void setLayoutPosition(float position, int index);
  void setPosition(
      const YGDirection direction,
      const float mainSize,
      const float crossSize,
      const float ownerWidth);
  void setAndPropogateUseLegacyFlag(bool useLegacyFlag);
  void markDirtyAndPropogateDownwards();

  // Other methods
  YGValue marginLeadingValue(const YGFlexDirection axis) const;
  YGValue marginTrailingValue(const YGFlexDirection axis) const;
  YGValue resolveFlexBasisPtr() const;
  void resolveDimension();
  YGDirection resolveDirection(const YGDirection ownerDirection);
  void clearChildren();
  /// Replaces the occurrences of oldChild with newChild
  void replaceChild(YGNodeRef oldChild, YGNodeRef newChild);
  void replaceChild(YGNodeRef child, uint32_t index);
  void insertChild(YGNodeRef child, uint32_t index);
  /// Removes the first occurrence of child
  bool removeChild(YGNodeRef child);
  void removeChild(uint32_t index);

  void cloneChildrenIfNeeded();
  void markDirtyAndPropogate();
  float resolveFlexGrow();
  float resolveFlexShrink();
  bool isNodeFlexible();
  bool isLayoutTreeEqualToNode(const YGNode& node) const;
  void reset();
};
