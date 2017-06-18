<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3e" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="S0" />
        <signal name="P0" />
        <signal name="S" />
        <signal name="Y0" />
        <signal name="S1" />
        <signal name="Y1" />
        <signal name="S2" />
        <signal name="P2" />
        <signal name="Y3" />
        <signal name="S3" />
        <signal name="P3" />
        <signal name="Y2" />
        <signal name="P1" />
        <port polarity="Input" name="S0" />
        <port polarity="Input" name="P0" />
        <port polarity="Input" name="S" />
        <port polarity="Output" name="Y0" />
        <port polarity="Input" name="S1" />
        <port polarity="Output" name="Y1" />
        <port polarity="Input" name="S2" />
        <port polarity="Input" name="P2" />
        <port polarity="Output" name="Y3" />
        <port polarity="Input" name="S3" />
        <port polarity="Input" name="P3" />
        <port polarity="Output" name="Y2" />
        <port polarity="Input" name="P1" />
        <blockdef name="muxf5">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="96" y1="-64" y2="-256" x1="96" />
            <line x2="96" y1="-96" y2="-64" x1="256" />
            <line x2="256" y1="-224" y2="-96" x1="256" />
            <line x2="256" y1="-256" y2="-224" x1="96" />
            <line x2="256" y1="-128" y2="-128" x1="320" />
            <line x2="96" y1="-224" y2="-224" x1="0" />
            <line x2="96" y1="-32" y2="-32" x1="0" />
            <line x2="96" y1="-96" y2="-96" x1="0" />
            <line x2="96" y1="-32" y2="-32" x1="176" />
            <line x2="176" y1="-80" y2="-32" x1="176" />
        </blockdef>
        <block symbolname="muxf5" name="XLXI_1">
            <blockpin signalname="S0" name="I0" />
            <blockpin signalname="P0" name="I1" />
            <blockpin signalname="S" name="S" />
            <blockpin signalname="Y0" name="O" />
        </block>
        <block symbolname="muxf5" name="XLXI_2">
            <blockpin signalname="S1" name="I0" />
            <blockpin signalname="P1" name="I1" />
            <blockpin signalname="S" name="S" />
            <blockpin signalname="Y1" name="O" />
        </block>
        <block symbolname="muxf5" name="XLXI_3">
            <blockpin signalname="S2" name="I0" />
            <blockpin signalname="P2" name="I1" />
            <blockpin signalname="S" name="S" />
            <blockpin signalname="Y2" name="O" />
        </block>
        <block symbolname="muxf5" name="XLXI_4">
            <blockpin signalname="S3" name="I0" />
            <blockpin signalname="P3" name="I1" />
            <blockpin signalname="S" name="S" />
            <blockpin signalname="Y3" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="944" y="848" name="XLXI_1" orien="R0" />
        <instance x="960" y="1248" name="XLXI_2" orien="R0" />
        <instance x="928" y="1552" name="XLXI_3" orien="R0" />
        <instance x="976" y="2080" name="XLXI_4" orien="R0" />
        <branch name="S0">
            <wire x2="944" y1="624" y2="624" x1="912" />
        </branch>
        <iomarker fontsize="28" x="912" y="624" name="S0" orien="R180" />
        <branch name="P0">
            <wire x2="944" y1="752" y2="752" x1="912" />
        </branch>
        <iomarker fontsize="28" x="912" y="752" name="P0" orien="R180" />
        <branch name="S">
            <wire x2="944" y1="816" y2="816" x1="912" />
        </branch>
        <iomarker fontsize="28" x="912" y="816" name="S" orien="R180" />
        <branch name="Y0">
            <wire x2="1296" y1="720" y2="720" x1="1264" />
        </branch>
        <iomarker fontsize="28" x="1296" y="720" name="Y0" orien="R0" />
        <branch name="S1">
            <wire x2="960" y1="1024" y2="1024" x1="928" />
        </branch>
        <iomarker fontsize="28" x="928" y="1024" name="S1" orien="R180" />
        <branch name="P1">
            <wire x2="960" y1="1152" y2="1152" x1="928" />
        </branch>
        <iomarker fontsize="28" x="928" y="1152" name="P1" orien="R180" />
        <branch name="S">
            <wire x2="960" y1="1216" y2="1216" x1="928" />
        </branch>
        <iomarker fontsize="28" x="928" y="1216" name="S" orien="R180" />
        <branch name="Y1">
            <wire x2="1312" y1="1120" y2="1120" x1="1280" />
        </branch>
        <iomarker fontsize="28" x="1312" y="1120" name="Y1" orien="R0" />
        <branch name="S2">
            <wire x2="928" y1="1328" y2="1328" x1="896" />
        </branch>
        <iomarker fontsize="28" x="896" y="1328" name="S2" orien="R180" />
        <branch name="P2">
            <wire x2="928" y1="1456" y2="1456" x1="896" />
        </branch>
        <iomarker fontsize="28" x="896" y="1456" name="P2" orien="R180" />
        <branch name="S">
            <wire x2="928" y1="1520" y2="1520" x1="896" />
        </branch>
        <iomarker fontsize="28" x="896" y="1520" name="S" orien="R180" />
        <branch name="Y2">
            <wire x2="1280" y1="1424" y2="1424" x1="1248" />
        </branch>
        <iomarker fontsize="28" x="1280" y="1424" name="Y2" orien="R0" />
        <branch name="S3">
            <wire x2="976" y1="1856" y2="1856" x1="944" />
        </branch>
        <iomarker fontsize="28" x="944" y="1856" name="S3" orien="R180" />
        <branch name="P3">
            <wire x2="960" y1="1984" y2="1984" x1="944" />
            <wire x2="976" y1="1984" y2="1984" x1="960" />
        </branch>
        <iomarker fontsize="28" x="944" y="1984" name="P3" orien="R180" />
        <branch name="S">
            <wire x2="976" y1="2048" y2="2048" x1="944" />
        </branch>
        <iomarker fontsize="28" x="944" y="2048" name="S" orien="R180" />
        <branch name="Y3">
            <wire x2="1328" y1="1952" y2="1952" x1="1296" />
        </branch>
        <iomarker fontsize="28" x="1328" y="1952" name="Y3" orien="R0" />
    </sheet>
</drawing>