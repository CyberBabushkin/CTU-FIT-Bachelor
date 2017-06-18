<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3e" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="B" />
        <signal name="A" />
        <signal name="q" />
        <signal name="S" />
        <signal name="XLXN_80" />
        <signal name="XLXN_81" />
        <signal name="XLXN_96" />
        <signal name="r" />
        <signal name="XLXN_106" />
        <signal name="XLXN_109" />
        <signal name="XLXN_110" />
        <signal name="XLXN_111" />
        <signal name="XLXN_114" />
        <signal name="XLXN_115" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="A" />
        <port polarity="Output" name="q" />
        <port polarity="Output" name="S" />
        <port polarity="Input" name="r" />
        <blockdef name="nand2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="216" y1="-96" y2="-96" x1="256" />
            <circle r="12" cx="204" cy="-96" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
        </blockdef>
        <blockdef name="xor2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="60" y1="-128" y2="-128" x1="0" />
            <line x2="208" y1="-96" y2="-96" x1="256" />
            <arc ex="44" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <arc ex="64" ey="-144" sx="64" sy="-48" r="56" cx="32" cy="-96" />
            <line x2="64" y1="-144" y2="-144" x1="128" />
            <line x2="64" y1="-48" y2="-48" x1="128" />
            <arc ex="128" ey="-144" sx="208" sy="-96" r="88" cx="132" cy="-56" />
            <arc ex="208" ey="-96" sx="128" sy="-48" r="88" cx="132" cy="-136" />
        </blockdef>
        <block symbolname="xor2" name="XLXI_4">
            <blockpin signalname="B" name="I0" />
            <blockpin signalname="A" name="I1" />
            <blockpin signalname="XLXN_96" name="O" />
        </block>
        <block symbolname="xor2" name="XLXI_11">
            <blockpin signalname="r" name="I0" />
            <blockpin signalname="XLXN_96" name="I1" />
            <blockpin signalname="S" name="O" />
        </block>
        <block symbolname="nand2" name="XLXI_12">
            <blockpin signalname="r" name="I0" />
            <blockpin signalname="XLXN_96" name="I1" />
            <blockpin signalname="XLXN_80" name="O" />
        </block>
        <block symbolname="nand2" name="XLXI_13">
            <blockpin signalname="A" name="I0" />
            <blockpin signalname="B" name="I1" />
            <blockpin signalname="XLXN_81" name="O" />
        </block>
        <block symbolname="nand2" name="XLXI_14">
            <blockpin signalname="XLXN_80" name="I0" />
            <blockpin signalname="XLXN_81" name="I1" />
            <blockpin signalname="q" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <branch name="B">
            <wire x2="800" y1="992" y2="992" x1="720" />
            <wire x2="944" y1="992" y2="992" x1="800" />
            <wire x2="1280" y1="736" y2="736" x1="800" />
            <wire x2="800" y1="736" y2="992" x1="800" />
        </branch>
        <branch name="q">
            <wire x2="1840" y1="848" y2="848" x1="1824" />
        </branch>
        <branch name="S">
            <wire x2="1840" y1="1072" y2="1072" x1="1792" />
        </branch>
        <instance x="1280" y="1024" name="XLXI_12" orien="R0" />
        <branch name="r">
            <wire x2="1264" y1="1104" y2="1104" x1="704" />
            <wire x2="1536" y1="1104" y2="1104" x1="1264" />
            <wire x2="1280" y1="960" y2="960" x1="1264" />
            <wire x2="1264" y1="960" y2="1104" x1="1264" />
        </branch>
        <iomarker fontsize="28" x="720" y="992" name="B" orien="R180" />
        <iomarker fontsize="28" x="704" y="1104" name="r" orien="R180" />
        <branch name="A">
            <wire x2="896" y1="928" y2="928" x1="720" />
            <wire x2="944" y1="928" y2="928" x1="896" />
            <wire x2="1280" y1="800" y2="800" x1="896" />
            <wire x2="896" y1="800" y2="928" x1="896" />
        </branch>
        <instance x="944" y="1056" name="XLXI_4" orien="R0" />
        <branch name="XLXN_96">
            <wire x2="1232" y1="960" y2="960" x1="1200" />
            <wire x2="1232" y1="960" y2="1040" x1="1232" />
            <wire x2="1536" y1="1040" y2="1040" x1="1232" />
            <wire x2="1232" y1="896" y2="960" x1="1232" />
            <wire x2="1280" y1="896" y2="896" x1="1232" />
        </branch>
        <iomarker fontsize="28" x="720" y="928" name="A" orien="R180" />
        <instance x="1280" y="864" name="XLXI_13" orien="R0" />
        <instance x="1568" y="944" name="XLXI_14" orien="R0" />
        <branch name="XLXN_81">
            <wire x2="1552" y1="768" y2="768" x1="1536" />
            <wire x2="1552" y1="768" y2="816" x1="1552" />
            <wire x2="1568" y1="816" y2="816" x1="1552" />
        </branch>
        <branch name="XLXN_80">
            <wire x2="1552" y1="928" y2="928" x1="1536" />
            <wire x2="1568" y1="880" y2="880" x1="1552" />
            <wire x2="1552" y1="880" y2="928" x1="1552" />
        </branch>
        <iomarker fontsize="28" x="1840" y="848" name="q" orien="R0" />
        <iomarker fontsize="28" x="1840" y="1072" name="S" orien="R0" />
        <instance x="1536" y="1168" name="XLXI_11" orien="R0" />
    </sheet>
</drawing>