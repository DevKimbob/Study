Vim bindings
===
# 1. Vim Cheet Sheet
reference : [vim.rtorr.com](https://vim.rtorr.com/ "https://vim.rtorr.com/")
## 1.1. Global
```
:h[elp] <keyword>
    open help for <keyword>
:sav[eas] <filename>
    save file as <filename>
:clo[se]
    close current pane
:ter[minal]
    open a terminal window
K
    open man page for word under the cursor
```

## 1.2. Cursor movement
```
h j k l : 
    left, down, up, right
gj gk : goto j/k
    Down, Up(multi-line text)

H M L : High, Middle, Low (home, middle, last)
    move to top/middle/bottom of the screen

w W : word
    jump forwards to the start of a word
    (cannot/can contain punctuation)
e E : end of a word
    jump forwards to the end of a word
    (cannot/can contain punctuation)
b B : backword
    jump backwards to the start of a word
    (cannot/can contain punctuation)
ge gE : goto end of a word
    jump backwards to the end of a word
    (cannot/can contain punctuation)
#punctuation : configure at 'iskeyword' option

% : 
    move to matching char
    default : (), {}, []
    use ':h matchpairs' for info

0 $ : 
    jump to start/end of the line
^ g_ : 
    jump to first/last non-blank char of the line

gg : goto
    go to the first line of the document
G : goto
    go to the last line of the document
<num>gg or <num>G : 
    go to line <num>

gd gD : goto declaration
    move to local/global declaration

f<ch> F<ch> : find <ch>
    jump to next/previous occurrence of the <ch>
t<ch> T<ch> : to <ch>
    jump to before-next/after-previous occurrence of the <ch>
; : 
    repeat previous f, F, t, T movement
, : 
    repeat previous f, F, t, T movement, backwards

} : 
    jump to next paragraph (or function/block, when editing code)
{ : 
    jump to previous paragraph (or function/block, when editing code)

zz : 
    center cursor on screen
Ctrl + e : 
    move screen down one line (without cursor movement)
Ctrl + y : 
    move screen up one line (without cursor movement)
Ctrl + f : forwafd
    move forward one full screen
Ctrl + b : backward
    move back one full screen
Ctrl + d : down
    move forward half screen
Ctrl + u : up
    move backward half screen
```

## 1.3. Insert mode - inserting/appending text
```
i I : insert
    insert before-the-cursor/at-the-beginning-at-the-line
a A : append
    insert after-the-cursor/at-the-end-of-the-line
o O : open
    append a new line below/above the current line

#during --insert mode--
Ctrl + h : cHar
    delete char before the cursor
Ctrl + w : word
    delete word before tue cursor
Ctrl + j :
    begin new line
Ctrl + t : tab
    indent currunt line
Ctrl + d : de-tab
    de-indent currunt line
Ctrl + n : next
    auto complete next match before the cursor
Ctrl + p : previous
    auto complete previous match before the cursor
Ctrl + r<reg> : register
    insert the contents of register <reg>
Ctrl + o<command> :
    temporarily enter normal mode to issue one noraml-mode <command>
Esc :
    exit insert mode
```

## 1.4. Editing

## 1.5. Visual mode - marking
## 1.6. Visual commads
## 1.7. Registers
## 1.8. Makrs and Positions
## 1.9. Macros
## 1.10. Cut and Paste
## 1.11. Indent text
## 1.12. Exiting
## 1.13. Search and Replace
## 1.14. Search in multiple files
## 1.15. Tabs
## 1.16. Working with multiple files
## 1.17. Diff

# 2. FreeCodeCamp.org - youtube
reference : [youtube.com](https://www.youtube.com/watch?v=RZ4p-saaQkc&ab_channel=freeCodeCamp.org "https://www.youtube.com/watch?v=RZ4p-saaQkc&ab_channel=freeCodeCamp.org")
```

```

# 3. Conclusion
```
h j k l
gj gk

w b e ge
W B E gE

%

0 $ ^ g_

[num]gg [num]G

f F

{ }

Ctrl + e y f d b u

ci<>
```