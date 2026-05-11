; Cards struct format:
;typedef struct Card {
;   int suit;
;   int value;
;}
; Card position is determined by user, like draw or click

section '.bss' writeable

;heart_tex:     rb 24
;heart_img:     rb 24
;
;diamond_tex:   rb 24
;diamond_img:   rb 24
;
;
;club_tex:      rb 24
;club_img:      rb 24

spade_tex:     rb 24
spade_img:     rb 24

font_data: rb 48

; -------- SECTION -----------
section '.data' writeable

font: db "cardsrc/Libre_Baskerville/LibreBaskerville-SemiBold.ttf", 0
text:
   .fontSize: dd 23.0
   .message:  db " 4", 15 dup(0)
   .spacing:  db 0 

; Breaks: Card update and sprintf
heart_path: db "cardsrc/card_images/heart.png", 0
diamond_path: db "cardsrc/card_images/diamond.png", 0
;spade_path: db "cardsrc/card_images/spade.png", 0
club_path: db "cardsrc/card_images/club.png", 0

; -------- SECTION -----------
section '.text' executable

; draw_num_on_card()
; values stored in this file
drawNumOnCard:
   ; -------- NUM 1 -----------
   push rbp
   mov rbp, rsp
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
   movups xmm0, [card_rectangle.xy]
   ; offset position to fit card
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
   movups xmm0, [card_rectangle.xy]
   movups xmm5, [card_rectangle.wh]
   ; offset position to fit card
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
   mov esi, 0xFFFFFFFF
   call DrawTextPro

   add rsp, 64
   
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
