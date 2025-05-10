// Copyright 2025 Subodh Singh

#include "uif/layout.h"

namespace uif {

void LayoutManager::add_rect(Rect rect) { rects.push_back(rect); }

void LayoutManager::clear() { rects.clear(); }

}  // namespace uif
