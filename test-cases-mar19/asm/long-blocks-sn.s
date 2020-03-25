#main: _t8_s0: 4
#main: _t6_s0: 8
#main: _t9_s0: 12
#main: two_s1: 16
#main: number_s1: 20
#main: _t7_s0: 24
#main: _t10_s0: 28
#main: _t5_s0: 32
#main: _t4_s0: 36
#main: six_s1: 40
#main: three_s1: 44
#main: _t2_s0: 48
#main: _t13_s0: 52
#main: _t3_s0: 56
#main: _t14_s0: 60
#main: _t12_s0: 64
#main: _t11_s0: 68
#main: _t16_s0: 72
#main: _t15_s0: 76
#main: _t17_s0: 80
#main: _t18_s0: 84
#main: _t19_s0: 88
#main: one_s1: 92
#main: _t1_s0: 96
.data
dregisters:	.space	64
sp_temp:	.word	0
.text
.globl main

######## main
_s0_main:
.text
sw	$ra, 0($sp)
addiu	$sp, $sp, -100	# Move stack pointer to accommodate variables in this function.
la	$s0, dregisters		# Load address of dregisters in $s0
sw	$sp, 0($s0)			# Move stack pointer to 4*function level in dregisters ($s0 is address of dregisters).
# assign,one_s1,1,
lw	$t9, 92($sp)
li	$t8, 1
move	$t9, $t8
sw	$t9, 92($sp)

# assign,two_s1,2,
lw	$t8, 16($sp)
li	$t9, 2
move	$t8, $t9
sw	$t8, 16($sp)

# assign,three_s1,3,
lw	$t9, 44($sp)
li	$t8, 3
move	$t9, $t8
sw	$t9, 44($sp)

# assign,six_s1,6,
lw	$t8, 40($sp)
li	$t9, 6
move	$t8, $t9
sw	$t8, 40($sp)

# assign,number_s1,0,
lw	$t9, 20($sp)
li	$t8, 0
move	$t9, $t8
sw	$t9, 20($sp)

# main:

# assign,number_s1,1,
lw	$t8, 20($sp)
li	$t9, 1
move	$t8, $t9
sw	$t8, 20($sp)

# loop_label_0:
loop_label_0:

# brgt,number_s1,2,loop_label_1
lw	$t9, 20($sp)
li	$t8, 2
bgt	$t9, $t8, loop_label_1
sw	$t9, 20($sp)

# assign,_t1_s0,0,
lw	$t8, 96($sp)
li	$t9, 0
move	$t8, $t9
sw	$t8, 96($sp)

# brneq,number_s1,1,if_label_2
lw	$t9, 20($sp)
li	$t8, 1
bne	$t9, $t8, if_label_2
sw	$t9, 20($sp)

# assign,_t1_s0,1,
lw	$t8, 96($sp)
li	$t9, 1
move	$t8, $t9
sw	$t8, 96($sp)

# if_label_2:
if_label_2:

# brneq,_t1_s0,1,if_label_3
lw	$t9, 96($sp)
li	$t8, 1
bne	$t9, $t8, if_label_3
sw	$t9, 96($sp)

# mul,two_s1,three_s1,_t2_s0
lw	$t8, 48($sp)
lw	$t9, 16($sp)
lw	$t7, 44($sp)
mul	$t8, $t9, $t7
sw	$t8, 48($sp)
sw	$t9, 16($sp)
sw	$t7, 44($sp)


# assign,six_s1,_t2_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t7, 40($sp)
lw	$t9, 48($sp)
move	$t7, $t9
sw	$t7, 40($sp)
sw	$t9, 48($sp)


# add,three_s1,three_s1,_t3_s0
lw	$t9, 56($sp)
lw	$t7, 44($sp)
add	$t9, $t7, $t7
sw	$t9, 56($sp)
sw	$t7, 44($sp)


# assign,six_s1,_t3_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t7, 40($sp)
lw	$t9, 56($sp)
move	$t7, $t9
sw	$t7, 40($sp)
sw	$t9, 56($sp)


# assign,_t4_s0,1,
lw	$t9, 36($sp)
li	$t7, 1
move	$t9, $t7
sw	$t9, 36($sp)

# assign,_t5_s0,1,
lw	$t7, 32($sp)
li	$t9, 1
move	$t7, $t9
sw	$t7, 32($sp)

# loop_label_5:
loop_label_5:

# brgt,_t5_s0,three_s1,loop_label_6
lw	$t9, 32($sp)
lw	$t7, 44($sp)
bgt	$t9, $t7, loop_label_6
sw	$t9, 32($sp)
sw	$t7, 44($sp)

# mult,_t4_s0,two_s1,_t6_s0
lw	$t7, 8($sp)
lw	$t9, 36($sp)
lw	$t8, 16($sp)
mul	$t7, $t9, $t8
sw	$t7, 8($sp)
sw	$t9, 36($sp)
sw	$t8, 16($sp)


# assign,_t4_s0,_t6_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t8, 36($sp)
lw	$t9, 8($sp)
move	$t8, $t9
sw	$t8, 36($sp)
sw	$t9, 8($sp)


# add,_t5_s0,1,_t5_s0
li	$t9, 1
lw	$t8, 32($sp)
add	$t8, $t8, $t9
sw	$t8, 32($sp)


# goto,loop_label_5,,
j loop_label_5

# loop_label_6:
loop_label_6:

# sub,_t4_s0,two_s1,_t7_s0
lw	$t8, 24($sp)
lw	$t9, 36($sp)
lw	$t7, 16($sp)
sub	$t8, $t9, $t7
sw	$t8, 24($sp)
sw	$t9, 36($sp)
sw	$t7, 16($sp)


# assign,six_s1,_t7_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t7, 40($sp)
lw	$t9, 24($sp)
move	$t7, $t9
sw	$t7, 40($sp)
sw	$t9, 24($sp)


# assign,six_s1,six_s1,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, 40($sp)
move	$t9, $t9
sw	$t9, 40($sp)


# mul,two_s1,two_s1,_t8_s0
lw	$t9, 4($sp)
lw	$t7, 16($sp)
mul	$t9, $t7, $t7
sw	$t9, 4($sp)
sw	$t7, 16($sp)


# mul,_t8_s0,three_s1,_t9_s0
lw	$t7, 12($sp)
lw	$t9, 4($sp)
lw	$t8, 44($sp)
mul	$t7, $t9, $t8
sw	$t7, 12($sp)
sw	$t9, 4($sp)
sw	$t8, 44($sp)


# div,_t9_s0,two_s1,_t10_s0
lw	$t8, 28($sp)
lw	$t9, 12($sp)
lw	$t7, 16($sp)
div	$t8, $t9, $t7
sw	$t8, 28($sp)
sw	$t9, 12($sp)
sw	$t7, 16($sp)


# assign,six_s1,_t10_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t7, 40($sp)
lw	$t9, 28($sp)
move	$t7, $t9
sw	$t7, 40($sp)
sw	$t9, 28($sp)


# goto,if_label_4,,
j if_label_4

# if_label_3:
if_label_3:

# mul,two_s1,three_s1,_t11_s0
lw	$t9, 68($sp)
lw	$t7, 16($sp)
lw	$t8, 44($sp)
mul	$t9, $t7, $t8
sw	$t9, 68($sp)
sw	$t7, 16($sp)
sw	$t8, 44($sp)


# assign,six_s1,_t11_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t8, 40($sp)
lw	$t7, 68($sp)
move	$t8, $t7
sw	$t8, 40($sp)
sw	$t7, 68($sp)


# add,three_s1,three_s1,_t12_s0
lw	$t7, 64($sp)
lw	$t8, 44($sp)
add	$t7, $t8, $t8
sw	$t7, 64($sp)
sw	$t8, 44($sp)


# assign,six_s1,_t12_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t8, 40($sp)
lw	$t7, 64($sp)
move	$t8, $t7
sw	$t8, 40($sp)
sw	$t7, 64($sp)


# assign,_t13_s0,1,
lw	$t7, 52($sp)
li	$t8, 1
move	$t7, $t8
sw	$t7, 52($sp)

# assign,_t14_s0,1,
lw	$t8, 60($sp)
li	$t7, 1
move	$t8, $t7
sw	$t8, 60($sp)

# loop_label_7:
loop_label_7:

# brgt,_t14_s0,three_s1,loop_label_8
lw	$t7, 60($sp)
lw	$t8, 44($sp)
bgt	$t7, $t8, loop_label_8
sw	$t7, 60($sp)
sw	$t8, 44($sp)

# mult,_t13_s0,two_s1,_t15_s0
lw	$t8, 76($sp)
lw	$t7, 52($sp)
lw	$t9, 16($sp)
mul	$t8, $t7, $t9
sw	$t8, 76($sp)
sw	$t7, 52($sp)
sw	$t9, 16($sp)


# assign,_t13_s0,_t15_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, 52($sp)
lw	$t7, 76($sp)
move	$t9, $t7
sw	$t9, 52($sp)
sw	$t7, 76($sp)


# add,_t14_s0,1,_t14_s0
li	$t7, 1
lw	$t9, 60($sp)
add	$t9, $t9, $t7
sw	$t9, 60($sp)


# goto,loop_label_7,,
j loop_label_7

# loop_label_8:
loop_label_8:

# sub,_t13_s0,two_s1,_t16_s0
lw	$t9, 72($sp)
lw	$t7, 52($sp)
lw	$t8, 16($sp)
sub	$t9, $t7, $t8
sw	$t9, 72($sp)
sw	$t7, 52($sp)
sw	$t8, 16($sp)


# assign,six_s1,_t16_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t8, 40($sp)
lw	$t7, 72($sp)
move	$t8, $t7
sw	$t8, 40($sp)
sw	$t7, 72($sp)


# assign,six_s1,six_s1,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t7, 40($sp)
move	$t7, $t7
sw	$t7, 40($sp)


# mul,two_s1,two_s1,_t17_s0
lw	$t7, 80($sp)
lw	$t8, 16($sp)
mul	$t7, $t8, $t8
sw	$t7, 80($sp)
sw	$t8, 16($sp)


# mul,_t17_s0,three_s1,_t18_s0
lw	$t8, 84($sp)
lw	$t7, 80($sp)
lw	$t9, 44($sp)
mul	$t8, $t7, $t9
sw	$t8, 84($sp)
sw	$t7, 80($sp)
sw	$t9, 44($sp)


# div,_t18_s0,two_s1,_t19_s0
lw	$t9, 88($sp)
lw	$t7, 84($sp)
lw	$t8, 16($sp)
div	$t9, $t7, $t8
sw	$t9, 88($sp)
sw	$t7, 84($sp)
sw	$t8, 16($sp)


# assign,six_s1,_t19_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t8, 40($sp)
lw	$t7, 88($sp)
move	$t8, $t7
sw	$t8, 40($sp)
sw	$t7, 88($sp)


# if_label_4:
if_label_4:

# add,number_s1,1,number_s1
li	$t7, 1
lw	$t8, 20($sp)
add	$t8, $t8, $t7
sw	$t8, 20($sp)


# goto,loop_label_0,,
j loop_label_0

# loop_label_1:
loop_label_1:

# call,printi,six_s1
lw	$t8, 40($sp)
move	$a0, $t8
sw	$t8, 40($sp)
jal	printi

# return,,,

addiu	$sp, $sp, 100
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

