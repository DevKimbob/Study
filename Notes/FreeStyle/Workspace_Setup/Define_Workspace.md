Definition of a "Workspace"  <!-- omit in toc -->
===

**Table of Contents**
- [Functionality](#functionality)
  - [Tree File Explorer](#tree-file-explorer)
  - [Open Tabs](#open-tabs)
  - [Toggle Word Wrap](#toggle-word-wrap)
  - [Debugging](#debugging)
  - [Terminal](#terminal)
  - [Git](#git)
  - [Compare Folders](#compare-folders)
  - [Search and Replace](#search-and-replace)
  - [Auto Complete](#auto-complete)
  - [Problems and Warnings](#problems-and-warnings)
  - [Go to Definition](#go-to-definition)
  - [Peek Definition](#peek-definition)
  - [Rename Symbol](#rename-symbol)
  - [Change All Occurrences](#change-all-occurrences)
  - [Format Document](#format-document)
  - [Intellisence](#intellisence)
  - [Cmake](#cmake)
  - [Utils](#utils)
  - [Include Path](#include-path)
  - [Doxygen](#doxygen)
- [LazyVim Stuff](#lazyvim-stuff)
  - [Buffers](#buffers)
  - [LSP](#lsp)

# Functionality
## Tree File Explorer
* NeoTree : \<space> e

|Command|HotKey|
|:-:|:-:|
|show_help|?|
|set_root|.|
|navigate_up|\<bs>|
|open|\<cr>|
|add|a|
|copy|c|
|move|m|
|rename|r|
|open_tabnew|t|
|open_vsplit|s|
|open_split|S|
|close_node|C|
|toggle_hidden|H|
|toggle_preview|P|
|focus_preview|l|
|order_by_modified|om|
|order_by_name|on|

## Open Tabs
|Command|HotKey|
|:-:|:-:|
|Split window below|\<space> -|
|Split window right|\<space> ||
|Navigate window|\<C-hjkl>|
|Increase window size|\<C-arrow>|
|Prev buffer|\<S-h>|
|Next buffer|\<S-l>|
|Other window|\<leader>ww|
|Delete window|\<leader>wd|
|Find Files|\<leader>\<space>|
|Switch Buffer|\<leader>,|

## Toggle Word Wrap
|Command|HotKey|
|:-:|:-:|
|Toggle Word Wrap|\<leader>uw|

## Debugging
DAP  
lldb?

## Terminal
|Command|HotKey|
|:-:|:-:|
|Terminal (cwd)|\<leader>fT|
|Terminal (root dir)|\<C-/>|

## Git
Lazygit?

## Compare Folders
## Search and Replace
## Auto Complete
LSP?  
clangd

## Problems and Warnings
## Go to Definition
## Peek Definition
## Rename Symbol
## Change All Occurrences
## Format Document
clang-format with `.clang-format` file
```xml
Language: "Cpp"
IndentWidth: 4
TabWidth: 4
```

## Intellisence
LSP?  
clangd

## Cmake
* cmake-tools.nvim basic usage  
  CMakeGenerate, CMakeBuild, CMakeRun

## Utils
|Command|HotKey|
|:-:|:-:|
|Move down|\<A-j>|
|Move up|\<A-k>|

## Include Path
using Cmake with compile_commands.json?
> cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1

## Doxygen

# LazyVim Stuff
## Buffers
bufferline.nvim  
|Command|HotKey|
|:-:|:-:|
|Move Buffer to the Left|\<leader>bH|
|Move Buffer to the Right|\<leader>bL|
> BufferLineMovePrev, BufferLineMoveNext

## LSP
[lazyvim.org reference](https://www.lazyvim.org/keymaps#lsp "https://www.lazyvim.org/keymaps#lsp")

<!-- |Command|HotKey|
|:-:|:-:| -->