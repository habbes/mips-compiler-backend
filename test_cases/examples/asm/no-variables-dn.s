#main: _t1_s0: 4
#main: _t2_s0: 8
#main: _t3_s0: 12
.data
dregisters:	.space	64
sp_temp:	.word	0
.text
.globl main

######## main
_s0_main:
.data
_s0__t1_s0:	.word	0
_s0__t2_s0:	.word	0
_s0__t3_s0:	.word	0
_s0_savera:	.word	0
.text
sw	$ra, _s0_savera
# main:

# add,2,3,_t1_s0
li	$t9, 2
li	$t8, 3
add	$t7, $t9, $t8
sw	$t7, _s0__t1_s0


# call,printi,_t1_s0
lw	$t9, _s0__t1_s0
lw	$t9, _s0__t1_s0
move	$a0, $t9
sw	$t9, _s0__t1_s0
jal	printi

# add,1,2,_t2_s0
li	$t9, 1
li	$t8, 2
add	$t6, $t9, $t8
sw	$t6, _s0__t2_s0


# add,_t2_s0,3,_t3_s0
li	$t9, 3
lw	$t8, _s0__t3_s0
lw	$t5, _s0__t2_s0
add	$t8, $t5, $t9
sw	$t8, _s0__t3_s0
sw	$t5, _s0__t2_s0


# call,printi,_t3_s0
lw	$t5, _s0__t3_s0
lw	$t5, _s0__t3_s0
move	$a0, $t5
sw	$t5, _s0__t3_s0
jal	printi

# return,,,

lw	$ra, _s0_savera
jr	$ra
######## main
main:
jal	_s0_main
j	exit

printi:
	.data
	lf:	.asciiz	"\n"
	.text
	li	$v0, 1
	syscall
	li	$v0,4
	la	$a0, lf
	syscall
	jr	$ra

printf:
	.data
	__lf:	.asciiz	"\n"
	.text
	li	$v0, 2
	syscall
	li	$v0, 4
	la	$a0, lf
	syscall
	jr	$ra

exit:
	li	$v0, 10
	syscall

initIntArray:
	# $a0=address of array, $a1 = size of array, $a2 = value
	li $s0, 0
	startloop:
	beq $s0, $a1, endloop
	sw $a2, ($a0)
	addi $a0, $a0, 4
	addi $s0, $s0, 1
	j startloop
	endloop: jr $ra

storeIntArray:
	# $a0=address of array, $a1 = index, $a2 = value
	li $s0, 4
	mul $s1, $a1, $s0
	add $a0, $a0, $s1
	sw $a2, ($a0)
	jr $ra

loadIntArray:
	# $a0=address of array, $a1 = index
	li $s0, 4
	mul $s1, $a1, $s0
	add $a0, $a0, $s1
	lw $v0, ($a0)
	jr $ra

initFloatArray:
	# $a0=address of array, $a1 = size of array, $a2 = address of value, $f12 = value
	li $s0, 0
	startloop_f:
	beq $s0, $a1, endloop_f
	s.s $f12, ($a0)
	addi $a0, $a0, 4
	addi $s0, $s0, 1
	j startloop_f
	endloop_f: jr $ra

loadFloatArray:
	# $a0=address of array, $a1 = index
	li $s0, 4
	mul $s1, $a1, $s0
	add $a0, $a0, $s1
	l.s $f0, ($a0)
	jr $ra

storeFloatArray:
	# $a0=address of array, $a1 = index, $a2 = value
	li $s0, 4
	mul $s1, $a1, $s0
	add $a0, $a0, $s1
	s.s $a2, ($a0)
	jr $ra

