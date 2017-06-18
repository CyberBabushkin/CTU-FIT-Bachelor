--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : schema.vhf
-- /___/   /\     Timestamp : 03/14/2016 15:34:07
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3e -flat -suppress -vhdl H:/SAP/lab3/schema.vhf -w H:/SAP/lab3/schema.sch
--Design Name: schema
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

entity schema is
   port ( m0_c0 : in    std_logic; 
          m1_c0 : in    std_logic; 
          m2_c0 : in    std_logic; 
          m3_c0 : in    std_logic; 
          an0   : out   std_logic; 
          an1   : out   std_logic; 
          an2   : out   std_logic; 
          an3   : out   std_logic; 
          a0    : out   std_logic; 
          b0    : out   std_logic; 
          c0    : out   std_logic; 
          d0    : out   std_logic; 
          e0    : out   std_logic; 
          f0    : out   std_logic; 
          g0    : out   std_logic);
end schema;

architecture BEHAVIORAL of schema is
   attribute BOX_TYPE   : string ;
   component algebra
      port ( x : in    std_logic; 
             y : in    std_logic; 
             z : in    std_logic; 
             t : in    std_logic; 
             a : out   std_logic; 
             b : out   std_logic; 
             c : out   std_logic; 
             d : out   std_logic; 
             e : out   std_logic; 
             f : out   std_logic; 
             g : out   std_logic);
   end component;
   
   component GND
      port ( G : out   std_logic);
   end component;
   attribute BOX_TYPE of GND : component is "BLACK_BOX";
   
   component VCC
      port ( P : out   std_logic);
   end component;
   attribute BOX_TYPE of VCC : component is "BLACK_BOX";
   
begin
   XLXI_1 : algebra
      port map (t=>m0_c0,
                x=>m3_c0,
                y=>m2_c0,
                z=>m1_c0,
                a=>a0,
                b=>b0,
                c=>c0,
                d=>d0,
                e=>e0,
                f=>f0,
                g=>g0);
   
   XLXI_6 : GND
      port map (G=>an0);
   
   XLXI_10 : VCC
      port map (P=>an2);
   
   XLXI_11 : VCC
      port map (P=>an1);
   
   XLXI_12 : VCC
      port map (P=>an3);
   
end BEHAVIORAL;


