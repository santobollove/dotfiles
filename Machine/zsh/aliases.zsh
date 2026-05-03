# --- Aliases ---
alias rmf='rm -rf'
alias mkzip='zip -r'
alias Fd='fd -c always'
alias vlang='command v'
alias v='nvim'
alias V='sudo -E nvim'
alias py='python'
alias Dl='cd ~/Machine/Downloads'
alias Anime='cd ~/Media/Anime'
alias GH='cd ~/Development/Git'
alias Gist='gist -c'
alias matrix='unimatrix -lgGonS -a -o -s 97 | lolcat'
alias h='bpytop'
alias pcin='sudo dnf install'
alias pcup='sudo dnf update'
alias pcrm='sudo dnf remove'
alias untar='tar -xvf'
alias top10='print -l ${(o)history%% *} | uniq -c | sort -nr | head -n 10'
alias passin='pass insert'
alias ytp='ytfzf -t'
alias pdf='zathura'
alias exp='searchsploit'
alias Xclip='xclip -sel clip'
alias dotc='/bin/git --git-dir=$HOME/Machine/DotFile --work-tree=$HOME'
alias ranger='lf'
alias live='live-server --no-css-inject'

# LS Shortcuts
alias l='lsd -F'
alias ls='lsd'
alias ld='lsd -d */'
alias lsa='l -A'
alias la='l -l'
alias ll='l -ld .?*'
alias lla='ls -lAh'
alias lt='l --tree'

# Utilities (Global Aliases)
alias -g g='grep --color=auto --perl-regexp'
alias -g G='| grep --color=auto --perl-regexp'
alias -g clip='xclip -selection clipboard'
alias grub-update='sudo grub-mkconfig -o /boot/grub/grub.cfg'

# Git
alias sign-on='git config commit.gpgsign true'
alias sign-off='git config commit.gpgsign false'

# --- Functions ---

# Create and move to directory
mcd() {
    mkdir -p "$1" && cd "$1"
}

# Virtualenv activator
activate() {
    local act_file
    act_file=$(find . -maxdepth 2 -type f -name activate)
    if [[ -n "$act_file" ]]; then
        source "$act_file"
    else
        echo "No activation file found."
    fi
}

# Set audio volume
bass() {
    pactl set-sink-volume @DEFAULT_SINK@ "${1:-50}%"
}

# Edit binary/command path
bine() {
    local cmd_path
    cmd_path=$(which "$1" 2>/dev/null)
    if [[ -n "$cmd_path" ]]; then
        $EDITOR "$cmd_path"
    else
        echo "Command not found: $1"
    fi
}

