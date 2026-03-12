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

Every time you open a terminal, `myfastfetch` fires — pulling a random anime logo from your local collection and rendering it alongside a full system snapshot via fastfetch. Shell templates for bash and zsh are injected during install, distro detection runs at startup, and aliases are set accordingly. No manual config needed.

---

## install

```bash
git clone https://github.com/0xb0rn3/fetch-tools.git
cd fetch-tools
chmod +x run 
sudo ./run
```

Open a new terminal. `myfastfetch` runs automatically on every session start.

---

## update logos

Logos are sourced from [`0xb0rn3/my-fastfetch-config`](https://github.com/0xb0rn3/my-fastfetch-config).

```bash
./run --update-logos
```

---

## terminal requirements

`myfastfetch` passes image files directly to fastfetch. Inline image rendering requires one of:

| Terminal | Support |
|----------|---------|
| [kitty](https://sw.kovidgoyal.net/kitty/) | ✓ |
| [Ghostty](https://ghostty.org/) | ✓ |
| [WezTerm](https://wezfurlong.org/wezterm/) | ✓ |
| [iTerm2](https://iterm2.com/) | ✓ (macOS) |
| [Terminology](https://www.enlightenment.org/about-terminology) | ✓ |
| [Konsole] | ✓ |

Text-only terminals will still display system info — just without the image logo.

---

## distro-aware aliases

Shell templates detect your package manager at startup and define a unified alias set. Write once, run everywhere.

| alias | arch `pacman` | debian/ubuntu `apt` | fedora/rhel `dnf` | opensuse `zypper` | void `xbps` |
|-------|--------------|---------------------|--------------------|-------------------|-------------|
| `update` | `pacman -Syy -Syu` | `apt upgrade` | `dnf update` | `zypper update` | `xbps-install -Su` |
| `install` | `pacman -S` | `apt install` | `dnf install` | `zypper install` | `xbps-install -S` |
| `remove` | `pacman -Rns` | `apt remove` | `dnf remove` | `zypper remove` | `xbps-remove -R` |
| `clean` | `pacman -Scc` | `apt autoremove` | `dnf clean all` | `zypper clean` | `xbps-remove -Oo` |
| `search` | `pacman -Ss` | `apt-cache search` | `dnf search` | `zypper search` | `xbps-query -Rs` |
| `orphans` | `pacman -Qtdq` | `apt autoremove` | `dnf autoremove` | `zypper --orphaned` | `xbps-remove -o` |

Additional aliases are also set per-distro for `pkglist`, `pkgcount`, `pkgown`, and where applicable `pkgsize`.

### arch / arxos extras

Arch and ArxOS users get an extended alias set on top of the standard ones:

```
arxos-update          full system update
arxos-install         install packages
arxos-remove          remove with deps
arxos-force-remove    remove without dep checks (pacman -Rdd)
arxos-clean           full package cache wipe
arxos-refresh-keys    reinit and repopulate keyring
arxos-mirrors         reflector — top 20 HTTPS mirrors by rate
arxos-orphans         remove orphaned packages
arxos-boostmode       set CPU governor to performance
arxos-powersave       set CPU governor to powersave
arxos-cpu-status      show current governor state
arxos-health          failed services · disk · memory · load · pending updates
arxos-selfscan        nmap -sS -sV localhost
```

---

## shell extras

Both bash and zsh templates ship with a curated function and alias set beyond package management:

**navigation** — `..` `...` `....` `dl` `docs` `mkcd` `dirhistory` `dback`

**network** — `myip` `localip` `gateway` `ports` `portsopen` `connections` `wifi` `wifi-connect` `whatsmyip` `isup` `testhost` `portcheck` `speedtest` `pingtest`

**system** — `sysinfo` `temps` `procs` `meminfo` `df` `free` `diskinfo` `duh` `bigfiles` `countfiles`

**services** — `service-list` `service-failed` `service-start/stop/restart/enable/disable`

**logs** — `logs` `logs-boot` `logs-follow` `logs-service`

**files** — `extract` `backup` `cp` `mv` `mkdir` `tree`

**git** — `gs` `ga` `gc` `gp` `gl` `gd` `gpl`

**utils** — `urlencode` `urldecode` `copypath` `copyfile` `killp` `web_search` `serve` `http-server`

---

## cache cleanup

`cleanup.sh` wipes caches for Brave, Firefox, OBS, VS Code, and system package managers. Targets IndexedDB, LocalStorage, ServiceWorker caches, GPUCache, ShaderCache, BlobStorage, and journal logs.

```bash
chmod +x cleanup.sh && ./cleanup.sh
```

Scope: Brave · Firefox · OBS Studio · VS Code · pacman cache · system `/var/cache` · thumbnails · journal vacuum to 100M

---

## fastfetch config

`config.jsonc` defines the display layout — chassis, OS, kernel, packages, display resolution, terminal, WM, CPU, GPU, GPU driver (Mesa/amdgpu via `glxinfo`), memory, OS install age, and uptime. Color palette rendered as circles at the bottom.

The logo field is dynamically resolved at runtime via the `myfastfetch` picker script.

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
│       ├── bashrc.template      # bash config with full alias + function set
│       └── zshrc.template       # zsh equivalent
└── README.md
```

---

## license

MIT — [0xb0rn3](https://github.com/0xb0rn3) | 0xbv1
