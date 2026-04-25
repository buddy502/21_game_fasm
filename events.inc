KEY_RIGHT   = 262
KEY_LEFT    = 263

extrn atoi
extrn sprintf

; Raylib external functions
extrn IsKeyPressed

section '.data' writeable

card_number: dd 4

section '.text' executable

updateGame:
.check_left_key:
    mov edi, KEY_LEFT
    call IsKeyPressed
    test rax, rax
    jz .check_right_key ; check right if left key isn't pressed

    mov eax, [card_number]
    cmp eax, 1
    jle .check_right_key
    dec eax
    mov [card_number], eax
    
    jmp .update_card_number

.check_right_key:    
    mov edi, KEY_RIGHT
    call IsKeyPressed
    test rax, rax
    jz .end_update_game    ; end if right key isn't pressed

    mov eax, [card_number]
    cmp eax, 10
    jge .end_update_game
    inc eax
    mov [card_number], eax

    jmp .update_card_number

.update_card_number:
    sub rsp, 8
    lea rdi, [text.message]
    lea rsi, [fmt_int]
    mov edx, [card_number]
    xor eax, eax
    call sprintf 
    add rsp, 8
    jmp .end_update_game

.end_update_game:
   ret
