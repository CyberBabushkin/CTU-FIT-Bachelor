<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3e" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="a" />
        <signal name="XLXN_2" />
        <signal name="c" />
        <signal name="b" />
        <signal name="XLXN_5" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="XLXN_8" />
        <signal name="XLXN_9" />
        <signal name="XLXN_10" />
        <signal name="f" />
        <port polarity="Input" name="a" />
        <port polarity="Input" name="c" />
        <port polarity="Input" name="b" />
        <port polarity="Output" name="f" />
        <blockdef name="nor2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="216" y1="-96" y2="-96" x1="256" />
            <circle r="12" cx="204" cy="-96" />
            <arc ex="192" ey="-96" sx="112" sy="-48" r="88" cx="116" cy="-136" />
            <arc ex="112" ey="-144" sx="192" sy="-96" r="88" cx="116" cy="-56" />
            <arc ex="48" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <line x2="48" y1="-48" y2="-48" x1="112" />
            <line x2="48" y1="-144" y2="-144" x1="112" />
        </blockdef>
        <blockdef name="or3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="72" y1="-128" y2="-128" x1="0" />
            <line x2="48" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <arc ex="192" ey="-128" sx="112" sy="-80" r="88" cx="116" cy="-168" />
            <arc ex="48" ey="-176" sx="48" sy="-80" r="56" cx="16" cy="-128" />
            <line x2="48" y1="-64" y2="-80" x1="48" />
            <line x2="48" y1="-192" y2="-176" x1="48" />
            <line x2="48" y1="-80" y2="-80" x1="112" />
            <arc ex="112" ey="-176" sx="192" sy="-128" r="88" cx="116" cy="-88" />
            <line x2="48" y1="-176" y2="-176" x1="112" />
        </blockdef>
        <blockdef name="and3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
        </blockdef>
        <block symbolname="nor2" name="XLXI_1">
            <blockpin signalname="c" name="I0" />
            <blockpin signalname="a" name="I1" />
            <blockpin signalname="XLXN_8" name="O" />
        </block>
        <block symbolname="nor2" name="XLXI_2">
            <blockpin signalname="b" name="I0" />
            <blockpin signalname="c" name="I1" />
            <blockpin signalname="XLXN_9" name="O" />
        </block>
        <block symbolname="or3" name="XLXI_5">
            <blockpin signalname="XLXN_10" name="I0" />
            <blockpin signalname="XLXN_9" name="I1" />
            <blockpin signalname="XLXN_8" name="I2" />
            <blockpin signalname="f" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_6">
            <blockpin signalname="b" name="I0" />
            <blockpin signalname="c" name="I1" />
            <blockpin signalname="a" name="I2" />
            <blockpin signalname="XLXN_10" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="880" y="720" name="XLXI_1" orien="R0" />
        <instance x="880" y="944" name="XLXI_2" orien="R0" />
        <branch name="a">
            <wire x2="752" y1="592" y2="592" x1="608" />
            <wire x2="880" y1="592" y2="592" x1="752" />
            <wire x2="752" y1="592" y2="992" x1="752" />
            <wire x2="880" y1="992" y2="992" x1="752" />
        </branch>
        <branch name="c">
            <wire x2="688" y1="656" y2="656" x1="608" />
            <wire x2="880" y1="656" y2="656" x1="688" />
            <wire x2="688" y1="656" y2="816" x1="688" />
            <wire x2="784" y1="816" y2="816" x1="688" />
            <wire x2="880" y1="816" y2="816" x1="784" />
            <wire x2="784" y1="816" y2="1056" x1="784" />
            <wire x2="880" y1="1056" y2="1056" x1="784" />
        </branch>
        <branch name="b">
            <wire x2="704" y1="880" y2="880" x1="608" />
            <wire x2="880" y1="880" y2="880" x1="704" />
            <wire x2="704" y1="880" y2="1120" x1="704" />
            <wire x2="880" y1="1120" y2="1120" x1="704" />
        </branch>
        <instance x="880" y="1184" name="XLXI_6" orien="R0" />
        <iomarker fontsize="28" x="608" y="592" name="a" orien="R180" />
        <iomarker fontsize="28" x="608" y="656" name="c" orien="R180" />
        <iomarker fontsize="28" x="608" y="880" name="b" orien="R180" />
        <instance x="1328" y="992" name="XLXI_5" orien="R0" />
        <branch name="XLXN_8">
            <wire x2="1328" y1="624" y2="624" x1="1136" />
            <wire x2="1328" y1="624" y2="800" x1="1328" />
        </branch>
        <branch name="XLXN_9">
            <wire x2="1232" y1="848" y2="848" x1="1136" />
            <wire x2="1232" y1="848" y2="864" x1="1232" />
            <wire x2="1328" y1="864" y2="864" x1="1232" />
        </branch>
        <branch name="XLXN_10">
            <wire x2="1328" y1="1056" y2="1056" x1="1136" />
            <wire x2="1328" y1="928" y2="1056" x1="1328" />
        </branch>
        <branch name="f">
            <wire x2="1744" y1="864" y2="864" x1="1584" />
        </branch>
        <iomarker fontsize="28" x="1744" y="864" name="f" orien="R0" />
    </sheet>
</drawing>