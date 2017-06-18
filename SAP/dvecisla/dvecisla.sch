<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3e" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="CLK" />
        <signal name="XLXN_2" />
        <signal name="CLR" />
        <signal name="XLXN_9" />
        <signal name="XLXN_12" />
        <signal name="XLXN_13" />
        <signal name="XLXN_14" />
        <signal name="XLXN_15" />
        <signal name="P0" />
        <signal name="P2" />
        <signal name="P3" />
        <signal name="P1" />
        <signal name="S0" />
        <signal name="S1" />
        <signal name="S2" />
        <signal name="S3" />
        <signal name="A" />
        <signal name="B" />
        <signal name="C" />
        <signal name="D" />
        <signal name="E" />
        <signal name="F" />
        <signal name="G" />
        <signal name="XLXN_32(15:0)" />
        <signal name="XLXN_32(3)" />
        <signal name="dioda0" />
        <signal name="dioda1" />
        <signal name="dioda2" />
        <signal name="dioda3" />
        <port polarity="Input" name="CLK" />
        <port polarity="Input" name="CLR" />
        <port polarity="Input" name="P0" />
        <port polarity="Input" name="P2" />
        <port polarity="Input" name="P3" />
        <port polarity="Input" name="P1" />
        <port polarity="Input" name="S0" />
        <port polarity="Input" name="S1" />
        <port polarity="Input" name="S2" />
        <port polarity="Input" name="S3" />
        <port polarity="Output" name="A" />
        <port polarity="Output" name="B" />
        <port polarity="Output" name="C" />
        <port polarity="Output" name="D" />
        <port polarity="Output" name="E" />
        <port polarity="Output" name="F" />
        <port polarity="Output" name="G" />
        <port polarity="Output" name="dioda0" />
        <port polarity="Output" name="dioda1" />
        <port polarity="Output" name="dioda2" />
        <port polarity="Output" name="dioda3" />
        <blockdef name="Mymux">
            <timestamp>2015-3-6T11:9:36</timestamp>
            <rect width="256" x="64" y="-576" height="576" />
            <line x2="0" y1="-544" y2="-544" x1="64" />
            <line x2="0" y1="-480" y2="-480" x1="64" />
            <line x2="0" y1="-416" y2="-416" x1="64" />
            <line x2="0" y1="-352" y2="-352" x1="64" />
            <line x2="0" y1="-288" y2="-288" x1="64" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <line x2="0" y1="-160" y2="-160" x1="64" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <line x2="384" y1="-544" y2="-544" x1="320" />
            <line x2="384" y1="-480" y2="-480" x1="320" />
            <line x2="384" y1="-416" y2="-416" x1="320" />
            <line x2="384" y1="-352" y2="-352" x1="320" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
        </blockdef>
        <blockdef name="algebra">
            <timestamp>2016-3-14T15:33:43</timestamp>
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
        </blockdef>
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-64" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-64" y2="-64" x1="96" />
        </blockdef>
        <blockdef name="cb16ce">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="320" y1="-192" y2="-192" x1="384" />
            <rect width="64" x="320" y="-268" height="24" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="320" y1="-128" y2="-128" x1="384" />
            <rect width="256" x="64" y="-320" height="256" />
        </blockdef>
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <blockdef name="buf">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="0" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="-64" x1="128" />
            <line x2="64" y1="-64" y2="0" x1="64" />
        </blockdef>
        <block symbolname="Mymux" name="XLXI_1">
            <blockpin signalname="S0" name="S0" />
            <blockpin signalname="P0" name="P0" />
            <blockpin signalname="XLXN_32(3)" name="S" />
            <blockpin signalname="S1" name="S1" />
            <blockpin signalname="S2" name="S2" />
            <blockpin signalname="P2" name="P2" />
            <blockpin signalname="S3" name="S3" />
            <blockpin signalname="P3" name="P3" />
            <blockpin signalname="P1" name="P1" />
            <blockpin signalname="XLXN_12" name="Y0" />
            <blockpin signalname="XLXN_13" name="Y1" />
            <blockpin signalname="XLXN_15" name="Y3" />
            <blockpin signalname="XLXN_14" name="Y2" />
        </block>
        <block symbolname="algebra" name="XLXI_2">
            <blockpin signalname="XLXN_12" name="x" />
            <blockpin signalname="XLXN_13" name="y" />
            <blockpin signalname="XLXN_14" name="z" />
            <blockpin signalname="XLXN_15" name="t" />
            <blockpin signalname="A" name="a" />
            <blockpin signalname="B" name="b" />
            <blockpin signalname="C" name="c" />
            <blockpin signalname="D" name="d" />
            <blockpin signalname="E" name="e" />
            <blockpin signalname="F" name="f" />
            <blockpin signalname="G" name="g" />
        </block>
        <block symbolname="vcc" name="XLXI_3">
            <blockpin signalname="XLXN_9" name="P" />
        </block>
        <block symbolname="cb16ce" name="XLXI_4">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_9" name="CE" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="XLXN_2" name="CEO" />
            <blockpin name="Q(15:0)" />
            <blockpin name="TC" />
        </block>
        <block symbolname="cb16ce" name="XLXI_5">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_2" name="CE" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin name="CEO" />
            <blockpin signalname="XLXN_32(15:0)" name="Q(15:0)" />
            <blockpin name="TC" />
        </block>
        <block symbolname="inv" name="XLXI_6">
            <blockpin signalname="XLXN_32(3)" name="I" />
            <blockpin signalname="dioda0" name="O" />
        </block>
        <block symbolname="buf" name="XLXI_8">
            <blockpin signalname="XLXN_32(3)" name="I" />
            <blockpin signalname="dioda1" name="O" />
        </block>
        <block symbolname="vcc" name="XLXI_9">
            <blockpin signalname="dioda2" name="P" />
        </block>
        <block symbolname="vcc" name="XLXI_10">
            <blockpin signalname="dioda3" name="P" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="288" y="1264" name="XLXI_5" orien="R0" />
        <branch name="XLXN_2">
            <wire x2="288" y1="1072" y2="1072" x1="272" />
            <wire x2="272" y1="1072" y2="1280" x1="272" />
            <wire x2="736" y1="1280" y2="1280" x1="272" />
            <wire x2="736" y1="608" y2="608" x1="640" />
            <wire x2="736" y1="608" y2="1280" x1="736" />
        </branch>
        <branch name="CLK">
            <wire x2="256" y1="672" y2="672" x1="176" />
            <wire x2="176" y1="672" y2="1136" x1="176" />
            <wire x2="176" y1="1136" y2="1328" x1="176" />
            <wire x2="320" y1="1328" y2="1328" x1="176" />
            <wire x2="288" y1="1136" y2="1136" x1="176" />
        </branch>
        <branch name="CLR">
            <wire x2="256" y1="768" y2="1232" x1="256" />
            <wire x2="288" y1="1232" y2="1232" x1="256" />
            <wire x2="256" y1="1232" y2="1392" x1="256" />
            <wire x2="320" y1="1392" y2="1392" x1="256" />
        </branch>
        <iomarker fontsize="28" x="320" y="1328" name="CLK" orien="R0" />
        <iomarker fontsize="28" x="320" y="1392" name="CLR" orien="R0" />
        <instance x="160" y="400" name="XLXI_3" orien="R0" />
        <branch name="XLXN_9">
            <wire x2="224" y1="400" y2="608" x1="224" />
            <wire x2="256" y1="608" y2="608" x1="224" />
        </branch>
        <instance x="256" y="800" name="XLXI_4" orien="R0" />
        <instance x="2256" y="1040" name="XLXI_2" orien="R0">
        </instance>
        <instance x="1584" y="1120" name="XLXI_1" orien="R0">
        </instance>
        <branch name="XLXN_12">
            <wire x2="2112" y1="576" y2="576" x1="1968" />
            <wire x2="2112" y1="560" y2="576" x1="2112" />
            <wire x2="2256" y1="560" y2="560" x1="2112" />
        </branch>
        <branch name="XLXN_13">
            <wire x2="2112" y1="640" y2="640" x1="1968" />
            <wire x2="2112" y1="640" y2="704" x1="2112" />
            <wire x2="2256" y1="704" y2="704" x1="2112" />
        </branch>
        <branch name="XLXN_14">
            <wire x2="2096" y1="704" y2="704" x1="1968" />
            <wire x2="2096" y1="704" y2="848" x1="2096" />
            <wire x2="2256" y1="848" y2="848" x1="2096" />
        </branch>
        <branch name="XLXN_15">
            <wire x2="2080" y1="768" y2="768" x1="1968" />
            <wire x2="2080" y1="768" y2="992" x1="2080" />
            <wire x2="2256" y1="992" y2="992" x1="2080" />
        </branch>
        <branch name="P0">
            <wire x2="1584" y1="576" y2="576" x1="1552" />
        </branch>
        <iomarker fontsize="28" x="1552" y="576" name="P0" orien="R180" />
        <branch name="P2">
            <wire x2="1584" y1="640" y2="640" x1="1552" />
        </branch>
        <iomarker fontsize="28" x="1552" y="640" name="P2" orien="R180" />
        <branch name="P3">
            <wire x2="1584" y1="704" y2="704" x1="1552" />
        </branch>
        <iomarker fontsize="28" x="1552" y="704" name="P3" orien="R180" />
        <branch name="P1">
            <wire x2="1584" y1="1088" y2="1088" x1="1552" />
        </branch>
        <iomarker fontsize="28" x="1552" y="1088" name="P1" orien="R180" />
        <branch name="S0">
            <wire x2="1584" y1="832" y2="832" x1="1552" />
        </branch>
        <iomarker fontsize="28" x="1552" y="832" name="S0" orien="R180" />
        <branch name="S1">
            <wire x2="1584" y1="896" y2="896" x1="1552" />
        </branch>
        <iomarker fontsize="28" x="1552" y="896" name="S1" orien="R180" />
        <branch name="S2">
            <wire x2="1584" y1="960" y2="960" x1="1552" />
        </branch>
        <iomarker fontsize="28" x="1552" y="960" name="S2" orien="R180" />
        <branch name="S3">
            <wire x2="1584" y1="1024" y2="1024" x1="1552" />
        </branch>
        <iomarker fontsize="28" x="1552" y="1024" name="S3" orien="R180" />
        <branch name="A">
            <wire x2="2672" y1="560" y2="560" x1="2640" />
        </branch>
        <iomarker fontsize="28" x="2672" y="560" name="A" orien="R0" />
        <branch name="B">
            <wire x2="2672" y1="624" y2="624" x1="2640" />
        </branch>
        <iomarker fontsize="28" x="2672" y="624" name="B" orien="R0" />
        <branch name="C">
            <wire x2="2672" y1="688" y2="688" x1="2640" />
        </branch>
        <iomarker fontsize="28" x="2672" y="688" name="C" orien="R0" />
        <branch name="D">
            <wire x2="2672" y1="752" y2="752" x1="2640" />
        </branch>
        <iomarker fontsize="28" x="2672" y="752" name="D" orien="R0" />
        <branch name="E">
            <wire x2="2672" y1="816" y2="816" x1="2640" />
        </branch>
        <iomarker fontsize="28" x="2672" y="816" name="E" orien="R0" />
        <branch name="F">
            <wire x2="2672" y1="880" y2="880" x1="2640" />
        </branch>
        <iomarker fontsize="28" x="2672" y="880" name="F" orien="R0" />
        <branch name="G">
            <wire x2="2672" y1="944" y2="944" x1="2640" />
        </branch>
        <iomarker fontsize="28" x="2672" y="944" name="G" orien="R0" />
        <branch name="XLXN_32(15:0)">
            <wire x2="832" y1="1008" y2="1008" x1="672" />
        </branch>
        <branch name="dioda0">
            <wire x2="1616" y1="1248" y2="1248" x1="1584" />
        </branch>
        <branch name="XLXN_32(3)">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="1184" y="1248" type="branch" />
            <wire x2="1280" y1="1248" y2="1248" x1="1184" />
            <wire x2="1280" y1="1248" y2="1408" x1="1280" />
            <wire x2="1360" y1="1408" y2="1408" x1="1280" />
            <wire x2="1360" y1="1248" y2="1248" x1="1280" />
            <wire x2="1280" y1="768" y2="1248" x1="1280" />
            <wire x2="1584" y1="768" y2="768" x1="1280" />
        </branch>
        <instance x="1360" y="1440" name="XLXI_8" orien="R0" />
        <branch name="dioda1">
            <wire x2="1616" y1="1408" y2="1408" x1="1584" />
        </branch>
        <iomarker fontsize="28" x="1616" y="1408" name="dioda1" orien="R0" />
        <instance x="1776" y="1312" name="XLXI_9" orien="R0" />
        <instance x="1904" y="1312" name="XLXI_10" orien="R0" />
        <branch name="dioda2">
            <wire x2="1840" y1="1312" y2="1344" x1="1840" />
        </branch>
        <branch name="dioda3">
            <wire x2="1968" y1="1312" y2="1344" x1="1968" />
        </branch>
        <iomarker fontsize="28" x="1840" y="1344" name="dioda2" orien="R90" />
        <iomarker fontsize="28" x="1968" y="1344" name="dioda3" orien="R90" />
        <iomarker fontsize="28" x="1616" y="1248" name="dioda0" orien="R0" />
        <instance x="1360" y="1280" name="XLXI_6" orien="R0" />
    </sheet>
</drawing>