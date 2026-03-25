ACE equ 0
DIAMOND equ 1
HEARTS equ 2
CLUBS equ 3

; Create suit and ranks of card
; Use bytes to access index easily

deck:
   times 52 db 0

deck_rank:
   db 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13

suits:
   db 0, 1, 2, 3
