#main: _t8_s0: 4
#main: _t6_s0: 8
#main: _t9_s0: 12
#main: _t7_s0: 16
#main: _t10_s0: 20
#main: _t5_s0: 24
#main: _t4_s0: 28
#main: _t2_s0: 32
#main: _t3_s0: 36
#main: _t12_s0: 40
#main: _t11_s0: 44
#main: true_s1: 48
#main: _t1_s0: 52
#main: false_s1: 56
.data
dregisters:	.space	64
sp_temp:	.word	0
.text
.globl main

######## main
_s0_main:
.data
_s0__t8_s0:	.word	0
_s0__t6_s0:	.word	0
_s0__t9_s0:	.word	0
_s0__t7_s0:	.word	0
_s0__t10_s0:	.word	0
_s0__t5_s0:	.word	0
_s0__t4_s0:	.word	0
_s0__t2_s0:	.word	0
_s0__t3_s0:	.word	0
_s0__t12_s0:	.word	0
_s0__t11_s0:	.word	0
_s0_true_s1:	.word	0
_s0__t1_s0:	.word	0
_s0_false_s1:	.word	0
_s0_savera:	.word	0
.text
sw	$ra, _s0_savera
# assign,true_s1,1,
lw	$t9, _s0_true_s1
li	$t8, 1
move	$t9, $t8
sw	$t9, _s0_true_s1

# assign,false_s1,0,
lw	$t8, _s0_false_s1
li	$t9, 0
move	$t8, $t9
sw	$t8, _s0_false_s1

# main:

# and,true_s1,true_s1,_t1_s0
lw	$t9, _s0__t1_s0
lw	$t8, _s0_true_s1
and	$t9, $t8, $t8
sw	$t9, _s0__t1_s0
sw	$t8, _s0_true_s1

# call,printi,_t1_s0
lw	$t8, _s0__t1_s0
lw	$t8, _s0__t1_s0
move	$a0, $t8
sw	$t8, _s0__t1_s0
jal	printi

# and,true_s1,false_s1,_t2_s0
lw	$t8, _s0__t2_s0
lw	$t9, _s0_true_s1
lw	$t7, _s0_false_s1
and	$t8, $t9, $t7
sw	$t8, _s0__t2_s0
sw	$t9, _s0_true_s1
sw	$t7, _s0_false_s1

# call,printi,_t2_s0
lw	$t7, _s0__t2_s0
lw	$t7, _s0__t2_s0
move	$a0, $t7
sw	$t7, _s0__t2_s0
jal	printi

# and,false_s1,false_s1,_t3_s0
lw	$t7, _s0__t3_s0
lw	$t9, _s0_false_s1
and	$t7, $t9, $t9
sw	$t7, _s0__t3_s0
sw	$t9, _s0_false_s1

# call,printi,_t3_s0
lw	$t9, _s0__t3_s0
lw	$t9, _s0__t3_s0
move	$a0, $t9
sw	$t9, _s0__t3_s0
jal	printi

# or,true_s1,true_s1,_t4_s0
lw	$t9, _s0__t4_s0
lw	$t7, _s0_true_s1
or	$t9, $t7, $t7
sw	$t9, _s0__t4_s0
sw	$t7, _s0_true_s1

# call,printi,_t4_s0
lw	$t7, _s0__t4_s0
lw	$t7, _s0__t4_s0
move	$a0, $t7
sw	$t7, _s0__t4_s0
jal	printi

# or,true_s1,false_s1,_t5_s0
lw	$t7, _s0__t5_s0
lw	$t9, _s0_true_s1
lw	$t8, _s0_false_s1
or	$t7, $t9, $t8
sw	$t7, _s0__t5_s0
sw	$t9, _s0_true_s1
sw	$t8, _s0_false_s1

# call,printi,_t5_s0
lw	$t8, _s0__t5_s0
lw	$t8, _s0__t5_s0
move	$a0, $t8
sw	$t8, _s0__t5_s0
jal	printi

# or,false_s1,false_s1,_t6_s0
lw	$t8, _s0__t6_s0
lw	$t9, _s0_false_s1
or	$t8, $t9, $t9
sw	$t8, _s0__t6_s0
sw	$t9, _s0_false_s1

# call,printi,_t6_s0
lw	$t9, _s0__t6_s0
lw	$t9, _s0__t6_s0
move	$a0, $t9
sw	$t9, _s0__t6_s0
jal	printi

# and,1,true_s1,_t7_s0
lw	$t9, _s0__t7_s0
lw	$t8, _s0_true_s1
andi	$t9, $t8, 1
sw	$t9, _s0__t7_s0
sw	$t8, _s0_true_s1

# call,printi,_t7_s0
lw	$t8, _s0__t7_s0
lw	$t8, _s0__t7_s0
move	$a0, $t8
sw	$t8, _s0__t7_s0
jal	printi

# and,true_s1,1,_t8_s0
lw	$t8, _s0__t8_s0
lw	$t9, _s0_true_s1
andi	$t8, $t9, 1
sw	$t8, _s0__t8_s0
sw	$t9, _s0_true_s1

# call,printi,_t8_s0
lw	$t9, _s0__t8_s0
lw	$t9, _s0__t8_s0
move	$a0, $t9
sw	$t9, _s0__t8_s0
jal	printi

# and,1,1,_t9_s0
lw	$t9, _s0__t9_s0
li	$t8, 1
andi	$t9, $t8, 1
sw	$t9, _s0__t9_s0

# call,printi,_t9_s0
lw	$t8, _s0__t9_s0
lw	$t8, _s0__t9_s0
move	$a0, $t8
sw	$t8, _s0__t9_s0
jal	printi

# or,0,false_s1,_t10_s0
lw	$t8, _s0__t10_s0
lw	$t9, _s0_false_s1
ori	$t8, $t9, 0
sw	$t8, _s0__t10_s0
sw	$t9, _s0_false_s1

# call,printi,_t10_s0
lw	$t9, _s0__t10_s0
lw	$t9, _s0__t10_s0
move	$a0, $t9
sw	$t9, _s0__t10_s0
jal	printi

# or,false_s1,0,_t11_s0
lw	$t9, _s0__t11_s0
lw	$t8, _s0_false_s1
ori	$t9, $t8, 0
sw	$t9, _s0__t11_s0
sw	$t8, _s0_false_s1

# call,printi,_t11_s0
lw	$t8, _s0__t11_s0
lw	$t8, _s0__t11_s0
move	$a0, $t8
sw	$t8, _s0__t11_s0
jal	printi

# or,0,0,_t12_s0
lw	$t8, _s0__t12_s0
li	$t9, 0
ori	$t8, $t9, 0
sw	$t8, _s0__t12_s0

# call,printi,_t12_s0
lw	$t9, _s0__t12_s0
lw	$t9, _s0__t12_s0
move	$a0, $t9
sw	$t9, _s0__t12_s0
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

