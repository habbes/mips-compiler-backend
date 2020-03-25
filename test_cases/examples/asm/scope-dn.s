#changex: _t1_s0: 4
#main: x_s1: 4
.data
dregisters:	.space	64
sp_temp:	.word	0
.text
.globl main

######## changex
_s0_changex:
.data
_s0__t1_s0:	.word	0
_s0_savera:	.word	0
.text
sw	$ra, _s0_savera
# add,x_s1,1,_t1_s0
li	$t9, 1
lw	$t8, _s0__t1_s0
lw	$t7, _s1_x_s1
add	$t8, $t7, $t9
sw	$t8, _s0__t1_s0
sw	$t7, _s1_x_s1


# assign,x_s1,_t1_s0,
#*** copyto level: 0
#*** copyfrom level: 1
lw	$t7, _s1_x_s1
lw	$t8, _s0__t1_s0
move	$t7, $t8
sw	$t7, _s1_x_s1
sw	$t8, _s0__t1_s0


lw	$ra, _s0_savera
jr	$ra

######## main
_s1_main:
.data
_s1_x_s1:	.word	0
_s1_savera:	.word	0
.text
sw	$ra, _s1_savera
# assign,x_s1,5,
lw	$t8, _s1_x_s1
li	$t7, 5
move	$t8, $t7
sw	$t8, _s1_x_s1

# main:

# call,printi,x_s1
lw	$t7, _s1_x_s1
lw	$t7, _s1_x_s1
move	$a0, $t7
sw	$t7, _s1_x_s1
jal	printi

# call,changex
jal	_s0_changex

# call,printi,x_s1
lw	$t7, _s1_x_s1
lw	$t7, _s1_x_s1
move	$a0, $t7
sw	$t7, _s1_x_s1
jal	printi

# return,,,

lw	$ra, _s1_savera
jr	$ra
######## main
main:
jal	_s1_main
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

