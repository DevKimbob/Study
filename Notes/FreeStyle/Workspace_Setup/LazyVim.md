LazyVim  <!-- omit in toc -->
===

**Table of Contents**
- [Installation](#installation)
- [Pure LazyVim.nvim](#pure-lazyvimnvim)
- [Reference : Youtube Video](#reference--youtube-video)
  - [Usage](#usage)
  - [Autocompletion](#autocompletion)
  - [splits](#splits)
  - [Search and Replace](#search-and-replace)
  - [.nvim](#nvim)


# Installation
Requirements : [Ref](https://www.lazyvim.org/#%EF%B8%8F-requirements "https://www.lazyvim.org/#%EF%B8%8F-requirements")
* Neovim >= 0.9.0 : [Ref](https://github.com/neovim/neovim/blob/master/BUILD.md "https://github.com/neovim/neovim/blob/master/BUILD.md")
* Nerd Fonts >= v3.0 : [Ref](https://github.com/ryanoasis/nerd-fonts?tab=readme-ov-file#option-6-install-script "https://github.com/ryanoasis/nerd-fonts?tab=readme-ov-file#option-6-install-script")
* Lazygit : [Ref](https://github.com/jesseduffield/lazygit?tab=readme-ov-file#ubuntu "https://github.com/jesseduffield/lazygit?tab=readme-ov-file#ubuntu")
* for telescope.nvim
  * live grep : [Ref](https://github.com/BurntSushi/ripgrep?tab=readme-ov-file#installation "https://github.com/BurntSushi/ripgrep?tab=readme-ov-file#installation")
  * find files : [Ref](https://github.com/sharkdp/fd?tab=readme-ov-file#on-ubuntu "https://github.com/sharkdp/fd?tab=readme-ov-file#on-ubuntu")

# Pure LazyVim.nvim


# Reference : Youtube Video
## Usage
* which key : \<space>
  * e : NeoTree
  * c : code
    * m : mason (not sure what it does yet)
    * r : lsp - rename
    * a : code actions
  * f : find
    * f : files (telescope.nvim)
    * b : buffer
        > ]b : next buffer  
        > [b : prev buffer
    * t : terminal
  * s : search
    * g : grep (live grep)
    * h : help
    * t : TODO (todo-comments.nvim)
    * k : keymaps
    * r : search and replace
  * x
    * x : Trouble plugin
  * u : ui
    * C : themes
    * l : lines
  * - : horizontal split
  * | : vertical split
  * g : git
    * g : lazygit
* s : leap.nvim
* K : hover documentation
* g : goto
  * f : file under cursor

## Autocompletion
Ctrl + n : togo autocomp  
snippets : tab to go to next

## splits
Ctrl + hjkl  
to adjust size : Ctrl + arrows

## Search and Replace
\<space> r c : replace one  
\<space> R : replace all  
dd : delete

## .nvim
* telescope.nvim : fuzzy finder over lists
* leap.nvim : general-purpose motion plugin, use 2-character search pattern
* trouble.nvim : diagnostics, reference, telescope results, quickfix, ...
* todo-comments.nvim : TODO: