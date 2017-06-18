--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : fourbits.vhf
-- /___/   /\     Timestamp : 02/26/2016 20:54:40
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3e -flat -suppress -vhdl H:/SAP/lab1/fourbits.vhf -w H:/SAP/lab1/fourbits.sch
--Design Name: fourbits
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

entity gates_MUSER_fourbits is
   port ( A : in    std_logic; 
          B : in    std_logic; 
          r : in    std_logic; 
          q : out   std_logic; 
          S : out   std_logic);
end gates_MUSER_fourbits;

architecture BEHAVIORAL of gates_MUSER_fourbits is
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



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity fourbits is
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
end fourbits;

architecture BEHAVIORAL of fourbits is
   signal XLXN_1 : std_logic;
   signal XLXN_2 : std_logic;
   signal XLXN_3 : std_logic;
   component gates_MUSER_fourbits
      port ( B : in    std_logic; 
             A : in    std_logic; 
             r : in    std_logic; 
             q : out   std_logic; 
             S : out   std_logic);
   end component;
   
begin
   XLXI_5 : gates_MUSER_fourbits
      port map (A=>A0,
                B=>B0,
                r=>CIN,
                q=>XLXN_1,
                S=>S0);
   
   XLXI_6 : gates_MUSER_fourbits
      port map (A=>A1,
                B=>B1,
                r=>XLXN_1,
                q=>XLXN_2,
                S=>S1);
   
   XLXI_7 : gates_MUSER_fourbits
      port map (A=>A2,
                B=>B2,
                r=>XLXN_2,
                q=>XLXN_3,
                S=>S2);
   
   XLXI_8 : gates_MUSER_fourbits
      port map (A=>A3,
                B=>B3,
                r=>XLXN_3,
                q=>COUT,
                S=>S3);
   
end BEHAVIORAL;


