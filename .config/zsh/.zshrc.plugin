plugins=(
  "zsh-completions|https://github.com/zsh-users/zsh-completions.git|zsh-completions.plugin.zsh"
  "globalias|https://github.com/ohmyzsh/ohmyzsh.git:plugins/globalias|globalias.plugin.zsh"
  "zsh-async|https://github.com/mafredri/zsh-async.git|async.zsh"
  "zsh-dircolors-solarized|https://github.com/joel-porquet/zsh-dircolors-solarized.git|zsh-dircolors-solarized.zsh"
  "zsh-syntax-highlighting|https://github.com/zsh-users/zsh-syntax-highlighting.git|zsh-syntax-highlighting.zsh"
  "pure|https://github.com/sindresorhus/pure.git|pure.zsh"
)

for entry in "${plugins[@]}"; do
  name=${entry%%|*}
  rest=${entry#*|}
  repo=${rest%%|*}
  file=${rest##*|}
  dir="$ZDOTDIR/plugins/$name"

  if [[ ! -d $dir ]]; then
    echo "Installing $name..."
    mkdir -p "$ZDOTDIR/plugins"
    git clone "${repo%%:*}" "$dir"
    # If path after colon exists (for subdir plugins)
    subpath=${repo#*:}
    [[ "$repo" == *:* && -d "$dir/$subpath" ]] && mv "$dir/$subpath"/* "$dir" && rm -rf "$dir/$subpath"
  fi

  [[ -r "$dir/$file" ]] && source "$dir/$file"
done

