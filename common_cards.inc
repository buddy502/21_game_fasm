; Cards struct format:
;typedef struct Card {
;   int suit;
;   int value;
;}
; Card position is determined by user, like draw or click

section '.bss' writeable

heart_tex:     rb 24
heart_data:     rb 24

diamond_tex:   rb 24
diamond_data:   rb 24

club_tex:      rb 24
club_data:      rb 24

spade_tex:     rb 24
spade_data:     rb 24

font_data: rb 48

; -------- SECTION -----------
section '.data' writeable

font: db "cardsrc/Libre_Baskerville/LibreBaskerville-SemiBold.ttf", 0

text:
   .fontSize: dd 23.0  ; 4 bytes
   .message:  db " 4", 15 dup(0) ; 17 byte
   .spacing:  db 0   ; 1 byte
   rb 3  ; 0-24, 4 + 17 + 1 = 22 + 3 = 25

; Breaks: Card update and sprintf
heart_path: db "cardsrc/card_images/heart.png", 0
diamond_path: db "cardsrc/card_images/diamond.png", 0
club_path: db "cardsrc/card_images/club.png", 0
spade_path: db "cardsrc/card_images/spade.png", 0

; -------- SECTION -----------
section '.text' executable

extrn UpdateTexture
extrn DrawTextureV

; draw_num_on_card()
; values stored in this file
drawNumOnCard:
   ; -------- NUM 1 -----------
   push rbp
   mov rbp, rsp
   sub rsp, 64

   mov rax, [font_data] ; use stack for font

   mov [rsp], rax
   mov rax, [font_data+8]
   mov [rsp+8], rax
   mov rax, [font_data+16]
   mov [rsp+16], rax
   mov rax, [font_data+24]
   mov [rsp+24], rax
   mov rax, [font_data+32]
   mov [rsp+32], rax
   mov rax, [font_data+40]
   mov [rsp+40], rax
   
   lea rdi, [text.message]
   ; position
   movups xmm0, [card_rectangle.x]
   ; offset position to fit card
   movups xmm6, [card_rectangle_offset.num1x]
   addps  xmm5, xmm6
   addps xmm0, xmm5

   pxor xmm1, xmm1
   pxor xmm2, xmm2

   ; font size
   movss xmm3, [card_rectangle.w]     ;fontsize
   addss xmm3, [card_rectangle.h]
   movss xmm4, [card_reference_size]
   divss xmm3, xmm4
   movss xmm4, [text.fontSize]
   mulss xmm3, xmm4  ; multiply with scale

   pxor xmm4, xmm4
   movss xmm4, [text.spacing]
   mov esi, 0xFFFFFFFF

   call DrawTextPro

   add rsp, 64

   ; -------- NUM 2 -----------

   sub rsp, 64
   
   mov rax, [font_data]
   mov [rsp], rax
   mov rax, [font_data+8]
   mov [rsp+8], rax
   mov rax, [font_data+16]
   mov [rsp+16], rax
   mov rax, [font_data+24]
   mov [rsp+24], rax
   mov rax, [font_data+32]
   mov [rsp+32], rax
   mov rax, [font_data+40]
   mov [rsp+40], rax
   
   lea rdi, [text.message]
   ; position
   movups xmm0, [card_rectangle.x]
   movups xmm5, [card_rectangle.w]
   ; offset position to fit card
   movups xmm6, [card_rectangle_offset.num2x]
   subps  xmm5, xmm6
   addps xmm0, xmm5

   pxor xmm1, xmm1
   pxor xmm2, xmm2

   ; font size
   movss xmm3, [card_rectangle.w]     ;fontsize
   addss xmm3, [card_rectangle.h]
   movss xmm4, [card_reference_size]
   divss xmm3, xmm4
   movss xmm4, [text.fontSize]
   mulss xmm3, xmm4  ; multiply with scale

   pxor xmm4, xmm4
   movss xmm4, [text.spacing]
   mov esi, 0xFFFFFFFF
   call DrawTextPro

   add rsp, 64
   
   mov rsp, rbp
   pop rbp
   ret

   drawSuitTexture:
   push rbp
   mov rbp, rsp
   sub rsp, 48
   
   mov [rbp-8], rdi                ; Image *
   mov [rbp-16], rsi               ; Texture2D *
   
   mov rdi, [rbp-8]

   ;movss xmm0, [card_rectangle_resize.x]
   ;cvtss2si esi, xmm0

   ;movss xmm0, [card_rectangle_resize.y]
   ;cvtss2si edx, xmm0

   ;call ImageResize
   
   mov rsi, [rbp-16]
   
   sub rsp, 32
   mov eax, [rsi]
   mov [rsp], eax
   mov eax, [rsi+4]
   mov [rsp+4], eax
   mov eax, [rsi+8]
   mov [rsp+8], eax
   mov eax, [rsi+12]
   mov [rsp+12], eax
   mov eax, [rsi+16]
   mov [rsp+16], eax
   
   mov rax, [rbp-8]
   mov rdi, [rax]
   
   call UpdateTexture 
   add rsp, 32

   mov rdi, [rbp-16]

   sub rsp, 32
   mov eax, [rdi]
   mov [rbp-40], eax
   mov eax, [rdi+4]
   mov [rbp-36], eax
   mov eax, [rdi+8]
   mov [rbp-32], eax
   mov eax, [rdi+12]
   mov [rbp-28], eax
   mov eax, [rdi+16]
   mov [rbp-24], eax

   movss xmm0, [card_rectangle.x]
   movss xmm1, [card_rectangle.y]
   
   mov esi, 0xFFFFFFFF
   
   call DrawTextureV
   add rsp, 32
   
   leave
   ret
