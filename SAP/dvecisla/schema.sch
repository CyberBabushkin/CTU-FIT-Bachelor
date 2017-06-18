<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3e" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="m3_c0" />
        <signal name="m2_c0" />
        <signal name="m1_c0" />
        <signal name="m0_c0" />
        <signal name="a0" />
        <signal name="b0" />
        <signal name="c0" />
        <signal name="g0" />
        <signal name="f0" />
        <signal name="d0" />
        <signal name="e0" />
        <signal name="an2" />
        <signal name="an1" />
        <signal name="an3" />
        <signal name="an0" />
        <port polarity="Input" name="m3_c0" />
        <port polarity="Input" name="m2_c0" />
        <port polarity="Input" name="m1_c0" />
        <port polarity="Input" name="m0_c0" />
        <port polarity="Output" name="a0" />
        <port polarity="Output" name="b0" />
        <port polarity="Output" name="c0" />
        <port polarity="Output" name="g0" />
        <port polarity="Output" name="f0" />
        <port polarity="Output" name="d0" />
        <port polarity="Output" name="e0" />
        <port polarity="Output" name="an2" />
        <port polarity="Output" name="an1" />
        <port polarity="Output" name="an3" />
        <port polarity="Output" name="an0" />
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
        <block symbolname="algebra" name="XLXI_1">
            <blockpin signalname="m3_c0" name="x" />
            <blockpin signalname="m2_c0" name="y" />
            <blockpin signalname="m1_c0" name="z" />
            <blockpin signalname="m0_c0" name="t" />
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
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="832" y="1456" name="XLXI_1" orien="R0">
        </instance>
        <branch name="m3_c0">
            <wire x2="752" y1="800" y2="976" x1="752" />
            <wire x2="832" y1="976" y2="976" x1="752" />
        </branch>
        <branch name="m2_c0">
            <wire x2="688" y1="800" y2="1120" x1="688" />
            <wire x2="832" y1="1120" y2="1120" x1="688" />
        </branch>
        <branch name="m1_c0">
            <wire x2="640" y1="800" y2="1264" x1="640" />
            <wire x2="832" y1="1264" y2="1264" x1="640" />
        </branch>
        <branch name="m0_c0">
            <wire x2="592" y1="800" y2="1408" x1="592" />
            <wire x2="832" y1="1408" y2="1408" x1="592" />
        </branch>
        <branch name="a0">
            <wire x2="1232" y1="976" y2="976" x1="1216" />
            <wire x2="1232" y1="720" y2="976" x1="1232" />
        </branch>
        <branch name="b0">
            <wire x2="1232" y1="1040" y2="1040" x1="1216" />
            <wire x2="1280" y1="1040" y2="1040" x1="1232" />
            <wire x2="1280" y1="720" y2="1040" x1="1280" />
        </branch>
        <branch name="c0">
            <wire x2="1232" y1="1104" y2="1104" x1="1216" />
            <wire x2="1328" y1="1104" y2="1104" x1="1232" />
            <wire x2="1328" y1="720" y2="1104" x1="1328" />
        </branch>
        <branch name="f0">
            <wire x2="1520" y1="1296" y2="1296" x1="1216" />
            <wire x2="1520" y1="800" y2="1296" x1="1520" />
        </branch>
        <branch name="d0">
            <wire x2="1392" y1="1168" y2="1168" x1="1216" />
            <wire x2="1392" y1="800" y2="1168" x1="1392" />
        </branch>
        <iomarker fontsize="28" x="752" y="800" name="m3_c0" orien="R270" />
        <iomarker fontsize="28" x="688" y="800" name="m2_c0" orien="R270" />
        <iomarker fontsize="28" x="640" y="800" name="m1_c0" orien="R270" />
        <iomarker fontsize="28" x="592" y="800" name="m0_c0" orien="R270" />
        <iomarker fontsize="28" x="1392" y="800" name="d0" orien="R270" />
        <branch name="g0">
            <wire x2="1584" y1="1360" y2="1360" x1="1216" />
            <wire x2="1584" y1="800" y2="1360" x1="1584" />
        </branch>
        <iomarker fontsize="28" x="1584" y="800" name="g0" orien="R270" />
        <branch name="e0">
            <wire x2="1456" y1="1232" y2="1232" x1="1216" />
            <wire x2="1456" y1="800" y2="1232" x1="1456" />
        </branch>
        <iomarker fontsize="28" x="1520" y="800" name="f0" orien="R270" />
        <iomarker fontsize="28" x="1456" y="800" name="e0" orien="R270" />
        <instance x="1776" y="1200" name="XLXI_10" orien="R0" />
        <branch name="an2">
            <wire x2="1840" y1="1200" y2="1232" x1="1840" />
        </branch>
        <iomarker fontsize="28" x="1840" y="1232" name="an2" orien="R90" />
        <instance x="1872" y="1200" name="XLXI_11" orien="R0" />
        <branch name="an1">
            <wire x2="1936" y1="1200" y2="1216" x1="1936" />
            <wire x2="1936" y1="1216" y2="1232" x1="1936" />
        </branch>
        <iomarker fontsize="28" x="1936" y="1232" name="an1" orien="R90" />
        <instance x="1968" y="1200" name="XLXI_12" orien="R0" />
        <branch name="an3">
            <wire x2="2032" y1="1200" y2="1232" x1="2032" />
        </branch>
        <iomarker fontsize="28" x="2032" y="1232" name="an3" orien="R90" />
        <instance x="1664" y="1360" name="XLXI_6" orien="R0" />
        <branch name="an0">
            <wire x2="1728" y1="1088" y2="1216" x1="1728" />
            <wire x2="1728" y1="1216" y2="1232" x1="1728" />
        </branch>
        <iomarker fontsize="28" x="1728" y="1088" name="an0" orien="R270" />
        <iomarker fontsize="28" x="1232" y="720" name="a0" orien="R270" />
        <iomarker fontsize="28" x="1280" y="720" name="b0" orien="R270" />
        <iomarker fontsize="28" x="1328" y="720" name="c0" orien="R270" />
    </sheet>
</drawing>