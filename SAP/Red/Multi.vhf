--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : Multi.vhf
-- /___/   /\     Timestamp : 03/06/2015 10:25:41
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3e -flat -suppress -vhdl H:/BI-SAP/Red/Multi.vhf -w H:/BI-SAP/Red/Multi.sch
--Design Name: Multi
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

entity Multiplier2x2_MUSER_Multi is
   port ( A0 : in    std_logic; 
          A1 : in    std_logic; 
          B0 : in    std_logic; 
          B1 : in    std_logic; 
          C0 : out   std_logic; 
          C1 : out   std_logic; 
          C2 : out   std_logic; 
          C3 : out   std_logic);
end Multiplier2x2_MUSER_Multi;

architecture BEHAVIORAL of Multiplier2x2_MUSER_Multi is
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



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity Multi is
   port ( A0 : in    std_logic; 
          A1 : in    std_logic; 
          B0 : in    std_logic; 
          B1 : in    std_logic; 
          CA : out   std_logic; 
          CB : out   std_logic; 
          CC : out   std_logic; 
          CD : out   std_logic; 
          CE : out   std_logic; 
          CF : out   std_logic; 
          CG : out   std_logic; 
          DP : out   std_logic);
end Multi;

architecture BEHAVIORAL of Multi is
   signal XLXN_1 : std_logic;
   signal XLXN_2 : std_logic;
   signal XLXN_3 : std_logic;
   signal XLXN_4 : std_logic;
   component Multiplier2x2_MUSER_Multi
      port ( A0 : in    std_logic; 
             A1 : in    std_logic; 
             B0 : in    std_logic; 
             B1 : in    std_logic; 
             C0 : out   std_logic; 
             C1 : out   std_logic; 
             C2 : out   std_logic; 
             C3 : out   std_logic);
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
   XLXI_1 : Multiplier2x2_MUSER_Multi
      port map (A0=>A0,
                A1=>A1,
                B0=>B0,
                B1=>B1,
                C0=>XLXN_1,
                C1=>XLXN_4,
                C2=>XLXN_2,
                C3=>XLXN_3);
   
   XLXI_2 : decoder_7seg
      port map (a=>XLXN_1,
                b=>XLXN_4,
                c=>XLXN_2,
                d=>XLXN_3,
                ca=>CA,
                cb=>CB,
                cc=>CC,
                cd=>CD,
                ce=>CE,
                cf=>CF,
                cg=>CG,
                dp=>DP);
   
end BEHAVIORAL;


