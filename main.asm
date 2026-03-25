format ELF64

section '.text' executable
public _start

; Include headers
include 'create_cards.inc'

; External Variables
extrn printf

extrn InitWindow
extrn WindowShouldClose
extrn CloseWindow
extrn BeginDrawing
extrn EndDrawing
extrn ClearBackground
extrn DrawRectangleRounded
extrn DrawText
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

   mov rdi, 0xFF000000
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

   sub rsp, 64               ; 64 = 56 + 8 padding to maintain 16-byte alignment

   mov rax, [font]
   mov [rsp], rax
   mov rax, [font+8]
   mov [rsp+8], rax
   mov rax, [font+16]
   mov [rsp+16], rax
   mov rax, [font+24]
   mov [rsp+24], rax
   mov rax, [font+32]
   mov [rsp+32], rax
   mov rax, [font+40]
   mov [rsp+40], rax
   mov rax, [font+48]
   mov [rsp+48], rax
   ; [rsp+56..63] = padding, unused

   lea rdi, [text.message]
   movsd xmm0, [text.xy]
   xorps xmm1, xmm1
   xorps xmm2, xmm2
   movss xmm3, [text.fontSize]
   movss xmm4, [text.spacing]
   mov esi, 0xFFFFFFFF

   call DrawTextPro
   add rsp, 64

   ;lea rdi, [Error_call]
   ;xor eax, eax
   ;call printf

   ; Program End Drawing ---------------------------------------------------
   call EndDrawing
   jmp .program_loop

.program_exited:
   ; Unload the font
   add rsp, 48

   call CloseWindow
   SYSCALL_EXIT 60, 0

section '.data' writeable

Error_call: db "Unexpected Error, segfault", 10, 0

text:          
   .message:   db "Hello, World!", 0
   .xy:        dd 100.0, 100.0
   .fontSize:  dd 30.0
   .spacing:   dd 0.0

font: rb 56

window_title: db "21 game", 0

card_rectangle:
    .xy: dd 200.0, 200.0 ; (x, y)
    .wh: dd 100.0, 150.0 ;  (w, h)

card_roundedness:
   dd 0.4

card_num_pos_relative:
   xy: dd 5, 5 ; (x, y)
