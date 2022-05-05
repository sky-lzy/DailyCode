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
jal brute_force

#printf
move $a0, $v0
li $v0, 1
syscall
#return 0
li $a0, 0
li $v0, 17
syscall


brute_force:
##### your code here #####

li		$t0, 0		        # $t0 = 0, cnt = 0
li		$t1, 0		        # $t1 = 0, i = 0
sub		$t8, $a0, $a2	    # $t8 = $a0 - $a2
addi	$t8, $t8, 1			# $t8 = $t8 + 1

for_i:
li		$t2, 0		        # $t2 = 0, j = 0

for_j:
add		$t3, $t1, $t2		# $t3 = $t1 + $t2, i + j
add		$t3, $a1, $t3		# $t3 = $a1 + $t3, &str[i + j]
lb		$t3, 0($t3)		    # str[i + j]
add		$t4, $a3, $t2		# $t4 = $a3 + $t2, &pattern[j]
lb		$t4, 0($t4)		    # pattern[j]
bne		$t3, $t4, end_for_j	# if $t3 != $t4 then end_for_j
addi	$t2, $t2, 1			# $t2 = $t2 + 1, j += 1
slt		$t9, $t2, $a2		# $t9 = ($t2 < $a2) ? 1 : 0
bne		$t9, $0, for_j  	# if $t9 != $0 then for_j
end_for_j:

bne		$t2, $a2, end_if_i	# if $t2 != $a2 then end_if_i
addi	$t0, $t0, 1			# $t0 = $t0 + 1, cnt += 1
end_if_i:

addi	$t1, $t1, 1			# $t1 = $t1 + 1, i += 1
slt		$t9, $t1, $t8		# $t9 = ($t1 < $t8) ? 1 : 0
bne		$t9, $0, for_i  	# if $t9 != $0 then for_i
end_for_i:

move 	$v0, $t0		    # $v0 = $t0
jr		$ra					# jump to $ra
