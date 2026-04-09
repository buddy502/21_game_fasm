KEY_RIGHT   = 262
KEY_LEFT    = 263

extrn IsKeyPressed
extrn atoi
extrn sprintf

section '.bss' writeable

card_number: rd 1

section '.data' writeable

fmt_int: db '%d', 0

section '.text' executable

updateGame:
   mov edi, KEY_LEFT
   call IsKeyPressed
   test rax, rax
   jz .check_right_key

.decrease_num:
   mov eax, [card_number]
   cmp eax, 1
   jle .end_update_game
   dec eax
   mov [card_number], eax
   jmp .update_card_number

.check_right_key:    
   mov edi, KEY_RIGHT
   call IsKeyPressed
   test rax, rax
   jz .end_update_game

.increase_num:
   mov eax, [card_number]
   cmp eax, 10
   jge .end_update_game
   inc eax
   mov [card_number], eax

.update_card_number:
   lea rdi, [text.message]
   lea rsi, [fmt_int]
   mov edx, [card_number]
   call sprintf 

.end_update_game:
   ret
