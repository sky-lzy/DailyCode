add		$v0, $0, $0		    # $v0 = $0 + $0
addi	$s0, $0, 41			# $s0 = $0 + 41
addi	$s1, $0, 4			# $s1 = $0 + 4
addi	$s2, $0, 0			# $s2 = $0 + 0
addi	$s3, $0, 100		# $s3 = $0 + 100

sub		$, 0x02FA           # 
addi	$s4, $s4, 0xF080			# $s4 = $s4 + 0xF080
, $s0, $s1		# $, 0x02FA         # 
addi	$s4, $s4, 0xF080			# $s4 = $s4 + 0xF080
 = $s0 - $s1
add		$t0, $0, $0		    # $t0 = $0 + $0

for_i:
sub		$t8, $t0, $, 0x02FA         # 
addi	$s4, $s4, 0xF080			# $s4 = $s4 + 0xF080
		# $t8 = $t0 - $, 0x02FA         # 
addi	$s4, $s4, 0xF080			# $s4 = $s4 + 0xF080

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

show:
add		$t0, $0, $0		    # $t0 = $0 + $0
addi	$s0, $0, 256		# $s0 = $0 + 256 (0x0100)
addi	$s1, $0, 15			# $s1 = $0 + 15 (0x000F)
lui     $s2, 16384          # (0x4000)
addi	$s2, $s2, 16		# $s2 = $s2 + 16 (0x0010)
add		$s3, $v0, $0		# $s3 = $v0 + $0
lui     $s4, 0x017D         # 
addi	$t1, $0, 0x7840		# $t1 = $0 + 0x7840
or		$s4, $s4, $t1		# $s4 = $s4 | $t1

for:
addi	$t8, $t0, -3		# $t8 = $t0 + -3
bgtz	$t8, end_for	    # if $t8 > 0 then end_for

addi	$t1, $0, 0			# $t1 = $0 + 0
and		$t2, $s3, $s1		# $t2 = $s3 & $s1
beq		$t2, $t1, L0	    # if $t2 == $t1 then L0
addi	$t1, $t1, 1			# $t1 = $t1 + 1
beq		$t2, $t1, L1	    # if $t2 == $t1 then L1
addi	$t1, $t1, 1			# $t1 = $t1 + 1
beq		$t2, $t1, L2	    # if $t2 == $t1 then L2
addi	$t1, $t1, 1			# $t1 = $t1 + 1
beq		$t2, $t1, L3	    # if $t2 == $t1 then L3
addi	$t1, $t1, 1			# $t1 = $t1 + 1
beq		$t2, $t1, L4	    # if $t2 == $t1 then L4
addi	$t1, $t1, 1			# $t1 = $t1 + 1
beq		$t2, $t1, L5	    # if $t2 == $t1 then L5
addi	$t1, $t1, 1			# $t1 = $t1 + 1
beq		$t2, $t1, L6	    # if $t2 == $t1 then L6
addi	$t1, $t1, 1			# $t1 = $t1 + 1
beq		$t2, $t1, L7	    # if $t2 == $t1 then L7
addi	$t1, $t1, 1			# $t1 = $t1 + 1
beq		$t2, $t1, L8	    # if $t2 == $t1 then L8
addi	$t1, $t1, 1			# $t1 = $t1 + 1
beq		$t2, $t1, L9	    # if $t2 == $t1 then L9
addi	$t1, $t1, 1			# $t1 = $t1 + 1
beq		$t2, $t1, LA	    # if $t2 == $t1 then LA
addi	$t1, $t1, 1			# $t1 = $t1 + 1
beq		$t2, $t1, LB	    # if $t2 == $t1 then LB
addi	$t1, $t1, 1			# $t1 = $t1 + 1
beq		$t2, $t1, LC	    # if $t2 == $t1 then LC
addi	$t1, $t1, 1			# $t1 = $t1 + 1
beq		$t2, $t1, LD	    # if $t2 == $t1 then LD
addi	$t1, $t1, 1			# $t1 = $t1 + 1
beq		$t2, $t1, LE	    # if $t2 == $t1 then LE
j		LF				    # jump to LF

L0:
addi	$t3, $0, 63			# $t3 = $0 + 63
j		L_end				# jump to L_end
L1:
addi	$t3, $0, 6			# $t3 = $0 + 6
j		L_end				# jump to L_end
L2:
addi	$t3, $0, 91			# $t3 = $0 + 91
j		L_end				# jump to L_end
L3:
addi	$t3, $0, 79			# $t3 = $0 + 79
j		L_end				# jump to L_end
L4:
addi	$t3, $0, 102		# $t3 = $0 + 102
j		L_end				# jump to L_end
L5:
addi	$t3, $0, 109		# $t3 = $0 + 109
j		L_end				# jump to L_end
L6:
addi	$t3, $0, 125		# $t3 = $0 + 125
j		L_end				# jump to L_end
L7:
addi	$t3, $0, 7			# $t3 = $0 + 7
j		L_end				# jump to L_end
L8:
addi	$t3, $0, 127		# $t3 = $0 + 127
j		L_end				# jump to L_end
L9:
addi	$t3, $0, 111		# $t3 = $0 + 111
j		L_end				# jump to L_end
LA:
addi	$t3, $0, 119		# $t3 = $0 + 119
j		L_end				# jump to L_end
LB:
addi	$t3, $0, 124		# $t3 = $0 + 124
j		L_end				# jump to L_end
LC:
addi	$t3, $0, 57			# $t3 = $0 + 57
j		L_end				# jump to L_end
LD:
addi	$t3, $0, 94			# $t3 = $0 + 94
j		L_end				# jump to L_end
LE:
addi	$t3, $0, 121		# $t3 = $0 + 121
j		L_end				# jump to L_end
LF:
addi	$t3, $0, 113		# $t3 = $0 + 113

L_end:
or		$t3, $t3, $s0		# $t3 = $t3 | $s0
sw		$t3, 0($s2)		    # 

add		$t4, $0, $0		    # $t4 = $0 + $0
for_count:
slt		$t9, $t4, $s4		# $t9 = ($t4 < $s4) ? 1 : 0
beq		$t9, $0, end_count	# if $t9 == $0 then end_count
addi	$t4, $t4, 1			# $t4 = $t4 + 1
j		for_count			# jump to for_count

end_count:

addi	$t0, $t0, 1			# $t0 = $t0 + 1
sll		$s0, $s0, 1			# $s0 = $s0 << 1
srl		$s3, $s3, 4			# $s3 = $s3 >> 4
j		for				    # jump to for
end_for:

j		show				# jump to show
