#pragma once

#include <map>
#include <vector>
#include <raylib.h>
#include <cstddef>
#include <string>
#include <set>

Rectangle GetCameraBounds(Camera2D camera, const float offset = 0.0f, const float width = (float)GetScreenWidth(), const float height = (float)GetScreenHeight());