<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3e" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="CD" />
        <signal name="CA" />
        <signal name="CE" />
        <signal name="CB" />
        <signal name="CC" />
        <signal name="XLXN_13" />
        <signal name="B" />
        <signal name="D" />
        <signal name="C" />
        <signal name="A" />
        <signal name="XLXN_45" />
        <signal name="XLXN_46" />
        <signal name="XLXN_47" />
        <signal name="XLXN_52" />
        <signal name="XLXN_48" />
        <signal name="XLXN_49" />
        <signal name="XLXN_50" />
        <signal name="XLXN_51" />
        <signal name="XLXN_57" />
        <signal name="XLXN_58" />
        <signal name="XLXN_59" />
        <signal name="XLXN_60" />
        <signal name="XLXN_61" />
        <signal name="XLXN_62" />
        <signal name="XLXN_63" />
        <signal name="CG" />
        <signal name="XLXN_64" />
        <signal name="XLXN_65" />
        <signal name="XLXN_66" />
        <signal name="CF" />
        <signal name="XLXN_90" />
        <signal name="XLXN_91" />
        <signal name="XLXN_92" />
        <signal name="XLXN_93" />
        <port polarity="Output" name="CD" />
        <port polarity="Output" name="CA" />
        <port polarity="Output" name="CE" />
        <port polarity="Output" name="CB" />
        <port polarity="Output" name="CC" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="D" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="XLXN_45" />
        <port polarity="Input" name="XLXN_46" />
        <port polarity="Input" name="XLXN_47" />
        <port polarity="Input" name="XLXN_48" />
        <port polarity="Input" name="XLXN_49" />
        <port polarity="Input" name="XLXN_50" />
        <port polarity="Input" name="XLXN_51" />
        <port polarity="Input" name="XLXN_57" />
        <port polarity="Input" name="XLXN_58" />
        <port polarity="Input" name="XLXN_59" />
        <port polarity="Input" name="XLXN_60" />
        <port polarity="Input" name="XLXN_61" />
        <port polarity="Input" name="XLXN_62" />
        <port polarity="Input" name="XLXN_63" />
        <port polarity="Output" name="CG" />
        <port polarity="Output" name="CF" />
        <blockdef name="and3b3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="52" cy="-128" />
            <line x2="40" y1="-192" y2="-192" x1="0" />
            <circle r="12" cx="52" cy="-192" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
        </blockdef>
        <blockdef name="and4b1">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="192" y1="-160" y2="-160" x1="256" />
            <line x2="64" y1="-64" y2="-256" x1="64" />
            <line x2="64" y1="-112" y2="-112" x1="144" />
            <arc ex="144" ey="-208" sx="144" sy="-112" r="48" cx="144" cy="-160" />
            <line x2="144" y1="-208" y2="-208" x1="64" />
        </blockdef>
        <blockdef name="and4b2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="52" cy="-128" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="192" y1="-160" y2="-160" x1="256" />
            <line x2="144" y1="-208" y2="-208" x1="64" />
            <arc ex="144" ey="-208" sx="144" sy="-112" r="48" cx="144" cy="-160" />
            <line x2="64" y1="-64" y2="-256" x1="64" />
            <line x2="64" y1="-112" y2="-112" x1="144" />
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
        <blockdef name="or4">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="48" y1="-256" y2="-256" x1="0" />
            <line x2="192" y1="-160" y2="-160" x1="256" />
            <arc ex="112" ey="-208" sx="192" sy="-160" r="88" cx="116" cy="-120" />
            <line x2="48" y1="-208" y2="-208" x1="112" />
            <line x2="48" y1="-112" y2="-112" x1="112" />
            <line x2="48" y1="-256" y2="-208" x1="48" />
            <line x2="48" y1="-64" y2="-112" x1="48" />
            <arc ex="48" ey="-208" sx="48" sy="-112" r="56" cx="16" cy="-160" />
            <arc ex="192" ey="-160" sx="112" sy="-112" r="88" cx="116" cy="-200" />
        </blockdef>
        <blockdef name="and3b2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="52" cy="-128" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
        </blockdef>
        <blockdef name="and3b1">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
        </blockdef>
        <blockdef name="and2b1">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-48" y2="-144" x1="64" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
        </blockdef>
        <blockdef name="and4b3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="52" cy="-128" />
            <line x2="40" y1="-192" y2="-192" x1="0" />
            <circle r="12" cx="52" cy="-192" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="192" y1="-160" y2="-160" x1="256" />
            <line x2="64" y1="-64" y2="-256" x1="64" />
            <line x2="64" y1="-112" y2="-112" x1="144" />
            <arc ex="144" ey="-208" sx="144" sy="-112" r="48" cx="144" cy="-160" />
            <line x2="144" y1="-208" y2="-208" x1="64" />
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
        <block symbolname="or4" name="XLXI_11">
            <blockpin name="I0" />
            <blockpin name="I1" />
            <blockpin name="I2" />
            <blockpin name="I3" />
            <blockpin signalname="CD" name="O" />
        </block>
        <block symbolname="or4" name="XLXI_14">
            <blockpin name="I0" />
            <blockpin name="I1" />
            <blockpin name="I2" />
            <blockpin name="I3" />
            <blockpin signalname="CA" name="O" />
        </block>
        <block symbolname="or3" name="XLXI_10">
            <blockpin name="I0" />
            <blockpin name="I1" />
            <blockpin name="I2" />
            <blockpin signalname="CE" name="O" />
        </block>
        <block symbolname="and2b1" name="XLXI_30">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="A" name="I1" />
            <blockpin name="O" />
        </block>
        <block symbolname="and4b3" name="XLXI_31">
            <blockpin signalname="B" name="I0" />
            <blockpin signalname="D" name="I1" />
            <blockpin signalname="A" name="I2" />
            <blockpin signalname="C" name="I3" />
            <blockpin name="O" />
        </block>
        <block symbolname="and4b2" name="XLXI_32">
            <blockpin signalname="XLXN_47" name="I0" />
            <blockpin signalname="XLXN_46" name="I1" />
            <blockpin signalname="XLXN_45" name="I2" />
            <blockpin signalname="A" name="I3" />
            <blockpin name="O" />
        </block>
        <block symbolname="and4b3" name="XLXI_34">
            <blockpin signalname="XLXN_60" name="I0" />
            <blockpin signalname="XLXN_59" name="I1" />
            <blockpin signalname="XLXN_58" name="I2" />
            <blockpin signalname="XLXN_57" name="I3" />
            <blockpin name="O" />
        </block>
        <block symbolname="and3" name="XLXI_35">
            <blockpin signalname="XLXN_63" name="I0" />
            <blockpin signalname="XLXN_62" name="I1" />
            <blockpin signalname="XLXN_61" name="I2" />
            <blockpin name="O" />
        </block>
        <block symbolname="and4b2" name="XLXI_36">
            <blockpin name="I0" />
            <blockpin name="I1" />
            <blockpin name="I2" />
            <blockpin name="I3" />
            <blockpin name="O" />
        </block>
        <block symbolname="or4" name="XLXI_13">
            <blockpin name="I0" />
            <blockpin name="I1" />
            <blockpin name="I2" />
            <blockpin name="I3" />
            <blockpin signalname="CB" name="O" />
        </block>
        <block symbolname="or3" name="XLXI_12">
            <blockpin name="I0" />
            <blockpin signalname="XLXN_13" name="I1" />
            <blockpin name="I2" />
            <blockpin signalname="CC" name="O" />
        </block>
        <block symbolname="and3b1" name="XLXI_39">
            <blockpin name="I0" />
            <blockpin name="I1" />
            <blockpin name="I2" />
            <blockpin name="O" />
        </block>
        <block symbolname="and3" name="XLXI_40">
            <blockpin name="I0" />
            <blockpin name="I1" />
            <blockpin name="I2" />
            <blockpin signalname="XLXN_13" name="O" />
        </block>
        <block symbolname="and4b2" name="XLXI_41">
            <blockpin name="I0" />
            <blockpin name="I1" />
            <blockpin name="I2" />
            <blockpin name="I3" />
            <blockpin name="O" />
        </block>
        <block symbolname="and3b1" name="XLXI_42">
            <blockpin name="I0" />
            <blockpin name="I1" />
            <blockpin name="I2" />
            <blockpin name="O" />
        </block>
        <block symbolname="and3" name="XLXI_43">
            <blockpin name="I0" />
            <blockpin name="I1" />
            <blockpin name="I2" />
            <blockpin name="O" />
        </block>
        <block symbolname="and3b1" name="XLXI_44">
            <blockpin name="I0" />
            <blockpin name="I1" />
            <blockpin name="I2" />
            <blockpin name="O" />
        </block>
        <block symbolname="and4b2" name="XLXI_45">
            <blockpin name="I0" />
            <blockpin name="I1" />
            <blockpin name="I2" />
            <blockpin name="I3" />
            <blockpin name="O" />
        </block>
        <block symbolname="and4b3" name="XLXI_46">
            <blockpin name="I0" />
            <blockpin name="I1" />
            <blockpin name="I2" />
            <blockpin name="I3" />
            <blockpin name="O" />
        </block>
        <block symbolname="and4b3" name="XLXI_47">
            <blockpin name="I0" />
            <blockpin name="I1" />
            <blockpin name="I2" />
            <blockpin name="I3" />
            <blockpin name="O" />
        </block>
        <block symbolname="and4b1" name="XLXI_48">
            <blockpin name="I0" />
            <blockpin name="I1" />
            <blockpin name="I2" />
            <blockpin name="I3" />
            <blockpin name="O" />
        </block>
        <block symbolname="and4b1" name="XLXI_49">
            <blockpin name="I0" />
            <blockpin name="I1" />
            <blockpin name="I2" />
            <blockpin name="I3" />
            <blockpin name="O" />
        </block>
        <block symbolname="and4b3" name="XLXI_33">
            <blockpin signalname="XLXN_51" name="I0" />
            <blockpin signalname="XLXN_50" name="I1" />
            <blockpin signalname="XLXN_49" name="I2" />
            <blockpin signalname="XLXN_48" name="I3" />
            <blockpin name="O" />
        </block>
        <block symbolname="and3b3" name="XLXI_1">
            <blockpin signalname="C" name="I0" />
            <blockpin signalname="D" name="I1" />
            <blockpin signalname="B" name="I2" />
            <blockpin signalname="XLXN_64" name="O" />
        </block>
        <block symbolname="and4b1" name="XLXI_2">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="C" name="I1" />
            <blockpin signalname="A" name="I2" />
            <blockpin signalname="B" name="I3" />
            <blockpin signalname="XLXN_65" name="O" />
        </block>
        <block symbolname="or3" name="XLXI_4">
            <blockpin signalname="XLXN_66" name="I0" />
            <blockpin signalname="XLXN_65" name="I1" />
            <blockpin signalname="XLXN_64" name="I2" />
            <blockpin signalname="CG" name="O" />
        </block>
        <block symbolname="and4b2" name="XLXI_3">
            <blockpin signalname="B" name="I0" />
            <blockpin signalname="A" name="I1" />
            <blockpin signalname="D" name="I2" />
            <blockpin signalname="C" name="I3" />
            <blockpin signalname="XLXN_66" name="O" />
        </block>
        <block symbolname="or4" name="XLXI_9">
            <blockpin signalname="XLXN_93" name="I0" />
            <blockpin signalname="XLXN_92" name="I1" />
            <blockpin signalname="XLXN_91" name="I2" />
            <blockpin signalname="XLXN_90" name="I3" />
            <blockpin signalname="CF" name="O" />
        </block>
        <block symbolname="and3b2" name="XLXI_15">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="C" name="I1" />
            <blockpin signalname="A" name="I2" />
            <blockpin signalname="XLXN_90" name="O" />
        </block>
        <block symbolname="and3b2" name="XLXI_16">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="C" name="I1" />
            <blockpin signalname="B" name="I2" />
            <blockpin signalname="XLXN_91" name="O" />
        </block>
        <block symbolname="and3b1" name="XLXI_17">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="B" name="I1" />
            <blockpin signalname="A" name="I2" />
            <blockpin signalname="XLXN_92" name="O" />
        </block>
        <block symbolname="and4b1" name="XLXI_18">
            <blockpin signalname="B" name="I0" />
            <blockpin signalname="A" name="I1" />
            <blockpin signalname="D" name="I2" />
            <blockpin signalname="C" name="I3" />
            <blockpin signalname="XLXN_93" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1344" y="2320" name="XLXI_11" orien="R270" />
        <instance x="2992" y="1392" name="XLXI_14" orien="R180" />
        <branch name="CD">
            <wire x2="1184" y1="2032" y2="2064" x1="1184" />
        </branch>
        <iomarker fontsize="28" x="1184" y="2032" name="CD" orien="R270" />
        <branch name="CA">
            <wire x2="2736" y1="1552" y2="1552" x1="2704" />
        </branch>
        <iomarker fontsize="28" x="2704" y="1552" name="CA" orien="R180" />
        <branch name="CE">
            <wire x2="768" y1="2192" y2="2192" x1="720" />
            <wire x2="784" y1="2192" y2="2192" x1="768" />
        </branch>
        <iomarker fontsize="28" x="784" y="2192" name="CE" orien="R0" />
        <instance x="176" y="2096" name="XLXI_30" orien="R0" />
        <instance x="144" y="2352" name="XLXI_31" orien="R0" />
        <instance x="160" y="2624" name="XLXI_32" orien="R0" />
        <instance x="3008" y="2352" name="XLXI_13" orien="R270" />
        <branch name="CB">
            <wire x2="2848" y1="2064" y2="2096" x1="2848" />
        </branch>
        <iomarker fontsize="28" x="2848" y="2064" name="CB" orien="R270" />
        <instance x="2208" y="2336" name="XLXI_12" orien="R270" />
        <branch name="CC">
            <wire x2="2080" y1="2048" y2="2080" x1="2080" />
        </branch>
        <iomarker fontsize="28" x="2080" y="2048" name="CC" orien="R270" />
        <branch name="XLXN_13">
            <wire x2="2080" y1="2336" y2="2368" x1="2080" />
        </branch>
        <instance x="2208" y="2624" name="XLXI_40" orien="R270" />
        <instance x="2704" y="2624" name="XLXI_42" orien="R270" />
        <instance x="2912" y="2624" name="XLXI_43" orien="R270" />
        <instance x="3376" y="2624" name="XLXI_45" orien="R270" />
        <instance x="3376" y="1680" name="XLXI_46" orien="R180" />
        <instance x="3376" y="1440" name="XLXI_47" orien="R180" />
        <instance x="3360" y="1152" name="XLXI_48" orien="R180" />
        <instance x="3360" y="896" name="XLXI_49" orien="R180" />
        <branch name="A">
            <wire x2="176" y1="1968" y2="1968" x1="144" />
        </branch>
        <iomarker fontsize="28" x="144" y="1968" name="A" orien="R180" />
        <branch name="D">
            <wire x2="176" y1="2032" y2="2032" x1="144" />
        </branch>
        <iomarker fontsize="28" x="144" y="2032" name="D" orien="R180" />
        <branch name="C">
            <wire x2="144" y1="2096" y2="2096" x1="112" />
        </branch>
        <iomarker fontsize="28" x="112" y="2096" name="C" orien="R180" />
        <branch name="A">
            <wire x2="144" y1="2160" y2="2160" x1="112" />
        </branch>
        <iomarker fontsize="28" x="112" y="2160" name="A" orien="R180" />
        <branch name="D">
            <wire x2="144" y1="2224" y2="2224" x1="112" />
        </branch>
        <iomarker fontsize="28" x="112" y="2224" name="D" orien="R180" />
        <branch name="B">
            <wire x2="144" y1="2288" y2="2288" x1="112" />
        </branch>
        <iomarker fontsize="28" x="112" y="2288" name="B" orien="R180" />
        <branch name="A">
            <wire x2="160" y1="2368" y2="2368" x1="128" />
        </branch>
        <iomarker fontsize="28" x="128" y="2368" name="A" orien="R180" />
        <branch name="XLXN_45">
            <wire x2="160" y1="2432" y2="2432" x1="128" />
        </branch>
        <iomarker fontsize="28" x="128" y="2432" name="XLXN_45" orien="R180" />
        <branch name="XLXN_46">
            <wire x2="160" y1="2496" y2="2496" x1="128" />
        </branch>
        <iomarker fontsize="28" x="128" y="2496" name="XLXN_46" orien="R180" />
        <branch name="XLXN_47">
            <wire x2="160" y1="2560" y2="2560" x1="128" />
        </branch>
        <iomarker fontsize="28" x="128" y="2560" name="XLXN_47" orien="R180" />
        <instance x="464" y="2320" name="XLXI_10" orien="R0" />
        <branch name="XLXN_48">
            <wire x2="688" y1="2528" y2="2528" x1="672" />
            <wire x2="704" y1="2528" y2="2528" x1="688" />
            <wire x2="704" y1="2512" y2="2528" x1="704" />
        </branch>
        <branch name="XLXN_49">
            <wire x2="768" y1="2512" y2="2544" x1="768" />
            <wire x2="768" y1="2544" y2="2560" x1="768" />
        </branch>
        <branch name="XLXN_50">
            <wire x2="832" y1="2512" y2="2544" x1="832" />
            <wire x2="832" y1="2544" y2="2560" x1="832" />
        </branch>
        <branch name="XLXN_51">
            <wire x2="896" y1="2512" y2="2544" x1="896" />
            <wire x2="896" y1="2544" y2="2560" x1="896" />
        </branch>
        <instance x="960" y="2512" name="XLXI_33" orien="R270" />
        <iomarker fontsize="28" x="672" y="2528" name="XLXN_48" orien="R90" />
        <iomarker fontsize="28" x="768" y="2560" name="XLXN_49" orien="R90" />
        <iomarker fontsize="28" x="832" y="2560" name="XLXN_50" orien="R90" />
        <iomarker fontsize="28" x="896" y="2560" name="XLXN_51" orien="R90" />
        <instance x="1456" y="2624" name="XLXI_35" orien="R270" />
        <instance x="1280" y="2608" name="XLXI_34" orien="R270" />
        <instance x="1696" y="2624" name="XLXI_36" orien="R270" />
        <instance x="2000" y="2608" name="XLXI_39" orien="R270" />
        <instance x="2448" y="2592" name="XLXI_41" orien="R270" />
        <instance x="3104" y="2624" name="XLXI_44" orien="R270" />
        <branch name="XLXN_57">
            <wire x2="1024" y1="2608" y2="2608" x1="992" />
        </branch>
        <iomarker fontsize="28" x="992" y="2608" name="XLXN_57" orien="R90" />
        <branch name="XLXN_58">
            <wire x2="1088" y1="2608" y2="2640" x1="1088" />
        </branch>
        <iomarker fontsize="28" x="1088" y="2640" name="XLXN_58" orien="R90" />
        <branch name="XLXN_59">
            <wire x2="1152" y1="2608" y2="2640" x1="1152" />
        </branch>
        <iomarker fontsize="28" x="1152" y="2640" name="XLXN_59" orien="R90" />
        <branch name="XLXN_60">
            <wire x2="1216" y1="2608" y2="2640" x1="1216" />
        </branch>
        <iomarker fontsize="28" x="1216" y="2640" name="XLXN_60" orien="R90" />
        <branch name="XLXN_61">
            <wire x2="1264" y1="2624" y2="2624" x1="1232" />
        </branch>
        <iomarker fontsize="28" x="1232" y="2624" name="XLXN_61" orien="R90" />
        <branch name="XLXN_62">
            <wire x2="1328" y1="2624" y2="2656" x1="1328" />
        </branch>
        <iomarker fontsize="28" x="1328" y="2656" name="XLXN_62" orien="R90" />
        <branch name="XLXN_63">
            <wire x2="1424" y1="2624" y2="2624" x1="1392" />
        </branch>
        <iomarker fontsize="28" x="1424" y="2624" name="XLXN_63" orien="R90" />
        <instance x="224" y="384" name="XLXI_1" orien="R0" />
        <instance x="224" y="688" name="XLXI_2" orien="R0" />
        <instance x="624" y="656" name="XLXI_4" orien="R0" />
        <branch name="CG">
            <wire x2="912" y1="528" y2="528" x1="880" />
        </branch>
        <branch name="B">
            <wire x2="224" y1="192" y2="192" x1="192" />
        </branch>
        <branch name="D">
            <wire x2="224" y1="256" y2="256" x1="192" />
        </branch>
        <branch name="C">
            <wire x2="224" y1="320" y2="320" x1="192" />
        </branch>
        <branch name="B">
            <wire x2="224" y1="432" y2="432" x1="192" />
        </branch>
        <branch name="A">
            <wire x2="224" y1="496" y2="496" x1="192" />
        </branch>
        <branch name="C">
            <wire x2="224" y1="560" y2="560" x1="192" />
        </branch>
        <branch name="D">
            <wire x2="224" y1="624" y2="624" x1="192" />
        </branch>
        <branch name="C">
            <wire x2="224" y1="720" y2="720" x1="192" />
        </branch>
        <branch name="D">
            <wire x2="224" y1="784" y2="784" x1="192" />
        </branch>
        <branch name="A">
            <wire x2="224" y1="848" y2="848" x1="192" />
        </branch>
        <branch name="B">
            <wire x2="224" y1="912" y2="912" x1="192" />
        </branch>
        <branch name="XLXN_64">
            <wire x2="624" y1="256" y2="256" x1="480" />
            <wire x2="624" y1="256" y2="464" x1="624" />
        </branch>
        <branch name="XLXN_65">
            <wire x2="624" y1="528" y2="528" x1="480" />
        </branch>
        <branch name="XLXN_66">
            <wire x2="624" y1="816" y2="816" x1="480" />
            <wire x2="624" y1="592" y2="816" x1="624" />
        </branch>
        <instance x="224" y="976" name="XLXI_3" orien="R0" />
        <iomarker fontsize="28" x="912" y="528" name="CG" orien="R0" />
        <iomarker fontsize="28" x="192" y="192" name="B" orien="R180" />
        <iomarker fontsize="28" x="192" y="256" name="D" orien="R180" />
        <iomarker fontsize="28" x="192" y="320" name="C" orien="R180" />
        <iomarker fontsize="28" x="192" y="432" name="B" orien="R180" />
        <iomarker fontsize="28" x="192" y="496" name="A" orien="R180" />
        <iomarker fontsize="28" x="192" y="560" name="C" orien="R180" />
        <iomarker fontsize="28" x="192" y="624" name="D" orien="R180" />
        <iomarker fontsize="28" x="192" y="720" name="C" orien="R180" />
        <iomarker fontsize="28" x="192" y="784" name="D" orien="R180" />
        <iomarker fontsize="28" x="192" y="848" name="A" orien="R180" />
        <iomarker fontsize="28" x="192" y="912" name="B" orien="R180" />
        <instance x="640" y="1488" name="XLXI_9" orien="R0" />
        <branch name="CF">
            <wire x2="928" y1="1328" y2="1328" x1="896" />
        </branch>
        <instance x="224" y="1200" name="XLXI_15" orien="R0" />
        <instance x="224" y="1392" name="XLXI_16" orien="R0" />
        <instance x="224" y="1600" name="XLXI_17" orien="R0" />
        <branch name="A">
            <wire x2="224" y1="1008" y2="1008" x1="192" />
        </branch>
        <branch name="C">
            <wire x2="224" y1="1072" y2="1072" x1="192" />
        </branch>
        <branch name="D">
            <wire x2="224" y1="1136" y2="1136" x1="192" />
        </branch>
        <branch name="B">
            <wire x2="224" y1="1200" y2="1200" x1="192" />
        </branch>
        <branch name="C">
            <wire x2="224" y1="1264" y2="1264" x1="192" />
        </branch>
        <branch name="D">
            <wire x2="224" y1="1328" y2="1328" x1="192" />
        </branch>
        <branch name="A">
            <wire x2="224" y1="1408" y2="1408" x1="192" />
        </branch>
        <branch name="B">
            <wire x2="224" y1="1472" y2="1472" x1="192" />
        </branch>
        <branch name="D">
            <wire x2="224" y1="1536" y2="1536" x1="192" />
        </branch>
        <instance x="224" y="1856" name="XLXI_18" orien="R0" />
        <branch name="C">
            <wire x2="208" y1="1600" y2="1600" x1="192" />
            <wire x2="224" y1="1600" y2="1600" x1="208" />
        </branch>
        <branch name="D">
            <wire x2="208" y1="1664" y2="1664" x1="192" />
            <wire x2="224" y1="1664" y2="1664" x1="208" />
        </branch>
        <branch name="A">
            <wire x2="208" y1="1728" y2="1728" x1="192" />
            <wire x2="224" y1="1728" y2="1728" x1="208" />
        </branch>
        <branch name="B">
            <wire x2="208" y1="1792" y2="1792" x1="192" />
            <wire x2="224" y1="1792" y2="1792" x1="208" />
        </branch>
        <branch name="XLXN_90">
            <wire x2="640" y1="1072" y2="1072" x1="480" />
            <wire x2="640" y1="1072" y2="1232" x1="640" />
        </branch>
        <branch name="XLXN_91">
            <wire x2="560" y1="1264" y2="1264" x1="480" />
            <wire x2="560" y1="1264" y2="1296" x1="560" />
            <wire x2="640" y1="1296" y2="1296" x1="560" />
        </branch>
        <branch name="XLXN_92">
            <wire x2="560" y1="1472" y2="1472" x1="480" />
            <wire x2="560" y1="1360" y2="1472" x1="560" />
            <wire x2="640" y1="1360" y2="1360" x1="560" />
        </branch>
        <branch name="XLXN_93">
            <wire x2="640" y1="1696" y2="1696" x1="480" />
            <wire x2="640" y1="1424" y2="1696" x1="640" />
        </branch>
        <iomarker fontsize="28" x="928" y="1328" name="CF" orien="R0" />
        <iomarker fontsize="28" x="192" y="1008" name="A" orien="R180" />
        <iomarker fontsize="28" x="192" y="1072" name="C" orien="R180" />
        <iomarker fontsize="28" x="192" y="1136" name="D" orien="R180" />
        <iomarker fontsize="28" x="192" y="1200" name="B" orien="R180" />
        <iomarker fontsize="28" x="192" y="1264" name="C" orien="R180" />
        <iomarker fontsize="28" x="192" y="1328" name="D" orien="R180" />
        <iomarker fontsize="28" x="192" y="1408" name="A" orien="R180" />
        <iomarker fontsize="28" x="192" y="1472" name="B" orien="R180" />
        <iomarker fontsize="28" x="192" y="1536" name="D" orien="R180" />
        <iomarker fontsize="28" x="192" y="1664" name="D" orien="R180" />
        <iomarker fontsize="28" x="192" y="1728" name="A" orien="R180" />
        <iomarker fontsize="28" x="192" y="1792" name="B" orien="R180" />
        <iomarker fontsize="28" x="192" y="1600" name="C" orien="R180" />
    </sheet>
</drawing>