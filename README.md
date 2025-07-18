# 🚀 Fetch Tools - Modern System Information Display

<div align="center">

**A sleek, modern system information display tool with beautiful ASCII art**

[![Made with C](https://img.shields.io/badge/Made%20with-C-blue.svg)](https://www.gnu.org/software/gcc/)
[![Linux](https://img.shields.io/badge/Platform-Linux-green.svg)](https://www.kernel.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

</div>

## ✨ Features

- **🎨 Beautiful ASCII Art**: Eye-catching system display with modern aesthetics
- **⚡ Lightning Fast**: Written in C for optimal performance
- **🔧 Cross-Platform**: Support for Debian, Arch, and RedHat-based distributions
- **🎯 Smart Detection**: Automatically detects your system configuration
- **🌈 Color-Coded Output**: Vibrant, easy-to-read system information
- **🔄 One-Click Setup**: Automated installation with shell configuration

## 📋 System Information Display

- **OS & Kernel**: Distribution and kernel version details
- **CPU**: Processor information and architecture
- **Memory**: RAM usage with real-time statistics
- **Uptime**: System uptime in human-readable format
- **Shell**: Current shell environment
- **Color Palette**: Terminal color support visualization

## 🚀 Quick Start

### Prerequisites

The installer will automatically handle all dependencies:
- `gcc` (C compiler)
- `make` (build tools)
- Development libraries

### Installation

```bash
# Clone the repository
git clone https://github.com/0xb0rn3/fetch-tools.git
cd fetch-tools

# Make executable and run
chmod +x run
sudo ./run
```

### Usage

After installation, simply run:
```bash
fetch
```

## 🎨 Screenshots

```
┌─────────────────────────────────────────────────────────────────────────┐
│  username@hostname                    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⣴⣶⣶⣶⣶⣦⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  │
│  ─────────────────                    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣶⣾⣿⣿⣿⣿⣟⠁⠀⢹⣿⣿⣿⣿⣿⣶⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀  │
│  OS: Ubuntu 22.04 LTS                 ⠀⠀⠀⠀⠀⠀⢠⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀  │
│  Kernel: Linux 5.15.0-72-generic     ⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀  │
│  Uptime: 2 days, 14 hours, 32 mins   ⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀  │
│  Shell: zsh                           ⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢫⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀⠀⠀⠀⠀  │
│  CPU: Intel Core i7-10700K           ⠀⠀⠀⢠⣿⣿⣿⣿⣿⣏⠹⣿⣿⣿⣿⣿⣿⡃⠀⢩⣿⣿⣶⣬⣿⠟⠙⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀  │
│  Memory: 8192 MB / 16384 MB          ⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⠀⠻⠛⠛⠿⠛⠛⠁⠀⠘⠛⠿⠛⠛⠿⠇⢰⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀  │
│  Colors: ● ● ● ● ● ● ●               ⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⣶⣶⡄⠀⠀⠀⣠⣤⣦⣄⡀⠀⠀⠀⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀  │
└─────────────────────────────────────────────────────────────────────────┘
```

## 🛠️ Development & Configuration

### Shell Integration

The installer automatically configures your shell environment:

**For Zsh users:**
- Oh My Zsh installation
- Syntax highlighting plugin
- Auto-suggestions plugin
- Custom prompt with fetch integration

**For Bash users:**
- Enhanced Bash with ble.sh
- Improved completion system
- Custom prompt configuration

### Customization

The tool integrates seamlessly with your shell startup. You can customize the behavior by editing:
- `~/.zshrc` (for Zsh)
- `~/.bashrc` (for Bash)

## 🌍 Platform Support

- **Debian/Ubuntu**: `apt-get` package manager
- **Arch Linux**: `pacman` package manager  
- **RedHat/Fedora**: `dnf` package manager
- **Automatic Detection**: No manual configuration needed

## 📁 Project Structure

```
fetch-tools/
├── run                    # Main installer script
├── .src/
│   ├── fetch.c           # Core system info display
│   └── templates/
│       ├── zshrc.template
│       └── bashrc.template
└── README.md
```

## 🤝 Contributing

We welcome contributions! Here's how to get started:

1. **Fork** the repository
2. **Create** your feature branch (`git checkout -b feature/amazing-feature`)
3. **Commit** your changes (`git commit -m 'Add some amazing feature'`)
4. **Push** to the branch (`git push origin feature/amazing-feature`)
5. **Open** a Pull Request

## 🏆 Acknowledgments

- Inspired by `neofetch` and `screenfetch`
- ASCII art optimized for modern terminals
- Built with performance and aesthetics in mind

## 👨‍💻 Author

**0xb0rn3** | **0xbv1**
- GitHub: [@0xb0rn3](https://github.com/0xb0rn3)
- Focused on creating modern, efficient system tools

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

<div align="center">

**⭐ If you found this project helpful, please give it a star! ⭐**

</div>
