// Copyright 2025 Subodh Singh

#include "uif/layout.h"

namespace uif {

void LayoutManager::AddRect(Rect rect) { rects.push_back(rect); }

void LayoutManager::Clear() { rects.clear(); }

}  // namespace uif
