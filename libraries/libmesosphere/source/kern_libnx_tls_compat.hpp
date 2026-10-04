/*
 * Copyright (c) Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 */
#pragma once
#include <mesosphere.hpp>

namespace ams::kern::impl {

    /* libnx stores ThreadVars at TLS + 0x1E0, beginning with the !TV$ magic.
     * Versions before 4.10.0 use TLS + 0x108 onward for user TLS slots.
     * Newer libnx keeps the same ThreadVars marker and obtains CPU time and
     * thread handles through SVCs/ThreadVars, so preserving this space is safe
     * for both versions. Nintendo SDK threads retain the official TLS updates.
     */
    inline bool IsLibnxThread(const KThread &thread) {
        constexpr u32 ThreadVarsMagic = 0x21545624;
        constexpr size_t ThreadVarsOffset = 0x1E0;
        static_assert(ThreadVarsOffset + sizeof(ThreadVarsMagic) <= ams::svc::ThreadLocalRegionSize);

        const auto *tls = static_cast<const u8 *>(thread.GetThreadLocalRegionHeapAddress());
        return tls != nullptr && *reinterpret_cast<const volatile u32 *>(tls + ThreadVarsOffset) == ThreadVarsMagic;
    }

}
