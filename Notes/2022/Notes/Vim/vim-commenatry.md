Vim commenatry
===
reference : [github.com](https://github.com/tpope/vim-commentary "https://github.com/tpope/vim-commentary")  
```
#commands
gcc 
    comment out a line (takes a count)
gc 
    comment out the target of a motion (ex gcap)
    in --visual mode-- : comment out the selection
    in operator pending mode : target a comment

:<startlinenum><endlinenum>Commentary
    choose a range
:g/TODO/Commentary
    part of a :global invocation
```