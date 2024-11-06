#!/usr/bin/env bash

# Enhanced color scheme
BOLD='\033[1m'
DIM='\033[2m'
ITALIC='\033[3m'
UNDERLINE='\033[4m'
RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
PURPLE='\033[1;35m'
CYAN='\033[1;36m'
WHITE='\033[1;37m'
GRAY='\033[0;90m'
NC='\033[0m'

# Configuration
VERSION="1.0.0"
INSTALL_DIR="/usr/bin"
BUILD_DIR="build"
LOG_FILE="/tmp/fetch_install_$(date +%Y%m%d_%H%M%S).log"
TERM_WIDTH=$(tput cols)

# Print tool header with banner
print_banner() {
    clear
    echo
    printf "%${TERM_WIDTH}s\n" | tr ' ' '═'
    echo -e "${BOLD}${BLUE}"
    echo '    ███████╗███████╗████████╗ ██████╗██╗  ██╗    ████████╗ ██████╗  ██████╗ ██╗     ███████╗'
    echo '    ██╔════╝██╔════╝╚══██╔══╝██╔════╝██║  ██║    ╚══██╔══╝██╔═══██╗██╔═══██╗██║     ██╔════╝'
    echo '    █████╗  █████╗     ██║   ██║     ███████║       ██║   ██║   ██║██║   ██║██║     ███████╗'
    echo '    ██╔══╝  ██╔══╝     ██║   ██║     ██╔══██║       ██║   ██║   ██║██║   ██║██║     ╚════██║'
    echo '    ██║     ███████╗   ██║   ╚██████╗██║  ██║       ██║   ╚██████╔╝╚██████╔╝███████╗███████║'
    echo '    ╚═╝     ╚══════╝   ╚═╝    ╚═════╝╚═╝  ╚═╝       ╚═╝    ╚═════╝  ╚═════╝ ╚══════╝╚══════╝'
    echo -e "${NC}"
    printf "%${TERM_WIDTH}s\n" | tr ' ' '═'
    echo -e "${BOLD}${PURPLE}                       System Information Display Tools Installer${NC}"
    echo -e "${DIM}                                Version $VERSION - 2024${NC}"
    printf "%${TERM_WIDTH}s\n" | tr ' ' '═'
    echo
}

# Print section headers
print_section() {
    local text="$1"
    echo -e "\n${BOLD}${CYAN}▶ ${text}${NC}"
    echo -e "${DIM}$(printf '%.s─' $(seq 1 $TERM_WIDTH))${NC}"
}

# Print status with icons
print_status() {
    local text="$1"
    local status="$2"
    printf "${ITALIC}%-50s" "$text"
    case $status in
        "OK")     echo -e "${GREEN}[✓] OK${NC}" ;;
        "FAIL")   echo -e "${RED}[✗] Failed${NC}" ;;
        "WARN")   echo -e "${YELLOW}[!] Warning${NC}" ;;
        "INFO")   echo -e "${BLUE}[i] Info${NC}" ;;
        *)        echo -e "${PURPLE}[*] $status${NC}" ;;
    esac
}

# Show progress bar
show_progress() {
    local text="$1"
    local current="$2"
    local total="$3"
    local width=50
    local percentage=$((current * 100 / total))
    local completed=$((width * current / total))
    local remaining=$((width - completed))
    
    printf "\r${ITALIC}%-30s${NC} [" "$text"
    printf "%${completed}s" | tr ' ' '█'
    printf "%${remaining}s" | tr ' ' '░'
    printf "] ${BOLD}%3d%%${NC}" $percentage
}

# Show spinner animation
show_spinner() {
    local pid=$1
    local text=$2
    local spin='⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏'
    local i=0
    
    while kill -0 $pid 2>/dev/null; do
        i=$(( (i + 1) % 10 ))
        printf "\r${ITALIC}%-50s${NC} ${BLUE}[${spin:$i:1}]${NC}" "$text"
        sleep .1
    done
    printf "\r%-50s${GREEN}[✓]${NC}\n" "$text"
}

# Check root privileges
check_root() {
    if [ "$EUID" -ne 0 ]; then
        print_status "Root Privileges" "FAIL"
        echo -e "${RED}Please run as root or with sudo${NC}"
        exit 1
    fi
    print_status "Root Privileges" "OK"
}

# Detect OS and package manager
detect_os() {
    print_section "System Detection"
    
    if [ -f "/etc/debian_version" ]; then
        PM="apt-get"
        PM_INSTALL="$PM install -y"
        PM_UPDATE="$PM update"
        REQUIRED_PACKAGES="build-essential"
        OS="Debian"
    elif [ -f "/etc/arch-release" ]; then
        PM="pacman"
        PM_INSTALL="$PM -S --noconfirm"
        PM_UPDATE="$PM -Sy"
        REQUIRED_PACKAGES="base-devel"
        OS="Arch"
    elif [ -f "/etc/redhat-release" ]; then
        PM="dnf"
        PM_INSTALL="$PM install -y"
        PM_UPDATE="$PM update -y"
        REQUIRED_PACKAGES="gcc gcc-c++ make"
        OS="RedHat"
    else
        print_status "OS Detection" "FAIL"
        echo -e "${RED}Unsupported distribution${NC}"
        exit 1
    fi
    
    print_status "OS Detection" "OK"
    echo -e "${DIM}Detected: $OS Linux${NC}"
}

# Install dependencies
install_dependencies() {
    print_section "Installing Dependencies"
    
    echo -e "${DIM}Updating package database...${NC}"
    (
        $PM_UPDATE >/dev/null 2>&1
    ) &
    show_spinner $! "Updating package manager"
    
    echo -e "${DIM}Installing required packages...${NC}"
    (
        $PM_INSTALL $REQUIRED_PACKAGES >/dev/null 2>&1
    ) &
    show_spinner $! "Installing build dependencies"
}

# Build tools
build_tools() {
    print_section "Building Fetch Tools"
    
    echo -e "${DIM}Compiling source code...${NC}"
    mkdir -p $BUILD_DIR
    
    # Clean any previous builds
    make clean >/dev/null 2>&1
    
    # Build tools
    (make >/dev/null 2>&1) &
    show_spinner $! "Compiling fetch tools"
    
    if [ $? -ne 0 ]; then
        print_status "Build Process" "FAIL"
        echo -e "${RED}Compilation failed. Check the logs for details.${NC}"
        exit 1
    fi
    
    print_status "Build Process" "OK"
}

# Install tools
install_tools() {
    print_section "Installing Fetch Tools"
    
    # Install binaries
    echo -e "${DIM}Installing binaries to $INSTALL_DIR...${NC}"
    install -m 755 $BUILD_DIR/dragon-fetch $INSTALL_DIR/
    install -m 755 $BUILD_DIR/sys-fetch $INSTALL_DIR/
    
    print_status "Installation" "OK"
}

# Configure default fetch tool
configure_fetch() {
    print_section "Configuration"
    
    echo -e "${CYAN}Select default fetch tool:${NC}"
    echo -e "1) Dragon Fetch  - Artistic dragon ASCII with system info"
    echo -e "2) System Fetch  - Clean system information display"
    echo -e "3) None         - Don't set a default\n"
    
    read -p "Enter your choice [1-3]: " choice
    
    case $choice in
        1)
            echo "dragon-fetch" >> /etc/zsh/zshrc
            echo "term" >> /etc/zsh/zshrc
            print_status "Default Tool" "Dragon Fetch"
            ;;
        2)
            echo "sys-fetch" >> /etc/zsh/zshrc
            echo "term" >> /etc/zsh/zshrc
            print_status "Default Tool" "System Fetch"
            ;;
        3)
            print_status "Default Tool" "None"
            ;;
        *)
            print_status "Default Tool" "WARN"
            echo -e "${YELLOW}Invalid choice. No default set.${NC}"
            ;;
    esac
}

# Cleanup function
cleanup() {
    print_section "Cleanup"
    echo -e "${DIM}Removing temporary files...${NC}"
    rm -rf $BUILD_DIR
    print_status "Cleanup" "OK"
}

# Print completion message
print_completion() {
    printf "%${TERM_WIDTH}s\n" | tr ' ' '═'
    echo -e "${BOLD}${GREEN}                            Installation Complete!${NC}"
    printf "%${TERM_WIDTH}s\n" | tr ' ' '═'
    echo -e "\n${BOLD}${WHITE}Available commands:${NC}"
    echo -e "  ${CYAN}dragon-fetch${NC}  - Display dragon-style system information"
    echo -e "  ${CYAN}sys-fetch${NC}     - Display alternative system information"
    echo
    echo -e "${BOLD}${WHITE}Installation location:${NC} $INSTALL_DIR"
    echo -e "${BOLD}${WHITE}Log file:${NC} $LOG_FILE"
    echo
    echo -e "${DIM}Thank you for installing Fetch Tools!${NC}"
    printf "%${TERM_WIDTH}s\n\n" | tr ' ' '═'
}

# Main function
main() {
    print_banner
    check_root
    detect_os
    install_dependencies
    build_tools
    install_tools
    configure_fetch
    cleanup
    print_completion
}

# Run main with error logging
{
    main "$@"
} 2>&1 | tee -a "$LOG_FILE"
