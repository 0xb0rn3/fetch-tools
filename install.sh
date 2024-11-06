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
CURRENT_USER=$SUDO_USER
USER_HOME=$(getent passwd $SUDO_USER | cut -d: -f6)

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
    if [ -z "$SUDO_USER" ]; then
        print_status "User Detection" "FAIL"
        echo -e "${RED}Please run with sudo, not as root directly${NC}"
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
    install -m 755 $BUILD_DIR/anime-fetch $INSTALL_DIR/
    
    print_status "Installation" "OK"
}

# Configure fetch tool
configure_fetch() {
    print_section "Configuration"
    
    # First, select installation scope
    echo -e "${CYAN}Select installation scope:${NC}"
    echo -e "1) User-specific  - Configure for current user only"
    echo -e "2) System-wide    - Configure for all users"
    echo -e "3) Both          - Configure for both current user and system-wide\n"
    
    read -p "Enter scope [1-3]: " scope_choice
    
    # Then select fetch tool
    echo -e "\n${CYAN}Select default fetch tool:${NC}"
    echo -e "1) Dragon Fetch  - Dragon style system info (Red theme)"
    echo -e "2) Anime Fetch   - Anime style system info (Cyan theme)"
    echo -e "3) None         - Don't set a default\n"
    
    read -p "Enter fetch tool [1-3]: " tool_choice

    # Prepare configuration content based on tool choice
    case $tool_choice in
        1)
            FETCH_CMD="command -v dragon-fetch >/dev/null && dragon-fetch"
            TOOL_NAME="Dragon Fetch"
            ;;
        2)
            FETCH_CMD="command -v anime-fetch >/dev/null && anime-fetch"
            TOOL_NAME="Anime Fetch"
            ;;
        3)
            FETCH_CMD=""
            TOOL_NAME="None"
            ;;
        *)
            print_status "Tool Selection" "WARN"
            echo -e "${YELLOW}Invalid choice. No default set.${NC}"
            return
            ;;
    esac

    # Add term function definition
    TERM_FUNC='# Term function definition
term() {
    clear
}
'

    # Apply configurations based on scope choice
    case $scope_choice in
        1|3)
            # User-specific configuration
            USER_ZSHRC="$USER_HOME/.zshrc"
            
            # Backup existing configuration
            if [ -f "$USER_ZSHRC" ]; then
                cp "$USER_ZSHRC" "$USER_ZSHRC.backup"
                # Remove existing configurations
                sed -i '/dragon-fetch/d' "$USER_ZSHRC"
                sed -i '/anime-fetch/d' "$USER_ZSHRC"
                sed -i '/term()/d' "$USER_ZSHRC"
                sed -i '/^term/d' "$USER_ZSHRC"
            fi
            
            # Add new configuration
            echo "$TERM_FUNC" >> "$USER_ZSHRC"
            if [ ! -z "$FETCH_CMD" ]; then
                echo "# Fetch tool configuration" >> "$USER_ZSHRC"
                echo "$FETCH_CMD" >> "$USER_ZSHRC"
            fi
            chown $SUDO_USER:$SUDO_USER "$USER_ZSHRC"
            print_status "User Configuration" "OK"
            ;;
    esac
    
    case $scope_choice in
        2|3)
            # System-wide configuration
            mkdir -p /etc/zsh
            GLOBAL_ZSHRC="/etc/zsh/zshrc"
            
            # Backup existing configuration
            if [ -f "$GLOBAL_ZSHRC" ]; then
                cp "$GLOBAL_ZSHRC" "$GLOBAL_ZSHRC.backup"
                # Remove existing configurations
                sed -i '/dragon-fetch/d' "$GLOBAL_ZSHRC"
                sed -i '/anime-fetch/d' "$GLOBAL_ZSHRC"
                sed -i '/term()/d' "$GLOBAL_ZSHRC"
                sed -i '/^term/d' "$GLOBAL_ZSHRC"
            fi
            
            # Add new configuration
            echo "$TERM_FUNC" >> "$GLOBAL_ZSHRC"
            if [ ! -z "$FETCH_CMD" ]; then
                echo "# Fetch tool configuration" >> "$GLOBAL_ZSHRC"
                echo "$FETCH_CMD" >> "$GLOBAL_ZSHRC"
            fi
            chmod 644 "$GLOBAL_ZSHRC"
            print_status "System-wide Configuration" "OK"
            ;;
    esac

    print_status "Default Tool" "$TOOL_NAME"
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
    echo -e "  ${CYAN}anime-fetch${NC}   - Display anime-style system information"
    echo -e "  ${CYAN}term${NC}          - Clear screen"
    echo
    echo -e "${BOLD}${WHITE}Installation location:${NC} $INSTALL_DIR"
    echo -e "${BOLD}${WHITE}Log file:${NC} $LOG_FILE"
    
    case $scope_choice in
        1) echo -e "${BOLD}${WHITE}Configuration:${NC} $USER_HOME/.zshrc" ;;
        2) echo -e "${BOLD}${WHITE}Configuration:${NC} /etc/zsh/zshrc" ;;
        3) echo -e "${BOLD}${WHITE}Configurations:${NC} $USER_HOME/.zshrc and /etc/zsh/zshrc" ;;
    esac
    
    echo
    echo -e "${DIM}Please restart your terminal or run 'source ~/.zshrc' to apply changes${NC}"
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
