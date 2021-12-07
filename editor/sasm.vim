if exists("b:current_syntax") 
    finish
endif

" Keywords
syntax keyword sasmKeywords push pop dup swap
syntax keyword sasmKeywords addi subi divi muli modi
syntax keyword sasmKeywords addf subf divf mulf
syntax keyword sasmKeywords addu subu divu mulu modu
syntax keyword sasmKeywords brnz halt jmp 
syntax keyword sasmKeywords eqi nqi gti lti
syntax keyword sasmKeywords eqf nqf gtf ltf
syntax keyword sasmKeywords equ nqu gtu ltu
syntax keyword sasmKeywords native

" Comments

syntax region sasmComment start=";" end="$"
syntax region sasmDirective start="@" end= " "

syntax match sasmLabel "[a-z_][a-z0-9_]*:"he=e-1

" Numbers
syntax match sasmDecInt display "\<[0-9][0-9_]*"
syntax match sasmHexInt display "\<0[xX][0-9a-fA-F][0-9_a-fA-F]*"
syntax match sasmFloat  display "\<[0-9][0-9_]*\%(\.[0-9][0-9_]*\)"

" set higlights
highlight default link sasmKeywords Identifier
highlight default link sasmComment Comment
highlight default link sasmDirective PreProc
highlight default link sasmDecInt Number
highlight default link sasmHexInt Number
highlight default link sasmFloat Float
highlight default link sasmLabel Label

let b:current_syntax = "sasm"
