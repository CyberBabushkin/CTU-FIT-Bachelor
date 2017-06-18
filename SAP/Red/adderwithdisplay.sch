<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3e" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="B1" />
        <signal name="A1" />
        <signal name="B2" />
        <signal name="A0" />
        <signal name="B0" />
        <signal name="A2" />
        <signal name="A3" />
        <signal name="B3" />
        <signal name="CIN" />
        <signal name="COUT" />
        <signal name="XLXN_27" />
        <signal name="XLXN_28" />
        <signal name="XLXN_29" />
        <signal name="XLXN_30" />
        <signal name="CA" />
        <signal name="CB" />
        <signal name="CC" />
        <signal name="CD" />
        <signal name="CE" />
        <signal name="CF" />
        <signal name="CG" />
        <signal name="DP" />
        <port polarity="Input" name="B1" />
        <port polarity="Input" name="A1" />
        <port polarity="Input" name="B2" />
        <port polarity="Input" name="A0" />
        <port polarity="Input" name="B0" />
        <port polarity="Input" name="A2" />
        <port polarity="Input" name="A3" />
        <port polarity="Input" name="B3" />
        <port polarity="Input" name="CIN" />
        <port polarity="Output" name="COUT" />
        <port polarity="Output" name="CA" />
        <port polarity="Output" name="CB" />
        <port polarity="Output" name="CC" />
        <port polarity="Output" name="CD" />
        <port polarity="Output" name="CE" />
        <port polarity="Output" name="CF" />
        <port polarity="Output" name="CG" />
        <port polarity="Output" name="DP" />
        <blockdef name="fourbitadder">
            <timestamp>2015-3-4T22:21:38</timestamp>
            <rect width="256" x="64" y="-576" height="576" />
            <line x2="0" y1="-544" y2="-544" x1="64" />
            <line x2="0" y1="-480" y2="-480" x1="64" />
            <line x2="0" y1="-416" y2="-416" x1="64" />
            <line x2="0" y1="-352" y2="-352" x1="64" />
            <line x2="0" y1="-288" y2="-288" x1="64" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <line x2="0" y1="-160" y2="-160" x1="64" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="384" y1="-544" y2="-544" x1="320" />
            <line x2="384" y1="-480" y2="-480" x1="320" />
            <line x2="384" y1="-416" y2="-416" x1="320" />
            <line x2="384" y1="-352" y2="-352" x1="320" />
            <line x2="384" y1="-288" y2="-288" x1="320" />
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
        <block symbolname="fourbitadder" name="XLXI_2">
            <blockpin signalname="B1" name="B1" />
            <blockpin signalname="A1" name="A1" />
            <blockpin signalname="B2" name="B2" />
            <blockpin signalname="A0" name="A0" />
            <blockpin signalname="B0" name="B0" />
            <blockpin signalname="A2" name="A2" />
            <blockpin signalname="A3" name="A3" />
            <blockpin signalname="B3" name="B3" />
            <blockpin signalname="CIN" name="CIN" />
            <blockpin signalname="COUT" name="COUT" />
            <blockpin signalname="XLXN_27" name="S3" />
            <blockpin signalname="XLXN_28" name="S0" />
            <blockpin signalname="XLXN_29" name="S2" />
            <blockpin signalname="XLXN_30" name="S1" />
        </block>
        <block symbolname="decoder_7seg" name="XLXI_5">
            <blockpin signalname="XLXN_27" name="d" />
            <blockpin signalname="XLXN_29" name="c" />
            <blockpin signalname="XLXN_30" name="b" />
            <blockpin signalname="XLXN_28" name="a" />
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
        <instance x="368" y="848" name="XLXI_2" orien="R0">
        </instance>
        <branch name="B1">
            <wire x2="352" y1="304" y2="304" x1="336" />
            <wire x2="368" y1="304" y2="304" x1="352" />
        </branch>
        <iomarker fontsize="28" x="336" y="304" name="B1" orien="R180" />
        <branch name="A1">
            <wire x2="352" y1="368" y2="368" x1="336" />
            <wire x2="368" y1="368" y2="368" x1="352" />
        </branch>
        <iomarker fontsize="28" x="336" y="368" name="A1" orien="R180" />
        <branch name="B2">
            <wire x2="352" y1="432" y2="432" x1="336" />
            <wire x2="368" y1="432" y2="432" x1="352" />
        </branch>
        <iomarker fontsize="28" x="336" y="432" name="B2" orien="R180" />
        <branch name="A0">
            <wire x2="352" y1="496" y2="496" x1="336" />
            <wire x2="368" y1="496" y2="496" x1="352" />
        </branch>
        <iomarker fontsize="28" x="336" y="496" name="A0" orien="R180" />
        <branch name="B0">
            <wire x2="352" y1="560" y2="560" x1="336" />
            <wire x2="368" y1="560" y2="560" x1="352" />
        </branch>
        <iomarker fontsize="28" x="336" y="560" name="B0" orien="R180" />
        <branch name="A2">
            <wire x2="352" y1="624" y2="624" x1="336" />
            <wire x2="368" y1="624" y2="624" x1="352" />
        </branch>
        <iomarker fontsize="28" x="336" y="624" name="A2" orien="R180" />
        <branch name="A3">
            <wire x2="352" y1="688" y2="688" x1="336" />
            <wire x2="368" y1="688" y2="688" x1="352" />
        </branch>
        <iomarker fontsize="28" x="336" y="688" name="A3" orien="R180" />
        <branch name="B3">
            <wire x2="352" y1="752" y2="752" x1="336" />
            <wire x2="368" y1="752" y2="752" x1="352" />
        </branch>
        <iomarker fontsize="28" x="336" y="752" name="B3" orien="R180" />
        <branch name="CIN">
            <wire x2="352" y1="816" y2="816" x1="336" />
            <wire x2="368" y1="816" y2="816" x1="352" />
        </branch>
        <iomarker fontsize="28" x="336" y="816" name="CIN" orien="R180" />
        <branch name="COUT">
            <wire x2="768" y1="304" y2="304" x1="752" />
            <wire x2="784" y1="304" y2="304" x1="768" />
        </branch>
        <iomarker fontsize="28" x="784" y="304" name="COUT" orien="R0" />
        <instance x="1360" y="768" name="XLXI_5" orien="R0">
        </instance>
        <branch name="XLXN_27">
            <wire x2="1056" y1="368" y2="368" x1="752" />
            <wire x2="1056" y1="288" y2="368" x1="1056" />
            <wire x2="1360" y1="288" y2="288" x1="1056" />
        </branch>
        <branch name="XLXN_28">
            <wire x2="1056" y1="432" y2="432" x1="752" />
            <wire x2="1056" y1="432" y2="720" x1="1056" />
            <wire x2="1360" y1="720" y2="720" x1="1056" />
        </branch>
        <branch name="XLXN_29">
            <wire x2="1072" y1="496" y2="496" x1="752" />
            <wire x2="1072" y1="432" y2="496" x1="1072" />
            <wire x2="1360" y1="432" y2="432" x1="1072" />
        </branch>
        <branch name="XLXN_30">
            <wire x2="1040" y1="560" y2="560" x1="752" />
            <wire x2="1040" y1="560" y2="576" x1="1040" />
            <wire x2="1360" y1="576" y2="576" x1="1040" />
        </branch>
        <branch name="CA">
            <wire x2="1776" y1="288" y2="288" x1="1744" />
        </branch>
        <iomarker fontsize="28" x="1776" y="288" name="CA" orien="R0" />
        <branch name="CB">
            <wire x2="1776" y1="352" y2="352" x1="1744" />
        </branch>
        <iomarker fontsize="28" x="1776" y="352" name="CB" orien="R0" />
        <branch name="CC">
            <wire x2="1776" y1="416" y2="416" x1="1744" />
        </branch>
        <iomarker fontsize="28" x="1776" y="416" name="CC" orien="R0" />
        <branch name="CD">
            <wire x2="1776" y1="480" y2="480" x1="1744" />
        </branch>
        <iomarker fontsize="28" x="1776" y="480" name="CD" orien="R0" />
        <branch name="CE">
            <wire x2="1776" y1="544" y2="544" x1="1744" />
        </branch>
        <iomarker fontsize="28" x="1776" y="544" name="CE" orien="R0" />
        <branch name="CF">
            <wire x2="1776" y1="608" y2="608" x1="1744" />
        </branch>
        <iomarker fontsize="28" x="1776" y="608" name="CF" orien="R0" />
        <branch name="CG">
            <wire x2="1776" y1="672" y2="672" x1="1744" />
        </branch>
        <iomarker fontsize="28" x="1776" y="672" name="CG" orien="R0" />
        <branch name="DP">
            <wire x2="1776" y1="736" y2="736" x1="1744" />
        </branch>
        <iomarker fontsize="28" x="1776" y="736" name="DP" orien="R0" />
    </sheet>
</drawing>