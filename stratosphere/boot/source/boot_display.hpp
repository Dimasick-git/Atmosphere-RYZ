/*
 * Copyright (c) Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include <stratosphere.hpp>

namespace ams::boot {

    /* Splash Screen/Display utilities. */
    void InitializeDisplay();
    void ShowDisplay(size_t x, size_t y, size_t width, size_t height, const u32 *img);
    void FinalizeDisplay();

    void SetDisplayBrightness(int percentage);

    /* Landscape (1280x720, origin top-left) drawing primitives for the loading screen. */
    void ClearFrame();
    void DrawPixel(size_t x, size_t y, u32 color);
    void DrawFilledRect(size_t x, size_t y, size_t width, size_t height, u32 color);
    void DrawBitmapRGBA(size_t x, size_t y, size_t width, size_t height, const u32 *data);
    void DrawBitmapRGBAClipped(size_t x, size_t y, size_t width, size_t height, const u32 *data, size_t draw_width);
    void PresentFrame();

}
