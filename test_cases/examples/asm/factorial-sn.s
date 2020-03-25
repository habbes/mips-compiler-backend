#fact: n_s2: 4
#fact: _t4_s0: 8
#fact: _t1_s0: 12
#fact: _t2_s0: 16
#fact: _t3_s0: 20
#main: _t6_s0: 4
#main: _t5_s0: 8
#main: r_s1: 12
.data
dregisters:	.space	64
sp_temp:	.word	0
.text
.globl main

######## fact
_s0_fact:
.text
sw	$ra, 0($sp)
addiu	$sp, $sp, -24	# Move stack pointer to accommodate variables in this function.
la	$s0, dregisters		# Load address of dregisters in $s0
sw	$sp, 4($s0)			# Move stack pointer to 4*function level in dregisters ($s0 is address of dregisters).
sw	$a0, 4($sp)
# assign,_t1_s0,0,
lw	$t9, 12($sp)
li	$t8, 0
move	$t9, $t8
sw	$t9, 12($sp)

# brneq,n_s2,1,if_label_1
lw	$t8, 4($sp)
li	$t9, 1
bne	$t8, $t9, if_label_1
sw	$t8, 4($sp)

# assign,_t1_s0,1,
lw	$t9, 12($sp)
li	$t8, 1
move	$t9, $t8
sw	$t9, 12($sp)

# if_label_1:
if_label_1:

# brneq,_t1_s0,1,if_label_0
lw	$t8, 12($sp)
li	$t9, 1
bne	$t8, $t9, if_label_0
sw	$t8, 12($sp)

# return,1,,
li	$v0, 1
addiu	$sp, $sp, 24
lw	$ra, 0($sp)
jr	$ra

# if_label_0:
if_label_0:

# sub,n_s2,1,_t2_s0
li	$t9, 1
lw	$t8, 16($sp)
lw	$t7, 4($sp)
sub	$t8, $t7, $t9
sw	$t8, 16($sp)
sw	$t7, 4($sp)


# callr,_t3_s0,fact,_t2_s0
lw	$t7, 16($sp)
move	$a0, $t7
sw	$t7, 16($sp)
jal	_s0_fact
lw	$t7, 20($sp)
move	$t7, $v0
sw	$t7, 20($sp)

# assign,r_s1,_t3_s0,
#*** copyto level: 0
#*** copyfrom level: 1
# method: main var: r_s1 level: 0 offset: 12
sw	$sp, sp_temp		# save out $sp
la	$s0, dregisters		# Get $sp for this level.
lw	$sp, 0($s0)
lw	$t7, 12($sp)
lw	$sp, sp_temp		# Restore previous value of $sp.
lw	$t8, 20($sp)
move	$t7, $t8
# method: main var: r_s1 level: 0 offset: 12
sw	$sp, sp_temp		# save out $sp
la	$s0, dregisters		# Get $sp for this level.
lw	$sp, 0($s0)
sw	$t7, 12($sp)
lw	$sp, sp_temp		# Restore previous value of $sp.
sw	$t8, 20($sp)


# mul,n_s2,r_s1,_t4_s0
lw	$t8, 8($sp)
lw	$t7, 4($sp)
# method: main var: r_s1 level: 0 offset: 12
sw	$sp, sp_temp		# save out $sp
la	$s0, dregisters		# Get $sp for this level.
lw	$sp, 0($s0)
lw	$t9, 12($sp)
lw	$sp, sp_temp		# Restore previous value of $sp.
mul	$t8, $t7, $t9
sw	$t8, 8($sp)
sw	$t7, 4($sp)
# method: main var: r_s1 level: 0 offset: 12
sw	$sp, sp_temp		# save out $sp
la	$s0, dregisters		# Get $sp for this level.
lw	$sp, 0($s0)
sw	$t9, 12($sp)
lw	$sp, sp_temp		# Restore previous value of $sp.


# return,_t4_s0,,
lw	$t9, 8($sp)
move	$v0, $t9
sw	$t9, 8($sp)
addiu	$sp, $sp, 24
lw	$ra, 0($sp)
jr	$ra

addiu	$sp, $sp, 24
lw	$ra, 0($sp)
jr	$ra

######## main
_s1_main:
.text
sw	$ra, 0($sp)
addiu	$sp, $sp, -16	# Move stack pointer to accommodate variables in this function.
la	$s0, dregisters		# Load address of dregisters in $s0
sw	$sp, 0($s0)			# Move stack pointer to 4*function level in dregisters ($s0 is address of dregisters).
# assign,r_s1,1,
lw	$t9, 12($sp)
li	$t7, 1
move	$t9, $t7
sw	$t9, 12($sp)

# main:

# callr,_t5_s0,fact,5
li	$a0, 5
jal	_s0_fact
lw	$t7, 8($sp)
move	$t7, $v0
sw	$t7, 8($sp)

# assign,r_s1,_t5_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t7, 12($sp)
lw	$t9, 8($sp)
move	$t7, $t9
sw	$t7, 12($sp)
sw	$t9, 8($sp)


# call,printi,r_s1
lw	$t9, 12($sp)
move	$a0, $t9
sw	$t9, 12($sp)
jal	printi

# call,printi,120
li	$a0, 120
jal	printi

# callr,_t6_s0,fact,7
li	$a0, 7
jal	_s0_fact
lw	$t9, 4($sp)
move	$t9, $v0
sw	$t9, 4($sp)

# assign,r_s1,_t6_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, 12($sp)
lw	$t7, 4($sp)
move	$t9, $t7
sw	$t9, 12($sp)
sw	$t7, 4($sp)


# call,printi,r_s1
lw	$t7, 12($sp)
move	$a0, $t7
sw	$t7, 12($sp)
jal	printi

# call,printi,5040
li	$a0, 5040
jal	printi

# return,,,

addiu	$sp, $sp, 16
lw	$ra, 0($sp)
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

