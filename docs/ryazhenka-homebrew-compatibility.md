# Legacy homebrew compatibility in Ryazhenka 8.1.0

## Reference and cause

Atmosphere-CNX commit `bae60e83a865ad2459e5f7aa7551182b9477c68e` reverts
the scheduler's write of the thread CPU-time differential to TLS + `0x108`.
This change is still present at CNX commit
`e65cc935d7db775e83904bee2556425c615ced4a`.

libnx v4.9.0's `nx/source/kernel/thread.c` defines `USER_TLS_BEGIN` as `0x108`.
libnx >= 4.10.0 moves user TLS slots to `0x180`. The scheduler write introduced
for HOS 21 therefore corrupts the first user TLS slot of older applications.
These slots are used by pthreads and C++ exception handling.

## Adaptation to Atmosphere 1.12.0

Ryazhenka omits the scheduler's TLS CPU-time write unconditionally, matching CNX.
A previous marker-based attempt missed the first switch into a new thread:
libnx's `ThreadVars` marker is initialized by its entry wrapper after the kernel
has already scheduled it. That first write left a nonzero value in legacy slot 0.
Even if subsequent writes are suppressed, libnx's destructor loop can later pass
this value to SDL's TLS destructor as an invalid pointer.

The reports `01791104656_010000000000100d.log` and
`01791104805_01000ca004dca000.log` identify PPSSPPSDL's TLS destructor loop
at `0xb9b314` / `0xb9b328` and SDL cleanup crash at `0xe1c6e4`, consistent with
that failure. The actual 2024 PPSSPP NRO initializes its marker at TLS + `0x1E0`
only in its entry wrapper at `0xb9b3a0` and uses slots starting at `0x108`.

As with CNX, this compatibility kernel does not provide the SDK CPU-time
differential in TLS + `0x108`. Existing SVC CPU-time accounting is retained.
This is an intentional kernel behavior difference from official Atmosphere.

HOS 23 additionally writes a newly created thread's handle at TLS + `0x110`.
Ryazhenka detects the libnx `ThreadVars` magic (`0x21545624`, `!TV$`) at `0x1E0`
in the creating thread. When the creator uses libnx, it leaves this field zero in the
child. libnx supplies the handle through its own `Thread` and `ThreadVars`
structures. The initial main-thread handle is assigned before libnx initializes
and before any user TLS slot is allocated, so the official initialization stays.

The HOS 23 kernel changes, shadow stacks, browser patches, decompression support,
and official loader remain in place. No CNX branding or unrelated signature
patches are imported. The displayed Ryazhenka version stays at 8.1.0.

## Verification

The release verifier checks that package3 embeds the locally built kernel,
loader, KIP hashes, splash and Fusée payload. Building and validating the package
does not verify application behavior on a console.

The owner confirmed that the corrected release works on their console on
2026-10-04, after testing the previously failing old homebrew. This confirmation
does not cover every historical NRO build. Eleven compiled AArch64 execution
checks also passed, including the actual 2024 PPSSPP entry wrapper before and
after its ThreadVars initialization.

On the console, fully reboot and use application mode (hold R while launching
a game) for Chiaki/PPSSPP. Test the exact older NRO builds that worked under CNX,
including normal use, exit to hbmenu and a second launch. Test a current libnx
application and a normal game as well.

hbmenu 3.6.1's ABI warning is based on the NRO's build marker, not on the running
kernel. Older NROs can therefore still show the warning with this compatibility
kernel; it does not block launching them. Application-specific service or
library incompatibilities may need additional changes after a console report.
