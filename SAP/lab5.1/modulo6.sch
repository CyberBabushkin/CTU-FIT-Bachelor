<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3e" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_8" />
        <signal name="CLR" />
        <signal name="CLK" />
        <signal name="CLK_BTN" />
        <signal name="Q2_1" />
        <signal name="Q1_1" />
        <signal name="Q0_1" />
        <signal name="Y" />
        <signal name="XLXN_9" />
        <signal name="XLXN_10" />
        <signal name="XLXN_11" />
        <signal name="EN" />
        <port polarity="Input" name="CLR" />
        <port polarity="Input" name="CLK" />
        <port polarity="Input" name="CLK_BTN" />
        <port polarity="Output" name="Q2_1" />
        <port polarity="Output" name="Q1_1" />
        <port polarity="Output" name="Q0_1" />
        <port polarity="Output" name="Y" />
        <port polarity="Input" name="EN" />
        <blockdef name="debounce">
            <timestamp>2016-3-23T13:38:19</timestamp>
            <rect width="256" x="64" y="-128" height="128" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="384" y1="-96" y2="-96" x1="320" />
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
        <blockdef name="algebra">
            <timestamp>2016-3-30T13:28:48</timestamp>
            <rect width="256" x="64" y="-256" height="256" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <line x2="0" y1="-160" y2="-160" x1="64" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="384" y1="-224" y2="-224" x1="320" />
            <line x2="384" y1="-160" y2="-160" x1="320" />
            <line x2="384" y1="-96" y2="-96" x1="320" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
        </blockdef>
        <block symbolname="fdc" name="XLXI_4">
            <blockpin signalname="XLXN_8" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="Q1_1" name="D" />
            <blockpin signalname="XLXN_10" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_3">
            <blockpin signalname="XLXN_8" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="Q2_1" name="D" />
            <blockpin signalname="XLXN_9" name="Q" />
        </block>
        <block symbolname="debounce" name="XLXI_1">
            <blockpin signalname="CLK" name="clk" />
            <blockpin signalname="CLK_BTN" name="tl_in" />
            <blockpin signalname="XLXN_8" name="tl_out" />
        </block>
        <block symbolname="fdc" name="XLXI_5">
            <blockpin signalname="XLXN_8" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="Q0_1" name="D" />
            <blockpin signalname="XLXN_11" name="Q" />
        </block>
        <block symbolname="algebra" name="XLXI_6">
            <blockpin signalname="EN" name="en" />
            <blockpin signalname="XLXN_9" name="q2" />
            <blockpin signalname="XLXN_10" name="q1" />
            <blockpin signalname="XLXN_11" name="q0" />
            <blockpin signalname="Q2_1" name="s2" />
            <blockpin signalname="Q1_1" name="s1" />
            <blockpin signalname="Q0_1" name="s0" />
            <blockpin signalname="Y" name="y" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1344" y="1168" name="XLXI_4" orien="R0" />
        <instance x="1344" y="704" name="XLXI_3" orien="R0" />
        <branch name="XLXN_8">
            <wire x2="1264" y1="576" y2="576" x1="1104" />
            <wire x2="1264" y1="576" y2="1040" x1="1264" />
            <wire x2="1344" y1="1040" y2="1040" x1="1264" />
            <wire x2="1264" y1="1040" y2="1440" x1="1264" />
            <wire x2="1344" y1="1440" y2="1440" x1="1264" />
            <wire x2="1344" y1="576" y2="576" x1="1264" />
        </branch>
        <branch name="CLR">
            <wire x2="1296" y1="1648" y2="1648" x1="1264" />
            <wire x2="1344" y1="672" y2="672" x1="1296" />
            <wire x2="1296" y1="672" y2="1136" x1="1296" />
            <wire x2="1344" y1="1136" y2="1136" x1="1296" />
            <wire x2="1296" y1="1136" y2="1536" x1="1296" />
            <wire x2="1344" y1="1536" y2="1536" x1="1296" />
            <wire x2="1296" y1="1536" y2="1648" x1="1296" />
        </branch>
        <branch name="CLK">
            <wire x2="720" y1="576" y2="576" x1="464" />
        </branch>
        <branch name="CLK_BTN">
            <wire x2="720" y1="640" y2="640" x1="368" />
        </branch>
        <instance x="720" y="672" name="XLXI_1" orien="R0">
        </instance>
        <instance x="1344" y="1568" name="XLXI_5" orien="R0" />
        <iomarker fontsize="28" x="368" y="640" name="CLK_BTN" orien="R180" />
        <iomarker fontsize="28" x="464" y="576" name="CLK" orien="R180" />
        <iomarker fontsize="28" x="1264" y="1648" name="CLR" orien="R180" />
        <branch name="Q2_1">
            <wire x2="1040" y1="1344" y2="1344" x1="816" />
            <wire x2="864" y1="864" y2="864" x1="832" />
            <wire x2="992" y1="816" y2="816" x1="864" />
            <wire x2="992" y1="816" y2="992" x1="992" />
            <wire x2="1152" y1="992" y2="992" x1="992" />
            <wire x2="992" y1="992" y2="1168" x1="992" />
            <wire x2="1040" y1="1168" y2="1168" x1="992" />
            <wire x2="1040" y1="1168" y2="1344" x1="1040" />
            <wire x2="864" y1="816" y2="864" x1="864" />
            <wire x2="1152" y1="448" y2="992" x1="1152" />
            <wire x2="1344" y1="448" y2="448" x1="1152" />
        </branch>
        <branch name="Q1_1">
            <wire x2="1056" y1="1408" y2="1408" x1="816" />
            <wire x2="864" y1="928" y2="928" x1="832" />
            <wire x2="1056" y1="880" y2="880" x1="864" />
            <wire x2="1056" y1="880" y2="1056" x1="1056" />
            <wire x2="1168" y1="1056" y2="1056" x1="1056" />
            <wire x2="1056" y1="1056" y2="1408" x1="1056" />
            <wire x2="864" y1="880" y2="928" x1="864" />
            <wire x2="1168" y1="912" y2="1056" x1="1168" />
            <wire x2="1344" y1="912" y2="912" x1="1168" />
        </branch>
        <branch name="Q0_1">
            <wire x2="1104" y1="1472" y2="1472" x1="816" />
            <wire x2="864" y1="992" y2="992" x1="832" />
            <wire x2="1104" y1="944" y2="944" x1="864" />
            <wire x2="1104" y1="944" y2="1120" x1="1104" />
            <wire x2="1152" y1="1120" y2="1120" x1="1104" />
            <wire x2="1152" y1="1120" y2="1312" x1="1152" />
            <wire x2="1344" y1="1312" y2="1312" x1="1152" />
            <wire x2="1104" y1="1120" y2="1472" x1="1104" />
            <wire x2="864" y1="944" y2="992" x1="864" />
        </branch>
        <iomarker fontsize="28" x="816" y="1344" name="Q2_1" orien="R180" />
        <iomarker fontsize="28" x="816" y="1408" name="Q1_1" orien="R180" />
        <iomarker fontsize="28" x="816" y="1472" name="Q0_1" orien="R180" />
        <branch name="Y">
            <wire x2="864" y1="1056" y2="1056" x1="832" />
            <wire x2="864" y1="1056" y2="1088" x1="864" />
            <wire x2="928" y1="1088" y2="1088" x1="864" />
            <wire x2="928" y1="1088" y2="1152" x1="928" />
            <wire x2="1872" y1="1152" y2="1152" x1="928" />
            <wire x2="1872" y1="1152" y2="1600" x1="1872" />
            <wire x2="1888" y1="1600" y2="1600" x1="1872" />
        </branch>
        <iomarker fontsize="28" x="1888" y="1600" name="Y" orien="R0" />
        <instance x="448" y="1088" name="XLXI_6" orien="R0">
        </instance>
        <branch name="XLXN_9">
            <wire x2="400" y1="768" y2="928" x1="400" />
            <wire x2="448" y1="928" y2="928" x1="400" />
            <wire x2="1808" y1="768" y2="768" x1="400" />
            <wire x2="1808" y1="448" y2="448" x1="1728" />
            <wire x2="1808" y1="448" y2="768" x1="1808" />
        </branch>
        <branch name="XLXN_10">
            <wire x2="368" y1="752" y2="992" x1="368" />
            <wire x2="448" y1="992" y2="992" x1="368" />
            <wire x2="1792" y1="752" y2="752" x1="368" />
            <wire x2="1792" y1="752" y2="912" x1="1792" />
            <wire x2="1792" y1="912" y2="912" x1="1728" />
        </branch>
        <branch name="XLXN_11">
            <wire x2="448" y1="1056" y2="1056" x1="368" />
            <wire x2="368" y1="1056" y2="1232" x1="368" />
            <wire x2="1792" y1="1232" y2="1232" x1="368" />
            <wire x2="1792" y1="1232" y2="1312" x1="1792" />
            <wire x2="1792" y1="1312" y2="1312" x1="1728" />
        </branch>
        <branch name="EN">
            <wire x2="448" y1="864" y2="864" x1="352" />
            <wire x2="352" y1="864" y2="1408" x1="352" />
            <wire x2="448" y1="1408" y2="1408" x1="352" />
        </branch>
        <iomarker fontsize="28" x="448" y="1408" name="EN" orien="R0" />
    </sheet>
</drawing>