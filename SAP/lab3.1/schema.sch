<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3e" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="a0" />
        <signal name="b0" />
        <signal name="c0" />
        <signal name="f0" />
        <signal name="d0" />
        <signal name="g0" />
        <signal name="e0" />
        <signal name="an2" />
        <signal name="an1" />
        <signal name="an3" />
        <signal name="an0" />
        <signal name="XLXN_31" />
        <signal name="XLXN_32" />
        <signal name="XLXN_33" />
        <signal name="XLXN_34" />
        <signal name="XLXN_35" />
        <signal name="m1_c1" />
        <signal name="m0_c1" />
        <signal name="XLXN_38" />
        <signal name="XLXN_39" />
        <signal name="XLXN_40" />
        <signal name="XLXN_41" />
        <signal name="m1_c0" />
        <signal name="m0_c0" />
        <signal name="XLXN_44" />
        <signal name="XLXN_45" />
        <signal name="XLXN_46" />
        <signal name="XLXN_47" />
        <signal name="XLXN_49" />
        <signal name="XLXN_50" />
        <signal name="XLXN_51" />
        <signal name="XLXN_52" />
        <signal name="XLXN_53" />
        <signal name="XLXN_55" />
        <port polarity="Output" name="a0" />
        <port polarity="Output" name="b0" />
        <port polarity="Output" name="c0" />
        <port polarity="Output" name="f0" />
        <port polarity="Output" name="d0" />
        <port polarity="Output" name="g0" />
        <port polarity="Output" name="e0" />
        <port polarity="Output" name="an2" />
        <port polarity="Output" name="an1" />
        <port polarity="Output" name="an3" />
        <port polarity="Output" name="an0" />
        <port polarity="Input" name="m1_c1" />
        <port polarity="Input" name="m0_c1" />
        <port polarity="Input" name="m1_c0" />
        <port polarity="Input" name="m0_c0" />
        <blockdef name="algebra">
            <timestamp>2016-3-14T14:33:43</timestamp>
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
        <blockdef name="gnd">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-96" x1="64" />
            <line x2="52" y1="-48" y2="-48" x1="76" />
            <line x2="60" y1="-32" y2="-32" x1="68" />
            <line x2="40" y1="-64" y2="-64" x1="88" />
            <line x2="64" y1="-64" y2="-80" x1="64" />
            <line x2="64" y1="-128" y2="-96" x1="64" />
        </blockdef>
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-64" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-64" y2="-64" x1="96" />
        </blockdef>
        <blockdef name="nasob">
            <timestamp>2016-3-14T15:10:36</timestamp>
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
        <block symbolname="algebra" name="XLXI_1">
            <blockpin signalname="XLXN_39" name="x" />
            <blockpin signalname="XLXN_38" name="y" />
            <blockpin signalname="XLXN_53" name="z" />
            <blockpin signalname="XLXN_55" name="t" />
            <blockpin signalname="a0" name="a" />
            <blockpin signalname="b0" name="b" />
            <blockpin signalname="c0" name="c" />
            <blockpin signalname="d0" name="d" />
            <blockpin signalname="e0" name="e" />
            <blockpin signalname="f0" name="f" />
            <blockpin signalname="g0" name="g" />
        </block>
        <block symbolname="vcc" name="XLXI_10">
            <blockpin signalname="an2" name="P" />
        </block>
        <block symbolname="vcc" name="XLXI_11">
            <blockpin signalname="an1" name="P" />
        </block>
        <block symbolname="vcc" name="XLXI_12">
            <blockpin signalname="an3" name="P" />
        </block>
        <block symbolname="gnd" name="XLXI_6">
            <blockpin signalname="an0" name="G" />
        </block>
        <block symbolname="nasob" name="XLXI_23">
            <blockpin signalname="m1_c1" name="m" />
            <blockpin signalname="m0_c1" name="n" />
            <blockpin signalname="m1_c0" name="o" />
            <blockpin signalname="m0_c0" name="p" />
            <blockpin signalname="XLXN_39" name="x" />
            <blockpin signalname="XLXN_38" name="y" />
            <blockpin signalname="XLXN_53" name="z" />
            <blockpin signalname="XLXN_55" name="t" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1408" y="1392" name="XLXI_1" orien="R0">
        </instance>
        <branch name="a0">
            <wire x2="1808" y1="912" y2="912" x1="1792" />
            <wire x2="1808" y1="656" y2="912" x1="1808" />
        </branch>
        <branch name="b0">
            <wire x2="1808" y1="976" y2="976" x1="1792" />
            <wire x2="1856" y1="976" y2="976" x1="1808" />
            <wire x2="1856" y1="656" y2="976" x1="1856" />
        </branch>
        <branch name="c0">
            <wire x2="1808" y1="1040" y2="1040" x1="1792" />
            <wire x2="1904" y1="1040" y2="1040" x1="1808" />
            <wire x2="1904" y1="656" y2="1040" x1="1904" />
        </branch>
        <branch name="f0">
            <wire x2="2096" y1="1232" y2="1232" x1="1792" />
            <wire x2="2096" y1="736" y2="1232" x1="2096" />
        </branch>
        <branch name="d0">
            <wire x2="1968" y1="1104" y2="1104" x1="1792" />
            <wire x2="1968" y1="736" y2="1104" x1="1968" />
        </branch>
        <branch name="g0">
            <wire x2="2160" y1="1296" y2="1296" x1="1792" />
            <wire x2="2160" y1="736" y2="1296" x1="2160" />
        </branch>
        <branch name="e0">
            <wire x2="2032" y1="1168" y2="1168" x1="1792" />
            <wire x2="2032" y1="736" y2="1168" x1="2032" />
        </branch>
        <instance x="2352" y="1136" name="XLXI_10" orien="R0" />
        <branch name="an2">
            <wire x2="2416" y1="1136" y2="1168" x1="2416" />
        </branch>
        <instance x="2448" y="1136" name="XLXI_11" orien="R0" />
        <branch name="an1">
            <wire x2="2512" y1="1136" y2="1152" x1="2512" />
            <wire x2="2512" y1="1152" y2="1168" x1="2512" />
        </branch>
        <instance x="2544" y="1136" name="XLXI_12" orien="R0" />
        <branch name="an3">
            <wire x2="2608" y1="1136" y2="1168" x1="2608" />
        </branch>
        <instance x="2240" y="1296" name="XLXI_6" orien="R0" />
        <branch name="an0">
            <wire x2="2304" y1="1024" y2="1152" x1="2304" />
            <wire x2="2304" y1="1152" y2="1168" x1="2304" />
        </branch>
        <iomarker fontsize="28" x="1968" y="736" name="d0" orien="R270" />
        <iomarker fontsize="28" x="2160" y="736" name="g0" orien="R270" />
        <iomarker fontsize="28" x="2096" y="736" name="f0" orien="R270" />
        <iomarker fontsize="28" x="2032" y="736" name="e0" orien="R270" />
        <iomarker fontsize="28" x="2416" y="1168" name="an2" orien="R90" />
        <iomarker fontsize="28" x="2512" y="1168" name="an1" orien="R90" />
        <iomarker fontsize="28" x="2608" y="1168" name="an3" orien="R90" />
        <iomarker fontsize="28" x="2304" y="1024" name="an0" orien="R270" />
        <iomarker fontsize="28" x="1808" y="656" name="a0" orien="R270" />
        <iomarker fontsize="28" x="1856" y="656" name="b0" orien="R270" />
        <iomarker fontsize="28" x="1904" y="656" name="c0" orien="R270" />
        <iomarker fontsize="28" x="816" y="704" name="m1_c1" orien="R270" />
        <iomarker fontsize="28" x="752" y="704" name="m0_c1" orien="R270" />
        <iomarker fontsize="28" x="704" y="704" name="m1_c0" orien="R270" />
        <iomarker fontsize="28" x="656" y="704" name="m0_c0" orien="R270" />
        <branch name="m1_c1">
            <wire x2="816" y1="704" y2="1024" x1="816" />
            <wire x2="912" y1="1024" y2="1024" x1="816" />
        </branch>
        <branch name="m0_c1">
            <wire x2="752" y1="704" y2="1088" x1="752" />
            <wire x2="912" y1="1088" y2="1088" x1="752" />
        </branch>
        <branch name="XLXN_38">
            <wire x2="1392" y1="1088" y2="1088" x1="1296" />
            <wire x2="1408" y1="1056" y2="1056" x1="1392" />
            <wire x2="1392" y1="1056" y2="1088" x1="1392" />
        </branch>
        <branch name="m1_c0">
            <wire x2="704" y1="704" y2="1152" x1="704" />
            <wire x2="912" y1="1152" y2="1152" x1="704" />
        </branch>
        <branch name="m0_c0">
            <wire x2="656" y1="704" y2="1216" x1="656" />
            <wire x2="912" y1="1216" y2="1216" x1="656" />
        </branch>
        <branch name="XLXN_39">
            <wire x2="1392" y1="1024" y2="1024" x1="1296" />
            <wire x2="1408" y1="912" y2="912" x1="1392" />
            <wire x2="1392" y1="912" y2="1024" x1="1392" />
        </branch>
        <instance x="912" y="1248" name="XLXI_23" orien="R0">
        </instance>
        <branch name="XLXN_53">
            <wire x2="1344" y1="1152" y2="1152" x1="1296" />
            <wire x2="1344" y1="1152" y2="1200" x1="1344" />
            <wire x2="1408" y1="1200" y2="1200" x1="1344" />
        </branch>
        <branch name="XLXN_55">
            <wire x2="1344" y1="1216" y2="1216" x1="1296" />
            <wire x2="1344" y1="1216" y2="1344" x1="1344" />
            <wire x2="1408" y1="1344" y2="1344" x1="1344" />
        </branch>
    </sheet>
</drawing>