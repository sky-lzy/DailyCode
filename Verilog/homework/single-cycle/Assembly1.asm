    addi	$a0, $zero, 12123		# $a0 = $zero + 12123
    addiu	$a1, $zero, -12345		# $a1 = $zero + -12345
    sll		$a2, $a1, 16			# $a2 = $a1 << 16
    sra		$a3, $a2, 16			# $a3 = $a2 >> 16
    beq		$a3, $a1, L1	        # if $a3 == $a1 then L1
    lui     $a0, 22222              # $a0 = {16'd22222, 16'b0}
L1:
    add		$t0, $a2, $a0		    # $t0 = $a2 + $a0
    sra		$t1, $t0, 8			    # $t1 = $t0 >> 8
    addi	$t2, $zero, -12123		# $t2 = $zero + -12123
    slt		$v0, $a0, $t2		    # $v0 = ($a0 < $t2) ? 1 : 0
    sltu	$v1, $a0, $t2		    # $v1 = ($a0 < $t2) ? 1 : 0
Loop:
    j		Loop				    # jump to Loop
    