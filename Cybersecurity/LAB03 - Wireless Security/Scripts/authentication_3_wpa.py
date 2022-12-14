#!/usr/bin/python

'This example shows how to work with authentication'

from mininet.log import setLogLevel, info
from mn_wifi.cli import CLI
from mn_wifi.net import Mininet_wifi


def topology():
    "Create a network."
    net = Mininet_wifi()

    info("*** Creating nodes\n")
    sta1 = net.addStation('sta1', passwd='123456789a', encrypt='wpa2')
    sta2 = net.addStation('sta2', passwd='123456789a', encrypt='wpa2')
    sta3 = net.addStation('sta3', passwd='123456789a', encrypt='wpa2')
    ap1 = net.addAccessPoint('ap1', ssid="simplewifi", mode="g", channel="1",
                             passwd='123456789a', encrypt='wpa2',
                             failMode="standalone", datapath='user')

    info("*** Configuring wifi nodes\n")
    net.configureWifiNodes()

    info("*** Associating Stations\n")
    net.addLink(sta1, ap1)
    net.addLink(sta2, ap1)

    info("*** Starting network\n")
    net.build()
    ap1.start([])

    sta1.cmd("xterm -xrm 'XTerm.vt100.allowTitleOps: false' -title sta1&")
    sta2.cmd("xterm -xrm 'XTerm.vt100.allowTitleOps: false' -title sta2&")
    sta3.cmd("xterm -xrm 'XTerm.vt100.allowTitleOps: false' -title sta3&")
    ap1.cmd("xterm  -xrm 'XTerm.vt100.allowTitleOps: false' -title ap&") 
    info("*** Running CLI\n")
    CLI(net)

    info("*** Stopping network\n")
    sta1.cmd('killall xterm ')
    net.stop()


if __name__ == '__main__':
    setLogLevel('info')
    topology()
