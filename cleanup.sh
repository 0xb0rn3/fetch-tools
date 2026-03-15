#!/bin/bash
# ─── fetch-tools cache cleanup ──────────────────────────────────────────────
# Wipes caches for browsers, editors, OBS, and system.
# Each section is independent — partial failures don't block the rest.
# Run: chmod +x cleanup.sh && ./cleanup.sh

set -o pipefail

BOLD='\033[1m'
GREEN='\033[1;32m'
BLUE='\033[1;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

section() { echo -e "\n${BOLD}${BLUE}[$1]${NC}"; }
ok()      { echo -e "  ${GREEN}✓${NC} $1"; }
skip()    { echo -e "  ${YELLOW}⏭${NC} $1 (not found)"; }

# ─── brave ───────────────────────────────────────────────────────────────────
section "Brave Browser"
BRAVE_DIR="$HOME/.config/BraveSoftware/Brave-Browser/Default"
if [ -d "$BRAVE_DIR" ]; then
    rm -rf "$BRAVE_DIR"/IndexedDB/*
    rm -rf "$BRAVE_DIR"/Local\ Storage/*
    rm -rf "$BRAVE_DIR"/Service\ Worker/CacheStorage/*
    rm -rf "$BRAVE_DIR"/GPUCache/*
    rm -rf "$BRAVE_DIR"/ShaderCache/*
    rm -rf "$BRAVE_DIR"/BlobStorage/*
    ok "Brave caches cleared"
else
    skip "Brave profile"
fi

# ─── firefox ─────────────────────────────────────────────────────────────────
section "Firefox"
PROFILE_DIR=$(find ~/.mozilla/firefox -maxdepth 1 -type d -name "*.default*" 2>/dev/null | head -n 1)
if [ -n "$PROFILE_DIR" ]; then
    rm -rf "$PROFILE_DIR"/cache2/*
    rm -rf "$PROFILE_DIR"/startupCache/*
    rm -rf "$PROFILE_DIR"/shader-cache/*
    rm -rf "$PROFILE_DIR"/storage/default/*/cache/*
    rm -rf "$PROFILE_DIR"/storage/default/*/idb/*
    rm -rf "$PROFILE_DIR"/storage/default/*/ls/*
    rm -rf ~/.cache/mozilla/firefox/*
    ok "Firefox caches cleared ($PROFILE_DIR)"
else
    skip "Firefox profile"
fi

# ─── vs code ────────────────────────────────────────────────────────────────
section "VS Code"
CODE_DIR="$HOME/.config/Code"
if [ -d "$CODE_DIR" ]; then
    rm -rf "$CODE_DIR"/Cache/*
    rm -rf "$CODE_DIR"/CachedData/*
    rm -rf "$CODE_DIR"/GPUCache/*
    rm -rf "$CODE_DIR"/User/workspaceStorage/*
    rm -rf "$CODE_DIR"/crashpad/*
    ok "VS Code caches cleared"
else
    skip "VS Code config"
fi

# ─── obs studio ──────────────────────────────────────────────────────────────
section "OBS Studio"
OBS_DIR="$HOME/.config/obs-studio"
if [ -d "$OBS_DIR" ]; then
    rm -rf ~/.cache/obs-studio/*
    rm -rf "$OBS_DIR"/plugin_config/*
    rm -rf "$OBS_DIR"/plugin_data/obs-browser/cache/*
    rm -rf "$OBS_DIR"/plugin_data/obs-browser/Code\ Cache/*
    rm -rf "$OBS_DIR"/logs/*
    ok "OBS caches cleared"
else
    skip "OBS Studio config"
fi

# ─── system caches ───────────────────────────────────────────────────────────
section "System"

# user caches
rm -rf ~/.cache/appimagekit 2>/dev/null
rm -rf ~/.cache/thumbnails/* 2>/dev/null
ok "User cache (appimage, thumbnails)"

# distro-aware package manager cache
if command -v pacman >/dev/null 2>&1; then
    sudo pacman -Scc --noconfirm >/dev/null 2>&1
    sudo rm -rf /var/tmp/pacman* 2>/dev/null
    ok "pacman cache"
elif command -v apt-get >/dev/null 2>&1; then
    sudo apt-get clean >/dev/null 2>&1
    ok "apt cache"
elif command -v dnf >/dev/null 2>&1; then
    sudo dnf clean all >/dev/null 2>&1
    ok "dnf cache"
elif command -v zypper >/dev/null 2>&1; then
    sudo zypper clean --all >/dev/null 2>&1
    ok "zypper cache"
elif command -v xbps-remove >/dev/null 2>&1; then
    sudo xbps-remove -O >/dev/null 2>&1
    ok "xbps cache"
fi

# journal logs — keep 100M
if command -v journalctl >/dev/null 2>&1; then
    sudo journalctl --vacuum-size=100M >/dev/null 2>&1
    ok "journal vacuumed to 100M"
fi

# system cache dir
sudo rm -rf /var/cache/* 2>/dev/null
ok "/var/cache cleared"

echo -e "\n${GREEN}${BOLD}✅ Cleanup complete.${NC}"
