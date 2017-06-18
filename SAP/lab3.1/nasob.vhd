-- knihovna typù pro práci
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- definice vstupù a výstupù - vstupy a, b, c, výstupy f
entity nasob is
    Port ( m : in std_logic;
			  n : in std_logic;
           o : in std_logic;
           p : in std_logic;
           x : out std_logic;
			  y : out std_logic;
			  z : out std_logic;
			  t : out std_logic);
end nasob;

architecture Behavioral of nasob is
begin
  x <= m and n and o and p;
  y <= (o and (not n) and m) or (o and m and (not p));
  z <= (m and p and (not (o and n))) or (n and o and (not (p and m)));
  t <= p and n;
end Behavioral;
