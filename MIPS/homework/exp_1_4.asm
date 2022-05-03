.text
Hanoi:
    # 保存参数
    addi	$sp, $sp, -4		# $sp = $sp + -4
    sw		$ra, 0($sp)		    #

    addi	$t0, $0, 1			# $t0 = $0 + 1
    bne		$a0, $t0, Next  	# if $a0 != $t0 then Next
    addi	$v0, $0, 1			# $v0 = $0 + 1
    jr		$ra					# jump to $ra
    
Next:
    addi	$sp, $sp, -8		# $sp = $sp + -8
    sw		$a0, 4($sp)		    # 
    sw		$ra, 0($sp)		    # 
    addi	$s1, $0, 1			# $s1 = $0 + 1
    addi	$a0, $a0, -1		# $a0 = $a0 + -1
    jal		Hanoi				# jump to Hanoi and save position to $ra
    add 	$s1, $v0, $s1		# $s1 = $v0 + $s1
    add		$s1, $v0, $s1		# $s1 = $v0 + $s1
    add		$v0, $s1, $0		# $v0 = $s1 + $0
    lw		$ra, 0($sp)		    # 
    lw		$a0, 4($sp)		    # 
    addi	$sp, $sp, 4			# $sp = $sp + 4
    jr		$ra					# jump to $ra
    