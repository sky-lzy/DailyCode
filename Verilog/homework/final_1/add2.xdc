create_clock -period 10.000 -name CLK -waveform {0.000 5.000} [get_ports sysclk]
set_max_delay 10.0 -from [get_ports I[0]] -to [get_ports Y[0]]
set_min_delay 2.0 -from [get_ports I[0]] -to [get_ports Y[0]]