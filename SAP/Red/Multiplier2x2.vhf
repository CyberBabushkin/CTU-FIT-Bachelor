--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : Multiplier2x2.vhf
-- /___/   /\     Timestamp : 03/06/2015 10:25:41
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3e -flat -suppress -vhdl H:/BI-SAP/Red/Multiplier2x2.vhf -w H:/BI-SAP/Red/Multiplier2x2.sch
--Design Name: Multiplier2x2
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

entity Multiplier2x2 is
   port ( A0 : in    std_logic; 
          A1 : in    std_logic; 
          B0 : in    std_logic; 
          B1 : in    std_logic; 
          C0 : out   std_logic; 
          C1 : out   std_logic; 
          C2 : out   std_logic; 
          C3 : out   std_logic);
end Multiplier2x2;

architecture BEHAVIORAL of Multiplier2x2 is
   attribute BOX_TYPE   : string ;
   signal XLXN_11 : std_logic;
   signal XLXN_13 : std_logic;
   signal XLXN_16 : std_logic;
   signal XLXN_17 : std_logic;
   component AND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2 : component is "BLACK_BOX";
   
   component XOR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of XOR2 : component is "BLACK_BOX";
   
begin
   XLXI_1 : AND2
      port map (I0=>B1,
                I1=>A0,
                O=>XLXN_11);
   
   XLXI_2 : AND2
      port map (I0=>B0,
                I1=>A0,
                O=>C0);
   
   XLXI_3 : AND2
      port map (I0=>B0,
                I1=>A1,
                O=>XLXN_13);
   
   XLXI_4 : AND2
      port map (I0=>B1,
                I1=>A1,
                O=>XLXN_16);
   
   XLXI_5 : AND2
      port map (I0=>XLXN_13,
                I1=>XLXN_11,
                O=>XLXN_17);
   
   XLXI_6 : AND2
      port map (I0=>XLXN_16,
                I1=>XLXN_17,
                O=>C3);
   
   XLXI_9 : XOR2
      port map (I0=>XLXN_13,
                I1=>XLXN_11,
                O=>C1);
   
   XLXI_11 : XOR2
      port map (I0=>XLXN_16,
                I1=>XLXN_17,
                O=>C2);
   
end BEHAVIORAL;


