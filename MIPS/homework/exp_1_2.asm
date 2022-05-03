.text
main:
    # 读入数据
    li		$v0, 5		    # $v0 = 5, 读取一个整数
    syscall
    move 	$s0, $v0	    # $s0 = $v0, 保存i
    li		$v0, 5		    # $v0 = 5
    syscall
    move 	$s1, $v0		# $s1 = $v0，保存j

    # if(i < 0)
    slt		$t0, $s0, $0	# $t0 = ($s0 < $0) ? 1 : 0
    beq		$t0, $0, end_i	# if $t0 == $0 then end_i
    sub		$s0, $0, $s0	# $s0 = $0 - $s0, i = -i
    end_i:

    # if(j < 0)
    slt		$t0, $s1, $0	# $t0 = ($s1 < $0) ? 1 : 0
    beq		$t0, $0, end_j	# if $t0 == $0 then end_j
    sub		$s1, $0, $s1	# $s1 = $0 - $s1, j = -j
    end_j:
    
    # 循环
    move 	$t1, $0		    # $t1 = $0, temp = 0
    beq		$s1, $0, endfor	# if $s1 == $0 then endfor
    for:
    addi	$s0, $s0, 1		# $s0 = $s0 + 1, i += 1
    addi	$t1, $t1, 1		# $t1 = $t1 + 1, temp++
    slt		$t0, $t1, $s1	# $t0 = ($t1 < $s1) ? 1 : 0, temp < j ?
    bne		$t0, $0, for	# if $t0 != $0 then for
    endfor:

    # 输出
    move 	$a0, $s0		# $a0 = $s0, i
    li		$v0, 1		    # $v0 = 1, 输出i
    syscall

    # 退出程序
    li		$v0, 17		    # $v0 = 17
    syscall
    