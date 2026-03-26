; draw_num_on_card(float* rect, char* message, Font* font_ptr)
; rdi = rect pointer
; rsi = message pointer
; rdx = font pointer
draw_num_on_card:
   push rbp
   mov rbp, rsp
   sub rsp, 88          ; [font:64 bytes][parameters:24 bytes]
   mov [rbp-8], rdi     ; card_rectangle
   mov [rbp-16], rsi    ; message
   mov [rbp-24], rdx    ; save font pointer
   
   ; copy font onto stack using rdx
   mov rax, [rdx]
   mov [rsp], rax
   mov rax, [rdx+8]
   mov [rsp+8], rax
   mov rax, [rdx+16]
   mov [rsp+16], rax
   mov rax, [rdx+24]
   mov [rsp+24], rax
   mov rax, [rdx+32]
   mov [rsp+32], rax
   mov rax, [rdx+40]
   mov [rsp+40], rax
   mov rax, [rdx+48]
   mov [rsp+48], rax

   ; set up DrawTextPro args
   mov rdi, [rbp-16]
   mov rax, [rbp-8]
   
   movsd xmm0, [rax]
   pxor xmm1, xmm1
   pxor xmm2, xmm2
   movss xmm3, [font_size]
   pxor xmm4, xmm4
   mov esi, 0xFFFFFFFF
   call DrawTextPro
   mov rsp, rbp
   pop rbp
   ret

section '.data' writeable
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
font_size: dd 12.0
