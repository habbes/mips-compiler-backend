#main: _t8_s0: 4
#main: _t6_s0: 8
#main: _t9_s0: 12
#main: number_s1: 16
#main: _t7_s0: 20
#main: _t10_s0: 24
#main: _t5_s0: 28
#main: _t4_s0: 32
#main: _t2_s0: 36
#main: _t13_s0: 40
#main: _t3_s0: 44
#main: _t12_s0: 48
#main: _t11_s0: 52
#main: _t1_s0: 56
#main: goblins_s1: 60
#main: four_s1: 80
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
_s0_number_s1:	.word	0
_s0__t7_s0:	.word	0
_s0__t10_s0:	.word	0
_s0__t5_s0:	.word	0
_s0__t4_s0:	.word	0
_s0__t2_s0:	.word	0
_s0__t13_s0:	.word	0
_s0__t3_s0:	.word	0
_s0__t12_s0:	.word	0
_s0__t11_s0:	.word	0
_s0__t1_s0:	.word	0
_s0_goblins_s1:	.space	20
_s0_four_s1:	.word	0
_s0_savera:	.word	0
.text
sw	$ra, _s0_savera
# assign,goblins_s1,5,16
la $a0, _s0_goblins_s1
li $a1, 5
li $a2, 16
jal initIntArray

# main:

# array_store,goblins_s1,3,11
la	$a0, _s0_goblins_s1
li $a1, 3
li	$a2, 11
jal storeIntArray

# call,printi,11
li	$a0, 11
jal	printi

# array_load,_t1_s0,goblins_s1,3
la $a0, _s0_goblins_s1
li $a1, 3
jal loadIntArray
lw	$t9, _s0__t1_s0
move	$t9, $v0
sw	$t9, _s0__t1_s0

# call,printi,_t1_s0
lw	$t9, _s0__t1_s0
lw	$t9, _s0__t1_s0
move	$a0, $t9
sw	$t9, _s0__t1_s0
jal	printi

# call,printi,16
li	$a0, 16
jal	printi

# array_load,_t2_s0,goblins_s1,4
la $a0, _s0_goblins_s1
li $a1, 4
jal loadIntArray
lw	$t9, _s0__t2_s0
move	$t9, $v0
sw	$t9, _s0__t2_s0

# call,printi,_t2_s0
lw	$t9, _s0__t2_s0
lw	$t9, _s0__t2_s0
move	$a0, $t9
sw	$t9, _s0__t2_s0
jal	printi

# array_store,goblins_s1,2,2
la	$a0, _s0_goblins_s1
li $a1, 2
li	$a2, 2
jal storeIntArray

# call,printi,2
li	$a0, 2
jal	printi

# array_load,_t3_s0,goblins_s1,2
la $a0, _s0_goblins_s1
li $a1, 2
jal loadIntArray
lw	$t9, _s0__t3_s0
move	$t9, $v0
sw	$t9, _s0__t3_s0

# call,printi,_t3_s0
lw	$t9, _s0__t3_s0
lw	$t9, _s0__t3_s0
move	$a0, $t9
sw	$t9, _s0__t3_s0
jal	printi

# array_load,_t4_s0,goblins_s1,2
la $a0, _s0_goblins_s1
li $a1, 2
jal loadIntArray
lw	$t9, _s0__t4_s0
move	$t9, $v0
sw	$t9, _s0__t4_s0

# assign,number_s1,_t4_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s0_number_s1
lw	$t8, _s0__t4_s0
move	$t9, $t8
sw	$t9, _s0_number_s1
sw	$t8, _s0__t4_s0


# call,printi,2
li	$a0, 2
jal	printi

# call,printi,number_s1
lw	$t8, _s0_number_s1
lw	$t8, _s0_number_s1
move	$a0, $t8
sw	$t8, _s0_number_s1
jal	printi

# array_load,_t5_s0,goblins_s1,four_s1
la $a0, _s0_goblins_s1
lw	$t8, _s0_four_s1
move	$a1, $t8
sw	$t8, _s0_four_s1
jal loadIntArray
lw	$t8, _s0__t5_s0
move	$t8, $v0
sw	$t8, _s0__t5_s0

# assign,number_s1,_t5_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t8, _s0_number_s1
lw	$t9, _s0__t5_s0
move	$t8, $t9
sw	$t8, _s0_number_s1
sw	$t9, _s0__t5_s0


# call,printi,16
li	$a0, 16
jal	printi

# call,printi,number_s1
lw	$t9, _s0_number_s1
lw	$t9, _s0_number_s1
move	$a0, $t9
sw	$t9, _s0_number_s1
jal	printi

# array_load,_t7_s0,goblins_s1,four_s1
la $a0, _s0_goblins_s1
lw	$t9, _s0_four_s1
move	$a1, $t9
sw	$t9, _s0_four_s1
jal loadIntArray
lw	$t9, _s0__t7_s0
move	$t9, $v0
sw	$t9, _s0__t7_s0

# array_load,_t8_s0,goblins_s1,2
la $a0, _s0_goblins_s1
li $a1, 2
jal loadIntArray
lw	$t9, _s0__t8_s0
move	$t9, $v0
sw	$t9, _s0__t8_s0

# array_load,_t9_s0,goblins_s1,4
la $a0, _s0_goblins_s1
li $a1, 4
jal loadIntArray
lw	$t9, _s0__t9_s0
move	$t9, $v0
sw	$t9, _s0__t9_s0

# array_load,_t10_s0,goblins_s1,3
la $a0, _s0_goblins_s1
li $a1, 3
jal loadIntArray
lw	$t9, _s0__t10_s0
move	$t9, $v0
sw	$t9, _s0__t10_s0

# add,_t10_s0,_t9_s0,_t11_s0
lw	$t9, _s0__t11_s0
lw	$t8, _s0__t10_s0
lw	$t7, _s0__t9_s0
add	$t9, $t8, $t7
sw	$t9, _s0__t11_s0
sw	$t8, _s0__t10_s0
sw	$t7, _s0__t9_s0


# add,_t11_s0,_t8_s0,_t12_s0
lw	$t7, _s0__t12_s0
lw	$t8, _s0__t11_s0
lw	$t9, _s0__t8_s0
add	$t7, $t8, $t9
sw	$t7, _s0__t12_s0
sw	$t8, _s0__t11_s0
sw	$t9, _s0__t8_s0


# add,_t12_s0,_t7_s0,_t13_s0
lw	$t9, _s0__t13_s0
lw	$t8, _s0__t12_s0
lw	$t7, _s0__t7_s0
add	$t9, $t8, $t7
sw	$t9, _s0__t13_s0
sw	$t8, _s0__t12_s0
sw	$t7, _s0__t7_s0


# assign,_t6_s0,0,
lw	$t7, _s0__t6_s0
li	$t8, 0
move	$t7, $t8
sw	$t7, _s0__t6_s0

# brneq,_t13_s0,45,if_label_0
lw	$t8, _s0__t13_s0
li	$t7, 45
bne	$t8, $t7, if_label_0
sw	$t8, _s0__t13_s0

# assign,_t6_s0,1,
lw	$t7, _s0__t6_s0
li	$t8, 1
move	$t7, $t8
sw	$t7, _s0__t6_s0

# if_label_0:
if_label_0:

# call,printi,_t6_s0
lw	$t8, _s0__t6_s0
lw	$t8, _s0__t6_s0
move	$a0, $t8
sw	$t8, _s0__t6_s0
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

