#getTaxes: _t8_s0: 4
#getTaxes: salary_s2: 8
#getTaxes: _t6_s0: 12
#getTaxes: _t9_s0: 16
#getTaxes: _t7_s0: 20
#getTaxes: _t10_s0: 24
#getTaxes: _t5_s0: 28
#getTaxes: _t4_s0: 32
#getTaxes: _t2_s0: 36
#getTaxes: _t13_s0: 40
#getTaxes: _t3_s0: 44
#getTaxes: _t14_s0: 48
#getTaxes: _t12_s0: 52
#getTaxes: _t11_s0: 56
#getTaxes: _t16_s0: 60
#getTaxes: _t15_s0: 64
#getTaxes: _t17_s0: 68
#getTaxes: _t18_s0: 72
#getTaxes: _t19_s0: 76
#getTaxes: _t1_s0: 80
#main: taxBrackets_s1: 4
#main: bestSalary_s1: 16
#main: betterTax_s1: 20
#main: bestTax_s1: 24
#main: betterSalary_s1: 28
#main: _t21_s0: 32
#main: tax_s1: 36
#main: _t20_s0: 40
#main: goodSalary_s1: 44
#main: _t25_s0: 48
#main: _t22_s0: 52
#main: _t23_s0: 56
#main: _t24_s0: 60
#main: goodTax_s1: 64
.data
dregisters:	.space	64
sp_temp:	.word	0
.text
.globl main

######## getTaxes
_s0_getTaxes:
.data
_s0__t8_s0:	.word	0
_s0_salary_s2:	.word	0
_s0__t6_s0:	.word	0
_s0__t9_s0:	.word	0
_s0__t7_s0:	.word	0
_s0__t10_s0:	.word	0
_s0__t5_s0:	.word	0
_s0__t4_s0:	.word	0
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
_s0__t1_s0:	.word	0
_s0_savera:	.word	0
.text
sw	$ra, _s0_savera
sw	$a0, _s0_salary_s2
# assign,_t1_s0,0,
lw	$t9, _s0__t1_s0
li	$t8, 0
move	$t9, $t8
sw	$t9, _s0__t1_s0

# brlt,salary_s2,100000,if_label_0
lw	$t8, _s0_salary_s2
li	$t9, 100000
blt	$t8, $t9, if_label_0
sw	$t8, _s0_salary_s2

# assign,_t1_s0,1,
lw	$t9, _s0__t1_s0
li	$t8, 1
move	$t9, $t8
sw	$t9, _s0__t1_s0

# if_label_0:
if_label_0:

# brneq,_t1_s0,1,if_label_1
lw	$t8, _s0__t1_s0
li	$t9, 1
bne	$t8, $t9, if_label_1
sw	$t8, _s0__t1_s0

# array_load,_t2_s0,taxBrackets_s1,0
la $a0, _s1_taxBrackets_s1
li $a1, 0
jal loadIntArray
lw	$t9, _s0__t2_s0
move	$t9, $v0
sw	$t9, _s0__t2_s0

# div,50000,_t2_s0,_t3_s0
li	$t9, 50000
lw	$t8, _s0__t3_s0
lw	$t7, _s0__t2_s0
div	$t8, $t9, $t7
sw	$t8, _s0__t3_s0
sw	$t7, _s0__t2_s0


# assign,tax_s1,_t3_s0,
#*** copyto level: 0
#*** copyfrom level: 1
lw	$t7, _s1_tax_s1
lw	$t8, _s0__t3_s0
move	$t7, $t8
sw	$t7, _s1_tax_s1
sw	$t8, _s0__t3_s0


# array_load,_t4_s0,taxBrackets_s1,1
la $a0, _s1_taxBrackets_s1
li $a1, 1
jal loadIntArray
lw	$t8, _s0__t4_s0
move	$t8, $v0
sw	$t8, _s0__t4_s0

# div,50000,_t4_s0,_t5_s0
li	$t8, 50000
lw	$t7, _s0__t5_s0
lw	$t9, _s0__t4_s0
div	$t7, $t8, $t9
sw	$t7, _s0__t5_s0
sw	$t9, _s0__t4_s0


# add,tax_s1,_t5_s0,_t6_s0
lw	$t9, _s0__t6_s0
lw	$t7, _s1_tax_s1
lw	$t8, _s0__t5_s0
add	$t9, $t7, $t8
sw	$t9, _s0__t6_s0
sw	$t7, _s1_tax_s1
sw	$t8, _s0__t5_s0


# assign,tax_s1,_t6_s0,
#*** copyto level: 0
#*** copyfrom level: 1
lw	$t8, _s1_tax_s1
lw	$t7, _s0__t6_s0
move	$t8, $t7
sw	$t8, _s1_tax_s1
sw	$t7, _s0__t6_s0


# array_load,_t7_s0,taxBrackets_s1,2
la $a0, _s1_taxBrackets_s1
li $a1, 2
jal loadIntArray
lw	$t7, _s0__t7_s0
move	$t7, $v0
sw	$t7, _s0__t7_s0

# sub,salary_s2,100000,_t8_s0
li	$t7, 100000
lw	$t8, _s0__t8_s0
lw	$t9, _s0_salary_s2
sub	$t8, $t9, $t7
sw	$t8, _s0__t8_s0
sw	$t9, _s0_salary_s2


# div,_t8_s0,_t7_s0,_t9_s0
lw	$t9, _s0__t9_s0
lw	$t8, _s0__t8_s0
lw	$t7, _s0__t7_s0
div	$t9, $t8, $t7
sw	$t9, _s0__t9_s0
sw	$t8, _s0__t8_s0
sw	$t7, _s0__t7_s0


# add,tax_s1,_t9_s0,_t10_s0
lw	$t7, _s0__t10_s0
lw	$t8, _s1_tax_s1
lw	$t9, _s0__t9_s0
add	$t7, $t8, $t9
sw	$t7, _s0__t10_s0
sw	$t8, _s1_tax_s1
sw	$t9, _s0__t9_s0


# assign,tax_s1,_t10_s0,
#*** copyto level: 0
#*** copyfrom level: 1
lw	$t9, _s1_tax_s1
lw	$t8, _s0__t10_s0
move	$t9, $t8
sw	$t9, _s1_tax_s1
sw	$t8, _s0__t10_s0


# goto,if_label_2,,
j if_label_2

# if_label_1:
if_label_1:

# assign,_t11_s0,0,
lw	$t8, _s0__t11_s0
li	$t9, 0
move	$t8, $t9
sw	$t8, _s0__t11_s0

# brlt,salary_s2,50000,if_label_3
lw	$t9, _s0_salary_s2
li	$t8, 50000
blt	$t9, $t8, if_label_3
sw	$t9, _s0_salary_s2

# assign,_t11_s0,1,
lw	$t8, _s0__t11_s0
li	$t9, 1
move	$t8, $t9
sw	$t8, _s0__t11_s0

# if_label_3:
if_label_3:

# brneq,_t11_s0,1,if_label_4
lw	$t9, _s0__t11_s0
li	$t8, 1
bne	$t9, $t8, if_label_4
sw	$t9, _s0__t11_s0

# array_load,_t12_s0,taxBrackets_s1,0
la $a0, _s1_taxBrackets_s1
li $a1, 0
jal loadIntArray
lw	$t8, _s0__t12_s0
move	$t8, $v0
sw	$t8, _s0__t12_s0

# div,50000,_t12_s0,_t13_s0
li	$t8, 50000
lw	$t9, _s0__t13_s0
lw	$t7, _s0__t12_s0
div	$t9, $t8, $t7
sw	$t9, _s0__t13_s0
sw	$t7, _s0__t12_s0


# assign,tax_s1,_t13_s0,
#*** copyto level: 0
#*** copyfrom level: 1
lw	$t7, _s1_tax_s1
lw	$t9, _s0__t13_s0
move	$t7, $t9
sw	$t7, _s1_tax_s1
sw	$t9, _s0__t13_s0


# array_load,_t14_s0,taxBrackets_s1,1
la $a0, _s1_taxBrackets_s1
li $a1, 1
jal loadIntArray
lw	$t9, _s0__t14_s0
move	$t9, $v0
sw	$t9, _s0__t14_s0

# sub,salary_s2,50000,_t15_s0
li	$t9, 50000
lw	$t7, _s0__t15_s0
lw	$t8, _s0_salary_s2
sub	$t7, $t8, $t9
sw	$t7, _s0__t15_s0
sw	$t8, _s0_salary_s2


# div,_t15_s0,_t14_s0,_t16_s0
lw	$t8, _s0__t16_s0
lw	$t7, _s0__t15_s0
lw	$t9, _s0__t14_s0
div	$t8, $t7, $t9
sw	$t8, _s0__t16_s0
sw	$t7, _s0__t15_s0
sw	$t9, _s0__t14_s0


# add,tax_s1,_t16_s0,_t17_s0
lw	$t9, _s0__t17_s0
lw	$t7, _s1_tax_s1
lw	$t8, _s0__t16_s0
add	$t9, $t7, $t8
sw	$t9, _s0__t17_s0
sw	$t7, _s1_tax_s1
sw	$t8, _s0__t16_s0


# assign,tax_s1,_t17_s0,
#*** copyto level: 0
#*** copyfrom level: 1
lw	$t8, _s1_tax_s1
lw	$t7, _s0__t17_s0
move	$t8, $t7
sw	$t8, _s1_tax_s1
sw	$t7, _s0__t17_s0


# goto,if_label_5,,
j if_label_5

# if_label_4:
if_label_4:

# array_load,_t18_s0,taxBrackets_s1,0
la $a0, _s1_taxBrackets_s1
li $a1, 0
jal loadIntArray
lw	$t7, _s0__t18_s0
move	$t7, $v0
sw	$t7, _s0__t18_s0

# div,salary_s2,_t18_s0,_t19_s0
lw	$t7, _s0__t19_s0
lw	$t8, _s0_salary_s2
lw	$t9, _s0__t18_s0
div	$t7, $t8, $t9
sw	$t7, _s0__t19_s0
sw	$t8, _s0_salary_s2
sw	$t9, _s0__t18_s0


# assign,tax_s1,_t19_s0,
#*** copyto level: 0
#*** copyfrom level: 1
lw	$t9, _s1_tax_s1
lw	$t8, _s0__t19_s0
move	$t9, $t8
sw	$t9, _s1_tax_s1
sw	$t8, _s0__t19_s0


# if_label_5:
if_label_5:

# if_label_2:
if_label_2:

# return,tax_s1,,
lw	$t8, _s1_tax_s1
move	$v0, $t8
sw	$t8, _s1_tax_s1
lw	$ra, _s0_savera
jr	$ra

lw	$ra, _s0_savera
jr	$ra

######## main
_s1_main:
.data
_s1_taxBrackets_s1:	.space	12
_s1_bestSalary_s1:	.word	0
_s1_betterTax_s1:	.word	0
_s1_bestTax_s1:	.word	0
_s1_betterSalary_s1:	.word	0
_s1__t21_s0:	.word	0
_s1_tax_s1:	.word	0
_s1__t20_s0:	.word	0
_s1_goodSalary_s1:	.word	0
_s1__t25_s0:	.word	0
_s1__t22_s0:	.word	0
_s1__t23_s0:	.word	0
_s1__t24_s0:	.word	0
_s1_goodTax_s1:	.word	0
_s1_savera:	.word	0
.text
sw	$ra, _s1_savera
# assign,goodSalary_s1,40000,
lw	$t8, _s1_goodSalary_s1
li	$t9, 40000
move	$t8, $t9
sw	$t8, _s1_goodSalary_s1

# assign,betterSalary_s1,80000,
lw	$t9, _s1_betterSalary_s1
li	$t8, 80000
move	$t9, $t8
sw	$t9, _s1_betterSalary_s1

# assign,bestSalary_s1,120000,
lw	$t8, _s1_bestSalary_s1
li	$t9, 120000
move	$t8, $t9
sw	$t8, _s1_bestSalary_s1

# main:

# array_store,taxBrackets_s1,0,20
la	$a0, _s1_taxBrackets_s1
li $a1, 0
li	$a2, 20
jal storeIntArray

# array_store,taxBrackets_s1,1,10
la	$a0, _s1_taxBrackets_s1
li $a1, 1
li	$a2, 10
jal storeIntArray

# array_store,taxBrackets_s1,2,4
la	$a0, _s1_taxBrackets_s1
li $a1, 2
li	$a2, 4
jal storeIntArray

# callr,_t20_s0,getTaxes,goodSalary_s1
lw	$t9, _s1_goodSalary_s1
move	$a0, $t9
sw	$t9, _s1_goodSalary_s1
jal	_s0_getTaxes
lw	$t9, _s1__t20_s0
move	$t9, $v0
sw	$t9, _s1__t20_s0

# assign,goodTax_s1,_t20_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s1_goodTax_s1
lw	$t8, _s1__t20_s0
move	$t9, $t8
sw	$t9, _s1_goodTax_s1
sw	$t8, _s1__t20_s0


# callr,_t21_s0,getTaxes,betterSalary_s1
lw	$t8, _s1_betterSalary_s1
move	$a0, $t8
sw	$t8, _s1_betterSalary_s1
jal	_s0_getTaxes
lw	$t8, _s1__t21_s0
move	$t8, $v0
sw	$t8, _s1__t21_s0

# assign,betterTax_s1,_t21_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t8, _s1_betterTax_s1
lw	$t9, _s1__t21_s0
move	$t8, $t9
sw	$t8, _s1_betterTax_s1
sw	$t9, _s1__t21_s0


# callr,_t22_s0,getTaxes,bestSalary_s1
lw	$t9, _s1_bestSalary_s1
move	$a0, $t9
sw	$t9, _s1_bestSalary_s1
jal	_s0_getTaxes
lw	$t9, _s1__t22_s0
move	$t9, $v0
sw	$t9, _s1__t22_s0

# assign,bestTax_s1,_t22_s0,
#*** copyto level: 0
#*** copyfrom level: 0
lw	$t9, _s1_bestTax_s1
lw	$t8, _s1__t22_s0
move	$t9, $t8
sw	$t9, _s1_bestTax_s1
sw	$t8, _s1__t22_s0


# call,printi,goodTax_s1
lw	$t8, _s1_goodTax_s1
lw	$t8, _s1_goodTax_s1
move	$a0, $t8
sw	$t8, _s1_goodTax_s1
jal	printi

# call,printi,betterTax_s1
lw	$t8, _s1_betterTax_s1
lw	$t8, _s1_betterTax_s1
move	$a0, $t8
sw	$t8, _s1_betterTax_s1
jal	printi

# call,printi,bestTax_s1
lw	$t8, _s1_bestTax_s1
lw	$t8, _s1_bestTax_s1
move	$a0, $t8
sw	$t8, _s1_bestTax_s1
jal	printi

# assign,_t23_s0,0,
lw	$t8, _s1__t23_s0
li	$t9, 0
move	$t8, $t9
sw	$t8, _s1__t23_s0

# brneq,goodTax_s1,2000,if_label_6
lw	$t9, _s1_goodTax_s1
li	$t8, 2000
bne	$t9, $t8, if_label_6
sw	$t9, _s1_goodTax_s1

# assign,_t23_s0,1,
lw	$t8, _s1__t23_s0
li	$t9, 1
move	$t8, $t9
sw	$t8, _s1__t23_s0

# if_label_6:
if_label_6:

# call,printi,_t23_s0
lw	$t9, _s1__t23_s0
lw	$t9, _s1__t23_s0
move	$a0, $t9
sw	$t9, _s1__t23_s0
jal	printi

# assign,_t24_s0,0,
lw	$t9, _s1__t24_s0
li	$t8, 0
move	$t9, $t8
sw	$t9, _s1__t24_s0

# brneq,betterTax_s1,5500,if_label_7
lw	$t8, _s1_betterTax_s1
li	$t9, 5500
bne	$t8, $t9, if_label_7
sw	$t8, _s1_betterTax_s1

# assign,_t24_s0,1,
lw	$t9, _s1__t24_s0
li	$t8, 1
move	$t9, $t8
sw	$t9, _s1__t24_s0

# if_label_7:
if_label_7:

# call,printi,_t24_s0
lw	$t8, _s1__t24_s0
lw	$t8, _s1__t24_s0
move	$a0, $t8
sw	$t8, _s1__t24_s0
jal	printi

# assign,_t25_s0,0,
lw	$t8, _s1__t25_s0
li	$t9, 0
move	$t8, $t9
sw	$t8, _s1__t25_s0

# brneq,bestTax_s1,12500,if_label_8
lw	$t9, _s1_bestTax_s1
li	$t8, 12500
bne	$t9, $t8, if_label_8
sw	$t9, _s1_bestTax_s1

# assign,_t25_s0,1,
lw	$t8, _s1__t25_s0
li	$t9, 1
move	$t8, $t9
sw	$t8, _s1__t25_s0

# if_label_8:
if_label_8:

# call,printi,_t25_s0
lw	$t9, _s1__t25_s0
lw	$t9, _s1__t25_s0
move	$a0, $t9
sw	$t9, _s1__t25_s0
jal	printi

# return,,,

lw	$ra, _s1_savera
jr	$ra
######## main
main:
jal	_s1_main
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

