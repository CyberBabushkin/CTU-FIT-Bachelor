-- knihovna typ� pro pr�ci
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
  
-- pr�zdn� entita zapouzd�uj�c� testovac� sadu
ENTITY l2_agebra_4_test IS
END l2_agebra_4_test;
 
-- popis chov�n� testovac� sady
-- hlavi�ka ve formatu: ARCHITECTURE <libovolny_nazev> OF <nazev_entity> IS
ARCHITECTURE behavior OF l2_agebra_4_test IS 
 
   -- definice vstup� a v�stup� testovan� komponenty
   -- vstupy:  a, b, c, d
   -- v�stupy: f
   -- POZOR!
   -- N�ZEV KOMPONENTY (COMPONENT <nazev>) MUS� B�T STEJN� JAKO N�ZEV TESTOVAN� ENTITY
   -- V TOMTO P��PAD�: COMPONENT algebra
   -- VSTUPY A V�STUPY KOMPONENTY (COMPONENT algebra) MUS� B�T STEJN� JAKO POPISY VSTUP� A V�STUP� TESTOVAN� ENTITY
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
    
   -- vstupn� sign�ly ovl�dan� testovac� sadou
   signal x : std_logic := '0';
   signal y : std_logic := '0';
   signal z : std_logic := '0';
   signal t : std_logic := '0';

   -- v�stupn� sign�ly ovl�dan� testovac� sadou
   signal a : std_logic;
	signal b : std_logic;
	signal c : std_logic;
	signal d : std_logic;
	signal e : std_logic;
	signal f : std_logic;
	signal g : std_logic;
 
BEGIN
 
   -- mapov�n� vstup� a v�stup� testovan� komponenty na sign�ly ovl�dan� testovac� sadou
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
 
   -- simula�n� proces realizuj�c� chov�n� testovac� sady
   stim_proc: process   
      -- deklarace prom�nn�ch pro pr�ci s for-cykly   
      variable i, j, r, l   :   integer;
   begin		
      -- po��te�n� nastaven� vstup�
      x   <=   '0';
      y   <=   '0';
      z   <=   '0';
      t   <=   '0';
		
      -- testov�n� v�ech mo�n�ch kombinac�
      -- 4 vstupy => 4 for-cykly => 2^4 mo�n�ch vstupn�ch kombinac�
      for i in 0 to 1 loop	
         x   <=	not(x);
         for j in 0 to 1 loop
            y   <=   not(y);
            for r in 0 to 1 loop
               z   <=   not(z);
               for l in 0 to 1 loop
                  t   <=   not(t);
                  -- vstup se zm�n� za 20 nanosekund
                  wait for 20 ns;		
               end loop;
            end loop;
         end loop;
      end loop;
      
      -- nekone�n� �ekac� smy�ka
      wait;									
		
   end process;

END;
