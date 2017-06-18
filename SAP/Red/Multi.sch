<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3e" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_1" />
        <signal name="XLXN_2" />
        <signal name="XLXN_3" />
        <signal name="XLXN_4" />
        <signal name="A0" />
        <signal name="B0" />
        <signal name="A1" />
        <signal name="B1" />
        <signal name="DP" />
        <signal name="CG" />
        <signal name="CF" />
        <signal name="CE" />
        <signal name="CD" />
        <signal name="CC" />
        <signal name="CB" />
        <signal name="CA" />
        <port polarity="Input" name="A0" />
        <port polarity="Input" name="B0" />
        <port polarity="Input" name="A1" />
        <port polarity="Input" name="B1" />
        <port polarity="Output" name="DP" />
        <port polarity="Output" name="CG" />
        <port polarity="Output" name="CF" />
        <port polarity="Output" name="CE" />
        <port polarity="Output" name="CD" />
        <port polarity="Output" name="CC" />
        <port polarity="Output" name="CB" />
        <port polarity="Output" name="CA" />
        <blockdef name="Multiplier2x2">
            <timestamp>2015-3-6T9:5:17</timestamp>
            <rect width="256" x="64" y="-256" height="256" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <line x2="0" y1="-160" y2="-160" x1="64" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="384" y1="-160" y2="-160" x1="320" />
            <line x2="384" y1="-224" y2="-224" x1="320" />
            <line x2="384" y1="-96" y2="-96" x1="320" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
        </blockdef>
        <blockdef name="decoder_7seg">
            <timestamp>2015-3-4T22:59:41</timestamp>
            <rect width="256" x="64" y="-512" height="512" />
            <line x2="0" y1="-480" y2="-480" x1="64" />
            <line x2="0" y1="-336" y2="-336" x1="64" />
            <line x2="0" y1="-192" y2="-192" x1="64" />
            <line x2="0" y1="-48" y2="-48" x1="64" />
            <line x2="384" y1="-480" y2="-480" x1="320" />
            <line x2="384" y1="-416" y2="-416" x1="320" />
            <line x2="384" y1="-352" y2="-352" x1="320" />
            <line x2="384" y1="-288" y2="-288" x1="320" />
            <line x2="384" y1="-224" y2="-224" x1="320" />
            <line x2="384" y1="-160" y2="-160" x1="320" />
            <line x2="384" y1="-96" y2="-96" x1="320" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
        </blockdef>
        <block symbolname="Multiplier2x2" name="XLXI_1">
            <blockpin signalname="A0" name="A0" />
            <blockpin signalname="A1" name="A1" />
            <blockpin signalname="B0" name="B0" />
            <blockpin signalname="B1" name="B1" />
            <blockpin signalname="XLXN_1" name="C0" />
            <blockpin signalname="XLXN_4" name="C1" />
            <blockpin signalname="XLXN_2" name="C2" />
            <blockpin signalname="XLXN_3" name="C3" />
        </block>
        <block symbolname="decoder_7seg" name="XLXI_2">
            <blockpin signalname="XLXN_3" name="d" />
            <blockpin signalname="XLXN_2" name="c" />
            <blockpin signalname="XLXN_4" name="b" />
            <blockpin signalname="XLXN_1" name="a" />
            <blockpin signalname="CA" name="ca" />
            <blockpin signalname="CB" name="cb" />
            <blockpin signalname="CC" name="cc" />
            <blockpin signalname="CD" name="cd" />
            <blockpin signalname="CE" name="ce" />
            <blockpin signalname="CF" name="cf" />
            <blockpin signalname="CG" name="cg" />
            <blockpin signalname="DP" name="dp" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="592" y="784" name="XLXI_1" orien="R0">
        </instance>
        <instance x="1392" y="912" name="XLXI_2" orien="R0">
        </instance>
        <branch name="XLXN_1">
            <wire x2="1184" y1="624" y2="624" x1="976" />
            <wire x2="1184" y1="624" y2="864" x1="1184" />
            <wire x2="1392" y1="864" y2="864" x1="1184" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="1200" y1="688" y2="688" x1="976" />
            <wire x2="1200" y1="576" y2="688" x1="1200" />
            <wire x2="1392" y1="576" y2="576" x1="1200" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="1168" y1="752" y2="752" x1="976" />
            <wire x2="1168" y1="432" y2="752" x1="1168" />
            <wire x2="1392" y1="432" y2="432" x1="1168" />
        </branch>
        <branch name="XLXN_4">
            <wire x2="1152" y1="560" y2="560" x1="976" />
            <wire x2="1152" y1="560" y2="720" x1="1152" />
            <wire x2="1392" y1="720" y2="720" x1="1152" />
        </branch>
        <branch name="A0">
            <wire x2="592" y1="560" y2="560" x1="560" />
        </branch>
        <iomarker fontsize="28" x="560" y="560" name="A0" orien="R180" />
        <branch name="B0">
            <wire x2="592" y1="624" y2="624" x1="560" />
        </branch>
        <iomarker fontsize="28" x="560" y="624" name="B0" orien="R180" />
        <branch name="A1">
            <wire x2="592" y1="688" y2="688" x1="560" />
        </branch>
        <iomarker fontsize="28" x="560" y="688" name="A1" orien="R180" />
        <branch name="B1">
            <wire x2="592" y1="752" y2="752" x1="560" />
        </branch>
        <iomarker fontsize="28" x="560" y="752" name="B1" orien="R180" />
        <branch name="DP">
            <wire x2="1808" y1="880" y2="880" x1="1776" />
        </branch>
        <iomarker fontsize="28" x="1808" y="880" name="DP" orien="R0" />
        <branch name="CG">
            <wire x2="1808" y1="816" y2="816" x1="1776" />
        </branch>
        <iomarker fontsize="28" x="1808" y="816" name="CG" orien="R0" />
        <branch name="CF">
            <wire x2="1808" y1="752" y2="752" x1="1776" />
        </branch>
        <iomarker fontsize="28" x="1808" y="752" name="CF" orien="R0" />
        <branch name="CE">
            <wire x2="1808" y1="688" y2="688" x1="1776" />
        </branch>
        <iomarker fontsize="28" x="1808" y="688" name="CE" orien="R0" />
        <branch name="CD">
            <wire x2="1808" y1="624" y2="624" x1="1776" />
        </branch>
        <iomarker fontsize="28" x="1808" y="624" name="CD" orien="R0" />
        <branch name="CC">
            <wire x2="1808" y1="560" y2="560" x1="1776" />
        </branch>
        <iomarker fontsize="28" x="1808" y="560" name="CC" orien="R0" />
        <branch name="CB">
            <wire x2="1808" y1="496" y2="496" x1="1776" />
        </branch>
        <iomarker fontsize="28" x="1808" y="496" name="CB" orien="R0" />
        <branch name="CA">
            <wire x2="1808" y1="432" y2="432" x1="1776" />
        </branch>
        <iomarker fontsize="28" x="1808" y="432" name="CA" orien="R0" />
    </sheet>
</drawing>