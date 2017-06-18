
# PlanAhead Launch Script for Pre-Synthesis Floorplanning, created by Project Navigator

create_project -name dvecisla -dir "H:/SAP/dvecisla/planAhead_run_2" -part xc3s100ecp132-4
set_param project.pinAheadLayout yes
set srcset [get_property srcset [current_run -impl]]
set_property target_constrs_file "schema.ucf" [current_fileset -constrset]
set hdlfile [add_files [list {Mymux.vhf}]]
set_property file_type VHDL $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {a.vhd}]]
set_property file_type VHDL $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {dvecisla.vhf}]]
set_property file_type VHDL $hdlfile
set_property library work $hdlfile
set_property top dvecisla $srcset
add_files [list {schema.ucf}] -fileset [get_property constrset [current_run]]
open_rtl_design -part xc3s100ecp132-4
