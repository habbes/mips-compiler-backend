#main: areEqual_s1: 4
#main: first_s1: 8
#main: _t1_s0: 12
#main: _t2_s0: 16
#main: second_s1: 20
.data
dregisters:	.space	64
sp_temp:	.word	0
.text
.globl main

######## main
_s0_main:
.data
_s0_areEqual_s1:	.word	0
_s0_first_s1:	.word	0
_s0__t1_s0:	.word	0
_s0__t2_s0:	.word	0
_s0_second_s1:	.word	0
_s0_savera:	.word	0
.text
sw	$ra, _s0_savera
# assign,first_s1,1,
lw	$t9, _s0_first_s1
li	$t8, 1
move	$t9, $t8
sw	$t9, _s0_first_s1

# assign,second_s1,2,
lw	$t8, _s0_second_s1
li	$t9, 2
move	$t8, $t9
sw	$t8, _s0_second_s1

# assign,areEqual_s1,0,
lw	$t9, _s0_areEqual_s1
li	$t8, 0
move	$t9, $t8
sw	$t9, _s0_areEqual_s1

# main:

# assign,_t1_s0,0,
lw	$t8, _s0__t1_s0
li	$t9, 0
move	$t8, $t9
sw	$t8, _s0__t1_s0

# brneq,first_s1,second_s1,if_label_0
lw	$t9, _s0_first_s1
lw	$t8, _s0_second_s1
bne	$t9, $t8, if_label_0
sw	$t9, _s0_first_s1
sw	$t8, _s0_second_s1

# assign,_t1_s0,1,
lw	$t8, _s0__t1_s0
li	$t9, 1
move	$t8, $t9
sw	$t8, _s0__t1_s0

# if_label_0:
if_label_0:

# brneq,_t1_s0,1,if_label_1
lw	$t9, _s0__t1_s0
li	$t8, 1
bne	$t9, $t8, if_label_1
sw	$t9, _s0__t1_s0

# assign,areEqual_s1,1,
lw	$t8, _s0_areEqual_s1
li	$t9, 1
move	$t8, $t9
sw	$t8, _s0_areEqual_s1

# goto,if_label_2,,
j if_label_2

# if_label_1:
if_label_1:

# assign,areEqual_s1,2,
lw	$t9, _s0_areEqual_s1
li	$t8, 2
move	$t9, $t8
sw	$t9, _s0_areEqual_s1

# if_label_2:
if_label_2:

# call,printi,first_s1
lw	$t8, _s0_first_s1
lw	$t8, _s0_first_s1
move	$a0, $t8
sw	$t8, _s0_first_s1
jal	printi

# call,printi,second_s1
lw	$t8, _s0_second_s1
lw	$t8, _s0_second_s1
move	$a0, $t8
sw	$t8, _s0_second_s1
jal	printi

# call,printi,areEqual_s1
lw	$t8, _s0_areEqual_s1
lw	$t8, _s0_areEqual_s1
move	$a0, $t8
sw	$t8, _s0_areEqual_s1
jal	printi

# assign,first_s1,2,
lw	$t8, _s0_first_s1
li	$t9, 2
move	$t8, $t9
sw	$t8, _s0_first_s1

# assign,_t2_s0,0,
lw	$t9, _s0__t2_s0
li	$t8, 0
move	$t9, $t8
sw	$t9, _s0__t2_s0

# brneq,first_s1,second_s1,if_label_3
lw	$t8, _s0_first_s1
lw	$t9, _s0_second_s1
bne	$t8, $t9, if_label_3
sw	$t8, _s0_first_s1
sw	$t9, _s0_second_s1

# assign,_t2_s0,1,
lw	$t9, _s0__t2_s0
li	$t8, 1
move	$t9, $t8
sw	$t9, _s0__t2_s0

# if_label_3:
if_label_3:

# brneq,_t2_s0,1,if_label_4
lw	$t8, _s0__t2_s0
li	$t9, 1
bne	$t8, $t9, if_label_4
sw	$t8, _s0__t2_s0

# assign,areEqual_s1,1,
lw	$t9, _s0_areEqual_s1
li	$t8, 1
move	$t9, $t8
sw	$t9, _s0_areEqual_s1

# goto,if_label_5,,
j if_label_5

# if_label_4:
if_label_4:

# assign,areEqual_s1,2,
lw	$t8, _s0_areEqual_s1
li	$t9, 2
move	$t8, $t9
sw	$t8, _s0_areEqual_s1

# if_label_5:
if_label_5:

# call,printi,first_s1
lw	$t9, _s0_first_s1
lw	$t9, _s0_first_s1
move	$a0, $t9
sw	$t9, _s0_first_s1
jal	printi

# call,printi,second_s1
lw	$t9, _s0_second_s1
lw	$t9, _s0_second_s1
move	$a0, $t9
sw	$t9, _s0_second_s1
jal	printi

# call,printi,areEqual_s1
lw	$t9, _s0_areEqual_s1
lw	$t9, _s0_areEqual_s1
move	$a0, $t9
sw	$t9, _s0_areEqual_s1
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

