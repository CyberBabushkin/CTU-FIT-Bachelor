<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3e" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="A0" />
        <signal name="B1" />
        <signal name="A1" />
        <signal name="B0" />
        <signal name="C0" />
        <signal name="XLXN_11" />
        <signal name="XLXN_12" />
        <signal name="XLXN_13" />
        <signal name="XLXN_14" />
        <signal name="XLXN_15" />
        <signal name="XLXN_16" />
        <signal name="XLXN_17" />
        <signal name="C1" />
        <signal name="C2" />
        <signal name="C3" />
        <port polarity="Input" name="A0" />
        <port polarity="Input" name="B1" />
        <port polarity="Input" name="A1" />
        <port polarity="Input" name="B0" />
        <port polarity="Output" name="C0" />
        <port polarity="Output" name="C1" />
        <port polarity="Output" name="C2" />
        <port polarity="Output" name="C3" />
        <blockdef name="and2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
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
        <block symbolname="and2" name="XLXI_1">
            <blockpin signalname="B1" name="I0" />
            <blockpin signalname="A0" name="I1" />
            <blockpin signalname="XLXN_11" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_2">
            <blockpin signalname="B0" name="I0" />
            <blockpin signalname="A0" name="I1" />
            <blockpin signalname="C0" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_3">
            <blockpin signalname="B0" name="I0" />
            <blockpin signalname="A1" name="I1" />
            <blockpin signalname="XLXN_13" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_4">
            <blockpin signalname="B1" name="I0" />
            <blockpin signalname="A1" name="I1" />
            <blockpin signalname="XLXN_16" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_5">
            <blockpin signalname="XLXN_13" name="I0" />
            <blockpin signalname="XLXN_11" name="I1" />
            <blockpin signalname="XLXN_17" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_6">
            <blockpin signalname="XLXN_16" name="I0" />
            <blockpin signalname="XLXN_17" name="I1" />
            <blockpin signalname="C3" name="O" />
        </block>
        <block symbolname="xor2" name="XLXI_9">
            <blockpin signalname="XLXN_13" name="I0" />
            <blockpin signalname="XLXN_11" name="I1" />
            <blockpin signalname="C1" name="O" />
        </block>
        <block symbolname="xor2" name="XLXI_11">
            <blockpin signalname="XLXN_16" name="I0" />
            <blockpin signalname="XLXN_17" name="I1" />
            <blockpin signalname="C2" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="480" y="448" name="XLXI_1" orien="R0" />
        <instance x="480" y="608" name="XLXI_2" orien="R0" />
        <instance x="480" y="784" name="XLXI_3" orien="R0" />
        <instance x="480" y="976" name="XLXI_4" orien="R0" />
        <instance x="960" y="864" name="XLXI_5" orien="R0" />
        <instance x="1456" y="960" name="XLXI_6" orien="R0" />
        <branch name="A0">
            <wire x2="480" y1="320" y2="320" x1="448" />
        </branch>
        <iomarker fontsize="28" x="448" y="320" name="A0" orien="R180" />
        <branch name="B1">
            <wire x2="480" y1="384" y2="384" x1="448" />
        </branch>
        <iomarker fontsize="28" x="448" y="384" name="B1" orien="R180" />
        <branch name="B0">
            <wire x2="480" y1="544" y2="544" x1="448" />
        </branch>
        <iomarker fontsize="28" x="448" y="544" name="B0" orien="R180" />
        <branch name="A1">
            <wire x2="480" y1="656" y2="656" x1="448" />
        </branch>
        <iomarker fontsize="28" x="448" y="656" name="A1" orien="R180" />
        <branch name="B0">
            <wire x2="480" y1="720" y2="720" x1="448" />
        </branch>
        <iomarker fontsize="28" x="448" y="720" name="B0" orien="R180" />
        <branch name="A1">
            <wire x2="480" y1="848" y2="848" x1="448" />
        </branch>
        <iomarker fontsize="28" x="448" y="848" name="A1" orien="R180" />
        <branch name="B1">
            <wire x2="480" y1="912" y2="912" x1="448" />
        </branch>
        <iomarker fontsize="28" x="448" y="912" name="B1" orien="R180" />
        <branch name="C0">
            <wire x2="768" y1="512" y2="512" x1="736" />
        </branch>
        <iomarker fontsize="28" x="768" y="512" name="C0" orien="R0" />
        <branch name="XLXN_11">
            <wire x2="880" y1="352" y2="352" x1="736" />
            <wire x2="880" y1="352" y2="448" x1="880" />
            <wire x2="1040" y1="448" y2="448" x1="880" />
            <wire x2="880" y1="448" y2="736" x1="880" />
            <wire x2="960" y1="736" y2="736" x1="880" />
        </branch>
        <branch name="XLXN_13">
            <wire x2="864" y1="688" y2="688" x1="736" />
            <wire x2="864" y1="688" y2="800" x1="864" />
            <wire x2="960" y1="800" y2="800" x1="864" />
            <wire x2="864" y1="512" y2="688" x1="864" />
            <wire x2="1040" y1="512" y2="512" x1="864" />
        </branch>
        <branch name="XLXN_16">
            <wire x2="1088" y1="880" y2="880" x1="736" />
            <wire x2="1088" y1="880" y2="896" x1="1088" />
            <wire x2="1280" y1="896" y2="896" x1="1088" />
            <wire x2="1456" y1="896" y2="896" x1="1280" />
            <wire x2="1280" y1="624" y2="896" x1="1280" />
            <wire x2="1424" y1="624" y2="624" x1="1280" />
            <wire x2="1440" y1="624" y2="624" x1="1424" />
        </branch>
        <branch name="XLXN_17">
            <wire x2="1328" y1="768" y2="768" x1="1216" />
            <wire x2="1328" y1="768" y2="832" x1="1328" />
            <wire x2="1344" y1="832" y2="832" x1="1328" />
            <wire x2="1456" y1="832" y2="832" x1="1344" />
            <wire x2="1344" y1="560" y2="832" x1="1344" />
            <wire x2="1424" y1="560" y2="560" x1="1344" />
            <wire x2="1440" y1="560" y2="560" x1="1424" />
        </branch>
        <branch name="C1">
            <wire x2="1328" y1="480" y2="480" x1="1296" />
        </branch>
        <iomarker fontsize="28" x="1328" y="480" name="C1" orien="R0" />
        <branch name="C2">
            <wire x2="1728" y1="592" y2="592" x1="1696" />
        </branch>
        <iomarker fontsize="28" x="1728" y="592" name="C2" orien="R0" />
        <branch name="C3">
            <wire x2="1744" y1="864" y2="864" x1="1712" />
        </branch>
        <iomarker fontsize="28" x="1744" y="864" name="C3" orien="R0" />
        <branch name="A0">
            <wire x2="480" y1="480" y2="480" x1="448" />
        </branch>
        <iomarker fontsize="28" x="448" y="480" name="A0" orien="R180" />
        <instance x="1040" y="576" name="XLXI_9" orien="R0" />
        <instance x="1440" y="688" name="XLXI_11" orien="R0" />
    </sheet>
</drawing>