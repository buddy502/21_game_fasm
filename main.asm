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
extrn UnloadImage
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
   mov rdi, 800
   mov rsi, 600
   mov rdx, window_title
   call InitWindow 

   ; Load font
   lea rdi, [font_data]
   mov rsi, font
   call LoadFont

   ; Load card suit textures -------------
   lea rdi, [heart_img]    ; heart
   mov rsi, heart_path
   call LoadImage

   lea rdi, [heart_tex]
   lea rsi, [heart_img]
   call LoadTextureFromImage

   lea rdi, [heart_img]
   call UnloadImage

   lea rdi, [diamond_img]  ; diamond
   mov rsi, diamond_path
   call LoadImage

   lea rdi, [diamond_tex]
   lea rsi, [diamond_img]
   call LoadTextureFromImage

   lea rdi, [diamond_img]
   call UnloadImage

   lea rdi, [club_img]     ; club
   mov rsi, club_path
   call LoadImage

   lea rdi, [club_tex]
   lea rsi, [club_img]
   call LoadTextureFromImage

   lea rdi, [club_img]
   call UnloadImage

   lea rdi, [spade_img]    ; spade
   mov rsi, spade_path
   call LoadImage

   lea rdi, [spade_tex]
   lea rsi, [spade_img]
   call LoadTextureFromImage

   lea rdi, [spade_img]
   call UnloadImage
   ; -------------------------------------

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

   call drawNumOnCard
   ;call updateGame

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
card_rectangle_offset:
   .num1xy: dd 6.0, 6.0
   .num2xy: dd 23.0, 25.0

card_reference_size: 
   dd 300.0

card_roundedness:
   dd 0.4

card_num_pos_relative:
   xy: dd 5, 5 ; (x, y)

; include headers
;include 'events.inc'
include 'create_cards.inc'
