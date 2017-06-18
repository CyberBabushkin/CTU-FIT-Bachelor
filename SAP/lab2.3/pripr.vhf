--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : pripr.vhf
-- /___/   /\     Timestamp : 03/02/2016 15:27:17
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3e -flat -suppress -vhdl H:/SAP/lab2.3/pripr.vhf -w H:/SAP/lab2.3/pripr.sch
--Design Name: pripr
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

entity pripr is
   port ( a : in    std_logic; 
          b : in    std_logic; 
          c : in    std_logic; 
          f : out   std_logic);
end pripr;

architecture BEHAVIORAL of pripr is
   attribute BOX_TYPE   : string ;
   signal XLXN_8  : std_logic;
   signal XLXN_9  : std_logic;
   signal XLXN_10 : std_logic;
   component NOR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of NOR2 : component is "BLACK_BOX";
   
   component OR3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR3 : component is "BLACK_BOX";
   
   component AND3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3 : component is "BLACK_BOX";
   
begin
   XLXI_1 : NOR2
      port map (I0=>c,
                I1=>a,
                O=>XLXN_8);
   
   XLXI_2 : NOR2
      port map (I0=>b,
                I1=>c,
                O=>XLXN_9);
   
   XLXI_5 : OR3
      port map (I0=>XLXN_10,
                I1=>XLXN_9,
                I2=>XLXN_8,
                O=>f);
   
   XLXI_6 : AND3
      port map (I0=>b,
                I1=>c,
                I2=>a,
                O=>XLXN_10);
   
end BEHAVIORAL;


