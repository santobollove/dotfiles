#!/bin/zsh

# Debug start
ZBUG=0
if [ 1 -eq "$ZBUG" ]; then
	zmodload zsh/zprof
	zmodload zsh/datetime
	setopt PROMPT_SUBST
	PS4='+$EPOCHREALTIME %N:%i> '

	logfile=$(mktemp zsh_profile.XXXXXXXX)
	echo "Logging to $logfile"
	exec 3>&2 2>$logfile

	setopt XTRACE
	setopt xtrace prompt_subst
fi

if [[ $- != *i* ]]; then
	return
fi

# completion cache path setup
typeset -g comppath="$HOME/.cache/zsh"
typeset -g compfile="$comppath/zcompdump"

if [[ -d "$comppath" ]]; then
	[[ -w "$compfile" ]] || rm -rf "$compfile" >/dev/null 2>&1
else
	mkdir -p "$comppath"
fi

# zsh internal stuff
SHELL=$(which zsh || echo '/usr/bin/zsh')
KEYTIMEOUT=1
SAVEHIST=100000
HISTSIZE=100000
HISTFILE="$ZDOTDIR/cache/zsh_history"

src() # recompile completion and reload zsh
{
	autoload -U zrecompile
	rm -rf "$compfile"*
	compinit -u -d "$compfile"
	zrecompile -p "$compfile"
	exec zsh
}

wd() {
    . /usr/share/wd/wd.sh
}

mcd() {
    mkdir "$1"; cd "$1"
}

# less/manpager colours
export MANWIDTH=120
export LESS='-R'
export LESSHISTFILE=-
export LESS_TERMCAP_me=$'\e[0m'
export LESS_TERMCAP_se=$'\e[0m'
export LESS_TERMCAP_ue=$'\e[0m'
export LESS_TERMCAP_us=$'\e[32m'
export LESS_TERMCAP_mb=$'\e[31m'
export LESS_TERMCAP_md=$'\e[31m'
export LESS_TERMCAP_so=$'\e[47;30m'
export LESSPROMPT='?f%f .?ltLine %lt:?pt%pt\%:?btByte %bt:-...'

# completion
setopt CORRECT
setopt NO_NOMATCH
setopt LIST_PACKED
setopt ALWAYS_TO_END
setopt GLOB_COMPLETE
setopt COMPLETE_ALIASES
setopt COMPLETE_IN_WORD

# builtin command behaviour
setopt AUTO_CD

# job control
setopt AUTO_CONTINUE
setopt LONG_LIST_JOBS

# history control
setopt HIST_VERIFY
setopt SHARE_HISTORY
setopt HIST_IGNORE_SPACE
setopt HIST_SAVE_NO_DUPS
setopt HIST_IGNORE_ALL_DUPS

# misc
setopt EXTENDED_GLOB
setopt TRANSIENT_RPROMPT
setopt INTERACTIVE_COMMENTS


autoload -Uz compinit     # completion
autoload -U terminfo     # terminfo keys
zmodload -i zsh/complist # menu completion
autoload -U promptinit   # prompt

# better history navigation, matching currently typed text
autoload -U up-line-or-beginning-search; zle -N up-line-or-beginning-search
autoload -U down-line-or-beginning-search; zle -N down-line-or-beginning-search

# set the terminal mode when entering or exiting zle, otherwise terminfo keys are not loaded
if (( ${+terminfo[smkx]} && ${+terminfo[rmkx]} )); then
	zle-line-init() { echoti smkx; }; zle -N zle-line-init
	zle-line-finish() { echoti rmkx; }; zle -N zle-line-finish
fi

first_tab() # on first tab without any text it will list the current directory
{ # empty line tab lists
	if [[ $#BUFFER == 0 ]]; then
		BUFFER="cd " CURSOR=3
		zle list-choices
		BUFFER="" CURSOR=1
	else
		zle expand-or-complete
	fi
}; zle -N first_tab

# bind keys not in terminfo
bindkey -- '^I'   first_tab
# bindkey -- ' '    exp_alias
bindkey -- '^P'   up-history
bindkey -- '^N'   down-history
bindkey -- '^E'   end-of-line
bindkey -- '^A'   beginning-of-line
bindkey -- '^[^M' self-insert-unmeta # alt-enter to insert a newline/carriage return
bindkey -- '^K'   up-line-or-beginning-search
bindkey -- '^J'   down-line-or-beginning-search

# default shell behaviour using terminfo keys
[[ -n ${terminfo[kdch1]} ]] && bindkey -- "${terminfo[kdch1]}" delete-char                   # delete
[[ -n ${terminfo[kend]}  ]] && bindkey -- "${terminfo[kend]}"  end-of-line                   # end
[[ -n ${terminfo[kcuf1]} ]] && bindkey -- "${terminfo[kcuf1]}" forward-char                  # right arrow
[[ -n ${terminfo[kcub1]} ]] && bindkey -- "${terminfo[kcub1]}" backward-char                 # left arrow
[[ -n ${terminfo[kich1]} ]] && bindkey -- "${terminfo[kich1]}" overwrite-mode                # insert
[[ -n ${terminfo[khome]} ]] && bindkey -- "${terminfo[khome]}" beginning-of-line             # home
[[ -n ${terminfo[kbs]}   ]] && bindkey -- "${terminfo[kbs]}"   backward-delete-char          # backspace
[[ -n ${terminfo[kcbt]}  ]] && bindkey -- "${terminfo[kcbt]}"  reverse-menu-complete         # shift-tab
[[ -n ${terminfo[kcuu1]} ]] && bindkey -- "${terminfo[kcuu1]}" up-line-or-beginning-search   # up arrow
[[ -n ${terminfo[kcud1]} ]] && bindkey -- "${terminfo[kcud1]}" down-line-or-beginning-search # down arrow

## correction
zstyle ':completion:*:correct:*' original true
zstyle ':completion:*:correct:*' insert-unambiguous true
zstyle ':completion:*:approximate:*' max-errors 'reply=($(( ($#PREFIX + $#SUFFIX) / 3 )) numeric)'

# completion
zstyle ':completion:*' use-cache on
zstyle ':completion:*' cache-path "$comppath"
zstyle ':completion:*' rehash true
zstyle ':completion:*' verbose true
zstyle ':completion:*' insert-tab false
zstyle ':completion:*' accept-exact '*(N)'
zstyle ':completion:*' squeeze-slashes true
zstyle ':completion:*:*:*:*:*' menu select
zstyle ':completion:*:match:*' original only
zstyle ':completion:*:-command-:*:' verbose false
zstyle ':completion::complete:*' gain-privileges 1
zstyle ':completion:*:manuals.*' insert-sections true
zstyle ':completion:*:manuals' separate-sections true
zstyle ':completion:*' completer _complete _match _approximate _ignored
zstyle ':completion:*' matcher-list 'm:{a-zA-Z}={A-Za-z}' 'r:|[._-]=* r:|=*' 'l:|=* r:|=*'
zstyle ':completion:*:cd:*' tag-order local-directories directory-stack path-directories
zstyle ':completion:*:descriptions' format '%U%B%d%b%u'

# labels and categories
zstyle ':completion:*' group-name ''
zstyle ':completion:*:matches' group 'yes'
zstyle ':completion:*:options' description 'yes'
zstyle ':completion:*:options' auto-description '%d'
zstyle ':completion:*:default' list-prompt '%S%M matches%s'
zstyle ':completion:*' format ' %F{green}->%F{yellow} %d%f'
zstyle ':completion:*:messages' format ' %F{green}->%F{purple} %d%f'
zstyle ':completion:*:descriptions' format ' %F{green}->%F{yellow} %d%f'
zstyle ':completion:*:warnings' format ' %F{green}->%F{red} no matches%f'
zstyle ':completion:*:corrections' format ' %F{green}->%F{green} %d: %e%f'

# command parameters
zstyle ':completion:*:functions' ignored-patterns '(prompt*|_*|*precmd*|*preexec*)'
zstyle ':completion::*:(-command-|export):*' fake-parameters ${${${_comps[(I)-value-*]#*,}%%,*}:#-*-}
zstyle ':completion:*:*:*:*:processes' command "ps -u $USER -o pid,user,comm -w -w"
zstyle ':completion:*:processes-names' command 'ps c -u ${USER} -o command | uniq'
zstyle ':completion:*:(vim|nvim|vi|nano):*' ignored-patterns '*.(wav|mp3|flac|ogg|mp4|avi|mkv|iso|so|o|7z|zip|tar|gz|bz2|rar|deb|pkg|gzip|pdf|png|jpeg|jpg|gif)'

# hostnames and addresses
zstyle ':completion:*:ssh:*' tag-order 'hosts:-host:host hosts:-domain:domain hosts:-ipaddr:ip\ address *'
zstyle ':completion:*:ssh:*' group-order users hosts-domain hosts-host users hosts-ipaddr
zstyle ':completion:*:(scp|rsync):*' tag-order 'hosts:-host:host hosts:-domain:domain hosts:-ipaddr:ip\ address *'
zstyle ':completion:*:(scp|rsync):*' group-order users files all-files hosts-domain hosts-host hosts-ipaddr
zstyle ':completion:*:(ssh|scp|rsync):*:hosts-host' ignored-patterns '*(.|:)*' loopback ip6-loopback localhost ip6-localhost broadcasthost
zstyle ':completion:*:(ssh|scp|rsync):*:hosts-domain' ignored-patterns '<->.<->.<->.<->' '^[-[:alnum:]]##(.[-[:alnum:]]##)##' '*@*'
zstyle ':completion:*:(ssh|scp|rsync):*:hosts-ipaddr' ignored-patterns '^(<->.<->.<->.<->|(|::)([[:xdigit:].]##:(#c,2))##(|%*))' '127.0.0.<->' '255.255.255.255' '::1' 'fe80::*'
zstyle -e ':completion:*:hosts' hosts 'reply=( ${=${=${=${${(f)"$(cat {/etc/ssh_,~/.ssh/known_}hosts(|2)(N) 2>/dev/null)"}%%[#| ]*}//\]:[0-9]*/ }//,/ }//\[/ } ${=${(f)"$(cat /etc/hosts(|)(N) <<(ypcat hosts 2>/dev/null))"}%%\#*} ${=${${${${(@M)${(f)"$(cat ~/.ssh/config 2>/dev/null)"}:#Host *}#Host }:#*\**}:#*\?*}})'
ttyctl -f

# menu colours
eval "$(dircolors)"
zstyle ':completion:*' list-colors ${(s.:.)LS_COLORS}
zstyle ':completion:*:*:kill:*:processes' list-colors '=(#b) #([0-9]#) ([0-9a-z-]#)*=36=0=01'
 
# initialize completion
compinit -u -d "$compfile"
#compinit -C
#compinit

# alias
alias l='lsd -F'
alias ls='lsd'
alias ld='lsd -d */'
alias lsa='l -A'
alias la='l -l'
alias ll='l -ld .?*'
alias lla='ls -lAh'
alias lt='l --tree'
alias -g g='grep --color=auto --perl-regexp'
alias -g G='| grep --color=auto --perl-regexp'
alias -g clip='xclip -selection clipboard'
alias grub-update='sudo grub-mkconfig -o /boot/grub/grub.cfg'
alias yay='yay --sudo doas --sudoflags -- --save'

# some personal alias
[[ -r $HOME/Machine/zsh/aliases.zsh ]] && source $HOME/Machine/zsh/aliases.zsh
[[ -r $HOME/Machine/zsh/git-alias.zsh ]] && source $HOME/Machine/zsh/git-alias.zsh
[[ -r $HOME/Machine/zsh/git-profile_INIT.zsh ]] && source $HOME/Machine/zsh/git-profile_INIT.zsh

# run nvm to load nvm in zsh 
# done this way to improve zsh startup time
nvm ()
{
if [[ -r /usr/share/nvm/init-nvm.sh ]]; then
	source /usr/share/nvm/init-nvm.sh
else
	echo "Install nvm";
fi
};

# --- Setup ZINIT ---
ZINIT_HOME="${XDG_DATA_HOME:-${HOME}/.local/share}/zinit/zinit.git"
[ ! -d $ZINIT_HOME ] && mkdir -p "$(dirname $ZINIT_HOME)"
[ ! -d $ZINIT_HOME/.git ] && git clone --depth 1 --recurse-submodules https://github.com/zdharma-continuum/zinit.git "$ZINIT_HOME"
source "${ZINIT_HOME}/zinit.zsh"

# --- Plugins ---
zinit load zdharma-continuum/history-search-multi-word
zinit light zsh-users/zsh-completions
zinit light mafredri/zsh-async
zinit light joel-porquet/zsh-dircolors-solarized
zinit light zsh-users/zsh-autosuggestions
zinit light zdharma-continuum/fast-syntax-highlighting

# --- Prompt (Pure) ---
zinit ice pick"async.zsh" src"pure.zsh"
zinit light sindresorhus/pure

zinit ice depth"1" # git clone depth
zinit ice pick"async.zsh" src"pure.zsh"
zinit light sindresorhus/pure
zinit light 


autoload -Uz +X bashcompinit && bashcompinit

function __calc_plugin {
    zcalc -f -e "$*"
}

# Debug end
if [ 1 -eq "$ZBUG" ]; then
  unsetopt XTRACE
  unsetopt xtrace
  exec 2>&3 3>&-
  zprof
fi
