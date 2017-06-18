library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


-- Popis vstupù a výstupù 7-segmentového dekodéru
--    vstupy: d, c, b, a
--    výstupy: ca, cb, cc, cd, ce, cf, cg, dp
-- výstupy ca ... cg ovládají jednotlivé segmenty displeje,
-- výstup dp ovládá "teèku" za každým výstupem (ponechán vypnutý)
entity decoder_7seg is
   Port ( 
      d : in  STD_LOGIC;
      c : in  STD_LOGIC;
      b : in  STD_LOGIC;
      a : in  STD_LOGIC;
      ca : out  STD_LOGIC;
      cb : out  STD_LOGIC;
      cc : out  STD_LOGIC;
      cd : out  STD_LOGIC;
      ce : out  STD_LOGIC;
      cf : out  STD_LOGIC;
      cg : out  STD_LOGIC;
      dp : out  STD_LOGIC
   );
end decoder_7seg;                                       
-- popis chování 7-segmentového dekodéru
architecture decoder_7seg_arch of decoder_7seg is       
   -- vnitøní signál, který se používá k rozlišení jednotlivých vstupù
   signal   input :  std_logic_vector (3 downto 0);     
   
begin

   -- zpracování vstupù pro jednodušší práci s tabulkou 
   input(3) <= d;
   input(2) <= c;
   input(1) <= b;
   input(0) <= a;
	
-- Znázornìní 7-segmentového displeje
-- (více se mùžete dozvìdìt v referenèním manuálu pøípravku Basys-2)       
--       CA  
--       --- 
--  CF  |   |  CB     
--       ---    <- CG  
--  CE  |   |  CC                                    
--       --- .  <- DP                               
--       CD
--
--  Každý segment je zapnutý (rozsvícený) hodnotou log. 0
--
--  Èísla 0..9 zobrazujte podle obecnì známé konvence,
--  pro ostatní hodnoty (A..F) použijte následující zobrazení:
--  A:      B:      C:      D:      E:      F:
--    ---             ---             ---     ---
--   |   |   |       |           |   |       |
--    ---     ---             ---     ---     ---
--   |   |   |   |   |       |   |   |       |
--            ---     ---     ---     ---

   -------------------------------------------------------------------
   -------------------------------------------------------------------
   -- Zde doplòte 3 algebraické výrazy pro segmenty CA, CB, CC      --
   -------------------------------------------------------------------
   -------------------------------------------------------------------

   ca <= ((a and (not b) and (not c) and (not d)) or ((not a) and (not b) and c and (not d)) or (a and (not b) and c and d) or (a and b and (not c) and d)) ;  -- <- DOPLÒTE VÝRAZ
   cb <= ((a and b and d) or ((not a) and c and d) or (b and c and (not a)) or (a and (not b) and c and (not d)));  -- <- DOPLÒTE VÝRAZ
   cc <= (((not a) and c and d) or (b and c and d) or ((not a) and b and (not c) and (not d)));  -- <- DOPLÒTE VÝRAZ
	
   -------------------------------------------------------------------
   -------------------------------------------------------------------
   -- Zde doplòte výrazy tabulkou pro zbylé segmenty CD, CE, CF, CG --
   -------------------------------------------------------------------
   -------------------------------------------------------------------
	
   -- ------------------------------------------------------------------------------
   -- |  funèkní hodnota cd(d, c, b, a) |  stavový index s  |  d  |  c  |  b  |  a  | 
   -- ------------------------------------------------------------------------------
   with input select
   cd <= '0'   when	"0000",         -- |           0       |  0  |  0  |  0  |  0  |       
         '1'   when	"0001",         -- |           1       |  0  |  0  |  0  |  1  |
         '0'   when	"0010",         -- |           2       |  0  |  0  |  1  |  0  |
         '0'   when	"0011",         -- |           3       |  0  |  0  |  1  |  1  |
         '1'   when	"0100",         -- |           4       |  0  |  1  |  0  |  0  |
         '0'   when	"0101",         -- |           5       |  0  |  1  |  0  |  1  |
         '0'   when	"0110",         -- |           6       |  0  |  1  |  1  |  0  |
         '1'   when	"0111",         -- |           7       |  0  |  1  |  1  |  1  |
         '0'   when	"1000",         -- |           8       |  1  |  0  |  0  |  0  |
         '0'   when	"1001",         -- |           9       |  1  |  0  |  0  |  1  |
         '1'   when	"1010",         -- |          10       |  1  |  0  |  1  |  0  |
         '0'   when	"1011",         -- |          11       |  1  |  0  |  1  |  1  |
         '0'   when	"1100",         -- |          12       |  1  |  1  |  0  |  0  |
         '0'   when	"1101",         -- |          13       |  1  |  1  |  0  |  1  |
         '0'   when	"1110",         -- |          14       |  1  |  1  |  1  |  0  |
         '1'   when	"1111",         -- |          15       |  1  |  1  |  1  |  1  |
         '0'	when others;
   
   -- ------------------------------------------------------------------------------;
   -- ------------------------------------------------------------------------------
   -- |  funèkní hodnota ce(d, c, b, a) |  stavový index s  |  d  |  c  |  b  |  a  | 
   -- ------------------------------------------------------------------------------
   with input select
   ce <= '0'   when	"0000",         -- |           0       |  0  |  0  |  0  |  0  |  
         '1'   when	"0001",         -- |           1       |  0  |  0  |  0  |  1  |   
         '0'   when	"0010",         -- |           2       |  0  |  0  |  1  |  0  |           
         '1'   when	"0011",         -- |           3       |  0  |  0  |  1  |  1  |
         '1'   when	"0100",         -- |           4       |  0  |  1  |  0  |  0  |   
         '1'   when	"0101",         -- |           5       |  0  |  1  |  0  |  1  |   
         '0'   when	"0110",         -- |           6       |  0  |  1  |  1  |  0  |
         '1'   when	"0111",         -- |           7       |  0  |  1  |  1  |  1  |
         '0'   when	"1000",         -- |           8       |  1  |  0  |  0  |  0  |
         '1'   when	"1001",         -- |           9       |  1  |  0  |  0  |  1  |
         '0'   when	"1010",         -- |          10       |  1  |  0  |  1  |  0  |   
         '0'   when	"1011",         -- |          11       |  1  |  0  |  1  |  1  |
         '0'   when	"1100",         -- |          12       |  1  |  1  |  0  |  0  |            
         '0'   when	"1101",         -- |          13       |  1  |  1  |  0  |  1  |
         '0'   when	"1110",         -- |          14       |  1  |  1  |  1  |  0  |         
         '0'   when	"1111",         -- |          15       |  1  |  1  |  1  |  1  |
         '0'	when others;
   
   -- ------------------------------------------------------------------------------;
   -- ------------------------------------------------------------------------------
   -- |  funèkní hodnota cf(d, c, b, a) |  stavový index s  |  d  |  c  |  b  |  a  | 
   -- ------------------------------------------------------------------------------
   with input select
   cf <= '0'   when	"0000",         -- |           0       |  0  |  0  |  0  |  0  |            
         '1'   when	"0001",         -- |           1       |  0  |  0  |  0  |  1  |
         '1'   when	"0010",         -- |           2       |  0  |  0  |  1  |  0  |
         '1'   when	"0011",         -- |           3       |  0  |  0  |  1  |  1  |
         '0'   when	"0100",         -- |           4       |  0  |  1  |  0  |  0  |           
         '0'   when	"0101",         -- |           5       |  0  |  1  |  0  |  1  |
         '0'   when	"0110",         -- |           6       |  0  |  1  |  1  |  0  |             
         '1'   when	"0111",         -- |           7       |  0  |  1  |  1  |  1  |           
         '0'   when	"1000",         -- |           8       |  1  |  0  |  0  |  0  |          
         '0'   when	"1001",         -- |           9       |  1  |  0  |  0  |  1  |          
         '0'   when	"1010",         -- |          10       |  1  |  0  |  1  |  0  |         
         '0'   when	"1011",         -- |          11       |  1  |  0  |  1  |  1  |          
         '0'   when	"1100",         -- |          12       |  1  |  1  |  0  |  0  |        
         '1'   when	"1101",         -- |          13       |  1  |  1  |  0  |  1  |      
         '0'   when	"1110",         -- |          14       |  1  |  1  |  1  |  0  |
         '0'   when	"1111",         -- |          15       |  1  |  1  |  1  |  1  |
         '0'	when others;
   
   -- ------------------------------------------------------------------------------;
   -- ------------------------------------------------------------------------------
   -- |  funèkní hodnota cg(d, c, b, a) |  stavový index s  |  d  |  c  |  b  |  a  | 
   -- ------------------------------------------------------------------------------
   with input select
   cg <= '1'   when	"0000",         -- |           0       |  0  |  0  |  0  |  0  |     
         '1'   when	"0001",         -- |           1       |  0  |  0  |  0  |  1  |            
         '0'   when	"0010",         -- |           2       |  0  |  0  |  1  |  0  |         
         '0'   when	"0011",         -- |           3       |  0  |  0  |  1  |  1  |
         '0'   when	"0100",         -- |           4       |  0  |  1  |  0  |  0  |
         '0'   when	"0101",         -- |           5       |  0  |  1  |  0  |  1  |
         '0'   when	"0110",         -- |           6       |  0  |  1  |  1  |  0  |
         '1'   when	"0111",         -- |           7       |  0  |  1  |  1  |  1  |             
         '0'   when	"1000",         -- |           8       |  1  |  0  |  0  |  0  |             
         '0'   when	"1001",         -- |           9       |  1  |  0  |  0  |  1  |
         '0'   when	"1010",         -- |          10       |  1  |  0  |  1  |  0  |
         '0'   when	"1011",         -- |          11       |  1  |  0  |  1  |  1  |
         '1'   when	"1100",         -- |          12       |  1  |  1  |  0  |  0  |
         '0'   when	"1101",         -- |          13       |  1  |  1  |  0  |  1  |
         '0'   when	"1110",         -- |          14       |  1  |  1  |  1  |  0  |
         '0'   when	"1111",         -- |          15       |  1  |  1  |  1  |  1  |
         '0'	when others;
    
   -- ------------------------------------------------------------------------------;

-------------------------------------------------------------------
-------------------------------------------------------------------
-- Výraz DP je ponechán na konstantní hodnotì '1' (vypnuto)      --
-------------------------------------------------------------------
-------------------------------------------------------------------
	
   dp <= '1';  -- mužete zmìnit, pokud mate chu
	
end decoder_7seg_arch;

