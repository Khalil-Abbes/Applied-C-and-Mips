# vim:sw=2 syntax=asm
.data
address: .word 0
.text
  .globl play_game_once

# Play the game once, that is
# (1) compute two moves (RPS) for the two computer players
# (2) Print (W)in (L)oss or (T)ie, whether the first player wins, looses or ties.
#
# Arguments:
#     $a0 : address of configuration in memory
#   0($a0): eca       (1 word)
#   4($a0): tape      (1 word)
#   8($a0): tape_len  (1 byte)
#   9($a0): rule      (1 byte)
#  10($a0): skip      (1 byte)
#  11($a0): column    (1 byte)
#
# Returns: Nothing, only print either character 'W', 'L', or 'T' to stdout
play_game_once:
# $ a3 = player one , $ fp = player two , $s7 = pc counter save , $k0 =  holder of $a0
  sw $ra , address + 40 # save pc to s4
  jal gen_byte      
  lw $ra , address + 40
  move $a3 $v0 #move first player
  sw $ra , address + 40 # save pc to s4 again
  jal gen_byte
  lw $ra , address + 40
  move $fp $v0 #move second player
  move $a0 $k0 # temp holder for $a0
  beq $a3 0 rock
  beq $a3 1 paper
  beq $a3 2 scissors
  
  
  paper:
  beq $fp 0 paper_rock
  beq $fp 1 paper_paper
  beq $fp 2 paper_scissors
  
  
  rock:
  beq $fp 0 rock_rock
  beq $fp 1 rock_paper
  beq $fp 2 rock_scissors
  scissors:
  beq $fp 0 scissors_rock
  beq $fp 1 scissors_paper
  beq $fp 2 scissors_scissors
  
  rock_rock:
  paper_paper:
  scissors_scissors:
  j Tie
  paper_rock:
  rock_scissors:
  scissors_paper:
  j Win
  paper_scissors:
  rock_paper:
  scissors_rock:
  j Lose
  
  
  Tie:
  
  li $a0 84 # T
  li $v0 11
  syscall
  j end
  
  Win:
  li $a0 87 # W
  li $v0 11
  syscall
  j end
  
  Lose:
  
  li $a0 76 # L
  li $v0 11
  syscall

 
  end:
  move $a0 $k0
  li $k0 0
  li $s1 0
  li $s2 0
  li $s4 0
  jr $ra
