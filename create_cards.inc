; External functions

extrn DrawTextureEx

;----------------

section '.bss' writeable

HEARTS   equ 1
DIAMOND  equ 2
SPADE    equ 3
CLUBS    equ 4

heart_tex:     rb 20
heart_img:     rb 24

diamond_tex:   rb 20
diamond_img:   rb 24

spade_tex:     rb 20
spade_img:     rb 24

club_tex:      rb 20
club_img:      rb 24

font_data: rb 48

; -------- SECTION -----------
section '.data' writeable

font: db "cardsrc/Libre_Baskerville/LibreBaskerville-SemiBold.ttf", 0
text:
   .fontSize: dd 23.0
   .message:  db " 4", 15 dup(0)
   .spacing:  db 0 

heart_path: db "cardsrc/card_images/heart.svg", 0
diamond_path: db "cardsrc/card_images/diamond.svg", 0
spade_path: db "cardsrc/card_images/spade.svg", 0
club_path: db "cardsrc/card_images/club.svg", 0

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

;loadCardSuits:
;.heart:
;   ; === Draw loop — centered with scale ===
;   ; posX = (screenW - texW * scale) / 2
;   ; posY = (screenH - texH * scale) / 2
;   
;   movss xmm0, [scale]
;   cvtsi2ss xmm1, [tex_width]      ; tex width as float
;   mulss xmm0, xmm1                ; texW * scale
;   mov eax, 800
;   cvtsi2ss xmm1, eax              ; screenW as float
;   subss xmm1, xmm0
;   movss xmm6, [half]              ; 0.5
;   mulss xmm1, xmm6                ; /2 -> posX
;   
;   ; similar for posY...
;   
;   ; DrawTextureEx(tex, position, rotation, scale, tint)
;   lea rdi, [heart_tex]
;   movq xmm0, xmm1                 ; Vector2 position {x, y} packed
;   movss xmm1, [rotation]
;   movss xmm2, [scale]
;   mov esi, 0xFFFFFFFF             ; WHITE
;   call DrawTextureEx 
;
;.diamond:
;.club:
;.spade:

; Create suit and ranks of card
; Use bytes to access index easily
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
