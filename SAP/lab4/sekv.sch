<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3e" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_54" />
        <signal name="XLXN_48" />
        <signal name="XLXN_49" />
        <signal name="XLXN_50" />
        <signal name="XLXN_54" />
        <port polarity="Input" name="XLXN_54" />
        <blockdef name="fdc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <rect width="256" x="64" y="-320" height="256" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
        </blockdef>
        <blockdef name="algebra">
            <timestamp>2016-3-16T14:14:30</timestamp>
            <rect width="256" x="64" y="-256" height="256" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <line x2="0" y1="-160" y2="-160" x1="64" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="384" y1="-224" y2="-224" x1="320" />
            <line x2="384" y1="-128" y2="-128" x1="320" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
        </blockdef>
        <blockdef name="debounce">
            <timestamp>2016-3-16T14:18:20</timestamp>
            <rect width="256" x="64" y="-128" height="128" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="384" y1="-96" y2="-96" x1="320" />
        </blockdef>
        <block symbolname="algebra" name="XLXI_5">
            <blockpin name="en" />
            <blockpin name="a2" />
            <blockpin name="a1" />
            <blockpin name="a0" />
            <blockpin name="q2" />
            <blockpin name="q1" />
            <blockpin name="q0" />
        </block>
        <block symbolname="debounce" name="XLXI_6">
            <blockpin name="clk" />
            <blockpin name="tl_in" />
            <blockpin name="tl_out" />
        </block>
        <block symbolname="fdc" name="XLXI_3">
            <blockpin name="C" />
            <blockpin name="CLR" />
            <blockpin name="D" />
            <blockpin name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_1">
            <blockpin name="C" />
            <blockpin name="CLR" />
            <blockpin name="D" />
            <blockpin name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_2">
            <blockpin name="C" />
            <blockpin name="CLR" />
            <blockpin name="D" />
            <blockpin name="Q" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="512" y="2144" name="XLXI_6" orien="R0">
        </instance>
        <instance x="624" y="1408" name="XLXI_5" orien="R0">
        </instance>
        <instance x="1504" y="1008" name="XLXI_1" orien="R0" />
        <instance x="1504" y="1440" name="XLXI_2" orien="R0" />
        <instance x="1488" y="1952" name="XLXI_3" orien="R0" />
    </sheet>
</drawing>