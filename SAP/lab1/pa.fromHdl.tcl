
# PlanAhead Launch Script for Pre-Synthesis Floorplanning, created by Project Navigator

create_project -name lab1 -dir "H:/SAP/lab1/planAhead_run_3" -part xc3s100ecp132-4
set_param project.pinAheadLayout yes
set srcset [get_property srcset [current_run -impl]]
set_property target_constrs_file "fourbits.ucf" [current_fileset -constrset]
set hdlfile [add_files [list {gates.vhf}]]
set_property file_type VHDL $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {fourbits.vhf}]]
set_property file_type VHDL $hdlfile
set_property library work $hdlfile
set_property top fourbits $srcset
add_files [list {fourbits.ucf}] -fileset [get_property constrset [current_run]]
open_rtl_design -part xc3s100ecp132-4
