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
.data
_s0_number6_s1:	.word	0
_s0__t9_s0:	.word	0
_s0_two_s1:	.word	0
_s0_number4_s1:	.word	0
_s0__t7_s0:	.word	0
_s0__t10_s0:	.word	0
_s0_number2_s1:	.word	0
_s0__t5_s0:	.word	0
_s0_three_s1:	.word	0
_s0__t3_s0:	.word	0
_s0__t14_s0:	.word	0
_s0__t12_s0:	.word	0
_s0__t16_s0:	.word	0
_s0__t18_s0:	.word	0
_s0__t19_s0:	.word	0
_s0__t20_s0:	.word	0
_s0__t22_s0:	.word	0
_s0_number5_s1:	.word	0
_s0__t8_s0:	.word	0
_s0__t6_s0:	.word	0
_s0_number3_s1:	.word	0
_s0__t4_s0:	.word	0
_s0__t2_s0:	.word	0
_s0__t13_s0:	.word	0
_s0__t11_s0:	.word	0
_s0__t15_s0:	.word	0
_s0__t17_s0:	.word	0
_s0__t21_s0:	.word	0
_s0__t1_s0:	.word	0
_s0_number1_s1:	.word	0
_s0__t23_s0:	.word	0
_s0_savera:	.word	0
.text
sw	$ra, _s0_savera
# assign,two_s1,2,
lw	$t9, _s0_two_s1
li	$t8, 2
move	$t9, $t8
sw	$t9, _s0_two_s1

# assign,three_s1,3,
lw	$t8, _s0_three_s1
li	$t9, 3
move	$t8, $t9
sw	$t8, _s0_three_s1

# main:

# mul,two_s1,three_s1,_t1_s0
lw	$t9, _s0__t1_s0
lw	$t8, _s0_two_s1
lw	$t7, _s0_three_s1
mul	$t9, $t8, $t7
sw	$t9, _s0__t1_s0
sw	$t8, _s0_two_s1
sw	$t7, _s0_three_s1


# call,printi,_t1_s0
lw	$t7, _s0__t1_s0
lw	$t7, _s0__t1_s0
move	$a0, $t7
sw	$t7, _s0__t1_s0
jal	printi

# add,three_s1,three_s1,_t2_s0
lw	$t7, _s0__t2_s0
lw	$t8, _s0_three_s1
add	$t7, $t8, $t8
sw	$t7, _s0__t2_s0
sw	$t8, _s0_three_s1


# assign,number1_s1,_t2_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t8, _s0_number1_s1
lw	$t7, _s0__t2_s0
move	$t8, $t7
sw	$t8, _s0_number1_s1
sw	$t7, _s0__t2_s0


# mul,2,three_s1,_t3_s0
li	$t7, 2
lw	$t8, _s0__t3_s0
lw	$t9, _s0_three_s1
mul	$t8, $t7, $t9
sw	$t8, _s0__t3_s0
sw	$t9, _s0_three_s1


# assign,number2_s1,_t3_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s0_number2_s1
lw	$t8, _s0__t3_s0
move	$t9, $t8
sw	$t9, _s0_number2_s1
sw	$t8, _s0__t3_s0


# add,2,2,_t4_s0
li	$t8, 2
li	$t9, 2
add	$t7, $t8, $t9
sw	$t7, _s0__t4_s0


# add,_t4_s0,2,_t5_s0
li	$t8, 2
lw	$t9, _s0__t5_s0
lw	$t6, _s0__t4_s0
add	$t9, $t6, $t8
sw	$t9, _s0__t5_s0
sw	$t6, _s0__t4_s0


# assign,number3_s1,_t5_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t6, _s0_number3_s1
lw	$t9, _s0__t5_s0
move	$t6, $t9
sw	$t6, _s0_number3_s1
sw	$t9, _s0__t5_s0


# mul,1,1,_t6_s0
li	$t9, 1
li	$t6, 1
mul	$t8, $t9, $t6
sw	$t8, _s0__t6_s0


# add,_t6_s0,2,_t7_s0
li	$t9, 2
lw	$t6, _s0__t7_s0
lw	$t5, _s0__t6_s0
add	$t6, $t5, $t9
sw	$t6, _s0__t7_s0
sw	$t5, _s0__t6_s0


# add,_t7_s0,three_s1,_t8_s0
lw	$t5, _s0__t8_s0
lw	$t6, _s0__t7_s0
lw	$t9, _s0_three_s1
add	$t5, $t6, $t9
sw	$t5, _s0__t8_s0
sw	$t6, _s0__t7_s0
sw	$t9, _s0_three_s1


# assign,number4_s1,_t8_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s0_number4_s1
lw	$t6, _s0__t8_s0
move	$t9, $t6
sw	$t9, _s0_number4_s1
sw	$t6, _s0__t8_s0


# add,three_s1,three_s1,_t9_s0
lw	$t6, _s0__t9_s0
lw	$t9, _s0_three_s1
add	$t6, $t9, $t9
sw	$t6, _s0__t9_s0
sw	$t9, _s0_three_s1


# assign,number5_s1,_t9_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s0_number5_s1
lw	$t6, _s0__t9_s0
move	$t9, $t6
sw	$t9, _s0_number5_s1
sw	$t6, _s0__t9_s0


# add,three_s1,three_s1,_t10_s0
lw	$t6, _s0__t10_s0
lw	$t9, _s0_three_s1
add	$t6, $t9, $t9
sw	$t6, _s0__t10_s0
sw	$t9, _s0_three_s1


# assign,number5_s1,_t10_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s0_number5_s1
lw	$t6, _s0__t10_s0
move	$t9, $t6
sw	$t9, _s0_number5_s1
sw	$t6, _s0__t10_s0


# add,two_s1,two_s1,_t11_s0
lw	$t6, _s0__t11_s0
lw	$t9, _s0_two_s1
add	$t6, $t9, $t9
sw	$t6, _s0__t11_s0
sw	$t9, _s0_two_s1


# add,_t11_s0,two_s1,_t12_s0
lw	$t9, _s0__t12_s0
lw	$t6, _s0__t11_s0
lw	$t5, _s0_two_s1
add	$t9, $t6, $t5
sw	$t9, _s0__t12_s0
sw	$t6, _s0__t11_s0
sw	$t5, _s0_two_s1


# assign,number5_s1,_t12_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t5, _s0_number5_s1
lw	$t6, _s0__t12_s0
move	$t5, $t6
sw	$t5, _s0_number5_s1
sw	$t6, _s0__t12_s0


# add,two_s1,two_s1,_t13_s0
lw	$t6, _s0__t13_s0
lw	$t5, _s0_two_s1
add	$t6, $t5, $t5
sw	$t6, _s0__t13_s0
sw	$t5, _s0_two_s1


# add,_t13_s0,two_s1,_t14_s0
lw	$t5, _s0__t14_s0
lw	$t6, _s0__t13_s0
lw	$t9, _s0_two_s1
add	$t5, $t6, $t9
sw	$t5, _s0__t14_s0
sw	$t6, _s0__t13_s0
sw	$t9, _s0_two_s1


# assign,number5_s1,_t14_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s0_number5_s1
lw	$t6, _s0__t14_s0
move	$t9, $t6
sw	$t9, _s0_number5_s1
sw	$t6, _s0__t14_s0


# assign,_t15_s0,1,
lw	$t6, _s0__t15_s0
li	$t9, 1
move	$t6, $t9
sw	$t6, _s0__t15_s0

# assign,_t16_s0,1,
lw	$t9, _s0__t16_s0
li	$t6, 1
move	$t9, $t6
sw	$t9, _s0__t16_s0

# loop_label_0:
loop_label_0:

# brgt,_t16_s0,3,loop_label_1
lw	$t6, _s0__t16_s0
li	$t9, 3
bgt	$t6, $t9, loop_label_1
sw	$t6, _s0__t16_s0

# mult,_t15_s0,2,_t17_s0
li	$t9, 2
lw	$t6, _s0__t17_s0
lw	$t5, _s0__t15_s0
mul	$t6, $t5, $t9
sw	$t6, _s0__t17_s0
sw	$t5, _s0__t15_s0


# assign,_t15_s0,_t17_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t5, _s0__t15_s0
lw	$t6, _s0__t17_s0
move	$t5, $t6
sw	$t5, _s0__t15_s0
sw	$t6, _s0__t17_s0


# add,_t16_s0,1,_t16_s0
li	$t6, 1
lw	$t5, _s0__t16_s0
add	$t5, $t5, $t6
sw	$t5, _s0__t16_s0


# goto,loop_label_0,,
j loop_label_0

# loop_label_1:
loop_label_1:

# sub,_t15_s0,2,_t18_s0
li	$t5, 2
lw	$t6, _s0__t18_s0
lw	$t9, _s0__t15_s0
sub	$t6, $t9, $t5
sw	$t6, _s0__t18_s0
sw	$t9, _s0__t15_s0


# assign,number6_s1,_t18_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s0_number6_s1
lw	$t6, _s0__t18_s0
move	$t9, $t6
sw	$t9, _s0_number6_s1
sw	$t6, _s0__t18_s0


# add,number1_s1,number2_s1,_t19_s0
lw	$t6, _s0__t19_s0
lw	$t9, _s0_number1_s1
lw	$t5, _s0_number2_s1
add	$t6, $t9, $t5
sw	$t6, _s0__t19_s0
sw	$t9, _s0_number1_s1
sw	$t5, _s0_number2_s1


# add,_t19_s0,number3_s1,_t20_s0
lw	$t5, _s0__t20_s0
lw	$t9, _s0__t19_s0
lw	$t6, _s0_number3_s1
add	$t5, $t9, $t6
sw	$t5, _s0__t20_s0
sw	$t9, _s0__t19_s0
sw	$t6, _s0_number3_s1


# add,_t20_s0,number4_s1,_t21_s0
lw	$t6, _s0__t21_s0
lw	$t9, _s0__t20_s0
lw	$t5, _s0_number4_s1
add	$t6, $t9, $t5
sw	$t6, _s0__t21_s0
sw	$t9, _s0__t20_s0
sw	$t5, _s0_number4_s1


# add,_t21_s0,number5_s1,_t22_s0
lw	$t5, _s0__t22_s0
lw	$t9, _s0__t21_s0
lw	$t6, _s0_number5_s1
add	$t5, $t9, $t6
sw	$t5, _s0__t22_s0
sw	$t9, _s0__t21_s0
sw	$t6, _s0_number5_s1


# add,_t22_s0,number6_s1,_t23_s0
lw	$t6, _s0__t23_s0
lw	$t9, _s0__t22_s0
lw	$t5, _s0_number6_s1
add	$t6, $t9, $t5
sw	$t6, _s0__t23_s0
sw	$t9, _s0__t22_s0
sw	$t5, _s0_number6_s1


# call,printi,_t23_s0
lw	$t5, _s0__t23_s0
lw	$t5, _s0__t23_s0
move	$a0, $t5
sw	$t5, _s0__t23_s0
jal	printi

# call,printi,36
li	$a0, 36
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

