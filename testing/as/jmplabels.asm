#org $600

start:
	jmp init

init:
	jsr main
	brk

main:
	lda #$F
	sta $10
	rts

end:	
