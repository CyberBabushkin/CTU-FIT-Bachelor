-- knihovna typù pro práci
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
  
-- prázdná entita zapouzdøující testovací sadu
ENTITY l2_agebra_4_test IS
END l2_agebra_4_test;
 
-- popis chování testovací sady
-- hlavièka ve formatu: ARCHITECTURE <libovolny_nazev> OF <nazev_entity> IS
ARCHITECTURE behavior OF l2_agebra_4_test IS 
 
   -- definice vstupù a výstupù testované komponenty
   -- vstupy:  a, b, c, d
   -- výstupy: f
   -- POZOR!
   -- NÁZEV KOMPONENTY (COMPONENT <nazev>) MUSÍ BÝT STEJNÝ JAKO NÁZEV TESTOVANÉ ENTITY
   -- V TOMTO PØÍPADÌ: COMPONENT algebra
   -- VSTUPY A VÝSTUPY KOMPONENTY (COMPONENT algebra) MUSÍ BÝT STEJNÉ JAKO POPISY VSTUPÙ A VÝSTUPÙ TESTOVANÉ ENTITY
   COMPONENT algebra
   PORT(
			  x : in std_logic;
			  y : in std_logic;
           z : in std_logic;
           t : in std_logic;
           a : out std_logic;
			  b : out std_logic;
			  c : out std_logic;
			  d : out std_logic;
			  e : out std_logic;
			  f : out std_logic;
			  g : out std_logic
   );
   END COMPONENT;
    
   -- vstupní signály ovládané testovací sadou
   signal x : std_logic := '0';
   signal y : std_logic := '0';
   signal z : std_logic := '0';
   signal t : std_logic := '0';

   -- výstupní signály ovládané testovací sadou
   signal a : std_logic;
	signal b : std_logic;
	signal c : std_logic;
	signal d : std_logic;
	signal e : std_logic;
	signal f : std_logic;
	signal g : std_logic;
 
BEGIN
 
   -- mapování vstupù a výstupù testované komponenty na signály ovládané testovací sadou
   uut: algebra PORT MAP (
      x => x,
      y => y,
      z => z,
      t => t,
		a => a,
		b => b,
		c => c,
		d => d,
		e => e,
      f => f,
		g => g
   );
 
   -- simulaèní proces realizující chování testovací sady
   stim_proc: process   
      -- deklarace promìnných pro práci s for-cykly   
      variable i, j, r, l   :   integer;
   begin		
      -- poèáteèní nastavení vstupù
      x   <=   '0';
      y   <=   '0';
      z   <=   '0';
      t   <=   '0';
		
      -- testování všech možných kombinací
      -- 4 vstupy => 4 for-cykly => 2^4 možných vstupních kombinací
      for i in 0 to 1 loop	
         x   <=	not(x);
         for j in 0 to 1 loop
            y   <=   not(y);
            for r in 0 to 1 loop
               z   <=   not(z);
               for l in 0 to 1 loop
                  t   <=   not(t);
                  -- vstup se zmìní za 20 nanosekund
                  wait for 20 ns;		
               end loop;
            end loop;
         end loop;
      end loop;
      
      -- nekoneèná èekací smyèka
      wait;									
		
   end process;

END;
