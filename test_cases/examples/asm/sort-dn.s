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
.data
_s0__t8_s0:	.word	0
_s0__t6_s0:	.word	0
_s0__t9_s0:	.word	0
_s0_lowestIndex_s1:	.word	0
_s0__t7_s0:	.word	0
_s0__t10_s0:	.word	0
_s0__t5_s0:	.word	0
_s0_subIndex_s1:	.word	0
_s0__t4_s0:	.word	0
_s0_cats_s1:	.space	32
_s0__t2_s0:	.word	0
_s0_temp_s1:	.word	0
_s0__t3_s0:	.word	0
_s0_smallest_s1:	.word	0
_s0_x_s1:	.word	0
_s0_first_s1:	.word	0
_s0__t1_s0:	.word	0
_s0_size_s1:	.word	0
_s0_index_s1:	.word	0
_s0_savera:	.word	0
.text
sw	$ra, _s0_savera
# main:

# array_store,cats_s1,0,7
la	$a0, _s0_cats_s1
li $a1, 0
li	$a2, 7
jal storeIntArray

# array_store,cats_s1,1,2
la	$a0, _s0_cats_s1
li $a1, 1
li	$a2, 2
jal storeIntArray

# array_store,cats_s1,2,10
la	$a0, _s0_cats_s1
li $a1, 2
li	$a2, 10
jal storeIntArray

# array_store,cats_s1,3,20
la	$a0, _s0_cats_s1
li $a1, 3
li	$a2, 20
jal storeIntArray

# array_store,cats_s1,4,5
la	$a0, _s0_cats_s1
li $a1, 4
li	$a2, 5
jal storeIntArray

# array_store,cats_s1,5,6
la	$a0, _s0_cats_s1
li $a1, 5
li	$a2, 6
jal storeIntArray

# array_store,cats_s1,6,44
la	$a0, _s0_cats_s1
li $a1, 6
li	$a2, 44
jal storeIntArray

# array_store,cats_s1,7,33
la	$a0, _s0_cats_s1
li $a1, 7
li	$a2, 33
jal storeIntArray

# assign,size_s1,8,
lw	$t9, _s0_size_s1
li	$t8, 8
move	$t9, $t8
sw	$t9, _s0_size_s1

# assign,index_s1,0,
lw	$t8, _s0_index_s1
li	$t9, 0
move	$t8, $t9
sw	$t8, _s0_index_s1

# loop_label_0:
loop_label_0:

# sub,size_s1,1,_t1_s0
li	$t9, 1
lw	$t8, _s0__t1_s0
lw	$t7, _s0_size_s1
sub	$t8, $t7, $t9
sw	$t8, _s0__t1_s0
sw	$t7, _s0_size_s1


# brgt,index_s1,_t1_s0,loop_label_1
lw	$t7, _s0_index_s1
lw	$t8, _s0__t1_s0
bgt	$t7, $t8, loop_label_1
sw	$t7, _s0_index_s1
sw	$t8, _s0__t1_s0

# assign,lowestIndex_s1,index_s1,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t8, _s0_lowestIndex_s1
lw	$t7, _s0_index_s1
move	$t8, $t7
sw	$t8, _s0_lowestIndex_s1
sw	$t7, _s0_index_s1


# add,index_s1,1,_t2_s0
li	$t7, 1
lw	$t8, _s0__t2_s0
lw	$t9, _s0_index_s1
add	$t8, $t9, $t7
sw	$t8, _s0__t2_s0
sw	$t9, _s0_index_s1


# assign,subIndex_s1,_t2_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s0_subIndex_s1
lw	$t8, _s0__t2_s0
move	$t9, $t8
sw	$t9, _s0_subIndex_s1
sw	$t8, _s0__t2_s0


# loop_label_2:
loop_label_2:

# sub,size_s1,1,_t3_s0
li	$t8, 1
lw	$t9, _s0__t3_s0
lw	$t7, _s0_size_s1
sub	$t9, $t7, $t8
sw	$t9, _s0__t3_s0
sw	$t7, _s0_size_s1


# brgt,subIndex_s1,_t3_s0,loop_label_3
lw	$t7, _s0_subIndex_s1
lw	$t9, _s0__t3_s0
bgt	$t7, $t9, loop_label_3
sw	$t7, _s0_subIndex_s1
sw	$t9, _s0__t3_s0

# array_load,_t5_s0,cats_s1,subIndex_s1
la $a0, _s0_cats_s1
lw	$t9, _s0_subIndex_s1
move	$a1, $t9
sw	$t9, _s0_subIndex_s1
jal loadIntArray
lw	$t9, _s0__t5_s0
move	$t9, $v0
sw	$t9, _s0__t5_s0

# array_load,_t6_s0,cats_s1,lowestIndex_s1
la $a0, _s0_cats_s1
lw	$t9, _s0_lowestIndex_s1
move	$a1, $t9
sw	$t9, _s0_lowestIndex_s1
jal loadIntArray
lw	$t9, _s0__t6_s0
move	$t9, $v0
sw	$t9, _s0__t6_s0

# assign,_t4_s0,0,
lw	$t9, _s0__t4_s0
li	$t7, 0
move	$t9, $t7
sw	$t9, _s0__t4_s0

# brgeq,_t5_s0,_t6_s0,if_label_5
lw	$t7, _s0__t5_s0
lw	$t9, _s0__t6_s0
bge	$t7, $t9, if_label_5
sw	$t7, _s0__t5_s0
sw	$t9, _s0__t6_s0

# assign,_t4_s0,1,
lw	$t9, _s0__t4_s0
li	$t7, 1
move	$t9, $t7
sw	$t9, _s0__t4_s0

# if_label_5:
if_label_5:

# brneq,_t4_s0,1,if_label_4
lw	$t7, _s0__t4_s0
li	$t9, 1
bne	$t7, $t9, if_label_4
sw	$t7, _s0__t4_s0

# assign,lowestIndex_s1,subIndex_s1,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s0_lowestIndex_s1
lw	$t7, _s0_subIndex_s1
move	$t9, $t7
sw	$t9, _s0_lowestIndex_s1
sw	$t7, _s0_subIndex_s1


# if_label_4:
if_label_4:

# add,subIndex_s1,1,subIndex_s1
li	$t7, 1
lw	$t9, _s0_subIndex_s1
add	$t9, $t9, $t7
sw	$t9, _s0_subIndex_s1


# goto,loop_label_2,,
j loop_label_2

# loop_label_3:
loop_label_3:

# array_load,_t7_s0,cats_s1,index_s1
la $a0, _s0_cats_s1
lw	$t9, _s0_index_s1
move	$a1, $t9
sw	$t9, _s0_index_s1
jal loadIntArray
lw	$t9, _s0__t7_s0
move	$t9, $v0
sw	$t9, _s0__t7_s0

# assign,first_s1,_t7_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s0_first_s1
lw	$t7, _s0__t7_s0
move	$t9, $t7
sw	$t9, _s0_first_s1
sw	$t7, _s0__t7_s0


# array_load,_t8_s0,cats_s1,lowestIndex_s1
la $a0, _s0_cats_s1
lw	$t7, _s0_lowestIndex_s1
move	$a1, $t7
sw	$t7, _s0_lowestIndex_s1
jal loadIntArray
lw	$t7, _s0__t8_s0
move	$t7, $v0
sw	$t7, _s0__t8_s0

# assign,smallest_s1,_t8_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t7, _s0_smallest_s1
lw	$t9, _s0__t8_s0
move	$t7, $t9
sw	$t7, _s0_smallest_s1
sw	$t9, _s0__t8_s0


# array_store,cats_s1,index_s1,smallest_s1
la	$a0, _s0_cats_s1
lw	$t9, _s0_index_s1
move	$a1, $t9
sw	$t9, _s0_index_s1
lw	$t9, _s0_smallest_s1
move	$a2, $t9
sw	$t9, _s0_smallest_s1
jal storeIntArray

# array_store,cats_s1,lowestIndex_s1,first_s1
la	$a0, _s0_cats_s1
lw	$t9, _s0_lowestIndex_s1
move	$a1, $t9
sw	$t9, _s0_lowestIndex_s1
lw	$t9, _s0_first_s1
move	$a2, $t9
sw	$t9, _s0_first_s1
jal storeIntArray

# add,index_s1,1,index_s1
li	$t9, 1
lw	$t7, _s0_index_s1
add	$t7, $t7, $t9
sw	$t7, _s0_index_s1


# goto,loop_label_0,,
j loop_label_0

# loop_label_1:
loop_label_1:

# assign,index_s1,0,
lw	$t7, _s0_index_s1
li	$t9, 0
move	$t7, $t9
sw	$t7, _s0_index_s1

# loop_label_6:
loop_label_6:

# sub,size_s1,1,_t9_s0
li	$t9, 1
lw	$t7, _s0__t9_s0
lw	$t8, _s0_size_s1
sub	$t7, $t8, $t9
sw	$t7, _s0__t9_s0
sw	$t8, _s0_size_s1


# brgt,index_s1,_t9_s0,loop_label_7
lw	$t8, _s0_index_s1
lw	$t7, _s0__t9_s0
bgt	$t8, $t7, loop_label_7
sw	$t8, _s0_index_s1
sw	$t7, _s0__t9_s0

# array_load,_t10_s0,cats_s1,index_s1
la $a0, _s0_cats_s1
lw	$t7, _s0_index_s1
move	$a1, $t7
sw	$t7, _s0_index_s1
jal loadIntArray
lw	$t7, _s0__t10_s0
move	$t7, $v0
sw	$t7, _s0__t10_s0

# call,printi,_t10_s0
lw	$t7, _s0__t10_s0
lw	$t7, _s0__t10_s0
move	$a0, $t7
sw	$t7, _s0__t10_s0
jal	printi

# add,index_s1,1,index_s1
li	$t7, 1
lw	$t8, _s0_index_s1
add	$t8, $t8, $t7
sw	$t8, _s0_index_s1


# goto,loop_label_6,,
j loop_label_6

# loop_label_7:
loop_label_7:

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

