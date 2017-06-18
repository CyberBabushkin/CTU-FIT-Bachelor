-- knihovna typù pro práci
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- definice vstupù a výstupù - vstupy a, b, c, výstupy f
entity algebra is
    Port ( en  : in std_logic;
			  q2 : in std_logic;
           q1 : in std_logic;
           q0 : in std_logic;
           s2 : out std_logic;
			  s1 : out std_logic;
			  s0 : out std_logic;
			  y  : out std_logic);
end algebra;

architecture Behavioral of algebra is
begin
  s2 <= ((not en) and (not q1)) or ((not en) and q0) or (q0 and q2);
  s1 <= (en and q0 and (not q1)) or ((not q0) and q1 and (not q2)) or (en and q2 and q1);
  s0 <= ((not q0) and (not q1) and en) or ((not en) and q1 and (not q2)) or (q2 and (not en) and (not q1));
  y  <= ((not q2) and q1 and q0 and en) or ((not q0) and q1 and q2 and (not en));
  
end Behavioral;
