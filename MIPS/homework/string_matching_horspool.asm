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
jal horspool

#printf
move $a0, $v0
li $v0, 1
syscall
#return 0
li $a0, 0
li $v0, 17
syscall


horspool:
##### your code here #####

addi	$sp, $sp, -16		# $sp = $sp + -16
sw		$s0, 0($sp)		    # *$sp = $s0
sw		$s1, 4($sp)		    # *($sp + 4) = $s1
sw		$s2, 8($sp)		    # *($sp + 8) = $s2
sw		$a0, 12($sp)		# *($sp + 12) = $a0

li		$s0, 0		        # $s0 = 0, cnt = 0
li		$s2, 256		    # $s2 = 256
sll		$a0, $s2, 2			# $a0 = $s2 << 2
li		$v0, 9		        # $v0 = 9
syscall
move 	$s1, $v0		    # $s1 = $v0
lw		$a0, 12($sp)		# $a0 = *($sp + 12)

li		$t0, 0		        # $t0 = 0, i = 0
li		$t8, -1		        # $t8 = -1
for_1:
sll		$t1, $t0, 2			# $t1 = $t0 << 2, 4 * i Bytes
add		$t1, $s1, $t1		# $t1 = $s1 + $t1, &table[i]
sw		$t8, 0($t1)		    # table[i] = -1
addi	$t0, $t0, 1			# $t0 = $t0 + 1, i += 1
slt		$t9, $t0, $s2		# $t9 = ($t0 < $s2) ? 1 : 0
bne		$t9, $0, for_1	    # if $t9 != $0 then for_1
end_for_1:

li		$t0, 0		        # $t0 = 0, i = 0
for_2:
add		$t1, $a3, $t0		# $t1 = $a3 + $t0, &pattern[i]
lb		$t1, 0($t1)		    # pattern[i]
sll		$t2, $t1, 2			# $t2 = $t1 << 2
add		$t2, $s1, $t2		# $t2 = $s1 + $t2, &table[pattern[i]]
sw		$t0, 0($t2)		    # table[pattern[i]] = i
addi	$t0, $t0, 1			# $t0 = $t0 + 1, i += 1
slt		$t9, $t0, $a2		# $t9 = ($t0 < $a2) ? 1 : 0
bne		$t9, $0, for_2	    # if $t9 != $0 then for_2
end_for_2:

addi	$t0, $a2, -1		# $t0 = $a2 + -1, i
while_i:
slt		$t8, $t0, $a0		# $t8 = ($t0 < $a0) ? 1 : 0
beq		$t8, $0, end_i	    # if $t8 == $0 then end_i
li		$t1, 0		        # $t1 = 0, j = 0

while_j:
slt		$t8, $t1, $a2		# $t8 = ($t1 < $a2) ? 1 : 0, j < len_pattern
subi	$t2, $a2, 1			# $t2 = $a2 - 1
sub		$t2, $t2, $t1		# $t2 = $t2 - $t1, len_pattern - 1 - j
add		$t2, $a3, $t2		# $t2 = $a3 + $t2, &pattern[len_pattern - 1 - j]
lb		$t2, 0($t2)		    # pattern[len_pattern - 1 - j]
sub		$t3, $t0, $t1		# $t3 = $t0 - $t1, i - j
add		$t3, $a1, $t3		# $t3 = $a1 + $t3, &str[i - j]
lb		$t3, 0($t3)		    # str[i - j]
li		$t9, 0		        # $t9 = 0
bne		$t2, $t3, if_1	    # if $t2 != $t3 then if_1
li		$t9, 1		        # $t9 = 1
if_1:
and		$t8, $t8, $t9		# $t8 = $t8 & $t9
beq		$t8, $0, end_j	    # if $t8 == $0 then end_j
addi	$t1, $t1, 1			# $t1 = $t1 + 1, j += 1
j		while_j				# jump to while_j
end_j:

bne		$t1, $a2, if_2	    # if $t1 != $a2 then if_2
addi	$s0, $s0, 1			# $s0 = $s0 + 1, cnt += 1
if_2:

add		$t2, $a1, $t0		# $t2 = $a1 + $t0, &str[i]
lb		$t2, 0($t2)		    # str[i]
sll		$t2, $t2, 2			# $t2 = $t2 << 2, 4 * str[i] Bytes
add		$t2, $s1, $t2		# $t2 = $s1 + $t2, &table[str[i]]
lw		$t2, 0($t2)		    # table[str[i]]
addi	$t2, $t2, 1			# $t2 = $t2 + 1, table[str[i]] + 1
sub		$t3, $a2, $t1		# $t3 = $a2 - $t1, len_pattern - j
slt		$t8, $t2, $t3		# $t8 = ($t2 < $t3) ? 1 : 0
li		$t4, 1		        # $t4 = 1
beq		$t8, $0, if_3	    # if $t8 == $0 then if_3
sub		$t4, $a2, $t2		# $t4 = $a2 - $t2
if_3:
add		$t0, $t0, $t4		# $t0 = $t0 + $t4

j		while_i				# jump to while_i
end_i:

move 	$v0, $s0		    # $v0 = $s0
lw		$s2, 8($sp)		    # $s2 = *($sp + 8)
lw		$s1, 4($sp)		    # $s2 = *($sp + 4)
lw		$s0, 0($sp)		    # $s2 = *$sp
addi	$sp, $sp, 12		# $sp = $sp + 12
jr		$ra					# jump to $ra
