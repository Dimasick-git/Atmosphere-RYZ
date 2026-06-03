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

        /* Baked text assets (alpha in high byte). */
        struct LoadLine { u32 w; u32 h; const u32 *data; u32 nchars; const u32 *cuts; };
        struct LoadImg  { u32 w; u32 h; const u32 *data; };
#include "boot_loading_assets.inc"

        /* Layout (landscape: x in [0,1280) horizontal, y in [0,720) vertical). Top-left. */
        constexpr size_t LineX  = 44;
        constexpr size_t StartY = 40;
        constexpr size_t LineH  = 30;
        constexpr size_t OkGap  = 10;

        /* Timing (very snappy: reveal several chars per frame, ~25x faster). */
        constexpr u32 CharStep   = 6;    /* characters revealed per frame */
        constexpr int CharMs     = 0;    /* delay per reveal step */
        constexpr int AfterLine  = 1;    /* pause once a line is typed */
        constexpr int AfterOk    = 3;    /* pause after OK appears */

        void PlayAnimation() {
            /* Clear once to black, then only ever add content (flicker-free). */
            ClearFrame();
            PresentFrame();

            for (size_t i = 0; i < util::size(LoadLines); i++) {
                const LoadLine &ln = LoadLines[i];
                const size_t y = StartY + i * LineH;

                /* Typewriter reveal, several characters per frame. */
                for (u32 k = 0; k < ln.nchars; k += CharStep) {
                    DrawBitmapRGBAClipped(LineX, y, ln.w, ln.h, ln.data, ln.cuts[k]);
                    PresentFrame();
                    os::SleepThread(TimeSpan::FromMilliSeconds(CharMs));
                }
                /* Ensure the full line is drawn (the step may skip the last char). */
                DrawBitmapRGBAClipped(LineX, y, ln.w, ln.h, ln.data, ln.cuts[ln.nchars - 1]);

                os::SleepThread(TimeSpan::FromMilliSeconds(AfterLine));

                /* Show the OK once the line finished "loading". */
                DrawBitmapRGBA(LineX + ln.w + OkGap, y, LoadOk.w, LoadOk.h, LoadOk.data);
                PresentFrame();
                os::SleepThread(TimeSpan::FromMilliSeconds(AfterOk));
            }

            os::SleepThread(TimeSpan::FromMilliSeconds(300));
        }

    }

    void ShowLoadingScreen() {
        /* NOTE: The boot sysmodule runs before the FS sysmodule has finished
           bringing up the SD card, so it must NOT touch the SD card here — doing
           so races/locks SD init and makes ams_mitm fail its own MountSdCard and
           abort. The screen is therefore purely on-screen, no SD access. */
        PlayAnimation();
    }

}
