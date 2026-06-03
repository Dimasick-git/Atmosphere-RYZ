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
#include <stratosphere.hpp>
#include "boot_display.hpp"
#include "boot_loading_screen.hpp"

namespace ams::boot {

    namespace {

        /* Baked text/glyph bitmaps (alpha in high byte). */
        struct LoadImg { u32 w; u32 h; const u32 *data; };
#include "boot_loading_assets.inc"

        /* "Milky" palette. */
        constexpr u32 ColorBarBorder = 0xFFE9DEC8;  /* cream */
        constexpr u32 ColorBarTrack  = 0xFF161320;  /* dark track */
        constexpr u32 ColorBarFill   = 0xFF9E88FF;  /* milky violet */

        /* Layout (landscape: x in [0,1280) horizontal, y in [0,720) vertical). */
        constexpr size_t MarginX  = 120;
        constexpr size_t TitleX   = MarginX,  TitleY = 64;
        constexpr size_t BarX     = MarginX,  BarY   = 200;
        constexpr size_t BarW     = 760,      BarH   = 72;
        constexpr size_t SegW     = 16,       SegGap = 6;
        constexpr size_t PctX     = BarX + BarW + 28;
        constexpr size_t ListX    = MarginX,  ListY  = 336, LineH = 62;
        constexpr size_t StatusX  = 720;

        void DrawPercent(size_t x, size_t y, int value) {
            char buf[8];
            const int n = util::SNPrintf(buf, sizeof(buf), "%d", value);
            size_t cx = x;
            for (int i = 0; i < n; i++) {
                const LoadImg &g = LoadDigits[buf[i] - '0'];
                DrawBitmapRGBA(cx, y, g.w, g.h, g.data);
                cx += g.w + 1;
            }
            DrawBitmapRGBA(cx + 2, y, LoadPercent.w, LoadPercent.h, LoadPercent.data);
        }

    }

    void ShowLoadingScreen() {
        /* Progress thresholds at which each checklist line flips to OK. */
        constexpr u32 Thresholds[5] = { 12, 32, 52, 72, 92 };

        const size_t pct_y = BarY + (BarH - LoadDigits[0].h) / 2;

        for (int p = 0; p <= 100; p += 2) {
            ClearFrame();

            /* Title. */
            DrawBitmapRGBA(TitleX, TitleY, LoadTitle.w, LoadTitle.h, LoadTitle.data);

            /* Progress bar: cream border, dark track, milky-violet segmented fill. */
            DrawFilledRect(BarX - 3, BarY - 3, BarW + 6, BarH + 6, ColorBarBorder);
            DrawFilledRect(BarX, BarY, BarW, BarH, ColorBarTrack);
            const size_t fill_w = (BarW * static_cast<size_t>(p)) / 100;
            for (size_t sx = 0; sx + SegW <= fill_w; sx += (SegW + SegGap)) {
                DrawFilledRect(BarX + sx, BarY + 4, SegW, BarH - 8, ColorBarFill);
            }

            /* Percentage. */
            DrawPercent(PctX, pct_y, p);

            /* Checklist. */
            for (size_t i = 0; i < 5; i++) {
                const LoadImg &lbl = LoadLabels[i];
                const size_t ly = ListY + i * LineH;
                DrawBitmapRGBA(ListX, ly, lbl.w, lbl.h, lbl.data);
                const LoadImg &st = (static_cast<u32>(p) >= Thresholds[i]) ? LoadOk : LoadDots;
                DrawBitmapRGBA(StatusX, ly, st.w, st.h, st.data);
            }

            PresentFrame();
            os::SleepThread(TimeSpan::FromMilliSeconds(28));
        }

        /* Hold the completed screen briefly before continuing boot. */
        os::SleepThread(TimeSpan::FromMilliSeconds(650));
    }

}
