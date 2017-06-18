--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : modulo6.vhf
-- /___/   /\     Timestamp : 03/30/2016 10:48:59
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3e -flat -suppress -vhdl H:/SAP/lab4.2/modulo6.vhf -w H:/SAP/lab4.2/modulo6.sch
--Design Name: modulo6
--Device: spartan3e
--Purpose:
--    This vhdl netlist is translated from an ECS schematic. It can be 
--    synthesized and simulated, but it should not be modified. 
--

library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity modulo6 is
   port ( CLK     : in    std_logic; 
          CLK_BTN : in    std_logic; 
          CLR     : in    std_logic; 
          EN      : in    std_logic; 
          Q0      : out   std_logic; 
          Q0_1    : out   std_logic; 
          Q1      : out   std_logic; 
          Q1_1    : out   std_logic; 
          Q2      : out   std_logic; 
          Q2_1    : out   std_logic);
end modulo6;

architecture BEHAVIORAL of modulo6 is
   attribute BOX_TYPE   : string ;
   signal XLXN_8     : std_logic;
   signal Q2_1_DUMMY : std_logic;
   signal Q0_DUMMY   : std_logic;
   signal Q1_DUMMY   : std_logic;
   signal Q2_DUMMY   : std_logic;
   signal Q1_1_DUMMY : std_logic;
   signal Q0_1_DUMMY : std_logic;
   component debounce
      port ( clk    : in    std_logic; 
             tl_in  : in    std_logic; 
             tl_out : out   std_logic);
   end component;
   
   component algebra
      port ( en : in    std_logic; 
             a2 : in    std_logic; 
             a1 : in    std_logic; 
             a0 : in    std_logic; 
             q2 : out   std_logic; 
             q1 : out   std_logic; 
             q0 : out   std_logic);
   end component;
   
   component FDC
      generic( INIT : bit :=  '0');
      port ( C   : in    std_logic; 
             CLR : in    std_logic; 
             D   : in    std_logic; 
             Q   : out   std_logic);
   end component;
   attribute BOX_TYPE of FDC : component is "BLACK_BOX";
   
begin
   Q0 <= Q0_DUMMY;
   Q0_1 <= Q0_1_DUMMY;
   Q1 <= Q1_DUMMY;
   Q1_1 <= Q1_1_DUMMY;
   Q2 <= Q2_DUMMY;
   Q2_1 <= Q2_1_DUMMY;
   XLXI_1 : debounce
      port map (clk=>CLK,
                tl_in=>CLK_BTN,
                tl_out=>XLXN_8);
   
   XLXI_2 : algebra
      port map (a0=>Q0_1_DUMMY,
                a1=>Q1_1_DUMMY,
                a2=>Q2_1_DUMMY,
                en=>EN,
                q0=>Q0_DUMMY,
                q1=>Q1_DUMMY,
                q2=>Q2_DUMMY);
   
   XLXI_3 : FDC
      port map (C=>XLXN_8,
                CLR=>CLR,
                D=>Q2_DUMMY,
                Q=>Q2_1_DUMMY);
   
   XLXI_4 : FDC
      port map (C=>XLXN_8,
                CLR=>CLR,
                D=>Q1_DUMMY,
                Q=>Q1_1_DUMMY);
   
   XLXI_5 : FDC
      port map (C=>XLXN_8,
                CLR=>CLR,
                D=>Q0_DUMMY,
                Q=>Q0_1_DUMMY);
   
end BEHAVIORAL;


