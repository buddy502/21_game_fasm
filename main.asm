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
extrn LoadFont
extrn UnloadFont
extrn LoadImage
extrn LoadTextureFromImage
; ------------------------

; Format printf
fmt_int: db '%2d', 10, 0
fmt_str: db '%s', 10, 0
fmt_ptr: db '%p', 10, 0

; Macros
macro SYSCALL_EXIT number, arg0 {
   mov rax, number
   mov rdi, arg0
   syscall
}

macro printnf str, len {
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
   lea rdi, [font_data]
   mov rsi, font
   call LoadFont

   ; LOAD SUIT TEXTURES

   ; load heart img
   lea rdi, [heart_data]
   mov rsi, heart_path
   call LoadImage

   lea rdi, [heart_tex]
   ; load heart data   
   sub rsp, 32
   lea rax, [heart_data]
   mov rcx, [rax]
   mov [rsp], rcx
   mov rcx, [rax+8]
   mov [rsp+8], rcx
   mov rcx, [rax+16]
   mov [rsp+16], rcx

   call LoadTextureFromImage
   add rsp, 32

   ; load diamond img
   lea rdi, [diamond_data]
   mov rsi, diamond_path
   call LoadImage
   
   lea rdi, [diamond_tex]
   ; load heart data   
   sub rsp, 32
   lea rax, [diamond_data]
   mov rcx, [rax]
   mov [rsp], rcx
   mov rcx, [rax+8]
   mov [rsp+8], rcx
   mov rcx, [rax+16]
   mov [rsp+16], rcx

   call LoadTextureFromImage
   add rsp, 32

   ; load club img
   lea rdi, [club_data]
   mov rsi, club_path
   call LoadImage
   
   lea rdi, [club_tex]
   ; load club data   
   sub rsp, 32
   lea rax, [club_data]
   mov rcx, [rax]
   mov [rsp], rcx
   mov rcx, [rax+8]
   mov [rsp+8], rcx
   mov rcx, [rax+16]
   mov [rsp+16], rcx

   call LoadTextureFromImage
   add rsp, 32

   ; load spade img
   lea rdi, [spade_data]
   mov rsi, spade_path
   call LoadImage

   lea rdi, [spade_tex]
   ; load spade data   
   sub rsp, 32
   lea rax, [spade_data]
   mov rcx, [rax]
   mov [rsp], rcx
   mov rcx, [rax+8]
   mov [rsp+8], rcx
   mov rcx, [rax+16]
   mov [rsp+16], rcx
   
   call LoadTextureFromImage
   add rsp, 32

   ; -------------------------------------------------------

   ; Program loop
.program_loop:
   call WindowShouldClose
   test rax, rax
   jnz .program_exited

   ; Program Drawing -------------------------------------------------------
   call BeginDrawing

   mov edi, 0xFFD3D3D3
   call ClearBackground

   movq xmm0, [card_rectangle]       ; load first 2 floats: x, y
   movq xmm1, [card_rectangle + 8]   ; load next 2 floats: w, h
   movss xmm2, [card_roundedness]
   mov edi, 10
   mov esi, 0xFF000000
   call DrawRectangleRounded
   ; --------------------------------

   lea rdi, [spade_data]
   lea rsi, [spade_tex]
   call drawSuitTexture

   call drawNumOnCard
   call updateGame

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
   .x: dd 200.0
   .y: dd 200.0
   .w: dd 100.0
   .h: dd 150.0
card_rectangle_offset:
   .num1x: dd 6.0
   .num1y: dd 6.0
   .num2x: dd 23.0
   .num2y: dd 25.0

card_reference_size: 
   dd 300.0

card_roundedness:
   dd 0.4

card_num_pos_relative:
   xy: dd 5, 5 ; (x, y)

; include headers
include "events.inc"
include "common_cards.inc"
