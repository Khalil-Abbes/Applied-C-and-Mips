# vim:sw=2 syntax=asm
.text
  .globl simulate_automaton, print_tape

# Simulate one step of the cellular automaton
# Arguments:
#     $a0 : address of configuration in memory
#   0($a0): eca       (1 word)
#   4($a0): tape      (1 word)
#   8($a0): tape_len  (1 byte)
#   9($a0): rule      (1 byte)
#  10($a0): skip      (1 byte)
#  11($a0): column    (1 byte)
#
# Returns: Nothing, but updates the tape in memory location 4($a0)
simulate_automaton:
 #$t0 = tape , $t1 length of tape for shifting , $t2 = rule , $t3 =new updated tape , $t4 apply rule or no
 lw $t0 , 4($a0)  # $t5 = shift + 1  , t6 = shift + 1   , t7 =                with shift and rule       		  # ( $t4 = $t1 + 1
 lb $t1 , 8($a0)  # s1 = value of shift t5 , s2 = value of shift t0 , s3 value shift t7
 lb $t2 , 9($a0)
 #first digit set up
 beq $t1 1 length_one
add $t1 $t1 -1 # adjust for shifting
move $v0 $t1 ##backup of og length - 1
li $t5 0 # set up msb shift 
add $t6 $t1 -1 # set up msb + 1 to the right
 and $s1 $t0 1 # find rightmost num first time
 srlv $s2 $t0 $t1 #find msb
 and $s2 $s2 1
srlv $s3 $t0 $t6 # find 2nd msb
and $s3 $s3 1

#set up for loop until last time
 lb $t1 , 8($a0)
 move $t5 $t1
 add $t1 $t1 -1
 add $t6 $t1 -1
 j first_time
 loop_simulate: # works until we reach last time
 add $t5 $t5 -1
 add $t1 $t1 -1
 add $t6 $t6 -1
  beq $t6 -421 end_simulate
 beq $t6 -1 last_time
 # do it one last time manually since numbers get messed up
 j normal_check
 last_time:
 li $t5 1
 li $t1 0
 move $t6 $v0
 srlv $s1 $t0 $t5
and $s1 $s1 1
srlv $s2 $t0 $t1
and $s2 $s2 1
srlv $s3 $t0 $t6
and $s3 $s3 1
li $t6 -420
j first_time
 normal_check:
 srlv $s1 $t0 $t5
and $s1 $s1 1
srlv $s2 $t0 $t1
and $s2 $s2 1
srlv $s3 $t0 $t6
and $s3 $s3 1
first_time:
 beq $s1 1 l
 beq $s1 0 O

 
 O:
 beq $s2 0 OO
 beq $s2 1 Ol
 
 
 l:
 beq $s2 0 lO
 beq $s2 1 ll
 
 OO:
 beq $s3 0 OOO
 beq $s3 1 OOl
 Ol:
 beq $s3 0 OlO
 beq $s3 1 Oll
 lO:
 beq $s3 0 lOO
 beq $s3 1 lOl
 
 ll:
 beq $s3 0 llO
 beq $s3 1 lll
 
 lll:
 srl $t4 $t2 7
 and $t4 $t4 1
 beq $t4 1 yes
 beq $t4 0 no
 llO:
 srl $t4 $t2 6
 and $t4 $t4 1
 beq $t4 1 yes
 beq $t4 0 no
 lOl:
 srl $t4 $t2 5
 and $t4 $t4 1
 beq $t4 1 yes
 beq $t4 0 no
 lOO:
 srl $t4 $t2 4
 and $t4 $t4 1
 beq $t4 1 yes
 beq $t4 0 no
 Oll:
 srl $t4 $t2 3
 and $t4 $t4 1
 beq $t4 1 yes
 beq $t4 0 no
 OlO:
 srl $t4 $t2 2
 and $t4 $t4 1
 beq $t4 1 yes
 beq $t4 0 no
 OOl:
 srl $t4 $t2 1
 and $t4 $t4 1
 beq $t4 1 yes
 beq $t4 0 no
 OOO:
 and $t4 $t2 1
 beq $t4 1 yes
 beq $t4 0 no
 
 yes:
 beq $t6 -420 yes_skip
 add $t3 $t3 1
 sll $t3 $t3 1
 j loop_simulate
 
 yes_skip:
 add $t3 $t3 1
 j loop_simulate
 
 no:
 beq $t6 -420 no_skip
 sll $t3 $t3 1
 j loop_simulate
 
 
 no_skip:
 j loop_simulate
 
 
 
length_one:
 li $t1 0
 andi $s1 $t0 1
 move $s2 $s1
 move $s3 $s1
 li $t6 -420
 j first_time

 end_simulate:
 sw $t3 , 4($a0)
 li $t1 0
 li $t2 0
 li $t3 0
 li $t5 0
 li $t6 0
 li $s1 0
 li $s2 0
 li $s3 0
 
 
 
  jr $ra

# Print the tape of the cellular automaton
# Arguments:
#     $a0 : address of configuration in memory
#   0($a0): eca       (1 word)
#   4($a0): tape      (1 word)
#   8($a0): tape_len  (1 byte)
#   9($a0): rule      (1 byte)
#  10($a0): skip      (1 byte)
#  11($a0): column    (1 byte)
#
# Return nothing, print the tape as follows:
#   Example:
#       tape: 42 (0b00101010)
#       tape_len: 8
#   Print:  
#       __X_X_X_
print_tape:  ## $t0 = backup tape , $t1 = tape length  , $t2 = temporary and result , $t3 =  tape
lb $t1 ,8($a0) #$k0 = backup address of a0
add $t1 $t1 -1 #adjust tape length
lw $t0 ,4($a0)
move $k0 $a0
loop:
beq  $t1 -1 end_print
move $t3 $t0
srlv $t2 $t3 $t1
andi $t2 $t2 1
beq $t2 1 One
  
  Zero:
li $v0 11
li $a0 95
syscall
add $t1 $t1 -1
 j loop
 
 One: 
 li $v0 11
 li $a0 88
 syscall
 add $t1 $t1 -1
  j loop
end_print:
li $v0 11
li $a0 10
syscall
move $a0 $k0
li $t0 0
li $t1 0
li $t2 0
li $t3 0
jr $ra
