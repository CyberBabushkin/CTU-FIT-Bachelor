--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : Clck.vhf
-- /___/   /\     Timestamp : 03/06/2015 11:16:08
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3e -flat -suppress -vhdl H:/BI-SAP/Red/Clck.vhf -w H:/BI-SAP/Red/Clck.sch
--Design Name: Clck
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

entity Mymux_MUSER_Clck is
   port ( P0 : in    std_logic; 
          P1 : in    std_logic; 
          P2 : in    std_logic; 
          P3 : in    std_logic; 
          S  : in    std_logic; 
          S0 : in    std_logic; 
          S1 : in    std_logic; 
          S2 : in    std_logic; 
          S3 : in    std_logic; 
          Y0 : out   std_logic; 
          Y1 : out   std_logic; 
          Y2 : out   std_logic; 
          Y3 : out   std_logic);
end Mymux_MUSER_Clck;

architecture BEHAVIORAL of Mymux_MUSER_Clck is
   attribute BOX_TYPE   : string ;
   component MUXF5
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             S  : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of MUXF5 : component is "BLACK_BOX";
   
begin
   XLXI_1 : MUXF5
      port map (I0=>S0,
                I1=>P0,
                S=>S,
                O=>Y0);
   
   XLXI_2 : MUXF5
      port map (I0=>S1,
                I1=>P1,
                S=>S,
                O=>Y1);
   
   XLXI_3 : MUXF5
      port map (I0=>S2,
                I1=>P2,
                S=>S,
                O=>Y2);
   
   XLXI_4 : MUXF5
      port map (I0=>S3,
                I1=>P3,
                S=>S,
                O=>Y3);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity FTCE_MXILINX_Clck is
   generic( INIT : bit :=  '0');
   port ( C   : in    std_logic; 
          CE  : in    std_logic; 
          CLR : in    std_logic; 
          T   : in    std_logic; 
          Q   : out   std_logic);
end FTCE_MXILINX_Clck;

architecture BEHAVIORAL of FTCE_MXILINX_Clck is
   attribute BOX_TYPE   : string ;
   attribute RLOC       : string ;
   signal TQ      : std_logic;
   signal Q_DUMMY : std_logic;
   component XOR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of XOR2 : component is "BLACK_BOX";
   
   component FDCE
      generic( INIT : bit :=  '0');
      port ( C   : in    std_logic; 
             CE  : in    std_logic; 
             CLR : in    std_logic; 
             D   : in    std_logic; 
             Q   : out   std_logic);
   end component;
   attribute BOX_TYPE of FDCE : component is "BLACK_BOX";
   
   attribute RLOC of I_36_35 : label is "X0Y0";
begin
   Q <= Q_DUMMY;
   I_36_32 : XOR2
      port map (I0=>T,
                I1=>Q_DUMMY,
                O=>TQ);
   
   I_36_35 : FDCE
   generic map( INIT => INIT)
      port map (C=>C,
                CE=>CE,
                CLR=>CLR,
                D=>TQ,
                Q=>Q_DUMMY);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity CB4CE_MXILINX_Clck is
   port ( C   : in    std_logic; 
          CE  : in    std_logic; 
          CLR : in    std_logic; 
          CEO : out   std_logic; 
          Q0  : out   std_logic; 
          Q1  : out   std_logic; 
          Q2  : out   std_logic; 
          Q3  : out   std_logic; 
          TC  : out   std_logic);
end CB4CE_MXILINX_Clck;

architecture BEHAVIORAL of CB4CE_MXILINX_Clck is
   attribute HU_SET     : string ;
   attribute BOX_TYPE   : string ;
   signal T2       : std_logic;
   signal T3       : std_logic;
   signal XLXN_1   : std_logic;
   signal Q0_DUMMY : std_logic;
   signal Q1_DUMMY : std_logic;
   signal Q2_DUMMY : std_logic;
   signal Q3_DUMMY : std_logic;
   signal TC_DUMMY : std_logic;
   component FTCE_MXILINX_Clck
      generic( INIT : bit :=  '0');
      port ( C   : in    std_logic; 
             CE  : in    std_logic; 
             CLR : in    std_logic; 
             T   : in    std_logic; 
             Q   : out   std_logic);
   end component;
   
   component AND4
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             I3 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND4 : component is "BLACK_BOX";
   
   component AND3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3 : component is "BLACK_BOX";
   
   component AND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2 : component is "BLACK_BOX";
   
   component VCC
      port ( P : out   std_logic);
   end component;
   attribute BOX_TYPE of VCC : component is "BLACK_BOX";
   
   attribute HU_SET of I_Q0 : label is "I_Q0_0";
   attribute HU_SET of I_Q1 : label is "I_Q1_1";
   attribute HU_SET of I_Q2 : label is "I_Q2_2";
   attribute HU_SET of I_Q3 : label is "I_Q3_3";
begin
   Q0 <= Q0_DUMMY;
   Q1 <= Q1_DUMMY;
   Q2 <= Q2_DUMMY;
   Q3 <= Q3_DUMMY;
   TC <= TC_DUMMY;
   I_Q0 : FTCE_MXILINX_Clck
      port map (C=>C,
                CE=>CE,
                CLR=>CLR,
                T=>XLXN_1,
                Q=>Q0_DUMMY);
   
   I_Q1 : FTCE_MXILINX_Clck
      port map (C=>C,
                CE=>CE,
                CLR=>CLR,
                T=>Q0_DUMMY,
                Q=>Q1_DUMMY);
   
   I_Q2 : FTCE_MXILINX_Clck
      port map (C=>C,
                CE=>CE,
                CLR=>CLR,
                T=>T2,
                Q=>Q2_DUMMY);
   
   I_Q3 : FTCE_MXILINX_Clck
      port map (C=>C,
                CE=>CE,
                CLR=>CLR,
                T=>T3,
                Q=>Q3_DUMMY);
   
   I_36_31 : AND4
      port map (I0=>Q3_DUMMY,
                I1=>Q2_DUMMY,
                I2=>Q1_DUMMY,
                I3=>Q0_DUMMY,
                O=>TC_DUMMY);
   
   I_36_32 : AND3
      port map (I0=>Q2_DUMMY,
                I1=>Q1_DUMMY,
                I2=>Q0_DUMMY,
                O=>T3);
   
   I_36_33 : AND2
      port map (I0=>Q1_DUMMY,
                I1=>Q0_DUMMY,
                O=>T2);
   
   I_36_58 : VCC
      port map (P=>XLXN_1);
   
   I_36_67 : AND2
      port map (I0=>CE,
                I1=>TC_DUMMY,
                O=>CEO);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity Clck is
   port ( A0  : in    std_logic; 
          A1  : in    std_logic; 
          A2  : in    std_logic; 
          A3  : in    std_logic; 
          B0  : in    std_logic; 
          B1  : in    std_logic; 
          B2  : in    std_logic; 
          B3  : in    std_logic; 
          CIN : in    std_logic; 
          CLK : in    std_logic; 
          CLR : in    std_logic; 
          AN0 : out   std_logic; 
          AN1 : out   std_logic; 
          CA  : out   std_logic; 
          CB  : out   std_logic; 
          CC  : out   std_logic; 
          CD  : out   std_logic; 
          CE  : out   std_logic; 
          CF  : out   std_logic; 
          CG  : out   std_logic; 
          DP  : out   std_logic);
end Clck;

architecture BEHAVIORAL of Clck is
   attribute HU_SET     : string ;
   attribute BOX_TYPE   : string ;
   signal XLXN_1    : std_logic;
   signal XLXN_2    : std_logic;
   signal XLXN_3    : std_logic;
   signal XLXN_4    : std_logic;
   signal XLXN_28   : std_logic;
   signal XLXN_29   : std_logic;
   signal XLXN_30   : std_logic;
   signal XLXN_31   : std_logic;
   signal XLXN_32   : std_logic;
   signal XLXN_33   : std_logic;
   signal XLXN_34   : std_logic;
   signal XLXN_35   : std_logic;
   signal XLXN_36   : std_logic;
   signal XLXN_38   : std_logic;
   signal AN0_DUMMY : std_logic;
   component CB4CE_MXILINX_Clck
      port ( C   : in    std_logic; 
             CE  : in    std_logic; 
             CLR : in    std_logic; 
             CEO : out   std_logic; 
             Q0  : out   std_logic; 
             Q1  : out   std_logic; 
             Q2  : out   std_logic; 
             Q3  : out   std_logic; 
             TC  : out   std_logic);
   end component;
   
   component VCC
      port ( P : out   std_logic);
   end component;
   attribute BOX_TYPE of VCC : component is "BLACK_BOX";
   
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
   
   component GND
      port ( G : out   std_logic);
   end component;
   attribute BOX_TYPE of GND : component is "BLACK_BOX";
   
   component Mymux_MUSER_Clck
      port ( S0 : in    std_logic; 
             P0 : in    std_logic; 
             S  : in    std_logic; 
             S1 : in    std_logic; 
             S2 : in    std_logic; 
             P2 : in    std_logic; 
             S3 : in    std_logic; 
             P3 : in    std_logic; 
             P1 : in    std_logic; 
             Y0 : out   std_logic; 
             Y1 : out   std_logic; 
             Y3 : out   std_logic; 
             Y2 : out   std_logic);
   end component;
   
   component INV
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of INV : component is "BLACK_BOX";
   
   attribute HU_SET of XLXI_1 : label is "XLXI_1_4";
   attribute HU_SET of XLXI_2 : label is "XLXI_2_5";
   attribute HU_SET of XLXI_3 : label is "XLXI_3_6";
   attribute HU_SET of XLXI_4 : label is "XLXI_4_7";
begin
   AN0 <= AN0_DUMMY;
   XLXI_1 : CB4CE_MXILINX_Clck
      port map (C=>CLK,
                CE=>XLXN_1,
                CLR=>CLR,
                CEO=>XLXN_2,
                Q0=>open,
                Q1=>open,
                Q2=>open,
                Q3=>open,
                TC=>open);
   
   XLXI_2 : CB4CE_MXILINX_Clck
      port map (C=>CLK,
                CE=>XLXN_2,
                CLR=>CLR,
                CEO=>XLXN_3,
                Q0=>open,
                Q1=>open,
                Q2=>open,
                Q3=>open,
                TC=>open);
   
   XLXI_3 : CB4CE_MXILINX_Clck
      port map (C=>CLK,
                CE=>XLXN_3,
                CLR=>CLR,
                CEO=>XLXN_4,
                Q0=>open,
                Q1=>open,
                Q2=>open,
                Q3=>open,
                TC=>open);
   
   XLXI_4 : CB4CE_MXILINX_Clck
      port map (C=>CLK,
                CE=>XLXN_4,
                CLR=>CLR,
                CEO=>open,
                Q0=>open,
                Q1=>open,
                Q2=>open,
                Q3=>AN0_DUMMY,
                TC=>open);
   
   XLXI_5 : VCC
      port map (P=>XLXN_1);
   
   XLXI_6 : fourbitadder
      port map (A0=>A0,
                A1=>A1,
                A2=>A2,
                A3=>A3,
                B0=>B0,
                B1=>B1,
                B2=>B2,
                B3=>B3,
                CIN=>CIN,
                COUT=>XLXN_36,
                S0=>XLXN_33,
                S1=>XLXN_32,
                S2=>XLXN_35,
                S3=>XLXN_34);
   
   XLXI_8 : decoder_7seg
      port map (a=>XLXN_28,
                b=>XLXN_29,
                c=>XLXN_30,
                d=>XLXN_31,
                ca=>CA,
                cb=>CB,
                cc=>CC,
                cd=>CD,
                ce=>CE,
                cf=>CF,
                cg=>CG,
                dp=>DP);
   
   XLXI_9 : GND
      port map (G=>XLXN_38);
   
   XLXI_12 : Mymux_MUSER_Clck
      port map (P0=>XLXN_36,
                P1=>XLXN_38,
                P2=>XLXN_38,
                P3=>XLXN_38,
                S=>AN0_DUMMY,
                S0=>XLXN_33,
                S1=>XLXN_32,
                S2=>XLXN_35,
                S3=>XLXN_34,
                Y0=>XLXN_28,
                Y1=>XLXN_29,
                Y2=>XLXN_30,
                Y3=>XLXN_31);
   
   XLXI_13 : INV
      port map (I=>AN0_DUMMY,
                O=>AN1);
   
end BEHAVIORAL;


