#addInt: first_s3: 4
#addInt: _t1_s0: 8
#addInt: second_s3: 12
#subInt: second_s4: 4
#subInt: _t2_s0: 8
#subInt: first_s4: 12
#main: _t3_s0: 4
#main: creatures_s2: 8
#main: goblins_s1: 12
.data
dregisters:	.space	64
sp_temp:	.word	0
.text
.globl main

######## addInt
_s0_addInt:
.data
_s0_first_s3:	.word	0
_s0__t1_s0:	.word	0
_s0_second_s3:	.word	0
_s0_savera:	.word	0
.text
sw	$ra, _s0_savera
sw	$a0, _s0_first_s3
sw	$a1, _s0_second_s3
# add,first_s3,second_s3,_t1_s0
lw	$t9, _s0__t1_s0
lw	$t8, _s0_first_s3
lw	$t7, _s0_second_s3
add	$t9, $t8, $t7
sw	$t9, _s0__t1_s0
sw	$t8, _s0_first_s3
sw	$t7, _s0_second_s3


# return,_t1_s0,,
lw	$t7, _s0__t1_s0
move	$v0, $t7
sw	$t7, _s0__t1_s0
lw	$ra, _s0_savera
jr	$ra

lw	$ra, _s0_savera
jr	$ra

######## subInt
_s1_subInt:
.data
_s1_second_s4:	.word	0
_s1__t2_s0:	.word	0
_s1_first_s4:	.word	0
_s1_savera:	.word	0
.text
sw	$ra, _s1_savera
sw	$a0, _s1_first_s4
sw	$a1, _s1_second_s4
# sub,first_s4,second_s4,_t2_s0
lw	$t7, _s1__t2_s0
lw	$t8, _s1_first_s4
lw	$t9, _s1_second_s4
sub	$t7, $t8, $t9
sw	$t7, _s1__t2_s0
sw	$t8, _s1_first_s4
sw	$t9, _s1_second_s4


# return,_t2_s0,,
lw	$t9, _s1__t2_s0
move	$v0, $t9
sw	$t9, _s1__t2_s0
lw	$ra, _s1_savera
jr	$ra

lw	$ra, _s1_savera
jr	$ra

######## main
_s2_main:
.data
_s2__t3_s0:	.word	0
_s2_creatures_s2:	.word	0
_s2_goblins_s1:	.word	0
_s2_savera:	.word	0
.text
sw	$ra, _s2_savera
# assign,goblins_s1,6,
lw	$t9, _s2_goblins_s1
li	$t8, 6
move	$t9, $t8
sw	$t9, _s2_goblins_s1

# main:

# assign,creatures_s2,2,
lw	$t8, _s2_creatures_s2
li	$t9, 2
move	$t8, $t9
sw	$t8, _s2_creatures_s2

# assign,creatures_s2,goblins_s1,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s2_creatures_s2
lw	$t8, _s2_goblins_s1
move	$t9, $t8
sw	$t9, _s2_creatures_s2
sw	$t8, _s2_goblins_s1


# callr,_t3_s0,addInt,creatures_s2,goblins_s1
lw	$t8, _s2_creatures_s2
move	$a0, $t8
sw	$t8, _s2_creatures_s2
lw	$t8, _s2_goblins_s1
move	$a1, $t8
sw	$t8, _s2_goblins_s1
jal	_s0_addInt
lw	$t8, _s2__t3_s0
move	$t8, $v0
sw	$t8, _s2__t3_s0

# assign,creatures_s2,_t3_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t8, _s2_creatures_s2
lw	$t9, _s2__t3_s0
move	$t8, $t9
sw	$t8, _s2_creatures_s2
sw	$t9, _s2__t3_s0


# call,printi,12
li	$a0, 12
jal	printi

# call,printi,creatures_s2
lw	$t9, _s2_creatures_s2
lw	$t9, _s2_creatures_s2
move	$a0, $t9
sw	$t9, _s2_creatures_s2
jal	printi

# return,,,

lw	$ra, _s2_savera
jr	$ra
######## main
main:
jal	_s2_main
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

