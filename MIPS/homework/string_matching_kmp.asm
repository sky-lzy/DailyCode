.data
str: .space 512
pattern: .space 512
filename: .asciiz "test.dat"

.text
main:
#fopen
la $a0, filename #load filename
li $a1, 0 #flag
li $a2, 0 #mode
li $v0, 13 #open file syscall index
syscall

#read str
move $a0, $v0 #load file description to $a0
la $a1, str
li $a2, 1
li $s0, 0 #len_pattern = 0
read_str_entry:
slti $t0, $s0, 512
beqz $t0, read_str_exit
li $v0, 14 #read file syscall index
syscall
lb $t0, 0($a1)
addi $t1, $zero, '\n'
beq $t0, $t1, read_str_exit
addi $a1, $a1, 1
addi $s0, $s0, 1
j read_str_entry
read_str_exit:

#read pattern
la $a1, pattern
li $a2, 1
li $s1, 0 #len_pattern = 0
read_pattern_entry:
slti $t0, $s1, 512
beqz $t0, read_pattern_exit
li $v0, 14 #read file syscall index
syscall
lb $t0, 0($a1)
addi $t1, $zero, '\n'
beq $t0, $t1, read_pattern_exit
addi $a1, $a1, 1
addi $s1, $s1, 1
j read_pattern_entry
read_pattern_exit:

#close file
li $v0, 16 #close file syscall index
syscall

#call brute_force
move $a0, $s0
la $a1, str
move $a2, $s1
la $a3, pattern
jal kmp

#printf
move $a0, $v0
li $v0, 1
syscall
#return 0
li $a0, 0
li $v0, 17
syscall


kmp:
##### your code here #####

addi	$sp, $sp, -28       # $sp = $sp + -28
sw		$s0, 0($sp)		    # 
sw		$s1, 4($sp)		    # 
sw		$s2, 8($sp)		    # 
sw		$s3, 12($sp)		# 
sw		$s4, 16($sp)		# 
sw		$s5, 20($sp)		# 
sw		$s6, 24($sp)		# 

li		$s0, 0		        # $s0 = 0, cnt = 0
move 	$s2, $a0		    # $s2 = $a0, len_str
move 	$s3, $a1		    # $s3 = $a1, *str
move 	$s4, $a2		    # $s4 = $a2, len_pattern
move 	$s5, $a3		    # $s5 = $a3, *pattern
move 	$s6, $ra		    # $s6 = $ra
sll		$a0, $s4, 16		# $a0 = $s4 << 16
li		$v0, 9		        # $v0 = 9
syscall
move 	$s1, $v0		    # $s1 = $v0, *next

move 	$a0, $s1		    # $a0 = $s1
move 	$a1, $s4		    # $a1 = $s4
move 	$a2, $s5		    # $a2 = $s5
jal		generateNext		# jump to generateNext and save position to $ra

li		$t0, 0		        # $t0 = 0, i = 0
li		$t1, 0		        # $t1 = 0, j = 0
while:
slt		$t8, $t0, $s2		# $t8 = ($t0 < $s2) ? 1 : 0
beq		$t8, $0, end_while	# if $t8 == $0 then end_while

add		$t2, $s5, $t1		# $t2 = $s5 + $t1, &pattern[j]
lb		$t2, 0($t2)		    # pattern[j]
add		$t3, $s3, $t0		# $t3 = $s3 + $t0, &str[i]
lb		$t3, 0($t3)		    # str[i]
bne		$t2, $t3, else_1	# if $t2 != $t3 then else_1

if_1:
subi	$t2, $s4, 1			# $t2 = $s4 - 1, len_pattern - 1
bne		$t1, $t2, else_2	# if $t1 != $t2 then else_2

if_2:
addi	$s0, $s0, 1			# $s0 = $s0 + 1
subi	$t2, $s4, 1			# $t2 = $s4 - 1, len_pattern - 1
sll		$t3, $t2, 2			# $t3 = $t2 << 2, 4*(len_pattern - 1) Bytes
add		$t3, $s1, $t3		# $t3 = $s1 + $t3, &next[len_pattern - 1]
lw		$t1, 0($t3)		    # j = next[len_pattern - 1]
addi	$t0, $t0, 1			# $t0 = $t0 + 1
j		end_if_2			# jump to end_if_2

else_2:
addi	$t0, $t0, 1			# $t0 = $t0 + 1, i += 1
addi	$t1, $t1, 1			# $t1 = $t1 + 1, j += 1

end_if_2:
j		end_if_1			# jump to end_if_1

else_1:
slt		$t8, $0, $t1		# $t8 = ($0 < $t1) ? 1 : 0
beq		$t8, $0, else_3 	# if $t8 == $0 then else_3

if_3:
subi	$t2, $t1, 1			# $t2 = $t1 - 1, j - 1
sll		$t2, $t2, 2			# $t2 = $t2 << 2, 4 * (j - 1) Bytes
add		$t2, $s1, $t2		# $t2 = $s1 + $t2, &next[j - 1]
lw		$t1, 0($t2)		    # j = next[j - 1]
j		end_if_3			# jump to end_if_3

else_3:
addi	$t0, $t0, 1			# $t0 = $t0 + 1, i += 1

end_if_3:
end_if_1:
j		while				# jump to while
end_while:

move 	$v0, $s0		    # $v0 = $s0
move 	$ra, $s6		    # $ra = $s6
lw		$s0, 0($sp)		    # 
lw		$s1, 4($sp)		    # 
lw		$s2, 8($sp)		    # 
lw		$s3, 12($sp)		# 
lw		$s4, 16($sp)		# 
lw		$s5, 20($sp)		# 
lw		$s6, 24($sp)		# 
addi	$sp, $sp, 28		# $sp = $sp + 28
jr		$ra					# jump to $ra


generateNext:

bne		$a1, $0, end_4	    # if $a1 != $0 then end_4
li		$v0, 1		        # $v0 = 1
jr		$ra					# jump to $ra
end_4:

sw		$0, 0($a0)		    # next[0] = 0
li		$t0, 1		        # $t0 = 1
li		$t1, 0		        # $t1 = 0

while_2:
slt		$t8, $t0, $a1		# $t8 = ($t0 < $a1) ? 1 : 0
beq		$t8, $0, end_while_2# if $t8 == $0 then end_while_2

add		$t2, $a2, $t0		# $t2 = $a2 + $t0, &pattern[i]
lb		$t2, 0($t2)		    # pattern[i]
add		$t3, $a2, $t1		# $t3 = $a2 + $t1, &pattern[j]
lb		$t3, 0($t3)		    # pattern[j]
bne		$t2, $t3, else_5	# if $t2 != $t3 then else_5

if_5:
sll		$t2, $t0, 2			# $t2 = $t0 << 2, 4 * i Bytes
add		$t2, $a0, $t2		# $t2 = $a0 + $t2, &next[i]
addi	$t3, $t1, 1			# $t3 = $t1 + 1, j + 1
sw		$t3, 0($t2)		    # next[i] = j + 1
addi	$t0, $t0, 1			# $t0 = $t0 + 1, i += 1
addi	$t1, $t1, 1			# $t1 = $t1 + 1, j += 1
j		end_if_5			# jump to end_if_5

else_5:
slt		$t8, $0, $t1		# $t8 = ($0 < $t1) ? 1 : 0
beq		$t8, $0, else_6 	# if $t8 == $0 then else_6

if_6:
subi	$t2, $t1, 1			# $t2 = $t1 - 1, j - 1
sll		$t2, $t2, 2			# $t2 = $t2 << 2, 4 * (j - 1) Bytes
add		$t2, $a0, $t2		# $t2 = $a0 + $t2, &next[j - 1]
lw		$t1, 0($t2)		    # j = next[j - 1]
j		end_if_6			# jump to end_if_6

else_6:
sll		$t2, $t0, 2			# $t2 = $t0 << 2, 4 * i Bytes
add		$t2, $a0, $t2		# $t2 = $a0 + $t2, next[i]
sw		$0, 0($t2)		    # next[i] = 0
addi	$t0, $t0, 1			# $t0 = $t0 + 1, i += 1

end_if_6:
end_if_5:
j		while_2				# jump to while_2
end_while_2:

move 	$v0, $0		        # $v0 = $0
jr		$ra					# jump to $ra
