cmd_/shared_folder/c/kernel/test_mod01.ko := ld -r  -m elf_x86_64  --build-id=sha1  -T scripts/module.lds -o /shared_folder/c/kernel/test_mod01.ko /shared_folder/c/kernel/test_mod01.o /shared_folder/c/kernel/test_mod01.mod.o;  true