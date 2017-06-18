--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : sekv.vhf
-- /___/   /\     Timestamp : 03/23/2016 14:04:59
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3e -flat -suppress -vhdl H:/SAP/lab4/sekv.vhf -w H:/SAP/lab4/sekv.sch
--Design Name: sekv
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

entity sekv is
   port ( );
end sekv;

architecture BEHAVIORAL of sekv is
   attribute BOX_TYPE   : string ;
   signal XLXI_1_C_openSignal     : std_logic;
   signal XLXI_1_CLR_openSignal   : std_logic;
   signal XLXI_1_D_openSignal     : std_logic;
   signal XLXI_2_C_openSignal     : std_logic;
   signal XLXI_2_CLR_openSignal   : std_logic;
   signal XLXI_2_D_openSignal     : std_logic;
   signal XLXI_3_C_openSignal     : std_logic;
   signal XLXI_3_CLR_openSignal   : std_logic;
   signal XLXI_3_D_openSignal     : std_logic;
   signal XLXI_5_a0_openSignal    : std_logic;
   signal XLXI_5_a1_openSignal    : std_logic;
   signal XLXI_5_a2_openSignal    : std_logic;
   signal XLXI_5_en_openSignal    : std_logic;
   signal XLXI_6_clk_openSignal   : std_logic;
   signal XLXI_6_tl_in_openSignal : std_logic;
   component FDC
      generic( INIT : bit :=  '0');
      port ( C   : in    std_logic; 
             CLR : in    std_logic; 
             D   : in    std_logic; 
             Q   : out   std_logic);
   end component;
   attribute BOX_TYPE of FDC : component is "BLACK_BOX";
   
   component algebra
      port ( en : in    std_logic; 
             a2 : in    std_logic; 
             a1 : in    std_logic; 
             a0 : in    std_logic; 
             q2 : out   std_logic; 
             q1 : out   std_logic; 
             q0 : out   std_logic);
   end component;
   
   component debounce
      port ( clk    : in    std_logic; 
             tl_in  : in    std_logic; 
             tl_out : out   std_logic);
   end component;
   
begin
   XLXI_1 : FDC
      port map (C=>XLXI_1_C_openSignal,
                CLR=>XLXI_1_CLR_openSignal,
                D=>XLXI_1_D_openSignal,
                Q=>open);
   
   XLXI_2 : FDC
      port map (C=>XLXI_2_C_openSignal,
                CLR=>XLXI_2_CLR_openSignal,
                D=>XLXI_2_D_openSignal,
                Q=>open);
   
   XLXI_3 : FDC
      port map (C=>XLXI_3_C_openSignal,
                CLR=>XLXI_3_CLR_openSignal,
                D=>XLXI_3_D_openSignal,
                Q=>open);
   
   XLXI_5 : algebra
      port map (a0=>XLXI_5_a0_openSignal,
                a1=>XLXI_5_a1_openSignal,
                a2=>XLXI_5_a2_openSignal,
                en=>XLXI_5_en_openSignal,
                q0=>open,
                q1=>open,
                q2=>open);
   
   XLXI_6 : debounce
      port map (clk=>XLXI_6_clk_openSignal,
                tl_in=>XLXI_6_tl_in_openSignal,
                tl_out=>open);
   
end BEHAVIORAL;


