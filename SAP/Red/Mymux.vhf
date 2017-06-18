--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : Mymux.vhf
-- /___/   /\     Timestamp : 03/06/2015 11:16:08
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3e -flat -suppress -vhdl H:/BI-SAP/Red/Mymux.vhf -w H:/BI-SAP/Red/Mymux.sch
--Design Name: Mymux
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

entity Mymux is
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
end Mymux;

architecture BEHAVIORAL of Mymux is
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


