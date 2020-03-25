#main: one_s1: 4
#main: _t10_s0: 8
#main: _t13_s0: 12
#main: zero_s1: 16
#main: _t14_s0: 20
#main: _t12_s0: 24
#main: _t11_s0: 28
#main: _t15_s0: 32
.data
dregisters:	.space	64
sp_temp:	.word	0
.text
.globl main

######## return88
_s0_return88:
.data
_s0_savera:	.word	0
.text
sw	$ra, _s0_savera
# return,88.0,,
li.s	$f0, 88.0
lw	$ra, _s0_savera
jr	$ra

lw	$ra, _s0_savera
jr	$ra

######## returnf
_s1_returnf:
.data
_s1_f_s3:	.float	0.0
_s1_savera:	.word	0
.text
sw	$ra, _s1_savera
s.s	$f14, _s1_f_s3
# return,f_s3,,
l.s	$f4, _s1_f_s3
mov.s	$f0, $f4
s.s	$f4, _s1_f_s3
lw	$ra, _s1_savera
jr	$ra

lw	$ra, _s1_savera
jr	$ra

######## main
_s2_main:
.data
_s2__t8_s0:	.float	0.0
_s2__t6_s0:	.float	0.0
_s2__t9_s0:	.float	0.0
_s2_two_s1:	.float	0.0
_s2_number_s1:	.float	0.0
_s2__t7_s0:	.float	0.0
_s2__t5_s0:	.float	0.0
_s2__t4_s0:	.float	0.0
_s2_six_s1:	.float	0.0
_s2__t2_s0:	.float	0.0
_s2__t3_s0:	.float	0.0
_s2__t16_s0:	.float	0.0
_s2__t17_s0:	.float	0.0
_s2__t1_s0:	.float	0.0
_s2_goblins_s1:	.space	40
_s2_four_s1:	.float	0.0
_s2_one_s1:	.word	0
_s2__t10_s0:	.word	0
_s2__t13_s0:	.word	0
_s2_zero_s1:	.word	0
_s2__t14_s0:	.word	0
_s2__t12_s0:	.word	0
_s2__t11_s0:	.word	0
_s2__t15_s0:	.word	0
_s2_savera:	.word	0
.text
sw	$ra, _s2_savera
# assign,goblins_s1,5,11.0
la $a0, _s2_goblins_s1
li $a1, 5
li.s	$f12, 11.0
jal initFloatArray

# assign,two_s1,2.0,
li.s	$f4, 2.0
l.s	$f6, _s2_two_s1
mov.s	$f6, $f4
s.s	$f6, _s2_two_s1

# assign,six_s1,6.0,
li.s	$f4, 6.0
l.s	$f6, _s2_six_s1
mov.s	$f6, $f4
s.s	$f6, _s2_six_s1

# assign,one_s1,1,
lw	$t9, _s2_one_s1
li	$t8, 1
move	$t9, $t8
sw	$t9, _s2_one_s1

# assign,zero_s1,1,
lw	$t8, _s2_zero_s1
li	$t9, 1
move	$t8, $t9
sw	$t8, _s2_zero_s1

# assign,number_s1,0.0,
li.s	$f4, 0.0
l.s	$f6, _s2_number_s1
mov.s	$f6, $f4
s.s	$f6, _s2_number_s1

# main:

# call,printf,two_s1
l.s	$f4, _s2_two_s1
mov.s	$f12, $f4
s.s	$f4, _s2_two_s1
jal	printf

# call,printf,2.0
li.s	$f12, 2.0
jal	printf

# add,2.0,2.0,_t1_s0
li.s	$f4, 2.0
li.s	$f6, 2.0
add.s	$f8, $f4, $f6
s.s	$f8, _s2__t1_s0


# call,printf,_t1_s0
l.s	$f4, _s2__t1_s0
mov.s	$f12, $f4
s.s	$f4, _s2__t1_s0
jal	printf

# call,printf,4.0
li.s	$f12, 4.0
jal	printf

# add,2.0,2.0,_t2_s0
li.s	$f4, 2.0
li.s	$f6, 2.0
add.s	$f10, $f4, $f6
s.s	$f10, _s2__t2_s0


# assign,four_s1,_t2_s0,
l.s	$f4, _s2_four_s1
l.s	$f6, _s2__t2_s0
mov.s	$f4, $f6
s.s	$f4, _s2_four_s1
s.s	$f6, _s2__t2_s0


# call,printf,four_s1
l.s	$f6, _s2_four_s1
mov.s	$f12, $f6
s.s	$f6, _s2_four_s1
jal	printf

# call,printf,4.0
li.s	$f12, 4.0
jal	printf

# mul,four_s1,four_s1,_t3_s0
l.s	$f6, _s2__t3_s0
l.s	$f4, _s2_four_s1
mul.s	$f6, $f4, $f4
s.s	$f6, _s2__t3_s0
s.s	$f4, _s2_four_s1


# call,printf,_t3_s0
l.s	$f4, _s2__t3_s0
mov.s	$f12, $f4
s.s	$f4, _s2__t3_s0
jal	printf

# call,printf,16.0
li.s	$f12, 16.0
jal	printf

# add,two_s1,2.0,_t4_s0
li.s	$f4, 2.0
l.s	$f6, _s2__t4_s0
l.s	$f16, _s2_two_s1
add.s	$f6, $f16, $f4
s.s	$f6, _s2__t4_s0
s.s	$f16, _s2_two_s1


# call,printf,_t4_s0
l.s	$f16, _s2__t4_s0
mov.s	$f12, $f16
s.s	$f16, _s2__t4_s0
jal	printf

# call,printf,4.0
li.s	$f12, 4.0
jal	printf

# add,2.0,two_s1,_t5_s0
li.s	$f16, 2.0
l.s	$f6, _s2__t5_s0
l.s	$f4, _s2_two_s1
add.s	$f6, $f16, $f4
s.s	$f6, _s2__t5_s0
s.s	$f4, _s2_two_s1


# call,printf,_t5_s0
l.s	$f4, _s2__t5_s0
mov.s	$f12, $f4
s.s	$f4, _s2__t5_s0
jal	printf

# call,printf,4.0
li.s	$f12, 4.0
jal	printf

# sub,four_s1,2.0,_t6_s0
li.s	$f4, 2.0
l.s	$f6, _s2__t6_s0
l.s	$f16, _s2_four_s1
sub.s	$f6, $f16, $f4
s.s	$f6, _s2__t6_s0
s.s	$f16, _s2_four_s1


# call,printf,_t6_s0
l.s	$f16, _s2__t6_s0
mov.s	$f12, $f16
s.s	$f16, _s2__t6_s0
jal	printf

# call,printf,2.0
li.s	$f12, 2.0
jal	printf

# sub,6.0,four_s1,_t7_s0
li.s	$f16, 6.0
l.s	$f6, _s2__t7_s0
l.s	$f4, _s2_four_s1
sub.s	$f6, $f16, $f4
s.s	$f6, _s2__t7_s0
s.s	$f4, _s2_four_s1


# call,printf,_t7_s0
l.s	$f4, _s2__t7_s0
mov.s	$f12, $f4
s.s	$f4, _s2__t7_s0
jal	printf

# call,printf,2.0
li.s	$f12, 2.0
jal	printf

# array_load,_t8_s0,goblins_s1,0
la $a0, _s2_goblins_s1
li $a1, 0
jal loadFloatArray
s.s	$f0, _s2__t8_s0

# call,printf,_t8_s0
l.s	$f4, _s2__t8_s0
mov.s	$f12, $f4
s.s	$f4, _s2__t8_s0
jal	printf

# call,printf,11.0
li.s	$f12, 11.0
jal	printf

# array_load,_t9_s0,goblins_s1,one_s1
la $a0, _s2_goblins_s1
lw	$t9, _s2_one_s1
move	$a1, $t9
sw	$t9, _s2_one_s1
jal loadFloatArray
s.s	$f0, _s2__t9_s0

# call,printf,_t9_s0
l.s	$f4, _s2__t9_s0
mov.s	$f12, $f4
s.s	$f4, _s2__t9_s0
jal	printf

# call,printf,11.0
li.s	$f12, 11.0
jal	printf

# assign,_t10_s0,0,
lw	$t9, _s2__t10_s0
li	$t8, 0
move	$t9, $t8
sw	$t9, _s2__t10_s0

# brgeq,1.0,2.0,if_label_0
li.s	$f4, 1.0
li.s	$f6, 2.0
c.lt.s	$f4, $f6
bc1f if_label_0


# assign,_t10_s0,1,
lw	$t8, _s2__t10_s0
li	$t9, 1
move	$t8, $t9
sw	$t8, _s2__t10_s0

# if_label_0:
if_label_0:

# call,printi,_t10_s0
lw	$t9, _s2__t10_s0
lw	$t9, _s2__t10_s0
move	$a0, $t9
sw	$t9, _s2__t10_s0
jal	printi

# call,printi,1
li	$a0, 1
jal	printi

# assign,_t11_s0,0,
lw	$t9, _s2__t11_s0
li	$t8, 0
move	$t9, $t8
sw	$t9, _s2__t11_s0

# brleq,1.0,2.0,if_label_1
li.s	$f6, 1.0
li.s	$f4, 2.0
c.le.s	$f6, $f4
bc1t if_label_1


# assign,_t11_s0,1,
lw	$t8, _s2__t11_s0
li	$t9, 1
move	$t8, $t9
sw	$t8, _s2__t11_s0

# if_label_1:
if_label_1:

# call,printi,_t11_s0
lw	$t9, _s2__t11_s0
lw	$t9, _s2__t11_s0
move	$a0, $t9
sw	$t9, _s2__t11_s0
jal	printi

# call,printi,0
li	$a0, 0
jal	printi

# assign,_t12_s0,0,
lw	$t9, _s2__t12_s0
li	$t8, 0
move	$t9, $t8
sw	$t9, _s2__t12_s0

# brneq,1.0,2.0,if_label_2
li.s	$f4, 1.0
li.s	$f6, 2.0
c.eq.s	$f4, $f6
bc1f if_label_2


# assign,_t12_s0,1,
lw	$t8, _s2__t12_s0
li	$t9, 1
move	$t8, $t9
sw	$t8, _s2__t12_s0

# if_label_2:
if_label_2:

# call,printi,_t12_s0
lw	$t9, _s2__t12_s0
lw	$t9, _s2__t12_s0
move	$a0, $t9
sw	$t9, _s2__t12_s0
jal	printi

# call,printi,0
li	$a0, 0
jal	printi

# assign,_t13_s0,0,
lw	$t9, _s2__t13_s0
li	$t8, 0
move	$t9, $t8
sw	$t9, _s2__t13_s0

# brleq,six_s1,4.0,if_label_3
li.s	$f6, 4.0
l.s	$f4, _s2_six_s1
c.le.s	$f4, $f6
bc1t if_label_3

# assign,_t13_s0,1,
lw	$t8, _s2__t13_s0
li	$t9, 1
move	$t8, $t9
sw	$t8, _s2__t13_s0

# if_label_3:
if_label_3:

# call,printi,_t13_s0
lw	$t9, _s2__t13_s0
lw	$t9, _s2__t13_s0
move	$a0, $t9
sw	$t9, _s2__t13_s0
jal	printi

# call,printi,1
li	$a0, 1
jal	printi

# assign,_t14_s0,0,
lw	$t9, _s2__t14_s0
li	$t8, 0
move	$t9, $t8
sw	$t9, _s2__t14_s0

# brleq,6.0,four_s1,if_label_4
li.s	$f4, 6.0
l.s	$f6, _s2_four_s1
c.le.s	$f4, $f6
bc1t if_label_4

# assign,_t14_s0,1,
lw	$t8, _s2__t14_s0
li	$t9, 1
move	$t8, $t9
sw	$t8, _s2__t14_s0

# if_label_4:
if_label_4:

# call,printi,_t14_s0
lw	$t9, _s2__t14_s0
lw	$t9, _s2__t14_s0
move	$a0, $t9
sw	$t9, _s2__t14_s0
jal	printi

# call,printi,1
li	$a0, 1
jal	printi

# assign,_t15_s0,0,
lw	$t9, _s2__t15_s0
li	$t8, 0
move	$t9, $t8
sw	$t9, _s2__t15_s0

# brleq,six_s1,four_s1,if_label_5
c.le.s	$f4, $f6
bc1t if_label_5

# assign,_t15_s0,1,
lw	$t8, _s2__t15_s0
li	$t9, 1
move	$t8, $t9
sw	$t8, _s2__t15_s0

# if_label_5:
if_label_5:

# call,printi,_t15_s0
lw	$t9, _s2__t15_s0
lw	$t9, _s2__t15_s0
move	$a0, $t9
sw	$t9, _s2__t15_s0
jal	printi

# call,printi,1
li	$a0, 1
jal	printi

# callr,_t16_s0,return88
jal	_s0_return88
l.s	$f6, _s2__t16_s0
mov.s	$f6, $f0
s.s	$f6, _s2__t16_s0

# assign,number_s1,_t16_s0,
l.s	$f6, _s2_number_s1
l.s	$f4, _s2__t16_s0
mov.s	$f6, $f4
s.s	$f6, _s2_number_s1
s.s	$f4, _s2__t16_s0


# call,printf,number_s1
l.s	$f4, _s2_number_s1
mov.s	$f12, $f4
s.s	$f4, _s2_number_s1
jal	printf

# call,printf,88.0
li.s	$f12, 88.0
jal	printf

# callr,_t17_s0,returnf,99.0
li.s	$f14, 99.0
jal	_s1_returnf
l.s	$f4, _s2__t17_s0
mov.s	$f4, $f0
s.s	$f4, _s2__t17_s0

# assign,number_s1,_t17_s0,
l.s	$f4, _s2_number_s1
l.s	$f6, _s2__t17_s0
mov.s	$f4, $f6
s.s	$f4, _s2_number_s1
s.s	$f6, _s2__t17_s0


# call,printf,number_s1
l.s	$f6, _s2_number_s1
mov.s	$f12, $f6
s.s	$f6, _s2_number_s1
jal	printf

# call,printf,99.0
li.s	$f12, 99.0
jal	printf

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

