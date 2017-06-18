<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3e" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_1" />
        <signal name="CIN" />
        <signal name="A0" />
        <signal name="B0" />
        <signal name="S0" />
        <signal name="COUT" />
        <signal name="XLXN_2" />
        <signal name="XLXN_3" />
        <signal name="A1" />
        <signal name="B1" />
        <signal name="A2" />
        <signal name="B2" />
        <signal name="A3" />
        <signal name="S1" />
        <signal name="S3" />
        <signal name="S2" />
        <signal name="B3" />
        <port polarity="Input" name="CIN" />
        <port polarity="Input" name="A0" />
        <port polarity="Input" name="B0" />
        <port polarity="Output" name="S0" />
        <port polarity="Output" name="COUT" />
        <port polarity="Input" name="A1" />
        <port polarity="Input" name="B1" />
        <port polarity="Input" name="A2" />
        <port polarity="Input" name="B2" />
        <port polarity="Input" name="A3" />
        <port polarity="Output" name="S1" />
        <port polarity="Output" name="S3" />
        <port polarity="Output" name="S2" />
        <port polarity="Input" name="B3" />
        <blockdef name="gates">
            <timestamp>2016-2-24T14:24:53</timestamp>
            <rect width="256" x="64" y="-192" height="192" />
            <line x2="0" y1="-160" y2="-160" x1="64" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="384" y1="-160" y2="-160" x1="320" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
        </blockdef>
        <block symbolname="gates" name="XLXI_4">
            <blockpin signalname="B3" name="B" />
            <blockpin signalname="A3" name="A" />
            <blockpin signalname="XLXN_3" name="p" />
            <blockpin signalname="S3" name="q" />
            <blockpin signalname="COUT" name="S" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <branch name="XLXN_1">
            <wire x2="1008" y1="672" y2="672" x1="992" />
            <wire x2="1136" y1="672" y2="672" x1="1008" />
        </branch>
        <branch name="CIN">
            <wire x2="608" y1="672" y2="672" x1="512" />
        </branch>
        <branch name="A0">
            <wire x2="512" y1="432" y2="608" x1="512" />
            <wire x2="608" y1="608" y2="608" x1="512" />
        </branch>
        <branch name="B0">
            <wire x2="576" y1="432" y2="544" x1="576" />
            <wire x2="608" y1="544" y2="544" x1="576" />
        </branch>
        <branch name="S0">
            <wire x2="1024" y1="544" y2="544" x1="992" />
            <wire x2="1024" y1="544" y2="752" x1="1024" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="1568" y1="672" y2="672" x1="1520" />
            <wire x2="1648" y1="672" y2="672" x1="1568" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="2208" y1="672" y2="672" x1="2032" />
        </branch>
        <branch name="COUT">
            <wire x2="2704" y1="672" y2="672" x1="2592" />
        </branch>
        <branch name="A1">
            <wire x2="1056" y1="432" y2="608" x1="1056" />
            <wire x2="1136" y1="608" y2="608" x1="1056" />
        </branch>
        <branch name="B1">
            <wire x2="1120" y1="432" y2="544" x1="1120" />
            <wire x2="1136" y1="544" y2="544" x1="1120" />
        </branch>
        <branch name="A2">
            <wire x2="1568" y1="432" y2="608" x1="1568" />
            <wire x2="1648" y1="608" y2="608" x1="1568" />
        </branch>
        <branch name="B2">
            <wire x2="1632" y1="432" y2="544" x1="1632" />
            <wire x2="1648" y1="544" y2="544" x1="1632" />
        </branch>
        <branch name="A3">
            <wire x2="2096" y1="416" y2="608" x1="2096" />
            <wire x2="2208" y1="608" y2="608" x1="2096" />
        </branch>
        <iomarker fontsize="28" x="512" y="672" name="CIN" orien="R180" />
        <iomarker fontsize="28" x="512" y="432" name="A0" orien="R270" />
        <iomarker fontsize="28" x="576" y="432" name="B0" orien="R270" />
        <iomarker fontsize="28" x="1024" y="752" name="S0" orien="R90" />
        <iomarker fontsize="28" x="1056" y="432" name="A1" orien="R270" />
        <iomarker fontsize="28" x="1120" y="432" name="B1" orien="R270" />
        <iomarker fontsize="28" x="1568" y="432" name="A2" orien="R270" />
        <iomarker fontsize="28" x="1632" y="432" name="B2" orien="R270" />
        <iomarker fontsize="28" x="2096" y="416" name="A3" orien="R270" />
        <iomarker fontsize="28" x="2704" y="672" name="COUT" orien="R0" />
        <branch name="S1">
            <wire x2="1552" y1="544" y2="544" x1="1520" />
            <wire x2="1552" y1="544" y2="752" x1="1552" />
        </branch>
        <branch name="S3">
            <wire x2="2608" y1="544" y2="544" x1="2592" />
            <wire x2="2608" y1="544" y2="784" x1="2608" />
        </branch>
        <branch name="S2">
            <wire x2="2080" y1="544" y2="544" x1="2032" />
            <wire x2="2080" y1="544" y2="784" x1="2080" />
        </branch>
        <iomarker fontsize="28" x="1552" y="752" name="S1" orien="R90" />
        <iomarker fontsize="28" x="2080" y="784" name="S2" orien="R90" />
        <instance x="2208" y="704" name="XLXI_4" orien="R0">
        </instance>
        <branch name="B3">
            <wire x2="2160" y1="416" y2="544" x1="2160" />
            <wire x2="2208" y1="544" y2="544" x1="2160" />
        </branch>
        <iomarker fontsize="28" x="2160" y="416" name="B3" orien="R270" />
        <iomarker fontsize="28" x="2608" y="784" name="S3" orien="R90" />
    </sheet>
</drawing>