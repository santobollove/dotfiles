########################################
# ZSH CORE
########################################

export ZDOTDIR="$HOME/.config/zsh"

########################################
# PATH (single source of truth)
########################################

typeset -U path
path=(
  $HOME/.local/bin
  $HOME/.local/share/cargo/bin
  $HOME/.local/share/npm/bin
  $HOME/.cabal/bin
  $HOME/Machine/bin
  /opt/bin

  /opt/android-sdk/platform-tools
  /opt/android-sdk/emulator

  $path
)
export PATH

########################################
# DEV TOOL CHAINS
########################################

export CARGO_HOME="$HOME/.local/share/cargo"
export RUSTUP_HOME="$HOME/.local/share/rustup"
export NVM_DIR="$HOME/.local/share/nvm"
export PYENV_ROOT="$HOME/.local/share/pyenv"
export GOPATH="$HOME/.local/share/go"
export SDKMAN_DIR="$HOME/.local/share/sdkman"

########################################
# ANDROID
########################################

export ANDROID_SDK_ROOT="/opt/android-sdk"

########################################
# NODE / JS
########################################

export NPM_CONFIG_USERCONFIG="$HOME/.config/npm/npmrc"
export NODE_REPL_HISTORY="$HOME/.cache/node/repl_history"

########################################
# DEV EXPERIENCE
########################################

export LESSHISTFILE=-
export PROMPT_EOL_MARK=""
