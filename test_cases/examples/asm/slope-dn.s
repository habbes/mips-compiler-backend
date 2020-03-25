#main: _t8_s0: 4
#main: _t6_s0: 8
#main: _t9_s0: 12
#main: _t7_s0: 16
#main: _t10_s0: 20
#main: _t5_s0: 24
#main: y1_s1: 28
#main: y2_s1: 32
#main: _t4_s0: 36
#main: _t2_s0: 40
#main: _t3_s0: 44
#main: intercept_s1: 48
#main: _t12_s0: 52
#main: _t11_s0: 56
#main: x2_s1: 60
#main: numerator_s1: 64
#main: x1_s1: 68
#main: _t1_s0: 72
#main: slope_s1: 76
#main: denominator_s1: 80
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
_s0_y1_s1:	.word	0
_s0_y2_s1:	.word	0
_s0__t4_s0:	.word	0
_s0__t2_s0:	.word	0
_s0__t3_s0:	.word	0
_s0_intercept_s1:	.word	0
_s0__t12_s0:	.word	0
_s0__t11_s0:	.word	0
_s0_x2_s1:	.word	0
_s0_numerator_s1:	.word	0
_s0_x1_s1:	.word	0
_s0__t1_s0:	.word	0
_s0_slope_s1:	.word	0
_s0_denominator_s1:	.word	0
_s0_savera:	.word	0
.text
sw	$ra, _s0_savera
# main:

# assign,y1_s1,1,
lw	$t9, _s0_y1_s1
li	$t8, 1
move	$t9, $t8
sw	$t9, _s0_y1_s1

# assign,x1_s1,y1_s1,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t8, _s0_x1_s1
lw	$t9, _s0_y1_s1
move	$t8, $t9
sw	$t8, _s0_x1_s1
sw	$t9, _s0_y1_s1


# assign,y2_s1,2,
lw	$t9, _s0_y2_s1
li	$t8, 2
move	$t9, $t8
sw	$t9, _s0_y2_s1

# assign,x2_s1,y2_s1,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t8, _s0_x2_s1
lw	$t9, _s0_y2_s1
move	$t8, $t9
sw	$t8, _s0_x2_s1
sw	$t9, _s0_y2_s1


# sub,y2_s1,y1_s1,_t1_s0
lw	$t9, _s0__t1_s0
lw	$t8, _s0_y2_s1
lw	$t7, _s0_y1_s1
sub	$t9, $t8, $t7
sw	$t9, _s0__t1_s0
sw	$t8, _s0_y2_s1
sw	$t7, _s0_y1_s1


# assign,numerator_s1,_t1_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t7, _s0_numerator_s1
lw	$t8, _s0__t1_s0
move	$t7, $t8
sw	$t7, _s0_numerator_s1
sw	$t8, _s0__t1_s0


# sub,x2_s1,x1_s1,_t2_s0
lw	$t8, _s0__t2_s0
lw	$t7, _s0_x2_s1
lw	$t9, _s0_x1_s1
sub	$t8, $t7, $t9
sw	$t8, _s0__t2_s0
sw	$t7, _s0_x2_s1
sw	$t9, _s0_x1_s1


# assign,denominator_s1,_t2_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s0_denominator_s1
lw	$t7, _s0__t2_s0
move	$t9, $t7
sw	$t9, _s0_denominator_s1
sw	$t7, _s0__t2_s0


# div,numerator_s1,denominator_s1,_t3_s0
lw	$t7, _s0__t3_s0
lw	$t9, _s0_numerator_s1
lw	$t8, _s0_denominator_s1
div	$t7, $t9, $t8
sw	$t7, _s0__t3_s0
sw	$t9, _s0_numerator_s1
sw	$t8, _s0_denominator_s1


# assign,slope_s1,_t3_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t8, _s0_slope_s1
lw	$t9, _s0__t3_s0
move	$t8, $t9
sw	$t8, _s0_slope_s1
sw	$t9, _s0__t3_s0


# mul,slope_s1,x2_s1,_t4_s0
lw	$t9, _s0__t4_s0
lw	$t8, _s0_slope_s1
lw	$t7, _s0_x2_s1
mul	$t9, $t8, $t7
sw	$t9, _s0__t4_s0
sw	$t8, _s0_slope_s1
sw	$t7, _s0_x2_s1


# sub,y2_s1,_t4_s0,_t5_s0
lw	$t7, _s0__t5_s0
lw	$t8, _s0_y2_s1
lw	$t9, _s0__t4_s0
sub	$t7, $t8, $t9
sw	$t7, _s0__t5_s0
sw	$t8, _s0_y2_s1
sw	$t9, _s0__t4_s0


# assign,intercept_s1,_t5_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s0_intercept_s1
lw	$t8, _s0__t5_s0
move	$t9, $t8
sw	$t9, _s0_intercept_s1
sw	$t8, _s0__t5_s0


# assign,x2_s1,7,
lw	$t8, _s0_x2_s1
li	$t9, 7
move	$t8, $t9
sw	$t8, _s0_x2_s1

# mul,slope_s1,x2_s1,_t6_s0
lw	$t9, _s0__t6_s0
lw	$t8, _s0_slope_s1
lw	$t7, _s0_x2_s1
mul	$t9, $t8, $t7
sw	$t9, _s0__t6_s0
sw	$t8, _s0_slope_s1
sw	$t7, _s0_x2_s1


# add,_t6_s0,intercept_s1,_t7_s0
lw	$t7, _s0__t7_s0
lw	$t8, _s0__t6_s0
lw	$t9, _s0_intercept_s1
add	$t7, $t8, $t9
sw	$t7, _s0__t7_s0
sw	$t8, _s0__t6_s0
sw	$t9, _s0_intercept_s1


# assign,y2_s1,_t7_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s0_y2_s1
lw	$t8, _s0__t7_s0
move	$t9, $t8
sw	$t9, _s0_y2_s1
sw	$t8, _s0__t7_s0


# sub,x2_s1,x1_s1,_t8_s0
lw	$t8, _s0__t8_s0
lw	$t9, _s0_x2_s1
lw	$t7, _s0_x1_s1
sub	$t8, $t9, $t7
sw	$t8, _s0__t8_s0
sw	$t9, _s0_x2_s1
sw	$t7, _s0_x1_s1


# sub,y2_s1,y1_s1,_t9_s0
lw	$t7, _s0__t9_s0
lw	$t9, _s0_y2_s1
lw	$t8, _s0_y1_s1
sub	$t7, $t9, $t8
sw	$t7, _s0__t9_s0
sw	$t9, _s0_y2_s1
sw	$t8, _s0_y1_s1


# div,_t9_s0,_t8_s0,_t10_s0
lw	$t8, _s0__t10_s0
lw	$t9, _s0__t9_s0
lw	$t7, _s0__t8_s0
div	$t8, $t9, $t7
sw	$t8, _s0__t10_s0
sw	$t9, _s0__t9_s0
sw	$t7, _s0__t8_s0


# assign,slope_s1,_t10_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t7, _s0_slope_s1
lw	$t9, _s0__t10_s0
move	$t7, $t9
sw	$t7, _s0_slope_s1
sw	$t9, _s0__t10_s0


# assign,_t11_s0,0,
lw	$t9, _s0__t11_s0
li	$t7, 0
move	$t9, $t7
sw	$t9, _s0__t11_s0

# brneq,slope_s1,1,if_label_0
lw	$t7, _s0_slope_s1
li	$t9, 1
bne	$t7, $t9, if_label_0
sw	$t7, _s0_slope_s1

# assign,_t11_s0,1,
lw	$t9, _s0__t11_s0
li	$t7, 1
move	$t9, $t7
sw	$t9, _s0__t11_s0

# if_label_0:
if_label_0:

# call,printi,_t11_s0
lw	$t7, _s0__t11_s0
lw	$t7, _s0__t11_s0
move	$a0, $t7
sw	$t7, _s0__t11_s0
jal	printi

# assign,_t12_s0,0,
lw	$t7, _s0__t12_s0
li	$t9, 0
move	$t7, $t9
sw	$t7, _s0__t12_s0

# brneq,intercept_s1,0,if_label_1
lw	$t9, _s0_intercept_s1
li	$t7, 0
bne	$t9, $t7, if_label_1
sw	$t9, _s0_intercept_s1

# assign,_t12_s0,1,
lw	$t7, _s0__t12_s0
li	$t9, 1
move	$t7, $t9
sw	$t7, _s0__t12_s0

# if_label_1:
if_label_1:

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

