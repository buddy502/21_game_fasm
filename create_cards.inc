; draw_num_on_card(float* rect, char* message, Font* font_ptr)
; rdi = rect pointer
; rsi = message pointer
; rdx = font pointer

; -------- SECTION -----------
section '.data' writeable

font: rb 56
text:
   .fontSize: dd 12.0
   .message:   db "1", 0
   .spacing:   db 0 

section '.text' executable

draw_num_on_card:
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
    movsd xmm0, [card_rectangle.xy]
    pxor xmm1, xmm1
    pxor xmm2, xmm2
    movss xmm3, [card_rectangle.wh]
    addss xmm3, [card_rectangle.wh+4]
    movss xmm4, [text.fontSize]
    divss xmm3, xmm4
    pxor xmm4, xmm4
    movss xmm4, [text.spacing]
    mov esi, 0xFFFFFFFF
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
