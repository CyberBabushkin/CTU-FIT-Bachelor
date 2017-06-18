--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : adderwithdisplay.vhf
-- /___/   /\     Timestamp : 03/05/2015 00:11:08
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3e -flat -suppress -vhdl C:/Users/GLEB/Desktop/XilinxProjects/Red/adderwithdisplay.vhf -w C:/Users/GLEB/Desktop/XilinxProjects/Red/adderwithdisplay.sch
--Design Name: adderwithdisplay
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

entity adderwithdisplay is
   port ( A0   : in    std_logic; 
          A1   : in    std_logic; 
          A2   : in    std_logic; 
          A3   : in    std_logic; 
          B0   : in    std_logic; 
          B1   : in    std_logic; 
          B2   : in    std_logic; 
          B3   : in    std_logic; 
          CIN  : in    std_logic; 
          CA   : out   std_logic; 
          CB   : out   std_logic; 
          CC   : out   std_logic; 
          CD   : out   std_logic; 
          CE   : out   std_logic; 
          CF   : out   std_logic; 
          CG   : out   std_logic; 
          COUT : out   std_logic; 
          DP   : out   std_logic);
end adderwithdisplay;

architecture BEHAVIORAL of adderwithdisplay is
   signal XLXN_27 : std_logic;
   signal XLXN_28 : std_logic;
   signal XLXN_29 : std_logic;
   signal XLXN_30 : std_logic;
   component fourbitadder
      port ( B1   : in    std_logic; 
             A1   : in    std_logic; 
             B2   : in    std_logic; 
             A0   : in    std_logic; 
             B0   : in    std_logic; 
             A2   : in    std_logic; 
             A3   : in    std_logic; 
             B3   : in    std_logic; 
             CIN  : in    std_logic; 
             COUT : out   std_logic; 
             S3   : out   std_logic; 
             S0   : out   std_logic; 
             S2   : out   std_logic; 
             S1   : out   std_logic);
   end component;
   
   component decoder_7seg
      port ( d  : in    std_logic; 
             c  : in    std_logic; 
             b  : in    std_logic; 
             a  : in    std_logic; 
             ca : out   std_logic; 
             cb : out   std_logic; 
             cc : out   std_logic; 
             cd : out   std_logic; 
             ce : out   std_logic; 
             cf : out   std_logic; 
             cg : out   std_logic; 
             dp : out   std_logic);
   end component;
   
begin
   XLXI_2 : fourbitadder
      port map (A0=>A0,
                A1=>A1,
                A2=>A2,
                A3=>A3,
                B0=>B0,
                B1=>B1,
                B2=>B2,
                B3=>B3,
                CIN=>CIN,
                COUT=>COUT,
                S0=>XLXN_28,
                S1=>XLXN_30,
                S2=>XLXN_29,
                S3=>XLXN_27);
   
   XLXI_5 : decoder_7seg
      port map (a=>XLXN_28,
                b=>XLXN_30,
                c=>XLXN_29,
                d=>XLXN_27,
                ca=>CA,
                cb=>CB,
                cc=>CC,
                cd=>CD,
                ce=>CE,
                cf=>CF,
                cg=>CG,
                dp=>DP);
   
end BEHAVIORAL;


