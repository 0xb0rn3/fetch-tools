#!/usr/bin/env bash

# Color definitions for consistent and attractive UI elements
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

# Configuration variables
VERSION="0.0.4"
INSTALL_DIR="/usr/bin"
BUILD_DIR="build"
LOG_FILE="/tmp/fetch_install_$(date +%Y%m%d_%H%M%S).log"
TERM_WIDTH=$(tput cols)
CURRENT_USER=$SUDO_USER
USER_HOME=$(getent passwd $SUDO_USER | cut -d: -f6)
ZSH_CUSTOM="$USER_HOME/.oh-my-zsh/custom"

# Display the application banner
print_banner() {
    clear
    echo
    printf "%${TERM_WIDTH}s\n" | tr ' ' '━'
    echo -e "${BOLD}${BLUE}"
    echo '   ┌─────────────────────────────────┐'
    echo '   │          FETCH TOOLS            │'
    echo '   │    System Info Display Suite    │'
    echo '   └─────────────────────────────────┘'
    echo -e "${NC}"
    echo -e "${BOLD}${PURPLE}       Setup & Configuration Tool${NC}"
    echo -e "${DIM}          Version $VERSION - LATEST${NC}"
    printf "%${TERM_WIDTH}s\n" | tr ' ' '━'
    echo
}

# Print formatted status messages
print_status() {
    local text="$1"
    local status="$2"
    printf "${ITALIC}%-45s" "$text"
    case $status in
        "OK")     echo -e "${GREEN}✓ Done${NC}" ;;
        "FAIL")   echo -e "${RED}✗ Failed${NC}" ;;
        "WARN")   echo -e "${YELLOW}⚠ Warning${NC}" ;;
        "INFO")   echo -e "${BLUE}ℹ Info${NC}" ;;
        "SKIP")   echo -e "${GRAY}⏭ Skipped${NC}" ;;
        *)        echo -e "${PURPLE}⋯ $status${NC}" ;;
    esac
}

# Display section headers
print_section() {
    local text="$1"
    echo -e "\n${BOLD}${CYAN}◆ ${text}${NC}"
    echo -e "${DIM}$(printf '%.s─' $(seq 1 $TERM_WIDTH))${NC}"
}

# Show progress spinner animation
show_spinner() {
    local pid=$1
    local text="$2"
    local spin='⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏'
    local i=0
    
    while kill -0 $pid 2>/dev/null; do
        i=$(( (i + 1) % 10 ))
        printf "\r${ITALIC}%-45s${NC} ${BLUE}${spin:$i:1}${NC}" "$text"
        sleep .1
    done
    printf "\r%-45s${GREEN}✓${NC}\n" "$text"
}

# Handle shell changing functionality
change_shell() {
    print_section "Shell Configuration"
    
    local current_shell=$(getent passwd $SUDO_USER | cut -d: -f7)
    local zsh_path=$(which zsh)
    
    if [ "$current_shell" = "$zsh_path" ]; then
        print_status "Current Shell" "Already using Zsh"
        return 0
    fi
    
    echo -e "${CYAN}Current shell: ${GRAY}$current_shell${NC}"
    echo -e "${CYAN}Available shell: ${GRAY}$zsh_path${NC}\n"
    
    if [ ! -f "$zsh_path" ]; then
        print_status "Zsh Installation" "FAIL"
        echo -e "${RED}Zsh not found. Installing dependencies first...${NC}"
        return 1
    fi
    
    if ! grep -q "^$zsh_path\$" /etc/shells; then
        echo -e "${DIM}Adding Zsh to /etc/shells...${NC}"
        echo "$zsh_path" >> /etc/shells
    fi
    
    echo -e "${CYAN}Would you like to change your default shell to Zsh? [y/N]${NC}"
    read -r -n 1 change_shell_choice
    echo
    
    if [[ "$change_shell_choice" =~ ^[Yy]$ ]]; then
        (chsh -s "$zsh_path" $SUDO_USER >/dev/null 2>&1) &
        show_spinner $! "Changing default shell"
        
        if [ $? -eq 0 ]; then
            print_status "Shell Change" "OK"
            echo -e "${GREEN}✓ Shell successfully changed to Zsh${NC}"
        else
            print_status "Shell Change" "FAIL"
            echo -e "${RED}✗ Failed to change shell${NC}"
        fi
    else
        print_status "Shell Change" "SKIP"
    fi
}

# Verify root privileges
check_root() {
    if [ "$EUID" -ne 0 ]; then
        print_status "Root Privileges" "FAIL"
        echo -e "${RED}Please run with sudo privileges${NC}"
        exit 1
    fi
    if [ -z "$SUDO_USER" ]; then
        print_status "User Detection" "FAIL"
        echo -e "${RED}Please run with sudo, not as root${NC}"
        exit 1
    fi
    print_status "Privilege Check" "OK"
}

# Detect operating system and set package manager
detect_os() {
    print_section "System Detection"
    
    if [ -f "/etc/debian_version" ]; then
        PM="apt-get"
        PM_INSTALL="$PM install -y"
        PM_UPDATE="$PM update"
        REQUIRED_PACKAGES="build-essential zsh git curl"
        OS="Debian"
    elif [ -f "/etc/arch-release" ]; then
        PM="pacman"
        PM_INSTALL="$PM -S --noconfirm"
        PM_UPDATE="$PM -Sy"
        REQUIRED_PACKAGES="base-devel zsh git curl"
        OS="Arch"
    elif [ -f "/etc/redhat-release" ]; then
        PM="dnf"
        PM_INSTALL="$PM install -y"
        PM_UPDATE="$PM update -y"
        REQUIRED_PACKAGES="gcc gcc-c++ make zsh git curl"
        OS="RedHat"
    else
        print_status "OS Detection" "FAIL"
        echo -e "${RED}Unsupported distribution${NC}"
        exit 1
    fi
    
    print_status "OS Detection" "OK"
    echo -e "${DIM}Detected: $OS Linux${NC}"
}

# Install required dependencies
install_dependencies() {
    print_section "Installing Dependencies"
    
    echo -e "${DIM}Updating package database...${NC}"
    ($PM_UPDATE >/dev/null 2>&1) &
    show_spinner $! "Updating package manager"
    
    echo -e "${DIM}Installing required packages...${NC}"
    ($PM_INSTALL $REQUIRED_PACKAGES >/dev/null 2>&1) &
    show_spinner $! "Installing build dependencies"
}

# Install Oh My Zsh framework
install_oh_my_zsh() {
    print_section "Installing Oh My Zsh"
    
    if [ -d "$USER_HOME/.oh-my-zsh" ]; then
        print_status "Oh My Zsh" "Already installed"
        return 0
    fi

    (sudo -u $SUDO_USER sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" "" --unattended >/dev/null 2>&1) &
    show_spinner $! "Installing Oh My Zsh"
    print_status "Oh My Zsh Setup" "OK"
}

# Install Zsh plugins
install_zsh_plugins() {
    print_section "Installing ZSH Plugins"
    
    local plugins=(
        "zsh-syntax-highlighting;https://github.com/zsh-users/zsh-syntax-highlighting.git"
        "zsh-autosuggestions;https://github.com/zsh-users/zsh-autosuggestions.git"
    )
    
    for plugin in "${plugins[@]}"; do
        IFS=';' read -r name url <<< "$plugin"
        local plugin_dir="$ZSH_CUSTOM/plugins/$name"
        
        if [ ! -d "$plugin_dir" ]; then
            (sudo -u $SUDO_USER git clone --depth=1 "$url" "$plugin_dir" >/dev/null 2>&1) &
            show_spinner $! "Installing $name"
        else
            print_status "$name" "Already installed"
        fi
    done
}

# Build fetch tools from source
build_tools() {
    print_section "Building Fetch Tools"
    
    mkdir -p $BUILD_DIR
    make clean >/dev/null 2>&1
    
    (make >/dev/null 2>&1) &
    show_spinner $! "Compiling fetch tools"
    
    if [ $? -ne 0 ]; then
        print_status "Build Process" "FAIL"
        exit 1
    fi
    
    print_status "Build Process" "OK"
}

# Install built tools
install_tools() {
    print_section "Installing Fetch Tools"
    
    (
        install -m 755 $BUILD_DIR/dragon-fetch $INSTALL_DIR/
        install -m 755 $BUILD_DIR/anime-fetch $INSTALL_DIR/
    ) &
    show_spinner $! "Installing binaries"
    print_status "Installation" "OK"
}

# Configure Zsh settings
configure_zsh() {
    print_section "Configuring ZSH"
    
    local zshrc="$USER_HOME/.zshrc"
    
    if [ -f "$zshrc" ]; then
        cp "$zshrc" "$zshrc.backup.$(date +%Y%m%d_%H%M%S)"
    fi
    
    cat templates/zshrc.template > "$zshrc"
    chown $SUDO_USER:$SUDO_USER "$zshrc"
    chmod 644 "$zshrc"
    
    echo -e "${CYAN}Select default fetch tool:${NC}"
    echo -e "1) ${RED}Dragon Fetch${NC}  - Dragon style system info"
    echo -e "2) ${BLUE}Anime Fetch${NC}   - Anime style system info"
    echo -e "3) ${GRAY}None${NC}         - Don't set a default\n"
    
    read -p "Enter choice [1-3]: " choice
    
    case $choice in
        1)
            echo 'command -v dragon-fetch >/dev/null && dragon-fetch' >> "$zshrc"
            print_status "Default Tool" "Dragon Fetch"
            ;;
        2)
            echo 'command -v anime-fetch >/dev/null && anime-fetch' >> "$zshrc"
            print_status "Default Tool" "Anime Fetch"
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

# Clean up temporary files
cleanup() {
    print_section "Cleanup"
    (rm -rf $BUILD_DIR) &
    show_spinner $! "Removing temporary files"
    print_status "Cleanup" "OK"
}

# Display completion message
print_completion() {
    printf "%${TERM_WIDTH}s\n" | tr ' ' '━'
    echo -e "${BOLD}${GREEN}             Installation Complete!${NC}"
    printf "%${TERM_WIDTH}s\n" | tr ' ' '━'
    echo -e "\n${BOLD}${WHITE}Available commands:${NC}"
    echo -e "  ${CYAN}dragon-fetch${NC}  - Dragon-style system info"
    echo -e "  ${CYAN}anime-fetch${NC}   - Anime-style system info"
    echo
    echo -e "${BOLD}${WHITE}Locations:${NC}"
    echo -e "  ${DIM}Installation:${NC} $INSTALL_DIR"
    echo -e "  ${DIM}Configuration:${NC} $USER_HOME/.zshrc"
    echo -e "  ${DIM}Log file:${NC} $LOG_FILE"
    echo
    echo -e "${YELLOW}Please log out and log back in to apply all changes${NC}"
    printf "%${TERM_WIDTH}s\n\n" | tr ' ' '━'
}

# Main execution flow
main() {
    print_banner
    check_root
    detect_os
    install_dependencies
    install_oh_my_zsh
    install_zsh_plugins
    build_tools
    install_tools
    change_shell
    configure_zsh
    cleanup
    print_completion
}

# Run main function with logging
{
    main "$@"
} 2>&1 | tee -a "$LOG_FILE"

if [ $? -eq 0 ]; then
    clear
    echo -e "${GREEN} Installation completed successfully!${NC}"
    echo -e "${YELLOW} Please log out and log back in to see the changes.${NC}"
    sleep 2
else
    echo -e "${RED} Installation encountered some issues. Please check the log file: $LOG_FILE${NC}"
fi
