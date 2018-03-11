label1:
	lda #$20
	sta $30
	pha
	lda #$30
	sta $31
	pla

label2:
	sta $32
	lda #$5
	pha
	lda #$7
	sta $33
	pla
	sta $34
