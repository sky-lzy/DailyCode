    addi	$a0, $zero, 5		# $a0 = $zero + 5
    xor		$v0, $zero, $zero	# $v0 = $zero ^ $zero
    jal		sum				    # jump to sum and save position to $ra
Loop:
    beq		$zero, $zero, Loop	# if $zero == $zero then Loop
sum:
    addi	$sp, $sp, -8		# $sp = $sp + -8
    sw		$ra, 4($sp)		    # 
    sw		$a0, 0($sp)		    # 
    slti	$t0, $a0, 1			# $t0 = ($a0 < 1) ? 1 : 0
    beq		$t0, $zero, L1	    # if $t0 == $zero then L1
    addi	$sp, $sp, 8			# $sp = $sp + 8
    jr		$ra					# jump to $ra
L1:
    add		$v0, $a0, $v0		# $v0 = $a0 + $v0
    addi	$a0, $a0, -1		# $a0 = $a0 + -1
    jal		sum				    # jump to sum and save position to $ra
    lw		$a0, 0($sp)		    # 
    lw		$ra, 4($sp)		    # 
    addi	$sp, $sp, 8			# $sp = $sp + 8
    add		$v0, $a0, $v0		# $v0 = $a0 + $v0
    jr		$ra					# jump to $ra
    