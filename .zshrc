# ~/.zshrc file for zsh interactive shells.

# Path to your oh-my-zsh installation.
export ZSH="$HOME/.oh-my-zsh"

# Set name of the theme to load
# ZSH_THEME="robbyrussell"

# Plugin list
plugins=(
  git
  colored-man-pages
  command-not-found
  extract
  sudo
  history
  dirhistory
  copypath
  copyfile
  web-search
  urltools
  zsh-syntax-highlighting
  zsh-autosuggestions
)

# Source oh-my-zsh
# source $ZSH/oh-my-z.sh

# Enable features and set options
setopt autocd              # change directory just by typing its name
setopt interactivecomments # allow comments in interactive mode
setopt magicequalsubst     # enable filename expansion for arguments of the form ‘anything=expression’
setopt nonomatch           # hide error message if there is no match for the pattern
setopt notify              # report the status of background jobs immediately
setopt numericglobsort     # sort filenames numerically when it makes sense
setopt promptsubst         # enable command substitution in prompt
WORDCHARS=${WORDCHARS//\/} # Don't consider certain characters part of the word

# hide EOL sign ('%')
PROMPT_EOL_MARK=""

# Configure key bindings
bindkey -e                                        # emacs key bindings
bindkey ' ' magic-space                           # do history expansion on space
bindkey '^U' backward-kill-line                   # ctrl + U
bindkey '^[[3;5~' kill-word                       # ctrl + Supr
bindkey '^[[3~' delete-char                       # delete
bindkey '^[[1;5C' forward-word                    # ctrl + ->
bindkey '^[[1;5D' backward-word                   # ctrl + <-
bindkey '^[[5~' beginning-of-buffer-or-history    # page up
bindkey '^[[6~' end-of-buffer-or-history          # page down
bindkey '^[[H' beginning-of-line                  # home
bindkey '^[[F' end-of-line                        # end
bindkey '^[[Z' undo                               # shift + tab undo

# Enable completion features
autoload -Uz compinit
compinit -d ~/.cache/zcompdump

# Configure completion styles
zstyle ':completion:*' menu select
zstyle ':completion:*' auto-description 'specify: %d'
zstyle ':completion:*' completer _expand _complete
zstyle ':completion:*' format 'Completing %d'
zstyle ':completion:*' group-name ''
zstyle ':completion:*' list-colors ''
zstyle ':completion:*' list-prompt %SAt %p: Hit TAB for more, or the character to insert%s
zstyle ':completion:*' matcher-list 'm:{a-zA-Z}={A-Za-z}'
zstyle ':completion:*' rehash true
zstyle ':completion:*' verbose true
zstyle ':completion:*:kill:*' command 'ps -u $USER -o pid,%cpu,tty,cputime,cmd'
zstyle ':completion:*:*:*:*:*' menu select=2  # Enable menu selection for completions
zstyle ':completion:*' use-cache yes           # Enable caching for completions
zstyle ':completion:*' cache-path ~/.cache/zsh-completions  # Set cache path for completions
setopt complete_in_word                          # Complete words in the middle of the command
setopt auto_list                                 # Automatically list completions if there's more than one
#setopt long_list_types                           # Enable long listing for completion types

# Activate command-not-found handler
if [ -f /usr/share/zsh/functions/Completion/Unix/CommandNotFound.zsh ]; then
    . /usr/share/zsh/functions/Completion/Unix/CommandNotFound.zsh
fi

# History configurations
HISTFILE=~/.zsh_history
HISTSIZE=1000
SAVEHIST=2000
setopt hist_expire_dups_first # delete duplicates first when HISTFILE size exceeds HISTSIZE
setopt hist_ignore_dups       # ignore duplicated commands history list
setopt hist_ignore_space      # ignore commands that start with space
setopt hist_verify            # show command with history expansion to user before running it

# Force zsh to show the complete history
alias history="history 0"

# Configure time format
TIMEFMT=$'\nreal\t%E\nuser\t%U\nsys\t%S\ncpu\t%P'

# Set variable identifying the chroot you work in (used in the prompt below)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# Set a fancy prompt (non-color, unless we know we "want" color)
case "$TERM" in
    xterm-color|*-256color) color_prompt=yes;;
esac

# Enable colored prompt if terminal has the capability
force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
        color_prompt=yes
    else
        color_prompt=
    fi
fi

# Configure custom prompt
configure_prompt() {
autoload -U colors && colors
PROMPT="%{$fg[red]%}╭─[%{$fg[white]%}ソロックス💀arch%{$fg[red]%}]-[%{$fg[white]%}%~%{$fg[red]%}]
╰─○ %{$reset_color%}" 
}
# Kali config variables (do not modify)
PROMPT_ALTERNATIVE='twoline'
NEWLINE_BEFORE_PROMPT='no'

if [ "$color_prompt" = yes ]; then
    VIRTUAL_ENV_DISABLE_PROMPT=1
    configure_prompt

    # Enable syntax-highlighting with dimmed colors
    if [ -f /usr/share/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh ]; then
        . /usr/share/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh
        ZSH_HIGHLIGHT_HIGHLIGHTERS=(main brackets pattern)
        ZSH_HIGHLIGHT_STYLES[default]=none
        ZSH_HIGHLIGHT_STYLES[unknown-token]=fg=160
        ZSH_HIGHLIGHT_STYLES[reserved-word]=fg=037,bold
        ZSH_HIGHLIGHT_STYLES[suffix-alias]=fg=064,underline
        ZSH_HIGHLIGHT_STYLES[global-alias]=fg=064,bold
        ZSH_HIGHLIGHT_STYLES[precommand]=fg=064,underline
        ZSH_HIGHLIGHT_STYLES[commandseparator]=fg=160
        ZSH_HIGHLIGHT_STYLES[autodirectory]=fg=064,underline
        ZSH_HIGHLIGHT_STYLES[path]=fg=178
        ZSH_HIGHLIGHT_STYLES[globbing]=fg=160
        ZSH_HIGHLIGHT_STYLES[history-expansion]=fg=160
        ZSH_HIGHLIGHT_STYLES[command-substitution]=none
        ZSH_HIGHLIGHT_STYLES[variable]=fg=178
    fi
    
    # Enable auto-completion
    if [ -f /usr/share/zsh/functions/Completion/Unix/CommandNotFound.zsh ]; then
        . /usr/share/zsh/functions/Completion/Unix/CommandNotFound.zsh
    fi

    # Enable history sharing between shells
    setopt share_history

    # Add custom bin directory to PATH
    export PATH="$HOME/bin:$PATH"
fi

# Load environment variables
if [ -f ~/.zshenv ]; then
    source ~/.zshenv
fi

# Add any other custom functions or aliases here
# Customize ls colors for a dimmed appearance
export LS_COLORS="di=1;34:ln=35:so=32:pi=33:ex=31:bd=34;46:cd=34;43:su=30;41:sg=30;46:tw=30;42:ow=30;43"

# Alias for listing files
alias ll='ls -l'
alias la='ls -A'
alias l='ls -CF'
alias cls='clear'
alias z3t4rupdate='sudo apt update && sudo apt upgrade -y && sudo apt autoremove'

# Show hidden files in directory listing
export LS_OPTIONS='--color=auto'
eval "$(dircolors -b)"

# Custom functions can be defined here
# e.g. alias lsd='ls --color=auto -l'

# Add color to man pages
export LESS_TERMCAP_mb=$'\E[1;31m'     
export LESS_TERMCAP_md=$'\E[1;36m'     
export LESS_TERMCAP_me=$'\E[0m'        
export LESS_TERMCAP_so=$'\E[01;44;33m' 
export LESS_TERMCAP_se=$'\E[0m'        
export LESS_TERMCAP_us=$'\E[1;32m'     
export LESS_TERMCAP_ue=$'\E[0m'        

# Colored GCC warnings and errors
export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'

# Pentesting-specific aliases
alias nmap-quick='sudo nmap -sV -O -F --version-light'
alias nmap-full='sudo nmap -sV -O -p- -v'
alias metasploit='msfconsole'
alias set-mac='sudo macchanger -r eth0'
alias wifi-scan='sudo airodump-ng wlan0mon'
alias start-beef='sudo beef-xss'
# Add the following aliases after your existing aliases (after the 'start-beef' alias)

# Network security aliases
alias myip='curl ifconfig.me'  # Show public IP address
alias ports='netstat -tulanp'  # List all open ports
alias listening='lsof -i -P | grep LISTEN'  # Show listening ports
alias ssh-list='ss | grep ssh'  # List active SSH connections
alias iptables-list='sudo iptables -L -n -v'  # Show iptables rules

# File and system security aliases
alias check-rootkits='sudo rkhunter --check'  # Check for rootkits
alias scan-malware='sudo clamscan -r /'  # Scan system for malware
alias files-changed='sudo find / -mtime -1 -type f -print'  # List files changed in last 24 hours

# Log analysis aliases
alias auth-log='sudo tail -f /var/log/auth.log'  # Show live authentication log
alias syslog='sudo tail -f /var/log/syslog'  # Show live system log

# Pentesting tool aliases
alias nmap-vuln='nmap --script vuln'  # Run nmap vulnerability scan
alias nikto-scan='nikto -h'  # Run Nikto web server scanner
alias dirb-scan='dirb'  # Run dirb web content scanner
alias sqlmap-basic='sqlmap --wizard'  # Run sqlmap in wizard mode

# Encryption and hashing aliases
alias encrypt-file='gpg -c'  # Encrypt a file
alias decrypt-file='gpg -d'  # Decrypt a file
alias hash-file='sha256sum'  # Generate SHA256 hash of a file

# Network analysis aliases
alias tcpdump-basic='sudo tcpdump -i any'  # Capture network traffic
alias wireshark='sudo wireshark'  # Launch Wireshark

# Security information aliases
alias kernel-version='uname -a'  # Show kernel version
alias os-version='cat /etc/os-release'  # Show OS version
alias list-users='cat /etc/passwd'  # List all users
alias list-sudoers='sudo cat /etc/sudoers'  # List users with sudo privileges
# Function to start a simple HTTP server
function http-server() {
  python3 -m http.server
}
