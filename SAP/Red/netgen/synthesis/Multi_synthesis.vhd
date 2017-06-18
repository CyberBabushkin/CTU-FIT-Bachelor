--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____
--  /   /\/   /
-- /___/  \  /    Vendor: Xilinx
-- \   \   \/     Version: P.20131013
--  \   \         Application: netgen
--  /   /         Filename: Multi_synthesis.vhd
-- /___/   /\     Timestamp: Fri Mar 06 10:10:48 2015
-- \   \  /  \ 
--  \___\/\___\
--             
-- Command	: -filter H:/BI-SAP/Red/iseconfig/filter.filter -intstyle ise -ar Structure -tm Multi -w -dir netgen/synthesis -ofmt vhdl -sim Multi.ngc Multi_synthesis.vhd 
-- Device	: xc3s100e-4-cp132
-- Input file	: Multi.ngc
-- Output file	: \\ucebnyfile.ucebny.adfit.fit.cvut.cz\home\a\arkhigle\BI-SAP\Red\netgen\synthesis\Multi_synthesis.vhd
-- # of Entities	: 1
-- Design Name	: Multi
-- Xilinx	: C:\Xilinx\14.7\ISE_DS\ISE\
--             
-- Purpose:    
--     This VHDL netlist is a verification model and uses simulation 
--     primitives which may not represent the true implementation of the 
--     device, however the netlist is functionally correct and should not 
--     be modified. This file cannot be synthesized and should only be used 
--     with supported simulation tools.
--             
-- Reference:  
--     Command Line Tools User Guide, Chapter 23
--     Synthesis and Simulation Design Guide, Chapter 6
--             
--------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
use UNISIM.VPKG.ALL;

entity Multi is
  port (
    CA : out STD_LOGIC; 
    CB : out STD_LOGIC; 
    CC : out STD_LOGIC; 
    CD : out STD_LOGIC; 
    CE : out STD_LOGIC; 
    CF : out STD_LOGIC; 
    CG : out STD_LOGIC; 
    DP : out STD_LOGIC; 
    A0 : in STD_LOGIC := 'X'; 
    A1 : in STD_LOGIC := 'X'; 
    B0 : in STD_LOGIC := 'X'; 
    B1 : in STD_LOGIC := 'X' 
  );
end Multi;

architecture Structure of Multi is
  signal A0_IBUF_1 : STD_LOGIC; 
  signal A1_IBUF_3 : STD_LOGIC; 
  signal B0_IBUF_5 : STD_LOGIC; 
  signal B1_IBUF_7 : STD_LOGIC; 
  signal CA_OBUF_9 : STD_LOGIC; 
  signal CB_OBUF_11 : STD_LOGIC; 
  signal CC_OBUF_13 : STD_LOGIC; 
  signal CD_OBUF_15 : STD_LOGIC; 
  signal CE_OBUF_17 : STD_LOGIC; 
  signal CF_OBUF_19 : STD_LOGIC; 
  signal CG_OBUF_21 : STD_LOGIC; 
  signal N1 : STD_LOGIC; 
  signal XLXI_1_XLXN_11 : STD_LOGIC; 
  signal XLXI_1_XLXN_13 : STD_LOGIC; 
  signal XLXI_1_XLXN_16 : STD_LOGIC; 
  signal XLXI_1_XLXN_17 : STD_LOGIC; 
  signal XLXN_1 : STD_LOGIC; 
  signal XLXN_2 : STD_LOGIC; 
  signal XLXN_3 : STD_LOGIC; 
  signal XLXN_4 : STD_LOGIC; 
begin
  XST_VCC : VCC
    port map (
      P => N1
    );
  XLXI_1_XLXI_8 : OR2
    port map (
      I0 => XLXI_1_XLXN_16,
      I1 => XLXI_1_XLXN_17,
      O => XLXN_2
    );
  XLXI_1_XLXI_7 : OR2
    port map (
      I0 => XLXI_1_XLXN_13,
      I1 => XLXI_1_XLXN_11,
      O => XLXN_4
    );
  XLXI_1_XLXI_6 : AND2
    port map (
      I0 => XLXI_1_XLXN_16,
      I1 => XLXI_1_XLXN_17,
      O => XLXN_3
    );
  XLXI_1_XLXI_5 : AND2
    port map (
      I0 => XLXI_1_XLXN_13,
      I1 => XLXI_1_XLXN_11,
      O => XLXI_1_XLXN_17
    );
  XLXI_1_XLXI_4 : AND2
    port map (
      I0 => B1_IBUF_7,
      I1 => A1_IBUF_3,
      O => XLXI_1_XLXN_16
    );
  XLXI_1_XLXI_3 : AND2
    port map (
      I0 => B0_IBUF_5,
      I1 => A1_IBUF_3,
      O => XLXI_1_XLXN_13
    );
  XLXI_1_XLXI_2 : AND2
    port map (
      I0 => B0_IBUF_5,
      I1 => A0_IBUF_1,
      O => XLXN_1
    );
  XLXI_1_XLXI_1 : AND2
    port map (
      I0 => B1_IBUF_7,
      I1 => A0_IBUF_1,
      O => XLXI_1_XLXN_11
    );
  XLXI_2_Mrom_input_rom000021 : LUT4
    generic map(
      INIT => X"454C"
    )
    port map (
      I0 => XLXN_3,
      I1 => XLXN_1,
      I2 => XLXN_4,
      I3 => XLXN_2,
      O => CE_OBUF_17
    );
  XLXI_2_cc1 : LUT4
    generic map(
      INIT => X"80A4"
    )
    port map (
      I0 => XLXN_3,
      I1 => XLXN_4,
      I2 => XLXN_2,
      I3 => XLXN_1,
      O => CC_OBUF_13
    );
  XLXI_2_cb1 : LUT4
    generic map(
      INIT => X"E228"
    )
    port map (
      I0 => XLXN_2,
      I1 => XLXN_1,
      I2 => XLXN_3,
      I3 => XLXN_4,
      O => CB_OBUF_11
    );
  XLXI_2_Mrom_input_rom0000111 : LUT4
    generic map(
      INIT => X"6054"
    )
    port map (
      I0 => XLXN_3,
      I1 => XLXN_4,
      I2 => XLXN_1,
      I3 => XLXN_2,
      O => CF_OBUF_19
    );
  XLXI_2_Mrom_input_rom000011 : LUT4
    generic map(
      INIT => X"2109"
    )
    port map (
      I0 => XLXN_2,
      I1 => XLXN_3,
      I2 => XLXN_4,
      I3 => XLXN_1,
      O => CG_OBUF_21
    );
  XLXI_2_ca1 : LUT4
    generic map(
      INIT => X"2190"
    )
    port map (
      I0 => XLXN_3,
      I1 => XLXN_4,
      I2 => XLXN_1,
      I3 => XLXN_2,
      O => CA_OBUF_9
    );
  XLXI_2_Mrom_input_rom000031 : LUT4
    generic map(
      INIT => X"9806"
    )
    port map (
      I0 => XLXN_1,
      I1 => XLXN_2,
      I2 => XLXN_3,
      I3 => XLXN_4,
      O => CD_OBUF_15
    );
  A0_IBUF : IBUF
    port map (
      I => A0,
      O => A0_IBUF_1
    );
  A1_IBUF : IBUF
    port map (
      I => A1,
      O => A1_IBUF_3
    );
  B0_IBUF : IBUF
    port map (
      I => B0,
      O => B0_IBUF_5
    );
  B1_IBUF : IBUF
    port map (
      I => B1,
      O => B1_IBUF_7
    );
  CA_OBUF : OBUF
    port map (
      I => CA_OBUF_9,
      O => CA
    );
  CB_OBUF : OBUF
    port map (
      I => CB_OBUF_11,
      O => CB
    );
  CC_OBUF : OBUF
    port map (
      I => CC_OBUF_13,
      O => CC
    );
  CD_OBUF : OBUF
    port map (
      I => CD_OBUF_15,
      O => CD
    );
  CE_OBUF : OBUF
    port map (
      I => CE_OBUF_17,
      O => CE
    );
  CF_OBUF : OBUF
    port map (
      I => CF_OBUF_19,
      O => CF
    );
  CG_OBUF : OBUF
    port map (
      I => CG_OBUF_21,
      O => CG
    );
  DP_OBUF : OBUF
    port map (
      I => N1,
      O => DP
    );

end Structure;

