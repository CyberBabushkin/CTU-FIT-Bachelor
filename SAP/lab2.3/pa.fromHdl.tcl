
# PlanAhead Launch Script for Pre-Synthesis Floorplanning, created by Project Navigator

create_project -name lab2.3 -dir "H:/SAP/lab2.3/planAhead_run_2" -part xc3s100ecp132-4
set_param project.pinAheadLayout yes
set srcset [get_property srcset [current_run -impl]]
set_property target_constrs_file "pripr.ucf" [current_fileset -constrset]
set hdlfile [add_files [list {pripr.vhf}]]
set_property file_type VHDL $hdlfile
set_property library work $hdlfile
set_property top pripr $srcset
add_files [list {pripr.ucf}] -fileset [get_property constrset [current_run]]
open_rtl_design -part xc3s100ecp132-4
