; -------- SECTION -----------
section '.data' writeable

font: rb 56
text:
   .fontSize: dd 23.0
   .message db "4", 15 dup(0)
   .spacing:   db 0 

section '.text' executable

; draw_num_on_card(float* rect, char* message, Font* font_ptr)
; rdi = rect pointer
; rsi = message pointer
; rdx = font pointer
drawNumOnCard:
   ; -------- NUM 1 -----------
   push rbp
   mov rbp, rsp
   sub rsp, 64
   
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
   
   lea rdi, [text.message]
   ; position
   movups xmm0, [card_rectangle.xy]
   movups xmm6, [card_rectangle_offset.num1xy]
   addps  xmm5, xmm6
   addps xmm0, xmm5

   pxor xmm1, xmm1
   pxor xmm2, xmm2

   ; font size
   movss xmm3, [card_rectangle.wh]     ;fontsize
   addss xmm3, [card_rectangle.wh+4]
   movss xmm4, [card_reference_size]
   divss xmm3, xmm4
   movss xmm4, [text.fontSize]
   mulss xmm3, xmm4  ; multiply with scale

   pxor xmm4, xmm4
   movss xmm4, [text.spacing]
   mov esi, 0xFF000000
   call DrawTextPro

   ; -------- NUM 2 -----------

   sub rsp, 64
   
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
   
   lea rdi, [text.message]
   ; position
   movups xmm0, [card_rectangle.xy]
   movups xmm5, [card_rectangle.wh]
   movups xmm6, [card_rectangle_offset.num2xy]
   subps  xmm5, xmm6
   addps xmm0, xmm5

   pxor xmm1, xmm1
   pxor xmm2, xmm2

   ; font size
   movss xmm3, [card_rectangle.wh]     ;fontsize
   addss xmm3, [card_rectangle.wh+4]
   movss xmm4, [card_reference_size]
   divss xmm3, xmm4
   movss xmm4, [text.fontSize]
   mulss xmm3, xmm4  ; multiply with scale

   pxor xmm4, xmm4
   movss xmm4, [text.spacing]
   mov esi, 0xFF000000
   call DrawTextPro
   
   mov rsp, rbp
   pop rbp
   ret

;ACE equ 0
;DIAMOND equ 1
;HEARTS equ 2
;CLUBS equ 3
;
;; Create suit and ranks of card
;; Use bytes to access index easily
;
;deck:
;times 52 db 0
;
;deck_rank:
;db 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
;
;suits:
;db 0, 1, 2, 3
;
