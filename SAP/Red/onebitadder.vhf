--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : onebitadder.vhf
-- /___/   /\     Timestamp : 03/05/2015 00:11:08
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3e -flat -suppress -vhdl C:/Users/GLEB/Desktop/XilinxProjects/Red/onebitadder.vhf -w C:/Users/GLEB/Desktop/XilinxProjects/fourbitadder/onebitadder.sch
--Design Name: onebitadder
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

entity onebitadder is
   port ( A    : in    std_logic; 
          B    : in    std_logic; 
          CIN  : in    std_logic; 
          COUT : out   std_logic; 
          S    : out   std_logic);
end onebitadder;

architecture BEHAVIORAL of onebitadder is
   attribute BOX_TYPE   : string ;
   signal XLXN_8  : std_logic;
   signal XLXN_9  : std_logic;
   signal XLXN_10 : std_logic;
   component AND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2 : component is "BLACK_BOX";
   
   component OR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR2 : component is "BLACK_BOX";
   
   component XOR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of XOR2 : component is "BLACK_BOX";
   
begin
   XLXI_3 : AND2
      port map (I0=>CIN,
                I1=>XLXN_8,
                O=>XLXN_9);
   
   XLXI_4 : AND2
      port map (I0=>B,
                I1=>A,
                O=>XLXN_10);
   
   XLXI_5 : OR2
      port map (I0=>XLXN_10,
                I1=>XLXN_9,
                O=>COUT);
   
   XLXI_6 : XOR2
      port map (I0=>B,
                I1=>A,
                O=>XLXN_8);
   
   XLXI_7 : XOR2
      port map (I0=>CIN,
                I1=>XLXN_8,
                O=>S);
   
end BEHAVIORAL;


