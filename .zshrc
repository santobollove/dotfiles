#!/bin/zsh

# --- 1. Core Settings & Performance ---
typeset -g comppath="$HOME/.cache/zsh"
typeset -g compfile="$comppath/zcompdump"
[[ -d "$comppath" ]] || mkdir -p "$comppath"

HISTSIZE=100000
SAVEHIST=100000
HISTFILE="$HOME/.cache/zsh/zsh_history"
KEYTIMEOUT=1

export MANWIDTH=120
export LESS='-R'
export LESSHISTFILE=-
export LESS_TERMCAP_me=$'\e[0m'
export LESS_TERMCAP_se=$'\e[0m'
export LESS_TERMCAP_ue=$'\e[0m'
export LESS_TERMCAP_us=$'\e[32m'
export LESS_TERMCAP_md=$'\e[31m'

# --- 2. Shell Options ---
setopt AUTO_CD AUTO_CONTINUE CORRECT NO_NOMATCH LIST_PACKED ALWAYS_TO_END 
setopt COMPLETE_ALIASES COMPLETE_IN_WORD HIST_VERIFY SHARE_HISTORY
setopt HIST_IGNORE_SPACE HIST_SAVE_NO_DUPS HIST_IGNORE_ALL_DUPS EXTENDED_GLOB
setopt TRANSIENT_RPROMPT INTERACTIVE_COMMENTS LONG_LIST_JOBS

# --- 3. Completion & Widgets ---
autoload -Uz compinit terminfo promptinit
zmodload -i zsh/complist
promptinit

# History search (sudo filtering)
autoload -U up-line-or-beginning-search
autoload -U down-line-or-beginning-search
zle -N up-line-or-beginning-search
zle -N down-line-or-beginning-search

# Terminal mode configuration
if (( ${+terminfo[smkx]} && ${+terminfo[rmkx]} )); then
    zle-line-init() { echoti smkx; }; zle -N zle-line-init
    zle-line-finish() { echoti rmkx; }; zle -N zle-line-finish
fi

# Custom helper: Tab-completion logic
first_tab() {
    if [[ $#BUFFER == 0 ]]; then
        BUFFER="cd " CURSOR=3
        zle list-choices
        BUFFER="" CURSOR=1
    else
        zle expand-or-complete
    fi
}
zle -N first_tab

# --- 4. Bindings ---
bindkey '^?' backward-delete-char
bindkey -- '^I'   first_tab
bindkey -- '^K'   up-line-or-beginning-search
bindkey -- '^J'   down-line-or-beginning-search

[[ -n ${terminfo[kcuu1]} ]] && bindkey -- "${terminfo[kcuu1]}" up-line-or-beginning-search
[[ -n ${terminfo[kcud1]} ]] && bindkey -- "${terminfo[kcud1]}" down-line-or-beginning-search
[[ -n ${terminfo[kdch1]} ]] && bindkey -- "${terminfo[kdch1]}" delete-char
[[ -n ${terminfo[kend]}  ]] && bindkey -- "${terminfo[kend]}"  end-of-line
[[ -n ${terminfo[kcuf1]} ]] && bindkey -- "${terminfo[kcuf1]}" forward-char
[[ -n ${terminfo[khome]} ]] && bindkey -- "${terminfo[khome]}" beginning-of-line
[[ -n ${terminfo[kcub1]} ]] && bindkey -- "${terminfo[kcub1]}" backward-char

# --- 5. Completion Logic (Prioritizing Commands) ---
zstyle ':completion:*' use-cache on
zstyle ':completion:*' cache-path "$comppath"

# Force command/option completion first; file paths last
zstyle ':completion:*' completer _extensions _complete _approximate
zstyle ':completion:*' tag-order 'commands' 'builtins' 'functions' 'aliases' 'options' 'parameters' 'local-directories' 'path-directories' 'files'

# UI Settings
zstyle ':completion:*:*:*:*:*' menu select
zstyle ':completion:*' matcher-list 'm:{a-zA-Z}={A-Za-z}' 'r:|[._-]=* r:|=*' 'l:|=* r:|=*'
zstyle ':completion:*' list-dirs-first false

# Ignore binary/media files in editor completion
zstyle ':completion:*:(vim|nvim|vi|nano):*' ignored-patterns '*.(wav|mp3|flac|iso|so|o|zip|tar|gz|pdf|png|jpeg|jpg|gif)'

# Advanced SSH/SCP host completion
zstyle ':completion:*:ssh:*' tag-order 'hosts:-host:host hosts:-domain:domain hosts:-ipaddr:ip\ address *'
zstyle ':completion:*:(scp|rsync):*' tag-order 'hosts:-host:host hosts:-domain:domain hosts:-ipaddr:ip\ address *'
# --- Setup ZINIT ---
ZINIT_HOME="${XDG_DATA_HOME:-${HOME}/.local/share}/zinit/zinit.git"

[ ! -d $ZINIT_HOME ] && mkdir -p "$(dirname $ZINIT_HOME)"
[ ! -d $ZINIT_HOME/.git ] && git clone --depth 1 --recurse-submodules \
    https://github.com/zdharma-continuum/zinit.git "$ZINIT_HOME"

autoload -Uz compinit
compinit -u -d "$compfile"

source "${ZINIT_HOME}/zinit.zsh"
# --- 6. Plugins (Zinit) ---
zinit light zsh-users/zsh-autosuggestions
zinit light zdharma-continuum/fast-syntax-highlighting
zinit light sindresorhus/pure
zinit light mfaerevaag/wd
zinit snippet OMZP::git

# --- 7. Aliases & Finalization ---
alias l='lsd -F'
alias ls='lsd'
[[ -r $HOME/Machine/zsh/aliases.zsh ]] && source $HOME/Machine/zsh/aliases.zsh

export GPG_TTY=$(tty)
