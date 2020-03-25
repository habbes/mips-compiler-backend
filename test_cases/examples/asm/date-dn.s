#main: month_s1: 4
#main: day_s1: 8
#main: _t6_s0: 12
#main: _t5_s0: 16
#main: _t4_s0: 20
#main: _t1_s0: 24
#main: date_s1: 28
#main: _t2_s0: 32
#main: _t3_s0: 36
#main: monthOK_s1: 40
#main: monthLengths_s1: 44
#main: dayOK_s1: 96
.data
dregisters:	.space	64
sp_temp:	.word	0
.text
.globl main

######## main
_s0_main:
.data
_s0_month_s1:	.word	0
_s0_day_s1:	.word	0
_s0__t6_s0:	.word	0
_s0__t5_s0:	.word	0
_s0__t4_s0:	.word	0
_s0__t1_s0:	.word	0
_s0_date_s1:	.word	0
_s0__t2_s0:	.word	0
_s0__t3_s0:	.word	0
_s0_monthOK_s1:	.word	0
_s0_monthLengths_s1:	.space	52
_s0_dayOK_s1:	.word	0
_s0_savera:	.word	0
.text
sw	$ra, _s0_savera
# assign,monthLengths_s1,13,31
la $a0, _s0_monthLengths_s1
li $a1, 13
li $a2, 31
jal initIntArray

# assign,date_s1,1042,
lw	$t9, _s0_date_s1
li	$t8, 1042
move	$t9, $t8
sw	$t9, _s0_date_s1

# main:

# array_store,monthLengths_s1,2,28
la	$a0, _s0_monthLengths_s1
li $a1, 2
li	$a2, 28
jal storeIntArray

# array_store,monthLengths_s1,4,30
la	$a0, _s0_monthLengths_s1
li $a1, 4
li	$a2, 30
jal storeIntArray

# array_store,monthLengths_s1,6,30
la	$a0, _s0_monthLengths_s1
li $a1, 6
li	$a2, 30
jal storeIntArray

# array_store,monthLengths_s1,9,30
la	$a0, _s0_monthLengths_s1
li $a1, 9
li	$a2, 30
jal storeIntArray

# array_store,monthLengths_s1,11,30
la	$a0, _s0_monthLengths_s1
li $a1, 11
li	$a2, 30
jal storeIntArray

# div,date_s1,100,_t1_s0
li	$t8, 100
lw	$t9, _s0__t1_s0
lw	$t7, _s0_date_s1
div	$t9, $t7, $t8
sw	$t9, _s0__t1_s0
sw	$t7, _s0_date_s1


# assign,month_s1,_t1_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t7, _s0_month_s1
lw	$t9, _s0__t1_s0
move	$t7, $t9
sw	$t7, _s0_month_s1
sw	$t9, _s0__t1_s0


# mul,month_s1,100,_t2_s0
li	$t9, 100
lw	$t7, _s0__t2_s0
lw	$t8, _s0_month_s1
mul	$t7, $t8, $t9
sw	$t7, _s0__t2_s0
sw	$t8, _s0_month_s1


# sub,date_s1,_t2_s0,_t3_s0
lw	$t8, _s0__t3_s0
lw	$t7, _s0_date_s1
lw	$t9, _s0__t2_s0
sub	$t8, $t7, $t9
sw	$t8, _s0__t3_s0
sw	$t7, _s0_date_s1
sw	$t9, _s0__t2_s0


# assign,day_s1,_t3_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s0_day_s1
lw	$t7, _s0__t3_s0
move	$t9, $t7
sw	$t9, _s0_day_s1
sw	$t7, _s0__t3_s0


# assign,dayOK_s1,99,
lw	$t7, _s0_dayOK_s1
li	$t9, 99
move	$t7, $t9
sw	$t7, _s0_dayOK_s1

# assign,_t4_s0,0,
lw	$t9, _s0__t4_s0
li	$t7, 0
move	$t9, $t7
sw	$t9, _s0__t4_s0

# brgt,month_s1,12,if_label_0
lw	$t7, _s0_month_s1
li	$t9, 12
bgt	$t7, $t9, if_label_0
sw	$t7, _s0_month_s1

# assign,_t4_s0,1,
lw	$t9, _s0__t4_s0
li	$t7, 1
move	$t9, $t7
sw	$t9, _s0__t4_s0

# if_label_0:
if_label_0:

# assign,monthOK_s1,_t4_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t7, _s0_monthOK_s1
lw	$t9, _s0__t4_s0
move	$t7, $t9
sw	$t7, _s0_monthOK_s1
sw	$t9, _s0__t4_s0


# brneq,monthOK_s1,1,if_label_1
lw	$t9, _s0_monthOK_s1
li	$t7, 1
bne	$t9, $t7, if_label_1
sw	$t9, _s0_monthOK_s1

# array_load,_t6_s0,monthLengths_s1,month_s1
la $a0, _s0_monthLengths_s1
lw	$t7, _s0_month_s1
move	$a1, $t7
sw	$t7, _s0_month_s1
jal loadIntArray
lw	$t7, _s0__t6_s0
move	$t7, $v0
sw	$t7, _s0__t6_s0

# assign,_t5_s0,0,
lw	$t7, _s0__t5_s0
li	$t9, 0
move	$t7, $t9
sw	$t7, _s0__t5_s0

# brgt,day_s1,_t6_s0,if_label_2
lw	$t9, _s0_day_s1
lw	$t7, _s0__t6_s0
bgt	$t9, $t7, if_label_2
sw	$t9, _s0_day_s1
sw	$t7, _s0__t6_s0

# assign,_t5_s0,1,
lw	$t7, _s0__t5_s0
li	$t9, 1
move	$t7, $t9
sw	$t7, _s0__t5_s0

# if_label_2:
if_label_2:

# assign,dayOK_s1,_t5_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s0_dayOK_s1
lw	$t7, _s0__t5_s0
move	$t9, $t7
sw	$t9, _s0_dayOK_s1
sw	$t7, _s0__t5_s0


# if_label_1:
if_label_1:

# call,printi,date_s1
lw	$t7, _s0_date_s1
lw	$t7, _s0_date_s1
move	$a0, $t7
sw	$t7, _s0_date_s1
jal	printi

# call,printi,monthOK_s1
lw	$t7, _s0_monthOK_s1
lw	$t7, _s0_monthOK_s1
move	$a0, $t7
sw	$t7, _s0_monthOK_s1
jal	printi

# call,printi,dayOK_s1
lw	$t7, _s0_dayOK_s1
lw	$t7, _s0_dayOK_s1
move	$a0, $t7
sw	$t7, _s0_dayOK_s1
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

