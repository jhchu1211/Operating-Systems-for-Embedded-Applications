cmd_/shared_folder/c/kernel/Module.symvers := sed 's/\.ko$$/\.o/' /shared_folder/c/kernel/modules.order | scripts/mod/modpost -m -a  -o /shared_folder/c/kernel/Module.symvers -e -i Module.symvers   -T -