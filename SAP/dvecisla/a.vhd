-- knihovna typù pro práci
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- definice vstupù a výstupù - vstupy a, b, c, výstupy f
entity algebra is
    Port ( x : in std_logic;
			  y : in std_logic;
           z : in std_logic;
           t : in std_logic;
           a : out std_logic;
			  b : out std_logic;
			  c : out std_logic;
			  d : out std_logic;
			  e : out std_logic;
			  f : out std_logic;
			  g : out std_logic);
end algebra;

architecture Behavioral of algebra is
begin
  a <= not ((x and (not z)) or (t and y) or ((not x) and z) or ((not t) and (not y)));
  b <= not ( (not y) or ((not z) and (not t)) or (x and (not z)) or (x and (not t)) or (z and t and (not x)) );
  c <= not (t or ((not z) and (not x)) or ((not y) and x) or (z and y));
  d <= not (((not t) and (not y)) or (x and (not z)) or (y and t and (not z)) or (t and y and x) or (z and (not y) and (not x)) or (z and (not t) and (not x)));
  e <= not (((not t) and (not y)) or ((not t) and (not x) and z) or (x and (not t) and (not z)));
  f <= not (((not x) and (not z) and (not t)) or (y and (not x) and (not z)) or (x and (not y) and (not z)) or (z and y and x) or (y and z and (not t)) or (x and z and (not t)));
  g <= not ((x and (not z)) or (y and (not z)) or (x and y) or (z and (not x) and (not t)) or (z and (not y) and (not x)));
end Behavioral;
