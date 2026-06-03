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

        /* Layout (landscape: x in [0,1280) horizontal, y in [0,720) vertical). */
        constexpr size_t LineX  = 160;
        constexpr size_t StartY = 222;
        constexpr size_t LineH  = 56;
        constexpr size_t OkGap  = 16;

        /* Timing. */
        constexpr int CharMs     = 16;   /* per typed character */
        constexpr int AfterLine  = 130;  /* pause once a line is typed */
        constexpr int AfterOk    = 150;  /* pause after OK appears */

        /* First-boot flag on the SD card. */
        constexpr const char *SdMount  = "sdmc";
        constexpr const char *FlagDir  = "sdmc:/atmosphere/startup";
        constexpr const char *FlagFile = "sdmc:/atmosphere/startup/ryazhenka_boot_shown";

        bool MountSdWithRetries() {
            for (int i = 0; i < 10; i++) {
                if (R_SUCCEEDED(fs::MountSdCard(SdMount))) {
                    return true;
                }
                os::SleepThread(TimeSpan::FromMilliSeconds(100));
            }
            return false;
        }

        bool FlagExists() {
            bool has = false;
            return R_SUCCEEDED(fs::HasFile(std::addressof(has), FlagFile)) && has;
        }

        void WriteFlag() {
            fs::EnsureDirectory(FlagDir);
            fs::CreateFile(FlagFile, 0);
        }

        void PlayAnimation() {
            /* Clear once to black, then only ever add content (flicker-free). */
            ClearFrame();
            PresentFrame();

            for (size_t i = 0; i < util::size(LoadLines); i++) {
                const LoadLine &ln = LoadLines[i];
                const size_t y = StartY + i * LineH;

                /* Typewriter reveal, letter by letter. */
                for (u32 k = 0; k < ln.nchars; k++) {
                    DrawBitmapRGBAClipped(LineX, y, ln.w, ln.h, ln.data, ln.cuts[k]);
                    PresentFrame();
                    os::SleepThread(TimeSpan::FromMilliSeconds(CharMs));
                }

                os::SleepThread(TimeSpan::FromMilliSeconds(AfterLine));

                /* Show the OK once the line finished "loading". */
                DrawBitmapRGBA(LineX + ln.w + OkGap, y, LoadOk.w, LoadOk.h, LoadOk.data);
                PresentFrame();
                os::SleepThread(TimeSpan::FromMilliSeconds(AfterOk));
            }

            os::SleepThread(TimeSpan::FromMilliSeconds(500));
        }

    }

    void ShowLoadingScreen() {
        /* Only on first boot: gated by a flag file on the SD card.
           All FS access is best-effort (fs auto-abort is disabled in boot). */
        if (!MountSdWithRetries()) {
            return;
        }

        if (FlagExists()) {
            fs::Unmount(SdMount);
            return;
        }

        PlayAnimation();

        WriteFlag();
        fs::Unmount(SdMount);
    }

}
