# vim:sw=2 syntax=asm
.data

.text
  .globl gen_byte, gen_bit

# Arguments:
#     $a0 : address of configuration in memory
#   0($a0): eca       (1 word)
#   4($a0): tape      (1 word)
#   8($a0): tape_len  (1 byte)
#   9($a0): rule      (1 byte)
#  10($a0): skip      (1 byte)
#  11($a0): column    (1 byte)
#
# Return value:
#  Compute the next valid byte (00, 01, 10) and put into $v0
#  If 11 would be returned, produce two new bits until valid
#
gen_byte:
loop:

# $ a1 = first bit , $t7 = second bit , $s4 = pc counter
  move $s4 $ra # backup old ra
  jal gen_bit # get first bit
  move $ra $s4 # bring back new ra
  move $a1 $v0 # move to callee save
  move $s4 $ra # backup old ra
  jal gen_bit # make second bit
  move $ra $s4 # bring back new ra
  move $t7 $v0 # move second bit  
 
 beq $a1 0 Zero
 beq $a1 1 One
 
 
 One:
 beq $t7 0 One_Zero
 li $a1 0
 li $t7 0
 j loop


 Zero:
  beq $t7 1 Zero_One
  beq $t7 0 Zero_Zero
 
 One_Zero:
 li $v0 2
 j end
 
 Zero_Zero:
 li $v0 0
 j end
 
 Zero_One:
 li $v0 1
 j end 
 
 
 
 
  
  end:
     
  li $a1 0
  li $t7 0 
  li $s4 0
  jr $ra

# Arguments:
#     $a0 : address of configuration in memory
#   0($a0): eca       (1 word)
#   4($a0): tape      (1 word)
#   8($a0): tape_len  (1 byte)
#   9($a0): rule      (1 byte)
#  10($a0): skip      (1 byte)
#  11($a0): column    (1 byte)
#
# Return value:
#  Look at the field {eca} and use the associated random number generator to generate one bit.
#  Put the computed bit into $v0
#
gen_bit: # $a2  = load eca 0 or 1 , $s5 = skip counter , $s6 = column  , $t9 = backup ra , $s7 = shifting position
bgt $k1, 0 ,again    # $t8 = tape , t9 = backup ra , $k0 = og address , $k1 = checker for address
lw $a2 , 0($a0) 
move $k0 $a0
addi  $k1 $k1 1
  
 again:
 move $a0 $k0
beqz $a2 rng 
lw $t8 ,4($a0)
lb $s5 , 10($a0)
lb $s6 , 11($a0)
lb $s7 , 8($a0)
add $s7 $s7 -1
sub  $s7 $s7 $s6
loop_eca:
beq $s5 0 end_eca
move $t9 $ra
jal simulate_automaton
move $ra $t9
add $s5 $s5 -1
j loop_eca

end_eca:
lw $t8 , 4($a0)
srlv $t8 $t8 $s7
andi $t8 $t8 1
move $v0 $t8
li $a2 0
li $s5 0
li $s6 0
li $s7 0
li $t8 0
li $t9 0
li $k1 0
jr $ra




rng:
li $a0 0
li $v0 41
syscall
andi $v0 $a0 1

  jr $ra
