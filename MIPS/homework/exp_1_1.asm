.data
input_file: .asciiz "a.in"
output_file: .asciiz "a.out"

.text
main:
    # 申请内存
    li		$a0, 8		    # $a0 = 8, 申请8个字节内存
    li		$v0, 9		    # $v0 = 9
    syscall
    move 	$s7, $v0	    # $s7 = $v0, 保存地址

    # 打开文件"a.in"
    la		$a0, input_file	# 读取文件名
    li		$a1, 0		    # $a1 = 0, 打开文件模式：只读
    li		$a2, 0		    # $a2 = 0
    li		$v0, 13		    # $v0 = 13
    syscall
    move 	$a0, $v0		# $a0 = $v0, 载入文件描述符

    # 读取文件"a.in"
    move 	$a1, $s7		# $a1 = $s7, 保存数据地址
    li		$a2, 8		    # $a2 = 8, 读取8Byte
    li		$v0, 14		    # $v0 = 14
    syscall

    # 关闭文件"a.in"
    li		$v0, 16		    # $v0 = 16
    syscall

    # 打开文件"a.out"
    la      $a0, output_file# 写入文件名
    li		$a1, 1		    # $a1 = 1, 打开文件模式：写入
    li		$a2, 0		    # $a2 = 0
    li		$v0, 13		    # $v0 = 13
    syscall
    move 	$a0, $v0		# $a0 = $v0, 载入文件描述符

    # 写入数据"a.out"
    move 	$a1, $s7		# $a1 = $s7, 输出数据
    li		$a2, 8		    # $a2 = 8, 写入8Byte
    li		$v0, 15		    # $v0 = 15, 写入文件
    
    syscall

    # 关闭文件"a.out"
    li		$v0, 16		    # $v0 = 16
    
    syscall

    # 从键盘读入数据
    li		$v0, 5		    # $v0 = 5
    syscall
    move 	$t0, $v0		# $t0 = $v0, 读入数据
    addi	$t0, $t0, 1		# $t0 = $t0 + 1
    

    # 输出数据
    move 	$a0, $t0	    # $a0 = $t0, 输出参数
    li		$v0, 1		    # $v0 = 1
    
    syscall

    # 退出程序
    li		$v0, 17		    # $v0 = 17
    
    syscall