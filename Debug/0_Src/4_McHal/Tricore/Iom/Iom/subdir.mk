################################################################################
# Automatically-generated file. Do not edit!
################################################################################

C_FILES += "..\0_Src\4_McHal\Tricore\Iom\Iom\IfxIom_Iom.c"
OBJ_FILES += "0_Src\4_McHal\Tricore\Iom\Iom\IfxIom_Iom.o"
"0_Src\4_McHal\Tricore\Iom\Iom\IfxIom_Iom.o" : "..\0_Src\4_McHal\Tricore\Iom\Iom\IfxIom_Iom.c" "0_Src\4_McHal\Tricore\Iom\Iom\.IfxIom_Iom.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "0_Src\4_McHal\Tricore\Iom\Iom\.IfxIom_Iom.o.opt"

"0_Src\4_McHal\Tricore\Iom\Iom\.IfxIom_Iom.o.opt" : .refresh
	@argfile "0_Src\4_McHal\Tricore\Iom\Iom\.IfxIom_Iom.o.opt" -o "0_Src\4_McHal\Tricore\Iom\Iom\IfxIom_Iom.o" "..\0_Src\4_McHal\Tricore\Iom\Iom\IfxIom_Iom.c" -Ctc27xc --lsl-core=vtc -t -I"D:\WorkSpace\Tasking\Tasking_TC27xD_ASC" -Wa-H"sfr/regtc27xc.def" -Wa-gAHLs --emit-locals=-equs,-symbols -Wa-Ogs -Wa--error-limit=42 -I"D:\WorkSpace\Tasking\Tasking_TC27xD_ASC\0_Src\0_AppSw\Config\Common" -I"D:\WorkSpace\Tasking\Tasking_TC27xD_ASC\0_Src\2_CDrv\Tricore" -I"D:\WorkSpace\Tasking\Tasking_TC27xD_ASC\0_Src\0_AppSw" -I"D:\WorkSpace\Tasking\Tasking_TC27xD_ASC\0_Src\0_AppSw\Tricore" -I"D:\WorkSpace\Tasking\Tasking_TC27xD_ASC\0_Src\1_SrvSw" -I"D:\WorkSpace\Tasking\Tasking_TC27xD_ASC\0_Src\0_AppSw\Tricore\Main" -I"D:\WorkSpace\Tasking\Tasking_TC27xD_ASC\0_Src\1_SrvSw\If" -I"D:\WorkSpace\Tasking\Tasking_TC27xD_ASC\0_Src\1_SrvSw\StdIf" -I"D:\WorkSpace\Tasking\Tasking_TC27xD_ASC\0_Src\1_SrvSw\SysSe" -I"D:\WorkSpace\Tasking\Tasking_TC27xD_ASC\0_Src\1_SrvSw\Tricore" -I"D:\WorkSpace\Tasking\Tasking_TC27xD_ASC\0_Src\1_SrvSw\Tricore\Compilers" -I"D:\WorkSpace\Tasking\Tasking_TC27xD_ASC\0_Src\4_McHal\Tricore" -I"D:\WorkSpace\Tasking\Tasking_TC27xD_ASC\0_Src\4_McHal\Tricore\_Impl" -I"D:\WorkSpace\Tasking\Tasking_TC27xD_ASC\0_Src\4_McHal\Tricore\_Lib" -I"D:\WorkSpace\Tasking\Tasking_TC27xD_ASC\0_Src\4_McHal\Tricore\_PinMap" -I"D:\WorkSpace\Tasking\Tasking_TC27xD_ASC\0_Src\4_McHal\Tricore\_Reg" --iso=99 --language=-gcc,-volatile,+strings,-kanji --fp-model=clfznrST --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O2 --tradeoff=4 --compact-max-size=200 -g --error-limit=42 --source -c --dep-file="0_Src\4_McHal\Tricore\Iom\Iom\.IfxIom_Iom.o.d" -Wc--make-target="0_Src\4_McHal\Tricore\Iom\Iom\IfxIom_Iom.o"
DEPENDENCY_FILES += "0_Src\4_McHal\Tricore\Iom\Iom\.IfxIom_Iom.o.d"


GENERATED_FILES += "0_Src\4_McHal\Tricore\Iom\Iom\IfxIom_Iom.o" "0_Src\4_McHal\Tricore\Iom\Iom\.IfxIom_Iom.o.opt" "0_Src\4_McHal\Tricore\Iom\Iom\.IfxIom_Iom.o.d" "0_Src\4_McHal\Tricore\Iom\Iom\IfxIom_Iom.src" "0_Src\4_McHal\Tricore\Iom\Iom\IfxIom_Iom.lst"
