#main: _t4_s0: 4
#main: _t1_s0: 8
#main: _t2_s0: 12
#main: _t3_s0: 16
#main: n_s1: 20
#main: total_s1: 24
#main: index_s1: 28
.data
dregisters:	.space	64
sp_temp:	.word	0
.text
.globl main

######## main
_s0_main:
.data
_s0__t4_s0:	.word	0
_s0__t1_s0:	.word	0
_s0__t2_s0:	.word	0
_s0__t3_s0:	.word	0
_s0_n_s1:	.word	0
_s0_total_s1:	.word	0
_s0_index_s1:	.word	0
_s0_savera:	.word	0
.text
sw	$ra, _s0_savera
# assign,n_s1,10,
# New web started: n_s1 in register *$t7*
lw	$t7, _s0_n_s1
li	$t3, 10
move	$t7, $t3
# main:
# assign,total_s1,0,
# New web started: total_s1 in register *$t8*
lw	$t8, _s0_total_s1
li	$t3, 0
move	$t8, $t3
# assign,index_s1,1,
# New web started: index_s1 in register *$t9*
lw	$t9, _s0_index_s1
li	$t3, 1
move	$t9, $t3
# loop_label_0:
loop_label_0:
# brgt,index_s1,n_s1,loop_label_1
bgt	$t9, $t7, loop_label_1
# add,total_s1,index_s1,_t1_s0
# New web started: _t1_s0 in register *$t6*
lw	$t6, _s0__t1_s0
add	$t6, $t8, $t9

# assign,total_s1,_t1_s0,
#*** copyto level: 0
#*** copyfrom level: 0
move	$t8, $t6

# Web ended: _t1_s0 in register *$t6*
sw	$t6, _s0__t1_s0
# add,index_s1,1,index_s1
li	$t3, 1
add	$t9, $t9, $t3

# goto,loop_label_0,,
j loop_label_0
# Web ended: index_s1 in register *$t9*
sw	$t9, _s0_index_s1
# loop_label_1:
loop_label_1:
# call,printi,total_s1
move	$a0, $t8
sw	$t7, _s0_n_s1
sw	$t8, _s0_total_s1
jal	printi
lw	$t7, _s0_n_s1
lw	$t8, _s0_total_s1
# Web ended: total_s1 in register *$t8*
sw	$t8, _s0_total_s1
# add,n_s1,1,_t2_s0
# New web started: _t2_s0 in register *$t8*
lw	$t8, _s0__t2_s0
li	$t3, 1
add	$t8, $t7, $t3

# mul,n_s1,_t2_s0,_t3_s0
# New web started: _t3_s0 in register *$t9*
lw	$t9, _s0__t3_s0
mul	$t9, $t7, $t8

# Web ended: _t2_s0 in register *$t8*
sw	$t8, _s0__t2_s0
# Web ended: n_s1 in register *$t7*
sw	$t7, _s0_n_s1
# div,_t3_s0,2,_t4_s0
# New web started: _t4_s0 in register *$t8*
lw	$t8, _s0__t4_s0
li	$t3, 2
div	$t8, $t9, $t3

# Web ended: _t3_s0 in register *$t9*
sw	$t9, _s0__t3_s0
# call,printi,_t4_s0
move	$a0, $t8
sw	$t8, _s0__t4_s0
jal	printi
lw	$t8, _s0__t4_s0
# Web ended: _t4_s0 in register *$t8*
sw	$t8, _s0__t4_s0
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

