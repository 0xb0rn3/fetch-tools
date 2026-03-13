<div align="center">

```
███████╗███████╗████████╗ ██████╗██╗  ██╗    ████████╗ ██████╗  ██████╗ ██╗     ███████╗
██╔════╝██╔════╝╚══██╔══╝██╔════╝██║  ██║    ╚══██╔══╝██╔═══██╗██╔═══██╗██║     ██╔════╝
█████╗  █████╗     ██║   ██║     ███████║       ██║   ██║   ██║██║   ██║██║     ███████╗
██╔══╝  ██╔══╝     ██║   ██║     ██╔══██║       ██║   ██║   ██║██║   ██║██║     ╚════██║
██║     ███████╗   ██║   ╚██████╗██║  ██║       ██║   ╚██████╔╝╚██████╔╝███████╗███████║
╚═╝     ╚══════╝   ╚═╝    ╚═════╝╚═╝  ╚═╝       ╚═╝    ╚═════╝  ╚═════╝ ╚══════╝╚══════╝
```

**random anime logo · system info · shell setup · distro-aware aliases**

[![License](https://img.shields.io/badge/license-MIT-blue?style=flat-square)](LICENSE)
[![Shell](https://img.shields.io/badge/shell-bash%20%7C%20zsh-89b4fa?style=flat-square&logo=gnu-bash&logoColor=white)](https://github.com/0xb0rn3/fetch-tools)
[![Platform](https://img.shields.io/badge/platform-linux-a6e3a1?style=flat-square&logo=linux&logoColor=white)](https://github.com/0xb0rn3/fetch-tools)
[![Author](https://img.shields.io/badge/by-0xb0rn3-f38ba8?style=flat-square)](https://github.com/0xb0rn3)

</div>

---

## what it does

Every time you open a terminal, `myfastfetch` fires — pulling a random anime logo from your local collection and rendering it alongside a full system snapshot via fastfetch. Shell templates for bash and zsh are deployed during install, distro detection runs at startup, and aliases are set accordingly. No manual config needed.

---

## install

```bash
git clone https://github.com/0xb0rn3/fetch-tools.git
cd fetch-tools
chmod +x run
sudo ./run
```

The installer asks whether to configure **Bash** (with ble.sh) or **Zsh** (with Oh My Zsh). It then:

- installs fastfetch via your distro's package manager
- pulls anime logos from [`0xb0rn3/my-fastfetch-config`](https://github.com/0xb0rn3/my-fastfetch-config) via sparse-checkout
- copies `myfastfetch` → `/usr/local/bin/myfastfetch` and makes it executable
- deploys `config.jsonc` → `~/.config/fastfetch/`
- writes the shell template to `~/.zshrc` or `~/.bashrc` (backs up the original first)
- installs Oh My Zsh + plugins, or ble.sh, depending on your choice

Open a new terminal. `myfastfetch` runs automatically on every session start.

---

## update logos

Logos are sourced from [`0xb0rn3/my-fastfetch-config`](https://github.com/0xb0rn3/my-fastfetch-config). To pull the latest set without re-running the full installer:

```bash
./run --update-logos
```

No sudo required. Writes directly to `~/.config/fastfetch/logos/`.

---

## how the logo cycle works

`myfastfetch` reads all files in `~/.config/fastfetch/logos/`, tracks which ones have been shown in `~/.config/fastfetch/used_logos.txt`, picks randomly from the remaining pool, and resets when every logo has been shown once. The full cycle repeats, never the same logo twice until the deck runs out.

---

## terminal requirements

`myfastfetch` passes image files directly to fastfetch. Inline image rendering requires one of:

| Terminal | Support |
|----------|---------|
| [kitty](https://sw.kovidgoyal.net/kitty/) | ✓ |
| [Ghostty](https://ghostty.org/) | ✓ |
| [WezTerm](https://wezfurlong.org/wezterm/) | ✓ |
| [iTerm2](https://iterm2.com/) | ✓ macOS |
| [Terminology](https://www.enlightenment.org/about-terminology) | ✓ |
| [Konsole](https://konsole.kde.org/) | ✓ |

Text-only terminals still display system info — just without the image logo.

---

## fastfetch layout

`config.jsonc` defines what fastfetch shows. Two bordered panels, color circles at the bottom:

| module | what it shows |
|--------|--------------|
| Chassis | form factor + chassis type |
| OS | distro name + architecture |
| Kernel | kernel version |
| Packages | pacman count + flatpak count |
| Display | resolution + refresh rate + display type |
| Terminal | terminal emulator name |
| WM | window manager + version + protocol |
| CPU | model + clock speed |
| GPU | name + type (integrated/discrete) |
| GPU Driver | Mesa/amdgpu version via `glxinfo` |
| Memory | used / total |
| OS Age | days since install + install date |
| Uptime | current session uptime |
| Colors | terminal color palette as circles |

Logo is resolved at runtime by `myfastfetch` — the `config.jsonc` logo field is overridden by the `--logo` flag.

---

## distro-aware aliases

Shell templates detect your package manager at startup and define a unified alias set. Every distro gets the same command names.

| alias | arch `pacman` | debian/ubuntu `apt` | fedora/rhel `dnf` | opensuse `zypper` | void `xbps` |
|-------|--------------|---------------------|--------------------|-------------------|-------------|
| `update` | `pacman -Syy -Syu` | `apt upgrade` | `dnf update` | `zypper update` | `xbps-install -Su` |
| `install` | `pacman -S` | `apt install` | `dnf install` | `zypper install` | `xbps-install -S` |
| `remove` | `pacman -Rns` | `apt remove` | `dnf remove` | `zypper remove` | `xbps-remove -R` |
| `clean` | `pacman -Scc` | `apt autoremove` | `dnf clean all` | `zypper clean` | `xbps-remove -Oo` |
| `search` | `pacman -Ss` | `apt-cache search` | `dnf search` | `zypper search` | `xbps-query -Rs` |
| `orphans` | `pacman -Qtdq` | `apt autoremove` | `dnf autoremove` | `zypper --orphaned` | `xbps-remove -o` |
| `pkglist` | `pacman -Qe` | `apt list --installed` | `dnf list installed` | `zypper packages --installed` | `xbps-query -l` |
| `pkgcount` | `pacman -Q \| wc -l` | `dpkg -l \| wc -l` | `rpm -qa \| wc -l` | `rpm -qa \| wc -l` | `xbps-query -l \| wc -l` |
| `pkgown` | `pacman -Qo` | `dpkg -S` | `rpm -qf` | `rpm -qf` | `xbps-query -o` |

### arch / arxos extras

```
arxos-update          full sync + system update
arxos-install         install packages
arxos-remove          remove package + unneeded deps
arxos-force-remove    remove without dep checks (pacman -Rdd)
arxos-clean           full package cache wipe
arxos-refresh-keys    reinit and repopulate keyring
arxos-mirrors         reflector — top 20 HTTPS mirrors sorted by rate
arxos-orphans         remove all orphaned packages
arxos-boostmode       set CPU governor to performance
arxos-powersave       set CPU governor to powersave
arxos-cpu-status      show current governor state
arxos-health          failed services · disk · memory · load · pending updates
arxos-selfscan        nmap -sS -sV on localhost
pkgsize               top 20 packages by installed size (requires expac)
mirrors               alias for arxos-mirrors
```

---

## full alias reference

### listing

| alias | command |
|-------|---------|
| `ls` | `ls --color=auto` |
| `ll` | `ls -l` |
| `la` | `ls -A` |
| `l` | `ls -CF` |
| `lt` | `ls -lht` — sort by time |
| `lz` | `ls -lhS` — sort by size |
| `lsd` | `ls -d */` — directories only |
| `lsf` | `ls -p \| grep -v /` — files only |
| `newest` | `ls -lt \| head -10` |
| `oldest` | `ls -ltr \| head -10` |
| `tree` | `tree -C` — colored tree |

### navigation

| alias | command |
|-------|---------|
| `..` | `cd ..` |
| `...` | `cd ../..` |
| `....` | `cd ../../..` |
| `.....` | `cd ../../../..` |
| `dl` | `cd ~/Downloads` |
| `docs` | `cd ~/Documents` |

### file operations

| alias | command |
|-------|---------|
| `mkdir` | `mkdir -pv` |
| `cp` | `cp -iv` |
| `mv` | `mv -iv` |
| `fhere` | `find . -name` |
| `ftext` | `grep -r` — recursive text search |

### system info

| alias | command |
|-------|---------|
| `df` | `df -h` |
| `free` | `free -m` |
| `sysinfo` | `inxi -Fxz` |
| `temps` | `sensors` |
| `procs` | `ps aux --sort=-%cpu \| head -20` |
| `meminfo` | memory + top 10 by mem |
| `diskinfo` | storage overview + top dirs by size |
| `duh` | `du -h --max-depth=1 \| sort -rh` |
| `bigfiles` | top N files by size in current dir |
| `countfiles` | count files recursively |
| `boot-time` | `systemd-analyze` |
| `boot-blame` | `systemd-analyze blame \| head -20` |

### process

| alias | command |
|-------|---------|
| `psmem` | top 10 processes by memory |
| `pscpu` | top 10 processes by CPU |
| `topmem` | detailed top 10 by memory |
| `killed` | `dmesg \| grep -i kill` — OOM kills |

### network

| alias | command |
|-------|---------|
| `myip` | external IP via `ifconfig.me` |
| `localip` | local IPv4 address |
| `gateway` | default gateway |
| `ports` | `netstat -tulanp` |
| `portsopen` | listening ports only |
| `connections` | active connections via `ss` |
| `wifi` | list nearby networks |
| `wifi-connect` | `nmcli device wifi connect` |
| `flush-dns` | flush systemd-resolved cache |
| `tracert` | `traceroute` |
| `headers` | `curl -I` — HTTP headers |
| `get` | `curl -sL` — silent fetch |
| `nmap-quick` | `sudo nmap -sV --open` |
| `nmap-ping` | `sudo nmap -sn` — ping sweep |

### network speed

| alias | command |
|-------|---------|
| `speedtest` | `netspeed -q` |
| `st` | `netspeed -q` (short) |
| `speedtest-full` | `netspeed -f` |
| `pingtest` | `netspeed -p` |
| `netinfo` | `netspeed -i` |
| `ping1` | `ping -c 5 1.1.1.1` |
| `ping8` | `ping -c 5 8.8.8.8` |

### services

| alias | command |
|-------|---------|
| `service-list` | all active services |
| `service-failed` | `systemctl --failed` |
| `service-start` | `sudo systemctl start` |
| `service-stop` | `sudo systemctl stop` |
| `service-restart` | `sudo systemctl restart` |
| `service-enable` | `sudo systemctl enable` |
| `service-disable` | `sudo systemctl disable` |

### logs

| alias | command |
|-------|---------|
| `logs` | `journalctl -xe` |
| `logs-boot` | `journalctl -b` |
| `logs-follow` | `journalctl -f` |
| `logs-service` | `journalctl -u` |

### git

| alias | command |
|-------|---------|
| `gs` | `git status` |
| `ga` | `git add` |
| `gc` | `git commit -m` |
| `gp` | `git push` |
| `gpl` | `git pull` |
| `gl` | `git log --oneline --graph --decorate` |
| `gd` | `git diff` |

### docker

| alias | command |
|-------|---------|
| `dps` | `docker ps` |
| `dpsa` | `docker ps -a` |
| `di` | `docker images` |
| `dex` | `docker exec -it` |
| `dlog` | `docker logs -f` |
| `dstop` | stop all running containers |
| `dclean` | `docker system prune -af` |
| `dcu` | `docker compose up -d` |
| `dcd` | `docker compose down` |
| `dcl` | `docker compose logs -f` |

### tmux

| alias | command |
|-------|---------|
| `ta` | `tmux attach` |
| `tls` | `tmux ls` |
| `tn` | `tmux new -s` |
| `tk` | `tmux kill-session -t` |

### web search

| alias | opens |
|-------|-------|
| `google <q>` | Google |
| `bing <q>` | Bing |
| `ddg <q>` | DuckDuckGo |

### utils

| alias | command |
|-------|---------|
| `reload` | re-source shell config |
| `aliases` | sorted alias list |
| `hist` | `history \| grep` |
| `now` | current date + time |
| `week` | current week number |
| `epoch` | unix timestamp |
| `calc` | `bc -l` — calculator |
| `weather` | `curl wttr.in` |
| `cheat` | `curl cheat.sh/` |
| `pubkey` | print `~/.ssh/id_rsa.pub` |
| `genpass` | `openssl rand -base64 32` |
| `sha` | `shasum -a 256` |
| `md5` | `md5sum` |
| `py` | `python3` |
| `serve` | `python3 -m http.server 8000` |

---

## functions

| function | usage | what it does |
|----------|-------|-------------|
| `mkcd` | `mkcd dirname` | mkdir + cd in one shot |
| `backup` | `backup file` | copies file with timestamp suffix |
| `killp` | `killp name` | kill all processes matching name |
| `whatsmyip` | `whatsmyip` | local + external IP |
| `isup` | `isup https://site.com` | checks if a URL returns 200 |
| `testhost` | `testhost hostname` | ping + DNS lookup |
| `portcheck` | `portcheck host port` | TCP port open/closed |
| `duh` | `duh` | disk usage, current dir, sorted |
| `bigfiles` | `bigfiles [N]` | top N files by size (default 20) |
| `countfiles` | `countfiles [dir]` | count all files recursively |
| `path` | `path` | print PATH entries one per line |
| `urlencode` | `urlencode string` | percent-encode a string |
| `urldecode` | `urldecode string` | decode percent-encoded string |
| `http-server` | `http-server` | `python3 -m http.server` |
| `extract` | `extract file` | decompress any archive format |
| `copypath` | `copypath` | copy current path to clipboard |
| `copyfile` | `copyfile file` | copy file contents to clipboard |
| `web_search` | `web_search google query` | open search in browser |
| `dirhistory` | `dirhistory path` | pushd wrapper |
| `arxos-health` | `arxos-health` | arch/arxos — system health overview |
| `arxos-selfscan` | `arxos-selfscan` | arch/arxos — nmap localhost scan |

> `extract` supports: `.tar.bz2` `.tar.gz` `.bz2` `.rar` `.gz` `.tar` `.tbz2` `.tgz` `.zip` `.Z` `.7z`

---

## cache cleanup

`cleanup.sh` wipes caches for Brave, Firefox, OBS, VS Code, and the system package manager. Runs sequentially — each section is independent so partial failures don't block the rest.

```bash
chmod +x cleanup.sh && ./cleanup.sh
```

**scope:**

| target | what gets wiped |
|--------|----------------|
| Brave | IndexedDB · LocalStorage · ServiceWorker CacheStorage · GPUCache · ShaderCache · BlobStorage |
| Firefox | cache2 · startupCache · shader-cache · ServiceWorker · IndexedDB · LocalStorage · thumbnails |
| OBS Studio | cache · plugin config · browser plugin cache + code cache · logs |
| VS Code | Cache · CachedData · GPUCache · workspaceStorage · crashpad |
| System | AppImage cache · thumbnails · `/var/cache` · pacman cache · journal vacuum to 100M |

---

## project layout

```
fetch-tools/
├── run                          # installer · handles --update-logos flag
├── myfastfetch                  # random logo picker — called at shell startup
├── config.jsonc                 # fastfetch module layout and display config
├── cleanup.sh                   # cache cleanup utility
├── .src/
│   └── templates/
│       ├── bashrc.template      # bash config · full alias + function set · ble.sh ready
│       └── zshrc.template       # zsh equivalent · oh-my-zsh · plugins
└── README.md
```

---

## troubleshooting

**myfastfetch: no logos found**
```bash
./run --update-logos
```

**fastfetch not found after install**
Install it manually for your distro then re-run:
```bash
# Arch
sudo pacman -S fastfetch
# Debian/Ubuntu
sudo apt install fastfetch
# Fedora
sudo dnf install fastfetch
```

**logo displays as text / broken characters**
Your terminal doesn't support inline images. Switch to kitty, Ghostty, or WezTerm.

**Oh My Zsh plugins not loading**
Make sure the plugin repos were cloned into `~/.oh-my-zsh/custom/plugins/`. The installer handles this, but if it was skipped:
```bash
git clone --depth=1 https://github.com/zsh-users/zsh-syntax-highlighting \
    ~/.oh-my-zsh/custom/plugins/zsh-syntax-highlighting
git clone --depth=1 https://github.com/zsh-users/zsh-autosuggestions \
    ~/.oh-my-zsh/custom/plugins/zsh-autosuggestions
```

**ble.sh not activating**
Check that the source line was appended to `~/.bashrc`:
```bash
tail -5 ~/.bashrc
```
It should contain: `source "$HOME/.local/share/blesh/ble.sh"`

---

## license

MIT — [0xb0rn3](https://github.com/0xb0rn3) | 0xbv1
