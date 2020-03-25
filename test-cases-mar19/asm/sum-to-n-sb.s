#main: _t4_s0: 4
#main: _t1_s0: 8
#main: _t2_s0: 12
#main: _t3_s0: 16
#main: n_s1: 20
#main: total_s1: 24
#main: index_s1: 28
.data
dregisters:	.space	64
sp_temp:	.word	0
.text
.globl main

######## main
_s0_main:
.text
sw	$ra, 0($sp)
addiu	$sp, $sp, -32	# Move stack pointer to accommodate variables in this function.
la	$s0, dregisters		# Load address of dregisters in $s0
sw	$sp, 0($s0)			# Move stack pointer to 4*function level in dregisters ($s0 is address of dregisters).
#### Block 1
lw	$t9, 20($sp)
# the assigned variable is n_s1: $t9
lw	$t8, 24($sp)
# the assigned variable is total_s1: $t8
lw	$t7, 28($sp)
# the assigned variable is index_s1: $t7
# assign,n_s1,10,
li	$t6, 10
move	$t9, $t6
# main:
# assign,total_s1,0,
li	$t6, 0
move	$t8, $t6
# assign,index_s1,1,
li	$t6, 1
move	$t7, $t6
sw	$t9, 20($sp)
sw	$t8, 24($sp)
sw	$t7, 28($sp)
#### Block 2
# loop_label_0:
loop_label_0:
lw	$t7, 20($sp)
# the assigned variable is n_s1: $t7
lw	$t8, 28($sp)
# the assigned variable is index_s1: $t8
# brgt,index_s1,n_s1,loop_label_1
# this is a jump, need to write it out
sw	$t7, 20($sp)
sw	$t8, 28($sp)
bgt	$t8, $t7, loop_label_1
#### Block 3
lw	$t8, 28($sp)
# the assigned variable is index_s1: $t8
lw	$t7, 8($sp)
# the assigned variable is _t1_s0: $t7
lw	$t9, 24($sp)
# the assigned variable is total_s1: $t9
# add,total_s1,index_s1,_t1_s0
add	$t7, $t9, $t8

# assign,total_s1,_t1_s0,
#*** copyto level: 0
#*** copyfrom level: 0
move	$t9, $t7

# add,index_s1,1,index_s1
li	$t6, 1
add	$t8, $t8, $t6

# goto,loop_label_0,,
# this is a jump, need to write it out
sw	$t8, 28($sp)
sw	$t7, 8($sp)
sw	$t9, 24($sp)
j loop_label_0
#### Block 4
# loop_label_1:
loop_label_1:
lw	$t9, 4($sp)
# the assigned variable is _t4_s0: $t9
lw	$t7, 12($sp)
# the assigned variable is _t2_s0: $t7
lw	$t8, 16($sp)
# the assigned variable is _t3_s0: $t8
lw	$t6, 20($sp)
# the assigned variable is n_s1: $t6
# call,printi,total_s1
lw	$t5, 24($sp)
move	$a0, $t5
sw	$t5, 24($sp)
sw	$t9, 4($sp)
sw	$t7, 12($sp)
sw	$t8, 16($sp)
sw	$t6, 20($sp)
jal	printi
lw	$t9, 4($sp)
lw	$t7, 12($sp)
lw	$t8, 16($sp)
lw	$t6, 20($sp)
# add,n_s1,1,_t2_s0
li	$t5, 1
add	$t7, $t6, $t5

# mul,n_s1,_t2_s0,_t3_s0
mul	$t8, $t6, $t7

# div,_t3_s0,2,_t4_s0
li	$t5, 2
div	$t9, $t8, $t5

# call,printi,_t4_s0
move	$a0, $t9
sw	$t9, 4($sp)
sw	$t7, 12($sp)
sw	$t8, 16($sp)
sw	$t6, 20($sp)
jal	printi
lw	$t9, 4($sp)
lw	$t7, 12($sp)
lw	$t8, 16($sp)
lw	$t6, 20($sp)
# return,,,
sw	$t9, 4($sp)
sw	$t7, 12($sp)
sw	$t8, 16($sp)
sw	$t6, 20($sp)
addiu	$sp, $sp, 32
lw	$ra, 0($sp)
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

