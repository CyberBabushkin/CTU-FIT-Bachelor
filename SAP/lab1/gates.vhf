--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : gates.vhf
-- /___/   /\     Timestamp : 02/26/2016 20:29:22
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3e -flat -suppress -vhdl H:/SAP/lab1/gates.vhf -w H:/SAP/lab1/gates.sch
--Design Name: gates
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

entity gates is
   port ( A : in    std_logic; 
          B : in    std_logic; 
          r : in    std_logic; 
          q : out   std_logic; 
          S : out   std_logic);
end gates;

architecture BEHAVIORAL of gates is
   attribute BOX_TYPE   : string ;
   signal XLXN_80 : std_logic;
   signal XLXN_81 : std_logic;
   signal XLXN_96 : std_logic;
   component XOR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of XOR2 : component is "BLACK_BOX";
   
   component NAND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of NAND2 : component is "BLACK_BOX";
   
begin
   XLXI_4 : XOR2
      port map (I0=>B,
                I1=>A,
                O=>XLXN_96);
   
   XLXI_11 : XOR2
      port map (I0=>r,
                I1=>XLXN_96,
                O=>S);
   
   XLXI_12 : NAND2
      port map (I0=>r,
                I1=>XLXN_96,
                O=>XLXN_80);
   
   XLXI_13 : NAND2
      port map (I0=>A,
                I1=>B,
                O=>XLXN_81);
   
   XLXI_14 : NAND2
      port map (I0=>XLXN_80,
                I1=>XLXN_81,
                O=>q);
   
end BEHAVIORAL;


