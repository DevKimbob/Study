Vim Surround
===
reference : [github.com](https://github.com/tpope/vim-surround "https://github.com/tpope/vim-surround")  
The `.` command will work with `ds`, `cs`, and `yss` if you install repeat.vim.  
```
#commands
--normal mode--
cs<before><after> : change surround <before> <after>
    change <before> to <after>
ds<surround> : delete surround <surround>
    delete <surround>
ys<target><surround> : y? surround <target> <surround>
    add <surround>
    <target> can be "s" for entire line
    <target> can be "iw" as In-a-Word
    <surround> can be "b" for bracket ()

<surround> : open/close brackets
    open : surround with space
    close : surround without space

--visual line--
S<surround> : Surround <surround>
    surrounds seleted line with <surrround>

#example
"Hello World!"
  ↓ cs"'
'Hello World!'
  ↓ cs'<q>
<q>Hello World!</q>
  ↓ cst"
"Hello World!"
  ↓ ds"
Hello World!
  ↓ ysiw]
[Hello] World!
  ↓ cs]{
{ Hello } World!
  ↓ yssb
({ Hello } World!)
  ↓ ds{ds)
Hello World!
  ↓ ysiw<em>
<em>Hello</em> World!
  ↓ VS<p class="important">
<p class="important">
  <em>Hello</em> world!
</p>
```