cmd_/shared_folder/c/kernel/modules.order := {   echo /shared_folder/c/kernel/g_mod.ko; :; } | awk '!x[$$0]++' - > /shared_folder/c/kernel/modules.order
