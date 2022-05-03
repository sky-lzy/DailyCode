.text
main:
    # 读取n
    li		$v0, 5		    # $v0 = 5, 读取数据
    syscall
    move 	$s0, $v0	    # $s0 = $v0

    # 申请内存
    add		$a0, $s0, $s0	# $a0 = $s0 + $s0
    add		$a0, $a0, $a0	# $a0 = $a0 + $a0, 4 * n
    move 	$s6, $a0		# $s6 = $a0, 保存数组字节数
    li		$v0, 9		    # $v0 = 9, 申请内存
    syscall
    move 	$s7, $v0		# $s7 = $v0, 保存内存空间的地址
    
    # 读入数据
    li		$t0, 0		    # $t0 = 0, i = 0
    move 	$t1, $s7		# $t1 = $s7, 内存地址
    for1:
    li		$v0, 5		    # $v0 = 5, 读入数据
    syscall
    sw		$v0, 0($t1)		# 存储数据
    addi	$t0, $t0, 1		# $t0 = $t0 + 1, i = i + 1
    addi	$t1, $t1, 4		# $t1 = $t1 + 4, a = a + 4
    slt		$t2, $t0, $s0	# $t2 = ($t0 < $s0) ? 1 : 0
    bne		$t2, $0, for1	# if $t2 != $0 then for
    
    # 交换数据
    li		$t0, 0		    # $t0 = 0, i = 0
    move 	$t1, $s7	    # $t1 = $s7, 内存首地址
    add		$t2, $s7, $s6	# $t2 = $s7 + $s6, 内存尾地址
    subi	$t2, $t2, 4		# $t2 = $t2 - 4
    srl		$t3, $s0, 1		# $t3 = $s0 >> 1, n / 2
    for2:
    lw		$t4, 0($t1)		# 
    lw		$t5, 0($t2)		# 
    sw		$t5, 0($t1)		# 
    sw		$t4, 0($t2)		# 
    addi	$t0, $t0, 1		# $t0 = $t0 + 1, i = i + 1
    addi	$t1, $t1, 4		# $t1 = $t1 + 4, 首地址加4
    subi	$t2, $t2, 4		# $t2 = $t2 - 4, 尾地址减4
    slt		$t6, $t0, $t3	# $t6 = ($t0 < $t3) ? 1 : 0
    bne		$t6, $0, for2	# if $t6 != $0 then for2
    
    # 打印数据
    li		$t0, 0		    # $t0 = 0, i = 0
    move 	$t1, $s7		# $t1 = $s7, 内存首地址
    for3:
    li		$v0, 1		    # $v0 = 1, 打印整数
    lw		$a0, 0($t1)		# 
    syscall
    addi	$t0, $t0, 1		# $t0 = $t0 + 1, i = i + 1
    addi	$t1, $t1, 4		# $t1 = $t1 + 4
    slt		$t2, $t0, $s0	# $t2 = ($t0 < $s0) ? 1 : 0
    bne		$t2, $0, for3	# if $t2 != $0 then for3
    
    # 退出程序
    li		$v0, 17		    # $v0 = 17
    syscall
    