#main: _t8_s0: 4
#main: _t6_s0: 8
#main: _t9_s0: 12
#main: lowestIndex_s1: 16
#main: _t7_s0: 20
#main: _t10_s0: 24
#main: _t5_s0: 28
#main: subIndex_s1: 32
#main: _t4_s0: 36
#main: cats_s1: 40
#main: _t2_s0: 72
#main: temp_s1: 76
#main: _t3_s0: 80
#main: smallest_s1: 84
#main: x_s1: 88
#main: first_s1: 92
#main: _t1_s0: 96
#main: size_s1: 100
#main: index_s1: 104
.data
dregisters:	.space	64
sp_temp:	.word	0
.text
.globl main

######## main
_s0_main:
.text
sw	$ra, 0($sp)
addiu	$sp, $sp, -108	# Move stack pointer to accommodate variables in this function.
la	$s0, dregisters		# Load address of dregisters in $s0
sw	$sp, 0($s0)			# Move stack pointer to 4*function level in dregisters ($s0 is address of dregisters).
# main:

# array_store,cats_s1,0,7
# var at same level
la	$a0, 40($sp)
li $a1, 0
li	$a2, 7
jal storeIntArray

# array_store,cats_s1,1,2
# var at same level
la	$a0, 40($sp)
li $a1, 1
li	$a2, 2
jal storeIntArray

# array_store,cats_s1,2,10
# var at same level
la	$a0, 40($sp)
li $a1, 2
li	$a2, 10
jal storeIntArray

# array_store,cats_s1,3,20
# var at same level
la	$a0, 40($sp)
li $a1, 3
li	$a2, 20
jal storeIntArray

# array_store,cats_s1,4,5
# var at same level
la	$a0, 40($sp)
li $a1, 4
li	$a2, 5
jal storeIntArray

# array_store,cats_s1,5,6
# var at same level
la	$a0, 40($sp)
li $a1, 5
li	$a2, 6
jal storeIntArray

# array_store,cats_s1,6,44
# var at same level
la	$a0, 40($sp)
li $a1, 6
li	$a2, 44
jal storeIntArray

# array_store,cats_s1,7,33
# var at same level
la	$a0, 40($sp)
li $a1, 7
li	$a2, 33
jal storeIntArray

# assign,size_s1,8,
lw	$t9, 100($sp)
li	$t8, 8
move	$t9, $t8
sw	$t9, 100($sp)

# assign,index_s1,0,
lw	$t8, 104($sp)
li	$t9, 0
move	$t8, $t9
sw	$t8, 104($sp)

# loop_label_0:
loop_label_0:

# sub,size_s1,1,_t1_s0
li	$t9, 1
lw	$t8, 96($sp)
lw	$t7, 100($sp)
sub	$t8, $t7, $t9
sw	$t8, 96($sp)
sw	$t7, 100($sp)


# brgt,index_s1,_t1_s0,loop_label_1
lw	$t7, 104($sp)
lw	$t8, 96($sp)
bgt	$t7, $t8, loop_label_1
sw	$t7, 104($sp)
sw	$t8, 96($sp)

# assign,lowestIndex_s1,index_s1,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t8, 16($sp)
lw	$t7, 104($sp)
move	$t8, $t7
sw	$t8, 16($sp)
sw	$t7, 104($sp)


# add,index_s1,1,_t2_s0
li	$t7, 1
lw	$t8, 72($sp)
lw	$t9, 104($sp)
add	$t8, $t9, $t7
sw	$t8, 72($sp)
sw	$t9, 104($sp)


# assign,subIndex_s1,_t2_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, 32($sp)
lw	$t8, 72($sp)
move	$t9, $t8
sw	$t9, 32($sp)
sw	$t8, 72($sp)


# loop_label_2:
loop_label_2:

# sub,size_s1,1,_t3_s0
li	$t8, 1
lw	$t9, 80($sp)
lw	$t7, 100($sp)
sub	$t9, $t7, $t8
sw	$t9, 80($sp)
sw	$t7, 100($sp)


# brgt,subIndex_s1,_t3_s0,loop_label_3
lw	$t7, 32($sp)
lw	$t9, 80($sp)
bgt	$t7, $t9, loop_label_3
sw	$t7, 32($sp)
sw	$t9, 80($sp)

# array_load,_t5_s0,cats_s1,subIndex_s1
# var at same level
la	$a0, 40($sp)
lw	$t9, 32($sp)
move	$a1, $t9
sw	$t9, 32($sp)
jal loadIntArray
lw	$t9, 28($sp)
move	$t9, $v0
sw	$t9, 28($sp)

# array_load,_t6_s0,cats_s1,lowestIndex_s1
# var at same level
la	$a0, 40($sp)
lw	$t9, 16($sp)
move	$a1, $t9
sw	$t9, 16($sp)
jal loadIntArray
lw	$t9, 8($sp)
move	$t9, $v0
sw	$t9, 8($sp)

# assign,_t4_s0,0,
lw	$t9, 36($sp)
li	$t7, 0
move	$t9, $t7
sw	$t9, 36($sp)

# brgeq,_t5_s0,_t6_s0,if_label_5
lw	$t7, 28($sp)
lw	$t9, 8($sp)
bge	$t7, $t9, if_label_5
sw	$t7, 28($sp)
sw	$t9, 8($sp)

# assign,_t4_s0,1,
lw	$t9, 36($sp)
li	$t7, 1
move	$t9, $t7
sw	$t9, 36($sp)

# if_label_5:
if_label_5:

# brneq,_t4_s0,1,if_label_4
lw	$t7, 36($sp)
li	$t9, 1
bne	$t7, $t9, if_label_4
sw	$t7, 36($sp)

# assign,lowestIndex_s1,subIndex_s1,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, 16($sp)
lw	$t7, 32($sp)
move	$t9, $t7
sw	$t9, 16($sp)
sw	$t7, 32($sp)


# if_label_4:
if_label_4:

# add,subIndex_s1,1,subIndex_s1
li	$t7, 1
lw	$t9, 32($sp)
add	$t9, $t9, $t7
sw	$t9, 32($sp)


# goto,loop_label_2,,
j loop_label_2

# loop_label_3:
loop_label_3:

# array_load,_t7_s0,cats_s1,index_s1
# var at same level
la	$a0, 40($sp)
lw	$t9, 104($sp)
move	$a1, $t9
sw	$t9, 104($sp)
jal loadIntArray
lw	$t9, 20($sp)
move	$t9, $v0
sw	$t9, 20($sp)

# assign,first_s1,_t7_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, 92($sp)
lw	$t7, 20($sp)
move	$t9, $t7
sw	$t9, 92($sp)
sw	$t7, 20($sp)


# array_load,_t8_s0,cats_s1,lowestIndex_s1
# var at same level
la	$a0, 40($sp)
lw	$t7, 16($sp)
move	$a1, $t7
sw	$t7, 16($sp)
jal loadIntArray
lw	$t7, 4($sp)
move	$t7, $v0
sw	$t7, 4($sp)

# assign,smallest_s1,_t8_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t7, 84($sp)
lw	$t9, 4($sp)
move	$t7, $t9
sw	$t7, 84($sp)
sw	$t9, 4($sp)


# array_store,cats_s1,index_s1,smallest_s1
# var at same level
la	$a0, 40($sp)
lw	$t9, 104($sp)
move	$a1, $t9
sw	$t9, 104($sp)
lw	$t9, 84($sp)
move	$a2, $t9
sw	$t9, 84($sp)
jal storeIntArray

# array_store,cats_s1,lowestIndex_s1,first_s1
# var at same level
la	$a0, 40($sp)
lw	$t9, 16($sp)
move	$a1, $t9
sw	$t9, 16($sp)
lw	$t9, 92($sp)
move	$a2, $t9
sw	$t9, 92($sp)
jal storeIntArray

# add,index_s1,1,index_s1
li	$t9, 1
lw	$t7, 104($sp)
add	$t7, $t7, $t9
sw	$t7, 104($sp)


# goto,loop_label_0,,
j loop_label_0

# loop_label_1:
loop_label_1:

# assign,index_s1,0,
lw	$t7, 104($sp)
li	$t9, 0
move	$t7, $t9
sw	$t7, 104($sp)

# loop_label_6:
loop_label_6:

# sub,size_s1,1,_t9_s0
li	$t9, 1
lw	$t7, 12($sp)
lw	$t8, 100($sp)
sub	$t7, $t8, $t9
sw	$t7, 12($sp)
sw	$t8, 100($sp)


# brgt,index_s1,_t9_s0,loop_label_7
lw	$t8, 104($sp)
lw	$t7, 12($sp)
bgt	$t8, $t7, loop_label_7
sw	$t8, 104($sp)
sw	$t7, 12($sp)

# array_load,_t10_s0,cats_s1,index_s1
# var at same level
la	$a0, 40($sp)
lw	$t7, 104($sp)
move	$a1, $t7
sw	$t7, 104($sp)
jal loadIntArray
lw	$t7, 24($sp)
move	$t7, $v0
sw	$t7, 24($sp)

# call,printi,_t10_s0
lw	$t7, 24($sp)
move	$a0, $t7
sw	$t7, 24($sp)
jal	printi

# add,index_s1,1,index_s1
li	$t7, 1
lw	$t8, 104($sp)
add	$t8, $t8, $t7
sw	$t8, 104($sp)


# goto,loop_label_6,,
j loop_label_6

# loop_label_7:
loop_label_7:

# return,,,

addiu	$sp, $sp, 108
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

