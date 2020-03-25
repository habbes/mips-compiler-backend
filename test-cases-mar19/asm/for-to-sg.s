#main: counter_s1: 4
#main: _t4_s0: 8
#main: _t1_s0: 12
#main: elves_s1: 16
#main: goblinCount_s1: 20
#main: _t2_s0: 24
#main: _t3_s0: 28
#main: goblins_s1: 32
.data
dregisters:	.space	64
sp_temp:	.word	0
.text
.globl main

######## main
_s0_main:
.text
sw	$ra, 0($sp)
addiu	$sp, $sp, -52	# Move stack pointer to accommodate variables in this function.
la	$s0, dregisters		# Load address of dregisters in $s0
sw	$sp, 0($s0)			# Move stack pointer to 4*function level in dregisters ($s0 is address of dregisters).
# main:
# assign,elves_s1,0,
# New web started: elves_s1 in register *$t8*
lw	$t8, 16($sp)
li	$t3, 0
move	$t8, $t3
# assign,counter_s1,0,
# New web started: counter_s1 in register *$t9*
lw	$t9, 4($sp)
li	$t3, 0
move	$t9, $t3
# loop_label_0:
loop_label_0:
# brgt,counter_s1,4,loop_label_1
li	$t3, 4
bgt	$t9, $t3, loop_label_1
# add,elves_s1,counter_s1,_t1_s0
# New web started: _t1_s0 in register *$t7*
lw	$t7, 12($sp)
add	$t7, $t8, $t9

# assign,elves_s1,_t1_s0,
#*** copyto level: 0
#*** copyfrom level: 0
move	$t8, $t7

# Web ended: _t1_s0 in register *$t7*
sw	$t7, 12($sp)
# call,printi,counter_s1
move	$a0, $t9
sw	$t9, 4($sp)
sw	$t8, 16($sp)
jal	printi
lw	$t9, 4($sp)
lw	$t8, 16($sp)
# add,counter_s1,1,counter_s1
li	$t3, 1
add	$t9, $t9, $t3

# goto,loop_label_0,,
j loop_label_0
# loop_label_1:
loop_label_1:
# call,printi,elves_s1
move	$a0, $t8
sw	$t9, 4($sp)
sw	$t8, 16($sp)
jal	printi
lw	$t9, 4($sp)
lw	$t8, 16($sp)
# Web ended: elves_s1 in register *$t8*
sw	$t8, 16($sp)
# assign,counter_s1,0,
li	$t3, 0
move	$t9, $t3
# loop_label_2:
loop_label_2:
# brgt,counter_s1,4,loop_label_3
li	$t3, 4
bgt	$t9, $t3, loop_label_3
# array_store,goblins_s1,counter_s1,counter_s1
# var at same level
la	$a0, 32($sp)
move	$a1, $t9
move	$a2, $t9
jal storeIntArray
# array_load,_t2_s0,goblins_s1,counter_s1
# New web started: _t2_s0 in register *$t8*
lw	$t8, 24($sp)
# var at same level
la	$a0, 32($sp)
move	$a1, $t9
jal loadIntArray
move	$t8, $v0
# call,printi,_t2_s0
move	$a0, $t8
sw	$t9, 4($sp)
sw	$t8, 24($sp)
jal	printi
lw	$t9, 4($sp)
lw	$t8, 24($sp)
# Web ended: _t2_s0 in register *$t8*
sw	$t8, 24($sp)
# add,counter_s1,1,counter_s1
li	$t3, 1
add	$t9, $t9, $t3

# goto,loop_label_2,,
j loop_label_2
# loop_label_3:
loop_label_3:
# assign,goblinCount_s1,0,
# New web started: goblinCount_s1 in register *$t7*
lw	$t7, 20($sp)
li	$t3, 0
move	$t7, $t3
# assign,counter_s1,0,
li	$t3, 0
move	$t9, $t3
# loop_label_4:
loop_label_4:
# brgt,counter_s1,4,loop_label_5
li	$t3, 4
bgt	$t9, $t3, loop_label_5
# array_load,_t3_s0,goblins_s1,counter_s1
# New web started: _t3_s0 in register *$t8*
lw	$t8, 28($sp)
# var at same level
la	$a0, 32($sp)
move	$a1, $t9
jal loadIntArray
move	$t8, $v0
# add,goblinCount_s1,_t3_s0,_t4_s0
# New web started: _t4_s0 in register *$t6*
lw	$t6, 8($sp)
add	$t6, $t7, $t8

# Web ended: _t3_s0 in register *$t8*
sw	$t8, 28($sp)
# assign,goblinCount_s1,_t4_s0,
#*** copyto level: 0
#*** copyfrom level: 0
move	$t7, $t6

# Web ended: _t4_s0 in register *$t6*
sw	$t6, 8($sp)
# call,printi,goblinCount_s1
move	$a0, $t7
sw	$t9, 4($sp)
sw	$t7, 20($sp)
jal	printi
lw	$t9, 4($sp)
lw	$t7, 20($sp)
# add,counter_s1,1,counter_s1
li	$t3, 1
add	$t9, $t9, $t3

# goto,loop_label_4,,
j loop_label_4
# Web ended: counter_s1 in register *$t9*
sw	$t9, 4($sp)
# loop_label_5:
loop_label_5:
# call,printi,goblinCount_s1
move	$a0, $t7
sw	$t7, 20($sp)
jal	printi
lw	$t7, 20($sp)
# Web ended: goblinCount_s1 in register *$t7*
sw	$t7, 20($sp)
# return,,,
addiu	$sp, $sp, 52
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

