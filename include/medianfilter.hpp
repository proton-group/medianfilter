#pragma once
#include "BitmapPlusPlus.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <cstddef>
#include <algorithm>
class WrongRange : public std::exception {};

bmp::Bitmap medianfilter_from_image(const bmp::Bitmap image, int squadSize, int radius);