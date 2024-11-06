# Fetch Tools

A collection of system information display tools with ASCII art for Linux systems.

## Features

- Cross-platform support (Debian, Arch, RedHat)
- Two display styles: Dragon and System
- System information display including:
  - OS and Kernel details
  - CPU information
  - Memory usage
  - Disk space
  - Uptime
  - Shell information
- Color-coded output
- Easy installation process

## Prerequisites

The following packages will be automatically installed if missing:
- gcc
- make
- basic development tools

## Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/fetch-tools.git
cd fetch-tools
```

2. Run the installer:
```bash
sudo ./install.sh
```

## Usage

After installation, you can use either:

```bash
dragon-fetch    # For dragon style display
sys-fetch      # For alternative style display
```

## Command Integration

To automatically run either fetch tool when opening a new terminal:
1. Add either of these lines to your ~/.zshrc:
```bash
dragon-fetch
# or
sys-fetch
```

## Building from Source

If you prefer to build manually:

```bash
make clean
make
sudo make install
```

## Support

- Debian-based distributions (Ubuntu, Linux Mint, etc.)
- Arch Linux and derivatives
- RedHat-based distributions (Fedora, CentOS, etc.)

## Contributing

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a new Pull Request


## Acknowledgments

- Inspired by neofetch and screenfetch
- ASCII art generated and modified for optimal terminal display

## Author

https://github.com/q4n0/
