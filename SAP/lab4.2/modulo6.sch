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
        <signal name="Q2_1" />
        <signal name="Q1_1" />
        <signal name="Q0_1" />
        <signal name="EN" />
        <signal name="XLXN_8" />
        <signal name="CLR" />
        <signal name="CLK" />
        <signal name="CLK_BTN" />
        <port polarity="Output" name="Q2" />
        <port polarity="Output" name="Q1" />
        <port polarity="Output" name="Q0" />
        <port polarity="Output" name="Q2_1" />
        <port polarity="Output" name="Q1_1" />
        <port polarity="Output" name="Q0_1" />
        <port polarity="Input" name="EN" />
        <port polarity="Input" name="CLR" />
        <port polarity="Input" name="CLK" />
        <port polarity="Input" name="CLK_BTN" />
        <blockdef name="debounce">
            <timestamp>2016-3-23T13:38:19</timestamp>
            <rect width="256" x="64" y="-128" height="128" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="384" y1="-96" y2="-96" x1="320" />
        </blockdef>
        <blockdef name="algebra">
            <timestamp>2016-3-23T13:38:37</timestamp>
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
        <block symbolname="fdc" name="XLXI_4">
            <blockpin signalname="XLXN_8" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="Q1" name="D" />
            <blockpin signalname="Q1_1" name="Q" />
        </block>
        <block symbolname="algebra" name="XLXI_2">
            <blockpin signalname="EN" name="en" />
            <blockpin signalname="Q2_1" name="a2" />
            <blockpin signalname="Q1_1" name="a1" />
            <blockpin signalname="Q0_1" name="a0" />
            <blockpin signalname="Q2" name="q2" />
            <blockpin signalname="Q1" name="q1" />
            <blockpin signalname="Q0" name="q0" />
        </block>
        <block symbolname="fdc" name="XLXI_3">
            <blockpin signalname="XLXN_8" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="Q2" name="D" />
            <blockpin signalname="Q2_1" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_5">
            <blockpin signalname="XLXN_8" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="Q0" name="D" />
            <blockpin signalname="Q0_1" name="Q" />
        </block>
        <block symbolname="debounce" name="XLXI_1">
            <blockpin signalname="CLK" name="clk" />
            <blockpin signalname="CLK_BTN" name="tl_in" />
            <blockpin signalname="XLXN_8" name="tl_out" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1696" y="1184" name="XLXI_4" orien="R0" />
        <instance x="944" y="1248" name="XLXI_2" orien="R0">
        </instance>
        <instance x="1696" y="720" name="XLXI_3" orien="R0" />
        <branch name="Q2">
            <wire x2="1360" y1="1344" y2="1344" x1="1296" />
            <wire x2="1360" y1="1024" y2="1024" x1="1328" />
            <wire x2="1504" y1="1024" y2="1024" x1="1360" />
            <wire x2="1360" y1="1024" y2="1344" x1="1360" />
            <wire x2="1504" y1="464" y2="1024" x1="1504" />
            <wire x2="1696" y1="464" y2="464" x1="1504" />
        </branch>
        <branch name="Q1">
            <wire x2="1392" y1="1392" y2="1392" x1="1264" />
            <wire x2="1392" y1="1120" y2="1120" x1="1328" />
            <wire x2="1568" y1="1120" y2="1120" x1="1392" />
            <wire x2="1392" y1="1120" y2="1392" x1="1392" />
            <wire x2="1696" y1="928" y2="928" x1="1568" />
            <wire x2="1568" y1="928" y2="1120" x1="1568" />
        </branch>
        <branch name="Q0">
            <wire x2="1424" y1="1456" y2="1456" x1="1200" />
            <wire x2="1424" y1="1216" y2="1216" x1="1328" />
            <wire x2="1424" y1="1216" y2="1456" x1="1424" />
            <wire x2="1552" y1="1216" y2="1216" x1="1424" />
            <wire x2="1552" y1="1216" y2="1328" x1="1552" />
            <wire x2="1696" y1="1328" y2="1328" x1="1552" />
        </branch>
        <branch name="Q2_1">
            <wire x2="2176" y1="784" y2="784" x1="816" />
            <wire x2="816" y1="784" y2="1088" x1="816" />
            <wire x2="944" y1="1088" y2="1088" x1="816" />
            <wire x2="2176" y1="464" y2="464" x1="2080" />
            <wire x2="2176" y1="464" y2="560" x1="2176" />
            <wire x2="2176" y1="560" y2="784" x1="2176" />
            <wire x2="2304" y1="560" y2="560" x1="2176" />
        </branch>
        <branch name="Q1_1">
            <wire x2="944" y1="1152" y2="1152" x1="816" />
            <wire x2="816" y1="1152" y2="1616" x1="816" />
            <wire x2="2352" y1="1616" y2="1616" x1="816" />
            <wire x2="2352" y1="928" y2="928" x1="2080" />
            <wire x2="2352" y1="928" y2="1008" x1="2352" />
            <wire x2="2352" y1="1008" y2="1616" x1="2352" />
            <wire x2="2528" y1="1008" y2="1008" x1="2352" />
        </branch>
        <branch name="Q0_1">
            <wire x2="944" y1="1216" y2="1216" x1="928" />
            <wire x2="928" y1="1216" y2="1584" x1="928" />
            <wire x2="2160" y1="1584" y2="1584" x1="928" />
            <wire x2="2160" y1="1328" y2="1328" x1="2080" />
            <wire x2="2160" y1="1328" y2="1392" x1="2160" />
            <wire x2="2160" y1="1392" y2="1584" x1="2160" />
            <wire x2="2480" y1="1392" y2="1392" x1="2160" />
        </branch>
        <branch name="EN">
            <wire x2="944" y1="1024" y2="1024" x1="576" />
        </branch>
        <branch name="XLXN_8">
            <wire x2="1616" y1="592" y2="592" x1="1456" />
            <wire x2="1616" y1="592" y2="1056" x1="1616" />
            <wire x2="1696" y1="1056" y2="1056" x1="1616" />
            <wire x2="1616" y1="1056" y2="1456" x1="1616" />
            <wire x2="1696" y1="1456" y2="1456" x1="1616" />
            <wire x2="1696" y1="592" y2="592" x1="1616" />
        </branch>
        <branch name="CLR">
            <wire x2="1648" y1="1664" y2="1664" x1="1616" />
            <wire x2="1696" y1="688" y2="688" x1="1648" />
            <wire x2="1648" y1="688" y2="1152" x1="1648" />
            <wire x2="1696" y1="1152" y2="1152" x1="1648" />
            <wire x2="1648" y1="1152" y2="1552" x1="1648" />
            <wire x2="1696" y1="1552" y2="1552" x1="1648" />
            <wire x2="1648" y1="1552" y2="1664" x1="1648" />
        </branch>
        <branch name="CLK">
            <wire x2="1072" y1="592" y2="592" x1="816" />
        </branch>
        <branch name="CLK_BTN">
            <wire x2="1072" y1="656" y2="656" x1="720" />
        </branch>
        <instance x="1072" y="688" name="XLXI_1" orien="R0">
        </instance>
        <iomarker fontsize="28" x="576" y="1024" name="EN" orien="R180" />
        <iomarker fontsize="28" x="1296" y="1344" name="Q2" orien="R180" />
        <iomarker fontsize="28" x="1264" y="1392" name="Q1" orien="R180" />
        <iomarker fontsize="28" x="1200" y="1456" name="Q0" orien="R180" />
        <iomarker fontsize="28" x="720" y="656" name="CLK_BTN" orien="R180" />
        <iomarker fontsize="28" x="816" y="592" name="CLK" orien="R180" />
        <instance x="1696" y="1584" name="XLXI_5" orien="R0" />
        <iomarker fontsize="28" x="1616" y="1664" name="CLR" orien="R180" />
        <iomarker fontsize="28" x="2304" y="560" name="Q2_1" orien="R0" />
        <iomarker fontsize="28" x="2528" y="1008" name="Q1_1" orien="R0" />
        <iomarker fontsize="28" x="2480" y="1392" name="Q0_1" orien="R0" />
    </sheet>
</drawing>