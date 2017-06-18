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
        <signal name="CLR" />
        <signal name="CLK" />
        <signal name="CA" />
        <signal name="CB" />
        <signal name="CC" />
        <signal name="CD" />
        <signal name="CE" />
        <signal name="CF" />
        <signal name="CG" />
        <signal name="DP" />
        <signal name="XLXN_28" />
        <signal name="XLXN_29" />
        <signal name="XLXN_30" />
        <signal name="XLXN_31" />
        <signal name="XLXN_32" />
        <signal name="XLXN_33" />
        <signal name="XLXN_34" />
        <signal name="XLXN_35" />
        <signal name="XLXN_36" />
        <signal name="XLXN_37" />
        <signal name="XLXN_38" />
        <signal name="AN0" />
        <signal name="AN1" />
        <signal name="B1" />
        <signal name="A1" />
        <signal name="B2" />
        <signal name="A0" />
        <signal name="B0" />
        <signal name="A2" />
        <signal name="A3" />
        <signal name="B3" />
        <signal name="CIN" />
        <port polarity="Input" name="CLR" />
        <port polarity="Input" name="CLK" />
        <port polarity="Output" name="CA" />
        <port polarity="Output" name="CB" />
        <port polarity="Output" name="CC" />
        <port polarity="Output" name="CD" />
        <port polarity="Output" name="CE" />
        <port polarity="Output" name="CF" />
        <port polarity="Output" name="CG" />
        <port polarity="Output" name="DP" />
        <port polarity="Output" name="AN0" />
        <port polarity="Output" name="AN1" />
        <port polarity="Input" name="B1" />
        <port polarity="Input" name="A1" />
        <port polarity="Input" name="B2" />
        <port polarity="Input" name="A0" />
        <port polarity="Input" name="B0" />
        <port polarity="Input" name="A2" />
        <port polarity="Input" name="A3" />
        <port polarity="Input" name="B3" />
        <port polarity="Input" name="CIN" />
        <blockdef name="cb4ce">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <rect width="256" x="64" y="-512" height="448" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <line x2="320" y1="-320" y2="-320" x1="384" />
            <line x2="320" y1="-384" y2="-384" x1="384" />
            <line x2="320" y1="-448" y2="-448" x1="384" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="320" y1="-128" y2="-128" x1="384" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="320" y1="-192" y2="-192" x1="384" />
        </blockdef>
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-64" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-64" y2="-64" x1="96" />
        </blockdef>
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
        <blockdef name="Mymux">
            <timestamp>2015-3-6T10:9:36</timestamp>
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
        <blockdef name="gnd">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-96" x1="64" />
            <line x2="52" y1="-48" y2="-48" x1="76" />
            <line x2="60" y1="-32" y2="-32" x1="68" />
            <line x2="40" y1="-64" y2="-64" x1="88" />
            <line x2="64" y1="-64" y2="-80" x1="64" />
            <line x2="64" y1="-128" y2="-96" x1="64" />
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
        <block symbolname="cb4ce" name="XLXI_1">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_1" name="CE" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="XLXN_2" name="CEO" />
            <blockpin name="Q0" />
            <blockpin name="Q1" />
            <blockpin name="Q2" />
            <blockpin name="Q3" />
            <blockpin name="TC" />
        </block>
        <block symbolname="cb4ce" name="XLXI_2">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_2" name="CE" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="XLXN_3" name="CEO" />
            <blockpin name="Q0" />
            <blockpin name="Q1" />
            <blockpin name="Q2" />
            <blockpin name="Q3" />
            <blockpin name="TC" />
        </block>
        <block symbolname="cb4ce" name="XLXI_3">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_3" name="CE" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="XLXN_4" name="CEO" />
            <blockpin name="Q0" />
            <blockpin name="Q1" />
            <blockpin name="Q2" />
            <blockpin name="Q3" />
            <blockpin name="TC" />
        </block>
        <block symbolname="cb4ce" name="XLXI_4">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_4" name="CE" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin name="CEO" />
            <blockpin name="Q0" />
            <blockpin name="Q1" />
            <blockpin name="Q2" />
            <blockpin signalname="AN0" name="Q3" />
            <blockpin name="TC" />
        </block>
        <block symbolname="vcc" name="XLXI_5">
            <blockpin signalname="XLXN_1" name="P" />
        </block>
        <block symbolname="fourbitadder" name="XLXI_6">
            <blockpin signalname="B1" name="B1" />
            <blockpin signalname="A1" name="A1" />
            <blockpin signalname="B2" name="B2" />
            <blockpin signalname="A0" name="A0" />
            <blockpin signalname="B0" name="B0" />
            <blockpin signalname="A2" name="A2" />
            <blockpin signalname="A3" name="A3" />
            <blockpin signalname="B3" name="B3" />
            <blockpin signalname="CIN" name="CIN" />
            <blockpin signalname="XLXN_36" name="COUT" />
            <blockpin signalname="XLXN_34" name="S3" />
            <blockpin signalname="XLXN_33" name="S0" />
            <blockpin signalname="XLXN_35" name="S2" />
            <blockpin signalname="XLXN_32" name="S1" />
        </block>
        <block symbolname="decoder_7seg" name="XLXI_8">
            <blockpin signalname="XLXN_31" name="d" />
            <blockpin signalname="XLXN_30" name="c" />
            <blockpin signalname="XLXN_29" name="b" />
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
        <block symbolname="gnd" name="XLXI_9">
            <blockpin signalname="XLXN_38" name="G" />
        </block>
        <block symbolname="Mymux" name="XLXI_12">
            <blockpin signalname="XLXN_33" name="S0" />
            <blockpin signalname="XLXN_36" name="P0" />
            <blockpin signalname="AN0" name="S" />
            <blockpin signalname="XLXN_32" name="S1" />
            <blockpin signalname="XLXN_35" name="S2" />
            <blockpin signalname="XLXN_38" name="P2" />
            <blockpin signalname="XLXN_34" name="S3" />
            <blockpin signalname="XLXN_38" name="P3" />
            <blockpin signalname="XLXN_38" name="P1" />
            <blockpin signalname="XLXN_28" name="Y0" />
            <blockpin signalname="XLXN_29" name="Y1" />
            <blockpin signalname="XLXN_31" name="Y3" />
            <blockpin signalname="XLXN_30" name="Y2" />
        </block>
        <block symbolname="inv" name="XLXI_13">
            <blockpin signalname="AN0" name="I" />
            <blockpin signalname="AN1" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="720" y="1328" name="XLXI_1" orien="R0" />
        <instance x="1488" y="1312" name="XLXI_2" orien="R0" />
        <instance x="2128" y="1312" name="XLXI_3" orien="R0" />
        <instance x="2768" y="1312" name="XLXI_4" orien="R0" />
        <instance x="512" y="1088" name="XLXI_5" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="576" y1="1088" y2="1136" x1="576" />
            <wire x2="720" y1="1136" y2="1136" x1="576" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="1296" y1="1136" y2="1136" x1="1104" />
            <wire x2="1296" y1="1120" y2="1136" x1="1296" />
            <wire x2="1488" y1="1120" y2="1120" x1="1296" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="2128" y1="1120" y2="1120" x1="1872" />
        </branch>
        <branch name="XLXN_4">
            <wire x2="2768" y1="1120" y2="1120" x1="2512" />
        </branch>
        <branch name="CLR">
            <wire x2="1488" y1="1280" y2="1280" x1="1456" />
        </branch>
        <iomarker fontsize="28" x="1456" y="1280" name="CLR" orien="R180" />
        <branch name="CLR">
            <wire x2="2128" y1="1280" y2="1280" x1="2096" />
        </branch>
        <iomarker fontsize="28" x="2096" y="1280" name="CLR" orien="R180" />
        <branch name="CLR">
            <wire x2="2768" y1="1280" y2="1280" x1="2736" />
        </branch>
        <iomarker fontsize="28" x="2736" y="1280" name="CLR" orien="R180" />
        <branch name="CLR">
            <wire x2="720" y1="1296" y2="1296" x1="688" />
        </branch>
        <iomarker fontsize="28" x="688" y="1296" name="CLR" orien="R180" />
        <branch name="CLK">
            <wire x2="720" y1="1200" y2="1200" x1="688" />
        </branch>
        <iomarker fontsize="28" x="688" y="1200" name="CLK" orien="R180" />
        <branch name="CLK">
            <wire x2="1488" y1="1184" y2="1184" x1="1456" />
        </branch>
        <iomarker fontsize="28" x="1456" y="1184" name="CLK" orien="R180" />
        <branch name="CLK">
            <wire x2="2128" y1="1184" y2="1184" x1="2096" />
        </branch>
        <iomarker fontsize="28" x="2096" y="1184" name="CLK" orien="R180" />
        <branch name="CLK">
            <wire x2="2768" y1="1184" y2="1184" x1="2736" />
        </branch>
        <iomarker fontsize="28" x="2736" y="1184" name="CLK" orien="R180" />
        <instance x="576" y="2144" name="XLXI_6" orien="R0">
        </instance>
        <instance x="1984" y="2016" name="XLXI_8" orien="R0">
        </instance>
        <instance x="1136" y="2240" name="XLXI_9" orien="R0" />
        <branch name="CA">
            <wire x2="2400" y1="1536" y2="1536" x1="2368" />
        </branch>
        <iomarker fontsize="28" x="2400" y="1536" name="CA" orien="R0" />
        <branch name="CB">
            <wire x2="2400" y1="1600" y2="1600" x1="2368" />
        </branch>
        <iomarker fontsize="28" x="2400" y="1600" name="CB" orien="R0" />
        <branch name="CC">
            <wire x2="2400" y1="1664" y2="1664" x1="2368" />
        </branch>
        <iomarker fontsize="28" x="2400" y="1664" name="CC" orien="R0" />
        <branch name="CD">
            <wire x2="2400" y1="1728" y2="1728" x1="2368" />
        </branch>
        <iomarker fontsize="28" x="2400" y="1728" name="CD" orien="R0" />
        <branch name="CE">
            <wire x2="2400" y1="1792" y2="1792" x1="2368" />
        </branch>
        <iomarker fontsize="28" x="2400" y="1792" name="CE" orien="R0" />
        <branch name="CF">
            <wire x2="2400" y1="1856" y2="1856" x1="2368" />
        </branch>
        <iomarker fontsize="28" x="2400" y="1856" name="CF" orien="R0" />
        <branch name="CG">
            <wire x2="2400" y1="1920" y2="1920" x1="2368" />
        </branch>
        <iomarker fontsize="28" x="2400" y="1920" name="CG" orien="R0" />
        <branch name="DP">
            <wire x2="2400" y1="1984" y2="1984" x1="2368" />
        </branch>
        <iomarker fontsize="28" x="2400" y="1984" name="DP" orien="R0" />
        <branch name="XLXN_28">
            <wire x2="1824" y1="1536" y2="1536" x1="1664" />
            <wire x2="1824" y1="1536" y2="1968" x1="1824" />
            <wire x2="1984" y1="1968" y2="1968" x1="1824" />
        </branch>
        <branch name="XLXN_29">
            <wire x2="1808" y1="1600" y2="1600" x1="1664" />
            <wire x2="1808" y1="1600" y2="1824" x1="1808" />
            <wire x2="1984" y1="1824" y2="1824" x1="1808" />
        </branch>
        <branch name="XLXN_30">
            <wire x2="1792" y1="1664" y2="1664" x1="1664" />
            <wire x2="1792" y1="1664" y2="1680" x1="1792" />
            <wire x2="1984" y1="1680" y2="1680" x1="1792" />
        </branch>
        <branch name="XLXN_31">
            <wire x2="1840" y1="1728" y2="1728" x1="1664" />
            <wire x2="1840" y1="1536" y2="1728" x1="1840" />
            <wire x2="1984" y1="1536" y2="1536" x1="1840" />
        </branch>
        <instance x="1280" y="2080" name="XLXI_12" orien="R0">
        </instance>
        <branch name="XLXN_32">
            <wire x2="1280" y1="1856" y2="1856" x1="960" />
        </branch>
        <branch name="XLXN_33">
            <wire x2="1120" y1="1728" y2="1728" x1="960" />
            <wire x2="1120" y1="1728" y2="1792" x1="1120" />
            <wire x2="1280" y1="1792" y2="1792" x1="1120" />
        </branch>
        <branch name="XLXN_34">
            <wire x2="1104" y1="1664" y2="1664" x1="960" />
            <wire x2="1104" y1="1664" y2="1984" x1="1104" />
            <wire x2="1280" y1="1984" y2="1984" x1="1104" />
        </branch>
        <branch name="XLXN_35">
            <wire x2="1088" y1="1792" y2="1792" x1="960" />
            <wire x2="1088" y1="1792" y2="1920" x1="1088" />
            <wire x2="1280" y1="1920" y2="1920" x1="1088" />
        </branch>
        <branch name="XLXN_36">
            <wire x2="1120" y1="1600" y2="1600" x1="960" />
            <wire x2="1120" y1="1536" y2="1600" x1="1120" />
            <wire x2="1280" y1="1536" y2="1536" x1="1120" />
        </branch>
        <branch name="XLXN_38">
            <wire x2="1280" y1="1600" y2="1600" x1="1200" />
            <wire x2="1200" y1="1600" y2="1664" x1="1200" />
            <wire x2="1200" y1="1664" y2="2048" x1="1200" />
            <wire x2="1280" y1="2048" y2="2048" x1="1200" />
            <wire x2="1200" y1="2048" y2="2112" x1="1200" />
            <wire x2="1280" y1="1664" y2="1664" x1="1200" />
        </branch>
        <branch name="AN0">
            <wire x2="1280" y1="1728" y2="1728" x1="1216" />
            <wire x2="1216" y1="1728" y2="2096" x1="1216" />
            <wire x2="3232" y1="2096" y2="2096" x1="1216" />
            <wire x2="3232" y1="1056" y2="1056" x1="3152" />
            <wire x2="3232" y1="1056" y2="1424" x1="3232" />
            <wire x2="3232" y1="1424" y2="1520" x1="3232" />
            <wire x2="3232" y1="1520" y2="2096" x1="3232" />
            <wire x2="3264" y1="1520" y2="1520" x1="3232" />
            <wire x2="3296" y1="1424" y2="1424" x1="3232" />
        </branch>
        <iomarker fontsize="28" x="3296" y="1424" name="AN0" orien="R0" />
        <instance x="3264" y="1552" name="XLXI_13" orien="R0" />
        <branch name="AN1">
            <wire x2="3520" y1="1520" y2="1520" x1="3488" />
        </branch>
        <iomarker fontsize="28" x="3520" y="1520" name="AN1" orien="R90" />
        <branch name="B1">
            <wire x2="576" y1="1600" y2="1600" x1="544" />
        </branch>
        <iomarker fontsize="28" x="544" y="1600" name="B1" orien="R180" />
        <branch name="A1">
            <wire x2="576" y1="1664" y2="1664" x1="544" />
        </branch>
        <iomarker fontsize="28" x="544" y="1664" name="A1" orien="R180" />
        <branch name="B2">
            <wire x2="576" y1="1728" y2="1728" x1="544" />
        </branch>
        <iomarker fontsize="28" x="544" y="1728" name="B2" orien="R180" />
        <branch name="A0">
            <wire x2="576" y1="1792" y2="1792" x1="544" />
        </branch>
        <iomarker fontsize="28" x="544" y="1792" name="A0" orien="R180" />
        <branch name="B0">
            <wire x2="576" y1="1856" y2="1856" x1="544" />
        </branch>
        <iomarker fontsize="28" x="544" y="1856" name="B0" orien="R180" />
        <branch name="A2">
            <wire x2="576" y1="1920" y2="1920" x1="544" />
        </branch>
        <iomarker fontsize="28" x="544" y="1920" name="A2" orien="R180" />
        <branch name="A3">
            <wire x2="576" y1="1984" y2="1984" x1="544" />
        </branch>
        <iomarker fontsize="28" x="544" y="1984" name="A3" orien="R180" />
        <branch name="B3">
            <wire x2="576" y1="2048" y2="2048" x1="544" />
        </branch>
        <iomarker fontsize="28" x="544" y="2048" name="B3" orien="R180" />
        <branch name="CIN">
            <wire x2="576" y1="2112" y2="2112" x1="544" />
        </branch>
        <iomarker fontsize="28" x="544" y="2112" name="CIN" orien="R180" />
    </sheet>
</drawing>