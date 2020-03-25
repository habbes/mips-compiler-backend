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
.data
_s0__t8_s0:	.word	0
_s0__t6_s0:	.word	0
_s0__t9_s0:	.word	0
_s0_two_s1:	.word	0
_s0_number_s1:	.word	0
_s0__t7_s0:	.word	0
_s0__t10_s0:	.word	0
_s0__t5_s0:	.word	0
_s0__t4_s0:	.word	0
_s0_six_s1:	.word	0
_s0_three_s1:	.word	0
_s0__t2_s0:	.word	0
_s0__t13_s0:	.word	0
_s0__t3_s0:	.word	0
_s0__t14_s0:	.word	0
_s0__t12_s0:	.word	0
_s0__t11_s0:	.word	0
_s0__t16_s0:	.word	0
_s0__t15_s0:	.word	0
_s0__t17_s0:	.word	0
_s0__t18_s0:	.word	0
_s0__t19_s0:	.word	0
_s0_one_s1:	.word	0
_s0__t1_s0:	.word	0
_s0_savera:	.word	0
.text
sw	$ra, _s0_savera
# assign,one_s1,1,
# New web started: one_s1 in register *$t9*
lw	$t9, _s0_one_s1
li	$t3, 1
move	$t9, $t3
# Web ended: one_s1 in register *$t9*
sw	$t9, _s0_one_s1
# assign,two_s1,2,
# New web started: two_s1 in register *$t9*
lw	$t9, _s0_two_s1
li	$t3, 2
move	$t9, $t3
# assign,three_s1,3,
# New web started: three_s1 in register *$t8*
lw	$t8, _s0_three_s1
li	$t3, 3
move	$t8, $t3
# assign,six_s1,6,
# New web started: six_s1 in register *$t7*
lw	$t7, _s0_six_s1
li	$t3, 6
move	$t7, $t3
# assign,number_s1,0,
# New web started: number_s1 in register *$t6*
lw	$t6, _s0_number_s1
li	$t3, 0
move	$t6, $t3
# main:
# assign,number_s1,1,
li	$t3, 1
move	$t6, $t3
# loop_label_0:
loop_label_0:
# brgt,number_s1,2,loop_label_1
li	$t3, 2
bgt	$t6, $t3, loop_label_1
# assign,_t1_s0,0,
# New web started: _t1_s0 in register *$t5*
lw	$t5, _s0__t1_s0
li	$t3, 0
move	$t5, $t3
# brneq,number_s1,1,if_label_2
li	$t3, 1
bne	$t6, $t3, if_label_2
# assign,_t1_s0,1,
li	$t3, 1
move	$t5, $t3
# if_label_2:
if_label_2:
# brneq,_t1_s0,1,if_label_3
li	$t3, 1
bne	$t5, $t3, if_label_3
# Web ended: _t1_s0 in register *$t5*
sw	$t5, _s0__t1_s0
# mul,two_s1,three_s1,_t2_s0
# New web started: _t2_s0 in register *$t5*
lw	$t5, _s0__t2_s0
mul	$t5, $t9, $t8

# assign,six_s1,_t2_s0,
#*** copyto level: 0
#*** copyfrom level: 0
move	$t7, $t5

# Web ended: _t2_s0 in register *$t5*
sw	$t5, _s0__t2_s0
# add,three_s1,three_s1,_t3_s0
# New web started: _t3_s0 in register *$t5*
lw	$t5, _s0__t3_s0
add	$t5, $t8, $t8

# assign,six_s1,_t3_s0,
#*** copyto level: 0
#*** copyfrom level: 0
move	$t7, $t5

# Web ended: _t3_s0 in register *$t5*
sw	$t5, _s0__t3_s0
# assign,_t4_s0,1,
# New web started: _t4_s0 in register *$t5*
lw	$t5, _s0__t4_s0
li	$t3, 1
move	$t5, $t3
# assign,_t5_s0,1,
# New web started: _t5_s0 in register *$t4*
lw	$t4, _s0__t5_s0
li	$t3, 1
move	$t4, $t3
# loop_label_5:
loop_label_5:
# brgt,_t5_s0,three_s1,loop_label_6
bgt	$t4, $t8, loop_label_6
# mult,_t4_s0,two_s1,_t6_s0
# Did not get a register: _t6_s0
lw	$t3, _s0__t6_s0
mul	$t3, $t5, $t9
sw	$t3, _s0__t6_s0

# assign,_t4_s0,_t6_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t3, _s0__t6_s0
move	$t5, $t3
sw	$t3, _s0__t6_s0

# add,_t5_s0,1,_t5_s0
li	$t3, 1
add	$t4, $t4, $t3

# goto,loop_label_5,,
j loop_label_5
# Web ended: _t5_s0 in register *$t4*
sw	$t4, _s0__t5_s0
# loop_label_6:
loop_label_6:
# sub,_t4_s0,two_s1,_t7_s0
# New web started: _t7_s0 in register *$t4*
lw	$t4, _s0__t7_s0
sub	$t4, $t5, $t9

# Web ended: _t4_s0 in register *$t5*
sw	$t5, _s0__t4_s0
# assign,six_s1,_t7_s0,
#*** copyto level: 0
#*** copyfrom level: 0
move	$t7, $t4

# Web ended: _t7_s0 in register *$t4*
sw	$t4, _s0__t7_s0
# assign,six_s1,six_s1,
#*** copyto level: 0
#*** copyfrom level: 0
move	$t7, $t7

# mul,two_s1,two_s1,_t8_s0
# New web started: _t8_s0 in register *$t4*
lw	$t4, _s0__t8_s0
mul	$t4, $t9, $t9

# mul,_t8_s0,three_s1,_t9_s0
# New web started: _t9_s0 in register *$t5*
lw	$t5, _s0__t9_s0
mul	$t5, $t4, $t8

# Web ended: _t8_s0 in register *$t4*
sw	$t4, _s0__t8_s0
# div,_t9_s0,two_s1,_t10_s0
# New web started: _t10_s0 in register *$t4*
lw	$t4, _s0__t10_s0
div	$t4, $t5, $t9

# Web ended: _t9_s0 in register *$t5*
sw	$t5, _s0__t9_s0
# assign,six_s1,_t10_s0,
#*** copyto level: 0
#*** copyfrom level: 0
move	$t7, $t4

# Web ended: _t10_s0 in register *$t4*
sw	$t4, _s0__t10_s0
# goto,if_label_4,,
j if_label_4
# if_label_3:
if_label_3:
# mul,two_s1,three_s1,_t11_s0
# New web started: _t11_s0 in register *$t5*
lw	$t5, _s0__t11_s0
mul	$t5, $t9, $t8

# assign,six_s1,_t11_s0,
#*** copyto level: 0
#*** copyfrom level: 0
move	$t7, $t5

# Web ended: _t11_s0 in register *$t5*
sw	$t5, _s0__t11_s0
# add,three_s1,three_s1,_t12_s0
# New web started: _t12_s0 in register *$t5*
lw	$t5, _s0__t12_s0
add	$t5, $t8, $t8

# assign,six_s1,_t12_s0,
#*** copyto level: 0
#*** copyfrom level: 0
move	$t7, $t5

# Web ended: _t12_s0 in register *$t5*
sw	$t5, _s0__t12_s0
# assign,_t13_s0,1,
# New web started: _t13_s0 in register *$t4*
lw	$t4, _s0__t13_s0
li	$t3, 1
move	$t4, $t3
# assign,_t14_s0,1,
# New web started: _t14_s0 in register *$t5*
lw	$t5, _s0__t14_s0
li	$t3, 1
move	$t5, $t3
# loop_label_7:
loop_label_7:
# brgt,_t14_s0,three_s1,loop_label_8
bgt	$t5, $t8, loop_label_8
# mult,_t13_s0,two_s1,_t15_s0
# Did not get a register: _t15_s0
lw	$t3, _s0__t15_s0
mul	$t3, $t4, $t9
sw	$t3, _s0__t15_s0

# assign,_t13_s0,_t15_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t3, _s0__t15_s0
move	$t4, $t3
sw	$t3, _s0__t15_s0

# add,_t14_s0,1,_t14_s0
li	$t3, 1
add	$t5, $t5, $t3

# goto,loop_label_7,,
j loop_label_7
# Web ended: _t14_s0 in register *$t5*
sw	$t5, _s0__t14_s0
# loop_label_8:
loop_label_8:
# sub,_t13_s0,two_s1,_t16_s0
# New web started: _t16_s0 in register *$t5*
lw	$t5, _s0__t16_s0
sub	$t5, $t4, $t9

# Web ended: _t13_s0 in register *$t4*
sw	$t4, _s0__t13_s0
# assign,six_s1,_t16_s0,
#*** copyto level: 0
#*** copyfrom level: 0
move	$t7, $t5

# Web ended: _t16_s0 in register *$t5*
sw	$t5, _s0__t16_s0
# assign,six_s1,six_s1,
#*** copyto level: 0
#*** copyfrom level: 0
move	$t7, $t7

# mul,two_s1,two_s1,_t17_s0
# New web started: _t17_s0 in register *$t4*
lw	$t4, _s0__t17_s0
mul	$t4, $t9, $t9

# mul,_t17_s0,three_s1,_t18_s0
# New web started: _t18_s0 in register *$t5*
lw	$t5, _s0__t18_s0
mul	$t5, $t4, $t8

# Web ended: _t17_s0 in register *$t4*
sw	$t4, _s0__t17_s0
# div,_t18_s0,two_s1,_t19_s0
# New web started: _t19_s0 in register *$t4*
lw	$t4, _s0__t19_s0
div	$t4, $t5, $t9

# Web ended: _t18_s0 in register *$t5*
sw	$t5, _s0__t18_s0
# assign,six_s1,_t19_s0,
#*** copyto level: 0
#*** copyfrom level: 0
move	$t7, $t4

# Web ended: _t19_s0 in register *$t4*
sw	$t4, _s0__t19_s0
# if_label_4:
if_label_4:
# add,number_s1,1,number_s1
li	$t3, 1
add	$t6, $t6, $t3

# goto,loop_label_0,,
j loop_label_0
# Web ended: two_s1 in register *$t9*
sw	$t9, _s0_two_s1
# Web ended: number_s1 in register *$t6*
sw	$t6, _s0_number_s1
# Web ended: three_s1 in register *$t8*
sw	$t8, _s0_three_s1
# loop_label_1:
loop_label_1:
# call,printi,six_s1
move	$a0, $t7
sw	$t7, _s0_six_s1
jal	printi
lw	$t7, _s0_six_s1
# Web ended: six_s1 in register *$t7*
sw	$t7, _s0_six_s1
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

