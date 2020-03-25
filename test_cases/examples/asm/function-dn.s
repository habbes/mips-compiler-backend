#subtractInt: _t1_s0: 4
#subtractInt: first_s2: 8
#subtractInt: second_s2: 12
#addInt: first_s3: 4
#addInt: _t2_s0: 8
#addInt: second_s3: 12
#multiply: a_s4: 4
#multiply: b_s4: 8
#multiply: _t3_s0: 12
#isFive: _t4_s0: 4
#isFive: number_s5: 8
#main: difference_s1: 4
#main: _t8_s0: 8
#main: _t6_s0: 12
#main: _t9_s0: 16
#main: two_s1: 20
#main: _t7_s0: 24
#main: _t10_s0: 28
#main: _t5_s0: 32
#main: _t13_s0: 36
#main: _t14_s0: 40
#main: _t12_s0: 44
#main: result_s1: 48
#main: _t11_s0: 52
#main: _t16_s0: 56
#main: _t15_s0: 60
#main: one_s1: 64
#main: sum_s1: 68
.data
dregisters:	.space	64
sp_temp:	.word	0
.text
.globl main

######## subtractInt
_s0_subtractInt:
.data
_s0__t1_s0:	.word	0
_s0_first_s2:	.word	0
_s0_second_s2:	.word	0
_s0_savera:	.word	0
.text
sw	$ra, _s0_savera
sw	$a0, _s0_first_s2
sw	$a1, _s0_second_s2
# sub,first_s2,second_s2,_t1_s0
lw	$t9, _s0__t1_s0
lw	$t8, _s0_first_s2
lw	$t7, _s0_second_s2
sub	$t9, $t8, $t7
sw	$t9, _s0__t1_s0
sw	$t8, _s0_first_s2
sw	$t7, _s0_second_s2


# return,_t1_s0,,
lw	$t7, _s0__t1_s0
move	$v0, $t7
sw	$t7, _s0__t1_s0
lw	$ra, _s0_savera
jr	$ra

lw	$ra, _s0_savera
jr	$ra

######## addInt
_s1_addInt:
.data
_s1_first_s3:	.word	0
_s1__t2_s0:	.word	0
_s1_second_s3:	.word	0
_s1_savera:	.word	0
.text
sw	$ra, _s1_savera
sw	$a0, _s1_first_s3
sw	$a1, _s1_second_s3
# add,first_s3,second_s3,_t2_s0
lw	$t7, _s1__t2_s0
lw	$t8, _s1_first_s3
lw	$t9, _s1_second_s3
add	$t7, $t8, $t9
sw	$t7, _s1__t2_s0
sw	$t8, _s1_first_s3
sw	$t9, _s1_second_s3


# return,_t2_s0,,
lw	$t9, _s1__t2_s0
move	$v0, $t9
sw	$t9, _s1__t2_s0
lw	$ra, _s1_savera
jr	$ra

lw	$ra, _s1_savera
jr	$ra

######## multiply
_s2_multiply:
.data
_s2_a_s4:	.word	0
_s2_b_s4:	.word	0
_s2__t3_s0:	.word	0
_s2_savera:	.word	0
.text
sw	$ra, _s2_savera
sw	$a0, _s2_a_s4
sw	$a1, _s2_b_s4
# assign,a_s4,0,
lw	$t9, _s2_a_s4
li	$t8, 0
move	$t9, $t8
sw	$t9, _s2_a_s4

# loop_label_0:
loop_label_0:

# brgt,a_s4,5,loop_label_1
lw	$t8, _s2_a_s4
li	$t9, 5
bgt	$t8, $t9, loop_label_1
sw	$t8, _s2_a_s4

# call,printi,a_s4
lw	$t9, _s2_a_s4
lw	$t9, _s2_a_s4
move	$a0, $t9
sw	$t9, _s2_a_s4
jal	printi

# add,a_s4,1,a_s4
li	$t9, 1
lw	$t8, _s2_a_s4
add	$t8, $t8, $t9
sw	$t8, _s2_a_s4


# goto,loop_label_0,,
j loop_label_0

# loop_label_1:
loop_label_1:

# mul,a_s4,b_s4,_t3_s0
lw	$t8, _s2__t3_s0
lw	$t9, _s2_a_s4
lw	$t7, _s2_b_s4
mul	$t8, $t9, $t7
sw	$t8, _s2__t3_s0
sw	$t9, _s2_a_s4
sw	$t7, _s2_b_s4


# return,_t3_s0,,
lw	$t7, _s2__t3_s0
move	$v0, $t7
sw	$t7, _s2__t3_s0
lw	$ra, _s2_savera
jr	$ra

lw	$ra, _s2_savera
jr	$ra

######## isFive
_s3_isFive:
.data
_s3__t4_s0:	.word	0
_s3_number_s5:	.word	0
_s3_savera:	.word	0
.text
sw	$ra, _s3_savera
sw	$a0, _s3_number_s5
# assign,_t4_s0,0,
lw	$t7, _s3__t4_s0
li	$t9, 0
move	$t7, $t9
sw	$t7, _s3__t4_s0

# brneq,number_s5,5,if_label_2
lw	$t9, _s3_number_s5
li	$t7, 5
bne	$t9, $t7, if_label_2
sw	$t9, _s3_number_s5

# assign,_t4_s0,1,
lw	$t7, _s3__t4_s0
li	$t9, 1
move	$t7, $t9
sw	$t7, _s3__t4_s0

# if_label_2:
if_label_2:

# brneq,_t4_s0,1,if_label_3
lw	$t9, _s3__t4_s0
li	$t7, 1
bne	$t9, $t7, if_label_3
sw	$t9, _s3__t4_s0

# assign,number_s5,5,
lw	$t7, _s3_number_s5
li	$t9, 5
move	$t7, $t9
sw	$t7, _s3_number_s5

# goto,if_label_4,,
j if_label_4

# if_label_3:
if_label_3:

# assign,number_s5,6,
lw	$t9, _s3_number_s5
li	$t7, 6
move	$t9, $t7
sw	$t9, _s3_number_s5

# if_label_4:
if_label_4:

# return,number_s5,,
lw	$t7, _s3_number_s5
move	$v0, $t7
sw	$t7, _s3_number_s5
lw	$ra, _s3_savera
jr	$ra

lw	$ra, _s3_savera
jr	$ra

######## main
_s4_main:
.data
_s4_difference_s1:	.word	0
_s4__t8_s0:	.word	0
_s4__t6_s0:	.word	0
_s4__t9_s0:	.word	0
_s4_two_s1:	.word	0
_s4__t7_s0:	.word	0
_s4__t10_s0:	.word	0
_s4__t5_s0:	.word	0
_s4__t13_s0:	.word	0
_s4__t14_s0:	.word	0
_s4__t12_s0:	.word	0
_s4_result_s1:	.word	0
_s4__t11_s0:	.word	0
_s4__t16_s0:	.word	0
_s4__t15_s0:	.word	0
_s4_one_s1:	.word	0
_s4_sum_s1:	.word	0
_s4_savera:	.word	0
.text
sw	$ra, _s4_savera
# main:

# callr,_t5_s0,subtractInt,4,3
li	$a0, 4
li	$a1, 3
jal	_s0_subtractInt
lw	$t7, _s4__t5_s0
move	$t7, $v0
sw	$t7, _s4__t5_s0

# assign,difference_s1,_t5_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t7, _s4_difference_s1
lw	$t9, _s4__t5_s0
move	$t7, $t9
sw	$t7, _s4_difference_s1
sw	$t9, _s4__t5_s0


# call,printi,1
li	$a0, 1
jal	printi

# call,printi,difference_s1
lw	$t9, _s4_difference_s1
lw	$t9, _s4_difference_s1
move	$a0, $t9
sw	$t9, _s4_difference_s1
jal	printi

# callr,_t6_s0,addInt,4,3
li	$a0, 4
li	$a1, 3
jal	_s1_addInt
lw	$t9, _s4__t6_s0
move	$t9, $v0
sw	$t9, _s4__t6_s0

# assign,sum_s1,_t6_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s4_sum_s1
lw	$t7, _s4__t6_s0
move	$t9, $t7
sw	$t9, _s4_sum_s1
sw	$t7, _s4__t6_s0


# call,printi,7
li	$a0, 7
jal	printi

# call,printi,sum_s1
lw	$t7, _s4_sum_s1
lw	$t7, _s4_sum_s1
move	$a0, $t7
sw	$t7, _s4_sum_s1
jal	printi

# call,printi,6
li	$a0, 6
jal	printi

# mul,2,3,_t7_s0
li	$t7, 2
li	$t9, 3
mul	$t8, $t7, $t9
sw	$t8, _s4__t7_s0


# call,printi,_t7_s0
lw	$t7, _s4__t7_s0
lw	$t7, _s4__t7_s0
move	$a0, $t7
sw	$t7, _s4__t7_s0
jal	printi

# callr,_t8_s0,multiply,4,4
li	$a0, 4
li	$a1, 4
jal	_s2_multiply
lw	$t7, _s4__t8_s0
move	$t7, $v0
sw	$t7, _s4__t8_s0

# assign,sum_s1,_t8_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t7, _s4_sum_s1
lw	$t9, _s4__t8_s0
move	$t7, $t9
sw	$t7, _s4_sum_s1
sw	$t9, _s4__t8_s0


# call,printi,24
li	$a0, 24
jal	printi

# call,printi,sum_s1
lw	$t9, _s4_sum_s1
lw	$t9, _s4_sum_s1
move	$a0, $t9
sw	$t9, _s4_sum_s1
jal	printi

# callr,_t9_s0,isFive,5
li	$a0, 5
jal	_s3_isFive
lw	$t9, _s4__t9_s0
move	$t9, $v0
sw	$t9, _s4__t9_s0

# assign,result_s1,_t9_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s4_result_s1
lw	$t7, _s4__t9_s0
move	$t9, $t7
sw	$t9, _s4_result_s1
sw	$t7, _s4__t9_s0


# call,printi,5
li	$a0, 5
jal	printi

# call,printi,result_s1
lw	$t7, _s4_result_s1
lw	$t7, _s4_result_s1
move	$a0, $t7
sw	$t7, _s4_result_s1
jal	printi

# callr,_t10_s0,isFive,3
li	$a0, 3
jal	_s3_isFive
lw	$t7, _s4__t10_s0
move	$t7, $v0
sw	$t7, _s4__t10_s0

# assign,result_s1,_t10_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t7, _s4_result_s1
lw	$t9, _s4__t10_s0
move	$t7, $t9
sw	$t7, _s4_result_s1
sw	$t9, _s4__t10_s0


# call,printi,6
li	$a0, 6
jal	printi

# call,printi,result_s1
lw	$t9, _s4_result_s1
lw	$t9, _s4_result_s1
move	$a0, $t9
sw	$t9, _s4_result_s1
jal	printi

# assign,one_s1,1,
lw	$t9, _s4_one_s1
li	$t7, 1
move	$t9, $t7
sw	$t9, _s4_one_s1

# assign,two_s1,2,
lw	$t7, _s4_two_s1
li	$t9, 2
move	$t7, $t9
sw	$t7, _s4_two_s1

# callr,_t11_s0,addInt,one_s1,two_s1
lw	$t9, _s4_one_s1
move	$a0, $t9
sw	$t9, _s4_one_s1
lw	$t9, _s4_two_s1
move	$a1, $t9
sw	$t9, _s4_two_s1
jal	_s1_addInt
lw	$t9, _s4__t11_s0
move	$t9, $v0
sw	$t9, _s4__t11_s0

# assign,result_s1,_t11_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s4_result_s1
lw	$t7, _s4__t11_s0
move	$t9, $t7
sw	$t9, _s4_result_s1
sw	$t7, _s4__t11_s0


# call,printi,3
li	$a0, 3
jal	printi

# call,printi,result_s1
lw	$t7, _s4_result_s1
lw	$t7, _s4_result_s1
move	$a0, $t7
sw	$t7, _s4_result_s1
jal	printi

# add,difference_s1,sum_s1,_t13_s0
lw	$t7, _s4__t13_s0
lw	$t9, _s4_difference_s1
lw	$t6, _s4_sum_s1
add	$t7, $t9, $t6
sw	$t7, _s4__t13_s0
sw	$t9, _s4_difference_s1
sw	$t6, _s4_sum_s1


# add,_t13_s0,result_s1,_t14_s0
lw	$t6, _s4__t14_s0
lw	$t9, _s4__t13_s0
lw	$t7, _s4_result_s1
add	$t6, $t9, $t7
sw	$t6, _s4__t14_s0
sw	$t9, _s4__t13_s0
sw	$t7, _s4_result_s1


# add,1,24,_t15_s0
li	$t7, 1
li	$t9, 24
add	$t6, $t7, $t9
sw	$t6, _s4__t15_s0


# add,_t15_s0,3,_t16_s0
li	$t7, 3
lw	$t9, _s4__t16_s0
lw	$t5, _s4__t15_s0
add	$t9, $t5, $t7
sw	$t9, _s4__t16_s0
sw	$t5, _s4__t15_s0


# assign,_t12_s0,0,
lw	$t5, _s4__t12_s0
li	$t9, 0
move	$t5, $t9
sw	$t5, _s4__t12_s0

# brneq,_t14_s0,_t16_s0,if_label_5
lw	$t9, _s4__t14_s0
lw	$t5, _s4__t16_s0
bne	$t9, $t5, if_label_5
sw	$t9, _s4__t14_s0
sw	$t5, _s4__t16_s0

# assign,_t12_s0,1,
lw	$t5, _s4__t12_s0
li	$t9, 1
move	$t5, $t9
sw	$t5, _s4__t12_s0

# if_label_5:
if_label_5:

# call,printi,_t12_s0
lw	$t9, _s4__t12_s0
lw	$t9, _s4__t12_s0
move	$a0, $t9
sw	$t9, _s4__t12_s0
jal	printi

# return,,,

lw	$ra, _s4_savera
jr	$ra
######## main
main:
jal	_s4_main
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

