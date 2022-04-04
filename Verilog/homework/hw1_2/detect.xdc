set_property -dict {PACKAGE_PIN R15 IOSTANDARD LVCMOS33} [get_ports {clk}]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets {clk}]

set_property -dict {PACKAGE_PIN P17 IOSTANDARD LVCMOS33} [get_ports {sys_clk}]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets {sys_clk}]

set_property -dict {PACKAGE_PIN U4 IOSTANDARD LVCMOS33} [get_ports {res}]

set_property -dict {PACKAGE_PIN N4 IOSTANDARD LVCMOS33} [get_ports {in}]

set_property -dict {PACKAGE_PIN K2 IOSTANDARD LVCMOS33} [get_ports {out}]

set_property -dict {PACKAGE_PIN J2 IOSTANDARD LVCMOS33} [get_ports {dict[0]}]
set_property -dict {PACKAGE_PIN J3 IOSTANDARD LVCMOS33} [get_ports {dict[1]}]
set_property -dict {PACKAGE_PIN H4 IOSTANDARD LVCMOS33} [get_ports {dict[2]}]
set_property -dict {PACKAGE_PIN J4 IOSTANDARD LVCMOS33} [get_ports {dict[3]}]
set_property -dict {PACKAGE_PIN G3 IOSTANDARD LVCMOS33} [get_ports {dict[4]}]
set_property -dict {PACKAGE_PIN G4 IOSTANDARD LVCMOS33} [get_ports {dict[5]}]
