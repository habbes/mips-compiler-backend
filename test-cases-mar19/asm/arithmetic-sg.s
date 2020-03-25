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
# New web started: two_s1 in register *$t8*
lw	$t8, 12($sp)
li	$t3, 2
move	$t8, $t3
# assign,three_s1,3,
# New web started: three_s1 in register *$t9*
lw	$t9, 36($sp)
li	$t3, 3
move	$t9, $t3
# main:
# mul,two_s1,three_s1,_t1_s0
# New web started: _t1_s0 in register *$t7*
lw	$t7, 116($sp)
mul	$t7, $t8, $t9

# call,printi,_t1_s0
move	$a0, $t7
sw	$t8, 12($sp)
sw	$t9, 36($sp)
sw	$t7, 116($sp)
jal	printi
lw	$t8, 12($sp)
lw	$t9, 36($sp)
lw	$t7, 116($sp)
# Web ended: _t1_s0 in register *$t7*
sw	$t7, 116($sp)
# add,three_s1,three_s1,_t2_s0
# New web started: _t2_s0 in register *$t6*
lw	$t6, 92($sp)
add	$t6, $t9, $t9

# assign,number1_s1,_t2_s0,
# New web started: number1_s1 in register *$t7*
lw	$t7, 120($sp)
#*** copyto level: 0
#*** copyfrom level: 0
move	$t7, $t6

# Web ended: _t2_s0 in register *$t6*
sw	$t6, 92($sp)
# mul,2,three_s1,_t3_s0
# New web started: _t3_s0 in register *$t6*
lw	$t6, 40($sp)
li	$t3, 2
mul	$t6, $t3, $t9

# assign,number2_s1,_t3_s0,
# Did not get a register: number2_s1
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t3, 28($sp)
move	$t3, $t6
sw	$t3, 28($sp)

# Web ended: _t3_s0 in register *$t6*
sw	$t6, 40($sp)
# add,2,2,_t4_s0
# New web started: _t4_s0 in register *$t5*
lw	$t5, 88($sp)
li	$t3, 2
li	$t2, 2
add	$t5, $t3, $t2

# add,_t4_s0,2,_t5_s0
# New web started: _t5_s0 in register *$t6*
lw	$t6, 32($sp)
li	$t3, 2
add	$t6, $t5, $t3

# Web ended: _t4_s0 in register *$t5*
sw	$t5, 88($sp)
# assign,number3_s1,_t5_s0,
# New web started: number3_s1 in register *$t5*
lw	$t5, 84($sp)
#*** copyto level: 0
#*** copyfrom level: 0
move	$t5, $t6

# Web ended: _t5_s0 in register *$t6*
sw	$t6, 32($sp)
# mul,1,1,_t6_s0
# New web started: _t6_s0 in register *$t6*
lw	$t6, 80($sp)
li	$t3, 1
li	$t2, 1
mul	$t6, $t3, $t2

# add,_t6_s0,2,_t7_s0
# New web started: _t7_s0 in register *$t4*
lw	$t4, 20($sp)
li	$t3, 2
add	$t4, $t6, $t3

# Web ended: _t6_s0 in register *$t6*
sw	$t6, 80($sp)
# add,_t7_s0,three_s1,_t8_s0
# New web started: _t8_s0 in register *$t6*
lw	$t6, 76($sp)
add	$t6, $t4, $t9

# Web ended: _t7_s0 in register *$t4*
sw	$t4, 20($sp)
# assign,number4_s1,_t8_s0,
# Did not get a register: number4_s1
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t3, 16($sp)
move	$t3, $t6
sw	$t3, 16($sp)

# Web ended: _t8_s0 in register *$t6*
sw	$t6, 76($sp)
# add,three_s1,three_s1,_t9_s0
# New web started: _t9_s0 in register *$t6*
lw	$t6, 8($sp)
add	$t6, $t9, $t9

# assign,number5_s1,_t9_s0,
# New web started: number5_s1 in register *$t4*
lw	$t4, 72($sp)
#*** copyto level: 0
#*** copyfrom level: 0
move	$t4, $t6

# Web ended: _t9_s0 in register *$t6*
sw	$t6, 8($sp)
# add,three_s1,three_s1,_t10_s0
# New web started: _t10_s0 in register *$t6*
lw	$t6, 24($sp)
add	$t6, $t9, $t9

# Web ended: three_s1 in register *$t9*
sw	$t9, 36($sp)
# assign,number5_s1,_t10_s0,
#*** copyto level: 0
#*** copyfrom level: 0
move	$t4, $t6

# Web ended: _t10_s0 in register *$t6*
sw	$t6, 24($sp)
# add,two_s1,two_s1,_t11_s0
# New web started: _t11_s0 in register *$t9*
lw	$t9, 100($sp)
add	$t9, $t8, $t8

# add,_t11_s0,two_s1,_t12_s0
# New web started: _t12_s0 in register *$t6*
lw	$t6, 48($sp)
add	$t6, $t9, $t8

# Web ended: _t11_s0 in register *$t9*
sw	$t9, 100($sp)
# assign,number5_s1,_t12_s0,
#*** copyto level: 0
#*** copyfrom level: 0
move	$t4, $t6

# Web ended: _t12_s0 in register *$t6*
sw	$t6, 48($sp)
# add,two_s1,two_s1,_t13_s0
# New web started: _t13_s0 in register *$t9*
lw	$t9, 96($sp)
add	$t9, $t8, $t8

# add,_t13_s0,two_s1,_t14_s0
# New web started: _t14_s0 in register *$t6*
lw	$t6, 44($sp)
add	$t6, $t9, $t8

# Web ended: two_s1 in register *$t8*
sw	$t8, 12($sp)
# Web ended: _t13_s0 in register *$t9*
sw	$t9, 96($sp)
# assign,number5_s1,_t14_s0,
#*** copyto level: 0
#*** copyfrom level: 0
move	$t4, $t6

# Web ended: _t14_s0 in register *$t6*
sw	$t6, 44($sp)
# assign,_t15_s0,1,
# New web started: _t15_s0 in register *$t9*
lw	$t9, 104($sp)
li	$t3, 1
move	$t9, $t3
# assign,_t16_s0,1,
# New web started: _t16_s0 in register *$t8*
lw	$t8, 52($sp)
li	$t3, 1
move	$t8, $t3
# loop_label_0:
loop_label_0:
# brgt,_t16_s0,3,loop_label_1
li	$t3, 3
bgt	$t8, $t3, loop_label_1
# mult,_t15_s0,2,_t17_s0
# New web started: _t17_s0 in register *$t6*
lw	$t6, 108($sp)
li	$t3, 2
mul	$t6, $t9, $t3

# assign,_t15_s0,_t17_s0,
#*** copyto level: 0
#*** copyfrom level: 0
move	$t9, $t6

# Web ended: _t17_s0 in register *$t6*
sw	$t6, 108($sp)
# add,_t16_s0,1,_t16_s0
li	$t3, 1
add	$t8, $t8, $t3

# goto,loop_label_0,,
j loop_label_0
# Web ended: _t16_s0 in register *$t8*
sw	$t8, 52($sp)
# loop_label_1:
loop_label_1:
# sub,_t15_s0,2,_t18_s0
# New web started: _t18_s0 in register *$t8*
lw	$t8, 56($sp)
li	$t3, 2
sub	$t8, $t9, $t3

# Web ended: _t15_s0 in register *$t9*
sw	$t9, 104($sp)
# assign,number6_s1,_t18_s0,
# New web started: number6_s1 in register *$t6*
lw	$t6, 4($sp)
#*** copyto level: 0
#*** copyfrom level: 0
move	$t6, $t8

# Web ended: _t18_s0 in register *$t8*
sw	$t8, 56($sp)
# add,number1_s1,number2_s1,_t19_s0
# New web started: _t19_s0 in register *$t8*
lw	$t8, 60($sp)
lw	$t3, 28($sp)
add	$t8, $t7, $t3
sw	$t3, 28($sp)

# Web ended: number1_s1 in register *$t7*
sw	$t7, 120($sp)
# add,_t19_s0,number3_s1,_t20_s0
# New web started: _t20_s0 in register *$t9*
lw	$t9, 64($sp)
add	$t9, $t8, $t5

# Web ended: number3_s1 in register *$t5*
sw	$t5, 84($sp)
# Web ended: _t19_s0 in register *$t8*
sw	$t8, 60($sp)
# add,_t20_s0,number4_s1,_t21_s0
# New web started: _t21_s0 in register *$t8*
lw	$t8, 112($sp)
lw	$t3, 16($sp)
add	$t8, $t9, $t3
sw	$t3, 16($sp)

# Web ended: _t20_s0 in register *$t9*
sw	$t9, 64($sp)
# add,_t21_s0,number5_s1,_t22_s0
# New web started: _t22_s0 in register *$t7*
lw	$t7, 68($sp)
add	$t7, $t8, $t4

# Web ended: number5_s1 in register *$t4*
sw	$t4, 72($sp)
# Web ended: _t21_s0 in register *$t8*
sw	$t8, 112($sp)
# add,_t22_s0,number6_s1,_t23_s0
# New web started: _t23_s0 in register *$t9*
lw	$t9, 124($sp)
add	$t9, $t7, $t6

# Web ended: number6_s1 in register *$t6*
sw	$t6, 4($sp)
# Web ended: _t22_s0 in register *$t7*
sw	$t7, 68($sp)
# call,printi,_t23_s0
move	$a0, $t9
sw	$t9, 124($sp)
jal	printi
lw	$t9, 124($sp)
# Web ended: _t23_s0 in register *$t9*
sw	$t9, 124($sp)
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

