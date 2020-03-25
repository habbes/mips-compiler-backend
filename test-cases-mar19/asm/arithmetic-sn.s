#main: number6_s1: 4
#main: _t9_s0: 8
#main: two_s1: 12
#main: number4_s1: 16
#main: _t7_s0: 20
#main: _t10_s0: 24
#main: number2_s1: 28
#main: _t5_s0: 32
#main: three_s1: 36
#main: _t3_s0: 40
#main: _t14_s0: 44
#main: _t12_s0: 48
#main: _t16_s0: 52
#main: _t18_s0: 56
#main: _t19_s0: 60
#main: _t20_s0: 64
#main: _t22_s0: 68
#main: number5_s1: 72
#main: _t8_s0: 76
#main: _t6_s0: 80
#main: number3_s1: 84
#main: _t4_s0: 88
#main: _t2_s0: 92
#main: _t13_s0: 96
#main: _t11_s0: 100
#main: _t15_s0: 104
#main: _t17_s0: 108
#main: _t21_s0: 112
#main: _t1_s0: 116
#main: number1_s1: 120
#main: _t23_s0: 124
.data
dregisters:	.space	64
sp_temp:	.word	0
.text
.globl main

######## main
_s0_main:
.text
sw	$ra, 0($sp)
addiu	$sp, $sp, -128	# Move stack pointer to accommodate variables in this function.
la	$s0, dregisters		# Load address of dregisters in $s0
sw	$sp, 0($s0)			# Move stack pointer to 4*function level in dregisters ($s0 is address of dregisters).
# assign,two_s1,2,
lw	$t9, 12($sp)
li	$t8, 2
move	$t9, $t8
sw	$t9, 12($sp)

# assign,three_s1,3,
lw	$t8, 36($sp)
li	$t9, 3
move	$t8, $t9
sw	$t8, 36($sp)

# main:

# mul,two_s1,three_s1,_t1_s0
lw	$t9, 116($sp)
lw	$t8, 12($sp)
lw	$t7, 36($sp)
mul	$t9, $t8, $t7
sw	$t9, 116($sp)
sw	$t8, 12($sp)
sw	$t7, 36($sp)


# call,printi,_t1_s0
lw	$t7, 116($sp)
move	$a0, $t7
sw	$t7, 116($sp)
jal	printi

# add,three_s1,three_s1,_t2_s0
lw	$t7, 92($sp)
lw	$t8, 36($sp)
add	$t7, $t8, $t8
sw	$t7, 92($sp)
sw	$t8, 36($sp)


# assign,number1_s1,_t2_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t8, 120($sp)
lw	$t7, 92($sp)
move	$t8, $t7
sw	$t8, 120($sp)
sw	$t7, 92($sp)


# mul,2,three_s1,_t3_s0
li	$t7, 2
lw	$t8, 40($sp)
lw	$t9, 36($sp)
mul	$t8, $t7, $t9
sw	$t8, 40($sp)
sw	$t9, 36($sp)


# assign,number2_s1,_t3_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, 28($sp)
lw	$t8, 40($sp)
move	$t9, $t8
sw	$t9, 28($sp)
sw	$t8, 40($sp)


# add,2,2,_t4_s0
li	$t8, 2
li	$t9, 2
add	$t7, $t8, $t9
sw	$t7, 88($sp)


# add,_t4_s0,2,_t5_s0
li	$t8, 2
lw	$t9, 32($sp)
lw	$t6, 88($sp)
add	$t9, $t6, $t8
sw	$t9, 32($sp)
sw	$t6, 88($sp)


# assign,number3_s1,_t5_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t6, 84($sp)
lw	$t9, 32($sp)
move	$t6, $t9
sw	$t6, 84($sp)
sw	$t9, 32($sp)


# mul,1,1,_t6_s0
li	$t9, 1
li	$t6, 1
mul	$t8, $t9, $t6
sw	$t8, 80($sp)


# add,_t6_s0,2,_t7_s0
li	$t9, 2
lw	$t6, 20($sp)
lw	$t5, 80($sp)
add	$t6, $t5, $t9
sw	$t6, 20($sp)
sw	$t5, 80($sp)


# add,_t7_s0,three_s1,_t8_s0
lw	$t5, 76($sp)
lw	$t6, 20($sp)
lw	$t9, 36($sp)
add	$t5, $t6, $t9
sw	$t5, 76($sp)
sw	$t6, 20($sp)
sw	$t9, 36($sp)


# assign,number4_s1,_t8_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, 16($sp)
lw	$t6, 76($sp)
move	$t9, $t6
sw	$t9, 16($sp)
sw	$t6, 76($sp)


# add,three_s1,three_s1,_t9_s0
lw	$t6, 8($sp)
lw	$t9, 36($sp)
add	$t6, $t9, $t9
sw	$t6, 8($sp)
sw	$t9, 36($sp)


# assign,number5_s1,_t9_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, 72($sp)
lw	$t6, 8($sp)
move	$t9, $t6
sw	$t9, 72($sp)
sw	$t6, 8($sp)


# add,three_s1,three_s1,_t10_s0
lw	$t6, 24($sp)
lw	$t9, 36($sp)
add	$t6, $t9, $t9
sw	$t6, 24($sp)
sw	$t9, 36($sp)


# assign,number5_s1,_t10_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, 72($sp)
lw	$t6, 24($sp)
move	$t9, $t6
sw	$t9, 72($sp)
sw	$t6, 24($sp)


# add,two_s1,two_s1,_t11_s0
lw	$t6, 100($sp)
lw	$t9, 12($sp)
add	$t6, $t9, $t9
sw	$t6, 100($sp)
sw	$t9, 12($sp)


# add,_t11_s0,two_s1,_t12_s0
lw	$t9, 48($sp)
lw	$t6, 100($sp)
lw	$t5, 12($sp)
add	$t9, $t6, $t5
sw	$t9, 48($sp)
sw	$t6, 100($sp)
sw	$t5, 12($sp)


# assign,number5_s1,_t12_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t5, 72($sp)
lw	$t6, 48($sp)
move	$t5, $t6
sw	$t5, 72($sp)
sw	$t6, 48($sp)


# add,two_s1,two_s1,_t13_s0
lw	$t6, 96($sp)
lw	$t5, 12($sp)
add	$t6, $t5, $t5
sw	$t6, 96($sp)
sw	$t5, 12($sp)


# add,_t13_s0,two_s1,_t14_s0
lw	$t5, 44($sp)
lw	$t6, 96($sp)
lw	$t9, 12($sp)
add	$t5, $t6, $t9
sw	$t5, 44($sp)
sw	$t6, 96($sp)
sw	$t9, 12($sp)


# assign,number5_s1,_t14_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, 72($sp)
lw	$t6, 44($sp)
move	$t9, $t6
sw	$t9, 72($sp)
sw	$t6, 44($sp)


# assign,_t15_s0,1,
lw	$t6, 104($sp)
li	$t9, 1
move	$t6, $t9
sw	$t6, 104($sp)

# assign,_t16_s0,1,
lw	$t9, 52($sp)
li	$t6, 1
move	$t9, $t6
sw	$t9, 52($sp)

# loop_label_0:
loop_label_0:

# brgt,_t16_s0,3,loop_label_1
lw	$t6, 52($sp)
li	$t9, 3
bgt	$t6, $t9, loop_label_1
sw	$t6, 52($sp)

# mult,_t15_s0,2,_t17_s0
li	$t9, 2
lw	$t6, 108($sp)
lw	$t5, 104($sp)
mul	$t6, $t5, $t9
sw	$t6, 108($sp)
sw	$t5, 104($sp)


# assign,_t15_s0,_t17_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t5, 104($sp)
lw	$t6, 108($sp)
move	$t5, $t6
sw	$t5, 104($sp)
sw	$t6, 108($sp)


# add,_t16_s0,1,_t16_s0
li	$t6, 1
lw	$t5, 52($sp)
add	$t5, $t5, $t6
sw	$t5, 52($sp)


# goto,loop_label_0,,
j loop_label_0

# loop_label_1:
loop_label_1:

# sub,_t15_s0,2,_t18_s0
li	$t5, 2
lw	$t6, 56($sp)
lw	$t9, 104($sp)
sub	$t6, $t9, $t5
sw	$t6, 56($sp)
sw	$t9, 104($sp)


# assign,number6_s1,_t18_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, 4($sp)
lw	$t6, 56($sp)
move	$t9, $t6
sw	$t9, 4($sp)
sw	$t6, 56($sp)


# add,number1_s1,number2_s1,_t19_s0
lw	$t6, 60($sp)
lw	$t9, 120($sp)
lw	$t5, 28($sp)
add	$t6, $t9, $t5
sw	$t6, 60($sp)
sw	$t9, 120($sp)
sw	$t5, 28($sp)


# add,_t19_s0,number3_s1,_t20_s0
lw	$t5, 64($sp)
lw	$t9, 60($sp)
lw	$t6, 84($sp)
add	$t5, $t9, $t6
sw	$t5, 64($sp)
sw	$t9, 60($sp)
sw	$t6, 84($sp)


# add,_t20_s0,number4_s1,_t21_s0
lw	$t6, 112($sp)
lw	$t9, 64($sp)
lw	$t5, 16($sp)
add	$t6, $t9, $t5
sw	$t6, 112($sp)
sw	$t9, 64($sp)
sw	$t5, 16($sp)


# add,_t21_s0,number5_s1,_t22_s0
lw	$t5, 68($sp)
lw	$t9, 112($sp)
lw	$t6, 72($sp)
add	$t5, $t9, $t6
sw	$t5, 68($sp)
sw	$t9, 112($sp)
sw	$t6, 72($sp)


# add,_t22_s0,number6_s1,_t23_s0
lw	$t6, 124($sp)
lw	$t9, 68($sp)
lw	$t5, 4($sp)
add	$t6, $t9, $t5
sw	$t6, 124($sp)
sw	$t9, 68($sp)
sw	$t5, 4($sp)


# call,printi,_t23_s0
lw	$t5, 124($sp)
move	$a0, $t5
sw	$t5, 124($sp)
jal	printi

# call,printi,36
li	$a0, 36
jal	printi

# return,,,

addiu	$sp, $sp, 128
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

