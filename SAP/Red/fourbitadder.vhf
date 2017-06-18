--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : fourbitadder.vhf
-- /___/   /\     Timestamp : 03/05/2015 00:11:08
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3e -flat -suppress -vhdl C:/Users/GLEB/Desktop/XilinxProjects/Red/fourbitadder.vhf -w C:/Users/GLEB/Desktop/XilinxProjects/fourbitadder/fourbitadder.sch
--Design Name: fourbitadder
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

entity onebitadder_MUSER_fourbitadder is
   port ( A    : in    std_logic; 
          B    : in    std_logic; 
          CIN  : in    std_logic; 
          COUT : out   std_logic; 
          S    : out   std_logic);
end onebitadder_MUSER_fourbitadder;

architecture BEHAVIORAL of onebitadder_MUSER_fourbitadder is
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



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity fourbitadder is
   port ( A0   : in    std_logic; 
          A1   : in    std_logic; 
          A2   : in    std_logic; 
          A3   : in    std_logic; 
          B0   : in    std_logic; 
          B1   : in    std_logic; 
          B2   : in    std_logic; 
          B3   : in    std_logic; 
          CIN  : in    std_logic; 
          COUT : out   std_logic; 
          S0   : out   std_logic; 
          S1   : out   std_logic; 
          S2   : out   std_logic; 
          S3   : out   std_logic);
end fourbitadder;

architecture BEHAVIORAL of fourbitadder is
   signal XLXN_33 : std_logic;
   signal XLXN_34 : std_logic;
   signal XLXN_88 : std_logic;
   component onebitadder_MUSER_fourbitadder
      port ( A    : in    std_logic; 
             B    : in    std_logic; 
             CIN  : in    std_logic; 
             S    : out   std_logic; 
             COUT : out   std_logic);
   end component;
   
begin
   XLXI_6 : onebitadder_MUSER_fourbitadder
      port map (A=>A2,
                B=>B2,
                CIN=>XLXN_33,
                COUT=>XLXN_88,
                S=>S2);
   
   XLXI_7 : onebitadder_MUSER_fourbitadder
      port map (A=>A1,
                B=>B1,
                CIN=>XLXN_34,
                COUT=>XLXN_33,
                S=>S1);
   
   XLXI_8 : onebitadder_MUSER_fourbitadder
      port map (A=>A0,
                B=>B0,
                CIN=>CIN,
                COUT=>XLXN_34,
                S=>S0);
   
   XLXI_9 : onebitadder_MUSER_fourbitadder
      port map (A=>A3,
                B=>B3,
                CIN=>XLXN_88,
                COUT=>COUT,
                S=>S3);
   
end BEHAVIORAL;


