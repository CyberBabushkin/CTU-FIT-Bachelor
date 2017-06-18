<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3e" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="Q2" />
        <signal name="Q1" />
        <signal name="Q0" />
        <signal name="XLXN_4" />
        <signal name="XLXN_5" />
        <signal name="XLXN_25" />
        <signal name="XLXN_26" />
        <signal name="EN" />
        <signal name="CLR" />
        <signal name="XLXN_29" />
        <signal name="XLXN_30" />
        <signal name="XLXN_31" />
        <signal name="CLK" />
        <signal name="XLXN_34" />
        <signal name="CLK_BTN" />
        <port polarity="Output" name="Q2" />
        <port polarity="Output" name="Q1" />
        <port polarity="Output" name="Q0" />
        <port polarity="Input" name="EN" />
        <port polarity="Input" name="CLR" />
        <port polarity="Input" name="CLK" />
        <port polarity="Input" name="CLK_BTN" />
        <blockdef name="algebra">
            <timestamp>2016-3-23T13:13:29</timestamp>
            <rect width="256" x="64" y="-256" height="256" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <line x2="0" y1="-160" y2="-160" x1="64" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="384" y1="-224" y2="-224" x1="320" />
            <line x2="384" y1="-128" y2="-128" x1="320" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
        </blockdef>
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
        <blockdef name="debounce">
            <timestamp>2016-3-23T13:13:19</timestamp>
            <rect width="256" x="64" y="-128" height="128" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="384" y1="-96" y2="-96" x1="320" />
        </blockdef>
        <block symbolname="algebra" name="XLXI_1">
            <blockpin signalname="EN" name="en" />
            <blockpin signalname="XLXN_4" name="a2" />
            <blockpin signalname="XLXN_25" name="a1" />
            <blockpin signalname="XLXN_26" name="a0" />
            <blockpin signalname="Q2" name="q2" />
            <blockpin signalname="Q1" name="q1" />
            <blockpin signalname="Q0" name="q0" />
        </block>
        <block symbolname="fdc" name="XLXI_2">
            <blockpin signalname="XLXN_30" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="Q2" name="D" />
            <blockpin signalname="XLXN_4" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_3">
            <blockpin signalname="XLXN_30" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="Q1" name="D" />
            <blockpin signalname="XLXN_25" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_4">
            <blockpin signalname="XLXN_30" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="Q0" name="D" />
            <blockpin signalname="XLXN_26" name="Q" />
        </block>
        <block symbolname="debounce" name="XLXI_5">
            <blockpin signalname="CLK" name="clk" />
            <blockpin signalname="CLK_BTN" name="tl_in" />
            <blockpin signalname="XLXN_30" name="tl_out" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1920" y="896" name="XLXI_2" orien="R0" />
        <branch name="Q2">
            <wire x2="1536" y1="1168" y2="1168" x1="1296" />
            <wire x2="1904" y1="1168" y2="1168" x1="1536" />
            <wire x2="1536" y1="1168" y2="1952" x1="1536" />
            <wire x2="1920" y1="640" y2="640" x1="1904" />
            <wire x2="1904" y1="640" y2="1168" x1="1904" />
        </branch>
        <instance x="1984" y="1504" name="XLXI_3" orien="R0" />
        <branch name="Q1">
            <wire x2="1472" y1="1264" y2="1264" x1="1296" />
            <wire x2="1968" y1="1264" y2="1264" x1="1472" />
            <wire x2="1472" y1="1264" y2="1840" x1="1472" />
            <wire x2="1984" y1="1248" y2="1248" x1="1968" />
            <wire x2="1968" y1="1248" y2="1264" x1="1968" />
        </branch>
        <instance x="2000" y="2048" name="XLXI_4" orien="R0" />
        <instance x="912" y="1392" name="XLXI_1" orien="R0">
        </instance>
        <branch name="XLXN_4">
            <wire x2="832" y1="1056" y2="1232" x1="832" />
            <wire x2="912" y1="1232" y2="1232" x1="832" />
            <wire x2="2320" y1="1056" y2="1056" x1="832" />
            <wire x2="2320" y1="640" y2="640" x1="2304" />
            <wire x2="2320" y1="640" y2="1056" x1="2320" />
        </branch>
        <branch name="Q0">
            <wire x2="1392" y1="1360" y2="1360" x1="1296" />
            <wire x2="1632" y1="1360" y2="1360" x1="1392" />
            <wire x2="1632" y1="1360" y2="1792" x1="1632" />
            <wire x2="2000" y1="1792" y2="1792" x1="1632" />
            <wire x2="1392" y1="1360" y2="1776" x1="1392" />
        </branch>
        <branch name="XLXN_25">
            <wire x2="912" y1="1296" y2="1296" x1="848" />
            <wire x2="848" y1="1296" y2="1488" x1="848" />
            <wire x2="2432" y1="1488" y2="1488" x1="848" />
            <wire x2="2432" y1="1248" y2="1248" x1="2368" />
            <wire x2="2432" y1="1248" y2="1488" x1="2432" />
        </branch>
        <branch name="XLXN_26">
            <wire x2="912" y1="1360" y2="1360" x1="784" />
            <wire x2="784" y1="1360" y2="1600" x1="784" />
            <wire x2="2432" y1="1600" y2="1600" x1="784" />
            <wire x2="2432" y1="1600" y2="1792" x1="2432" />
            <wire x2="2432" y1="1792" y2="1792" x1="2384" />
        </branch>
        <branch name="EN">
            <wire x2="912" y1="1168" y2="1168" x1="352" />
        </branch>
        <branch name="CLR">
            <wire x2="1920" y1="864" y2="864" x1="1792" />
            <wire x2="1792" y1="864" y2="1472" x1="1792" />
            <wire x2="1984" y1="1472" y2="1472" x1="1792" />
            <wire x2="1792" y1="1472" y2="2016" x1="1792" />
            <wire x2="1792" y1="2016" y2="2192" x1="1792" />
            <wire x2="2000" y1="2016" y2="2016" x1="1792" />
        </branch>
        <branch name="XLXN_30">
            <wire x2="1568" y1="608" y2="608" x1="1392" />
            <wire x2="1568" y1="608" y2="768" x1="1568" />
            <wire x2="1744" y1="768" y2="768" x1="1568" />
            <wire x2="1920" y1="768" y2="768" x1="1744" />
            <wire x2="1744" y1="768" y2="1376" x1="1744" />
            <wire x2="1984" y1="1376" y2="1376" x1="1744" />
            <wire x2="1744" y1="1376" y2="1920" x1="1744" />
            <wire x2="2000" y1="1920" y2="1920" x1="1744" />
        </branch>
        <instance x="1008" y="704" name="XLXI_5" orien="R0">
        </instance>
        <branch name="CLK">
            <wire x2="1008" y1="608" y2="608" x1="816" />
        </branch>
        <branch name="CLK_BTN">
            <wire x2="960" y1="720" y2="720" x1="816" />
            <wire x2="1008" y1="672" y2="672" x1="960" />
            <wire x2="960" y1="672" y2="720" x1="960" />
        </branch>
        <iomarker fontsize="28" x="816" y="608" name="CLK" orien="R180" />
        <iomarker fontsize="28" x="816" y="720" name="CLK_BTN" orien="R180" />
        <iomarker fontsize="28" x="352" y="1168" name="EN" orien="R180" />
        <iomarker fontsize="28" x="1792" y="2192" name="CLR" orien="R90" />
        <iomarker fontsize="28" x="1392" y="1776" name="Q0" orien="R90" />
        <iomarker fontsize="28" x="1472" y="1840" name="Q1" orien="R90" />
        <iomarker fontsize="28" x="1536" y="1952" name="Q2" orien="R90" />
    </sheet>
</drawing>