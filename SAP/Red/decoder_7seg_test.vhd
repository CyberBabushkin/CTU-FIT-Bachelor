-- knihovna typù pro práci
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- prázdná entita zapouzdøující testovací sadu
ENTITY decoder_7seg_test IS
END decoder_7seg_test;

-- popis chování testovací sady
-- hlavièka ve formatu: ARCHITECTURE <libovolny_nazev> OF <nazev_entity> IS 
ARCHITECTURE behavior OF decoder_7seg_test IS 
 
-- definice vstupù a výstupù testované komponenty
  -- vstupy:  D, C, B, A 
  -- výstupy: CA, CB, CC, CD, CE, CF, CG, DP
-- POZOR!
   -- NÁZEV KOMPONENTY (COMPONENT <nazev>) MUSÍ BÝT STEJNÝ JAKO NÁZEV TESTOVANÉHO SCHÉMATU 
-- V TOMTO PØÍPADÌ: COMPONENT decoder_7seg
-- VSTUPY A VÝSTUPY KOMPONENTY (COMPONENT decoder_7seg) MUSÍ BÝT STEJNÉ JAKO POPISY VSTUPÙ A VÝSTUPÙ VE SCHÉMATU
   COMPONENT decoder_7seg
   PORT(
      d : IN  std_logic;
      c : IN  std_logic;
      b : IN  std_logic;
      a : IN  std_logic;
      ca : OUT  std_logic;
      cb : OUT  std_logic;
      cc : OUT  std_logic;
      cd : OUT  std_logic;
      ce : OUT  std_logic;
      cf : OUT  std_logic;
      cg : OUT  std_logic;
      dp : OUT  std_logic
   );
   END COMPONENT;
    
   -- vstupní signály ovládané testovací sadou
   signal d : std_logic := '0';
   signal c : std_logic := '0';
   signal b : std_logic := '0';
   signal a : std_logic := '0';

   -- výstupní signály ovládané testovací sadou
   signal ca : std_logic;
   signal cb : std_logic;
   signal cc : std_logic;
   signal cd : std_logic;
   signal ce : std_logic;
   signal cf : std_logic;
   signal cg : std_logic;
   signal dp : std_logic;
 
BEGIN
 
   -- mapování vstupù a výstupù testované komponenty na signály ovládané testovací sadou
   uut: decoder_7seg PORT MAP (
      d => d,
      c => c,
      b => b,
      a => a,
      ca => ca,
      cb => cb,
      cc => cc,
      cd => cd,
      ce => ce,
      cf => cf,
      cg => cg,
      dp => dp
   );

   -- simulaèní proces realizující chování testovací sady
   stim_proc: process
   begin		
      -- testovani zobrazeni cisla 0
      d   <= '0';
      c   <= '0';
      b   <= '0';
      a   <= '0';
      wait for 5 ns;
      assert ca='0' and cb='0' and cc='0' and cd='0' and ce='0' and cf='0' and cg='1'                      
      report "chyba pri zobrazeni 0"                                                                 
      severity ERROR;
		
      wait for 20 ns;

      -- testovani zobrazeni cisla 1
      d   <= '0';
      c   <= '0';
      b   <= '0';
      a   <= '1';
      wait for 5 ns;
      assert ca='1' and cb='0' and cc='0' and cd='1' and ce='1' and cf='1' and cg='1'                
      report "chyba pri zobrazeni 1"                                                                 
      severity ERROR;
		
      wait for 20 ns;

      -- testovani zobrazeni cisla 2
      d   <= '0';
      c   <= '0';
      b   <= '1';
      a   <= '0';
      wait for 5 ns;
      assert ca='0' and cb='0' and cc='1' and cd='0' and ce='0' and cf='1' and cg='0'                
      report "chyba pri zobrazeni 2"                                                                 
      severity ERROR;
		
      wait for 20 ns;		

      -- testovani zobrazeni cisla 3
      d   <= '0';
      c   <= '0';
      b   <= '1';
      a   <= '1';
      wait for 5 ns;
      assert ca='0' and cb='0' and cc='0' and cd='0' and ce='1' and cf='1' and cg='0'                
      report "chyba pri zobrazeni 3"                                                                 
      severity ERROR;
		
      wait for 20 ns;

      -- testovani zobrazeni cisla 4		
      d   <= '0';
      c   <= '1';
      b   <= '0';
      a   <= '0';
      wait for 5 ns;
      assert ca='1' and cb='0' and cc='0' and cd='1' and ce='1' and cf='0' and cg='0'                
      report "chyba pri zobrazeni 4"                                                                 
      severity ERROR;
		
      wait for 20 ns;

      -- testovani zobrazeni cisla 5		
      d   <= '0';
      c   <= '1';
      b   <= '0';
      a   <= '1';
      wait for 5 ns;
      assert ca='0' and cb='1' and cc='0' and cd='0' and ce='1' and cf='0' and cg='0'                
      report "chyba pri zobrazeni 5"

      severity ERROR;
		
      wait for 20 ns;

      -- testovani zobrazeni cisla 6		
      d   <= '0';
      c   <= '1';
      b   <= '1';
      a   <= '0';
      wait for 5 ns;
      assert ca='0' and cb='1' and cc='0' and cd='0' and ce='0' and cf='0' and cg='0'                
      report "chyba pri zobrazeni 6"

      severity ERROR;
		
      wait for 20 ns;

      -- testovani zobrazeni cisla 7		
      d   <= '0';
      c   <= '1';
      b   <= '1';
      a   <= '1';
      wait for 5 ns;
      assert ca='0' and cb='0' and cc='0' and cd='1' and ce='1' and cf='1' and cg='1'                
      report "chyba pri zobrazeni 7"

      severity ERROR;
		
      wait for 20 ns;

      -- testovani zobrazeni cisla 8
      d   <= '1';
      c   <= '0';
      b   <= '0';
      a   <= '0';
      wait for 5 ns;
      assert ca='0' and cb='0' and cc='0' and cd='0' and ce='0' and cf='0' and cg='0'                
      report "chyba pri zobrazeni 8"

      severity ERROR;
		
      wait for 20 ns;

      -- testovani zobrazeni cisla 9		
      d   <= '1';
      c   <= '0';
      b   <= '0';
      a   <= '1';
      wait for 5 ns;
      assert ca='0' and cb='0' and cc='0' and cd='0' and ce='1' and cf='0' and cg='0'                
      report "chyba pri zobrazeni 9"

      severity ERROR;
		
      wait for 20 ns;

      -- testovani zobrazeni cisla A		
      d   <= '1';
      c   <= '0';
      b   <= '1';
      a   <= '0';
      wait for 5 ns;
      assert ca='0' and cb='0' and cc='0' and cd='1' and ce='0' and cf='0' and cg='0'                
      report "chyba pri zobrazeni A"

      severity ERROR;
		
		wait for 20 ns;

      -- testovani zobrazeni cisla B		
      d   <= '1';
      c   <= '0';
      b   <= '1';
      a   <= '1';
      wait for 5 ns;
      assert ca='1' and cb='1' and cc='0' and cd='0' and ce='0' and cf='0' and cg='0'                
      report "chyba pri zobrazeni B"

      severity ERROR;
		
      wait for 20 ns;

      -- testovani zobrazeni cisla C		
      d   <= '1';
      c   <= '1';
      b   <= '0';
      a   <= '0';
      wait for 5 ns;
      assert ca='0' and cb='1' and cc='1' and cd='0' and ce='0' and cf='0' and cg='1'                
      report "chyba pri zobrazeni C"

      severity ERROR;
		
      wait for 20 ns;

      -- testovani zobrazeni cisla D		
      d   <= '1';
      c   <= '1';
      b   <= '0';
      a   <= '1';
      wait for 5 ns;
      assert ca='1' and cb='0' and cc='0' and cd='0' and ce='0' and cf='1' and cg='0'                
      report "chyba pri zobrazeni D"

      severity ERROR;
		
      wait for 20 ns;

      -- testovani zobrazeni cisla E		
      d   <= '1';
      c   <= '1';
      b   <= '1';
      a   <= '0';
      wait for 5 ns;
      assert ca='0' and cb='1' and cc='1' and cd='0' and ce='0' and cf='0' and cg='0'                
      report "chyba pri zobrazeni E"

      severity ERROR;
		
      wait for 20 ns;

      -- testovani zobrazeni cisla F		
      d   <= '1';
      c   <= '1';
      b   <= '1';
      a   <= '1';
      wait for 5 ns;
      assert ca='0' and cb='1' and cc='1' and cd='1' and ce='0' and cf='0' and cg='0'                
      report "chyba pri zobrazeni F"

      severity ERROR;
		
      wait for 20 ns;
				
      wait;
   end process;

END;
