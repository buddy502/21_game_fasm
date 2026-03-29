format ELF64

section '.text' executable
public _start

; External Variables
extrn printf

extrn InitWindow
extrn WindowShouldClose
extrn CloseWindow
extrn BeginDrawing
extrn EndDrawing
extrn ClearBackground
extrn DrawRectangleRounded
extrn DrawTextPro
extrn GetFontDefault
extrn UnloadFont
; ------------------------

; Macros
macro SYSCALL_EXIT number, arg0 {
   mov rax, number
   mov rdi, arg0
   syscall
}

macro print str, len {
    mov rax, 1      ; sys_write
    mov rdi, 1      ; stdout
    mov rsi, str    ; pointer to string
    mov rdx, len    ; length
    syscall
}
; ------------------------

_start:
   and rsp, -16 
   ; create window
   mov rdi, 800
   mov rsi, 600
   mov rdx, window_title
   call InitWindow 

   ; Create a valid font struct
   lea rdi, [font]
   call GetFontDefault

   ; Program loop
.program_loop:
   call WindowShouldClose
   test rax, rax
   jnz .program_exited

   ; Program Drawing -------------------------------------------------------
   call BeginDrawing

   mov edi, 0xFF000000
   call ClearBackground

   ; Draw Card
   ; Card rectangle
   movq xmm0, [card_rectangle]       ; load first 2 floats: x, y
   movq xmm1, [card_rectangle + 8]   ; load next 2 floats: w, h
   ; Card roundedness
   movss xmm2, [card_roundedness]
   ; Card segments
   mov edi, 10
   ; Card color
   mov esi, 0xFF0000FF
   ; Call the function
   call DrawRectangleRounded
   ; --------------------------------

   call draw_num_on_card

   ; Program End Drawing ---------------------------------------------------
   call EndDrawing
   jmp .program_loop

.program_exited:
   call CloseWindow
   SYSCALL_EXIT 60, 0

section '.data' writeable

Error_call: db "Unexpected Error, segfault", 10, 0

window_title: db "21 game", 0

card_rectangle:
    .xy: dd 200.0, 200.0 ; (x, y)
    .wh: dd 100.0, 150.0 ;  (w, h)

card_roundedness:
   dd 0.4

card_num_pos_relative:
   xy: dd 5, 5 ; (x, y)

; include headers
include 'create_cards.inc'
