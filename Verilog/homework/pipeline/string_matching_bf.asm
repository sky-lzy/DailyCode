add		$v0, $0, $0		    # $v0 = $0 + $0
addi	$s0, $0, 41			# $s0 = $0 + 41
addi	$s1, $0, 4			# $s1 = $0 + 4
addi	$s2, $0, 0			# $s2 = $0 + 0
addi	$s3, $0, 100		# $s3 = $0 + 100

sub		$s4, $s0, $s1		# $s4 = $s0 - $s1
add		$t0, $0, $0		    # $t0 = $0 + $0

for_i:
sub		$t8, $t0, $s4		# $t8 = $t0 - $s4
bgtz    $t8, end_i          # if $t8 > 0 then end_i
add		$t1, $0, $0		    # $t1 = $0 + $0

for_j:
sub		$t8, $s1, $t1		# $t8 = $s1 - $t1
blez	$t8, end_j          # if $t0 <= $t1 then target

add		$t2, $t0, $t1		# $t2 = $t0 + $t1
add		$t2, $s2, $t2		# $t2 = $s2 + $t2
lbu		$t2, 0($t2)		    # 
add		$t3, $s3, $t1		# $t3 = $s3 + $t1
lbu		$t3, 0($t3)		    # 
bne		$t2, $t3, end_j	    # if $t2 != $t3 then end_j
addi	$t1, $t1, 1			# $t1 = $t1 + 1
j		for_j				# jump to for_j
end_j:

addi	$t0, $t0, 1			# $t0 = $t0 + 1
bne		$t1, $s1, for_i	    # if $t1 != $s1 then for_i
addi	$v0, $v0, 1			# $v0 = $v0 + 1
j		for_i				# jump to for_i
end_i:

lui     $t8, 16384          # 0x4000
addi	$t9, $0, 347		# $t9 = $0 + 347 (0x015B)
sw		$t9, 16($t8)		# 
j		end_i				# jump to end_i
